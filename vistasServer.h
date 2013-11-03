#pragma once

#include <stdexcept>
#include <cstring>
#include <vistas/vistas.h>

#include <boost/tr1/memory.hpp>


using std::tr1::shared_ptr;
using std::vector;
using std::find_if;
using std::string;
using std::runtime_error;
using std::pair;

typedef struct NewVELMAPlugins {
	NewVELMAPlugins(shared_ptr<VI_DataPlugin> a, shared_ptr<VI_DataPlugin> b, shared_ptr<VI_VizPlugin3D> c) {
		attributePlugin = a;
		demPlugin = b;
		terrainPlugin = c;
	}

	shared_ptr<VI_DataPlugin> attributePlugin;
	shared_ptr<VI_DataPlugin> demPlugin;
	shared_ptr<VI_VizPlugin3D> terrainPlugin;
} NewVELMAPlugins;

class not_found_error: public runtime_error {
public:
	explicit not_found_error(const string& what) : runtime_error(what) {};
};

const VI_String getDataRoot();
VI_PathList getAllFilesInFolder( const string& folderName);
bool doesContainSHPFile(const string& folderName);
const VI_Path getPathToSHPFile(const string& folderName);
const VI_Path getPathToDEMFile(const string& folderName);
const VI_Path getPathToESRIGridFile(const string& folderName);
shared_ptr<VI_DataPlugin> initDataPlugin(const string& folderName);
pair<shared_ptr<VI_DataPlugin>, shared_ptr<VI_VizPlugin3D>> initENVISIONPlugins(const string& folderName);
NewVELMAPlugins initVELMAPlugins(const string& folderName);
VI_Mesh getMesh(const string& folderName);
VI_Mesh getMesh( const string& folderName, const string& attribute );
