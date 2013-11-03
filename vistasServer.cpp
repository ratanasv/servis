#include "vistasServer.h"
#include <SHP3D.h>
#include <Envision.h>
#include <ESRIGridASCII.h>
#include <TerrainAndColor.h>

#ifdef MACOSX
const VI_String DATA_PREFIX = VI_String("/Users/ratanasv/Documents/data/");
#else
const VI_String DATA_PREFIX = VI_String("/home/ubuntu/data/");
#endif

const VI_String SHP_EXTENSION = VI_String("shp");
const VI_String ESRIGRIDASCII_EXTENSION = VI_String("asc");

typedef pair<shared_ptr<VI_DataPlugin>, shared_ptr<VI_VizPlugin3D>> PluginPair;
const VI_String getDataRoot()
{
	return DATA_PREFIX;
}

VI_PathList getAllFilesInFolder(const std::string& folderName) {
	const VI_Path pathtoFolder = VI_Path(DATA_PREFIX + VI_String(folderName));
	if (pathtoFolder.Exists() == false) {
		throw not_found_error(string(pathtoFolder.Get().c_str()) + " doesn't exist");
	}
	return pathtoFolder.GetFiles();
}

bool doesContainSHPFile(const std::string& folderName) {
	auto datasetsList = getAllFilesInFolder(folderName);
	auto foundFile = find_if(datasetsList.begin(), datasetsList.end(), [](const VI_Path& elem) {
		return elem.GetExtension() == SHP_EXTENSION;
	});
	if (foundFile == datasetsList.end()) { // not found
		return false;
	} else {
		return true;
	}
}

const VI_Path getPathToSHPFile(const std::string& folderName) {
	auto datasetsList = getAllFilesInFolder(folderName);
	auto foundFile = find_if(datasetsList.begin(), datasetsList.end(), [](const VI_Path& elem) {
		return elem.GetExtension() == SHP_EXTENSION;
	});
	if (foundFile == datasetsList.end()) { // not found
		throw not_found_error(folderName + " does not contain a SHP file");
	} 
	return *foundFile;
}


const VI_Path getPathToDEMFile(const std::string& folderName) {
	auto datasetsList = getAllFilesInFolder(folderName);
	auto foundFile = find_if(datasetsList.begin(), datasetsList.end(), [](const VI_Path& elem) {
		bool isDEM = elem.GetElement(-1).Find(VI_String("DEM")) != -1;
		return elem.GetExtension() == ESRIGRIDASCII_EXTENSION && isDEM;
	});
	if (foundFile == datasetsList.end()) { // not found
		throw runtime_error("folder doesn't contain a DEM file");
	} 
	return *foundFile;
}

const VI_Path getPathToESRIGridFile(const std::string& folderName) {
	auto datasetsList = getAllFilesInFolder(folderName);
	auto foundFile = find_if(datasetsList.begin(), datasetsList.end(), [](const VI_Path& elem) {
		bool isDEM = elem.GetElement(-1).Find(VI_String("DEM")) != -1;
		return elem.GetExtension() == ESRIGRIDASCII_EXTENSION && !isDEM;
	});
	if (foundFile == datasetsList.end()) { // not found
		throw runtime_error("folder doesn't contain a ESRIGrid data file");
	} 
	return *foundFile;
}


shared_ptr<VI_DataPlugin> initDataPlugin(const string& folderName) {
	shared_ptr<VI_DataPlugin> dataPlugin;
	if (doesContainSHPFile(folderName))	{
		dataPlugin.reset(new EnvisionDataPlugin());
		dataPlugin->Set(getPathToSHPFile(folderName));
	} else {
		dataPlugin.reset(new ESRIGridPlugin());
		dataPlugin->Set(getPathToESRIGridFile(folderName));
	}
	
	return dataPlugin;
}

PluginPair initENVISIONPlugins(const std::string& folderName) {
	shared_ptr<VI_DataPlugin> dataPlugin;
	shared_ptr<VI_VizPlugin3D> vizPlugin;
	dataPlugin.reset(new EnvisionDataPlugin());
	vizPlugin.reset(new SHP3D());
	auto path = getPathToSHPFile(folderName);
	dataPlugin->Set(path);
	vizPlugin->SetData(dataPlugin.get(), 0);

	return PluginPair(dataPlugin, vizPlugin);
}

NewVELMAPlugins initVELMAPlugins(const string& folderName) {
	shared_ptr<VI_DataPlugin> dataPlugin(new ESRIGridPlugin());
	shared_ptr<VI_DataPlugin> demPlugin(new ESRIGridPlugin());
	shared_ptr<VI_VizPlugin3D> vizPlugin(new TerrainPlugin());
	dataPlugin->Set(getPathToESRIGridFile(folderName));
	demPlugin->Set(getPathToDEMFile(folderName));
	vizPlugin->SetData(demPlugin.get(), 0);
	vizPlugin->SetData(dataPlugin.get(), 1);
	vizPlugin->Refresh();
	return NewVELMAPlugins(dataPlugin, demPlugin, vizPlugin);
}

VI_Mesh getMesh(const string& folderName) {
	if (doesContainSHPFile(folderName)) {
		 auto plugins = initENVISIONPlugins(folderName);
		 return plugins.second->GetMesh();
	} else {
		auto plugins = initVELMAPlugins(folderName);
		return plugins.terrainPlugin->GetMesh();
	}
}

VI_Mesh getMesh(const string& folderName, const string& attribute) {
	if (doesContainSHPFile(folderName)) {
		auto plugins = initENVISIONPlugins(folderName);
		plugins.second->SetAttribute(attribute);
		return plugins.second->GetMesh();
	} else {
		auto plugins = initVELMAPlugins(folderName);
		plugins.terrainPlugin->SetAttribute(attribute);
		return plugins.terrainPlugin->GetMesh();
	}
	return VI_Mesh();
}
