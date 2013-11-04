#include <cppunit/config/SourcePrefix.h>
#include "PluginsTest.h"
#include <vistas/vistas.h>
#include <boost/tr1/memory.hpp>
#include <SHP3D.h>
#include <Envision.h>
#include <ESRIGridASCII.h>
#include <TerrainAndColor.h>
#include <vector>
#include "vistasServer.h"
#include <algorithm>

using std::tr1::shared_ptr;
using std::vector;
using std::find;
using std::tr1::dynamic_pointer_cast;

CPPUNIT_TEST_SUITE_REGISTRATION( PluginsTest );


void PluginsTest::testInitDataPlugin() {
	auto dataPlugin = initDataPlugin("easternOregon");
	auto envisionPlugin = dynamic_pointer_cast<EnvisionDataPlugin>(dataPlugin);
	CPPUNIT_ASSERT_EQUAL(8616, envisionPlugin->GetNumShapes());

	dataPlugin = initDataPlugin("chesapeakeBay");
	CPPUNIT_ASSERT_EQUAL(1, (int)dataPlugin->GetAttributes().size());


}

void PluginsTest::testGetAllFilesInFolder() {
	auto pathList = getAllFilesInFolder("");
	CPPUNIT_ASSERT(pathList.size() != 0);
}

void PluginsTest::testDoesContainSHPFile() {
	CPPUNIT_ASSERT_EQUAL(true, doesContainSHPFile("easternOregon"));
	CPPUNIT_ASSERT_EQUAL(false, doesContainSHPFile("chesapeakeBay"));
}

void PluginsTest::testGetPathToSHPFile() {
	auto expected = VI_Path(getDataRoot() + "/easternOregon/idu3D.shp");
	CPPUNIT_ASSERT_EQUAL(expected, getPathToSHPFile("easternOregon"));
}

void PluginsTest::testGetPathToDEMFile() {
	auto expected = VI_Path(getDataRoot() + "/chesapeakeBay/Chesapeake_10mDEM.asc");
	CPPUNIT_ASSERT_EQUAL(expected, getPathToDEMFile("chesapeakeBay"));
}

void PluginsTest::testGetPathToESRIGridFile() {
	auto expected = VI_Path(getDataRoot() + "/chesapeakeBay/Spatial_VolumetricSoilMoistureLayer_1_3_2003_1.asc");
	CPPUNIT_ASSERT_EQUAL(expected, getPathToESRIGridFile("chesapeakeBay"));
}

void PluginsTest::testInitENVISIONPlugins() {
	auto plugins = initENVISIONPlugins("easternOregon");
	CPPUNIT_ASSERT(NULL != plugins.first.get());
	CPPUNIT_ASSERT(NULL != plugins.second.get());
}

void PluginsTest::testInitVELMAPlugins() {
	auto plugins = initVELMAPlugins("chesapeakeBay");
	CPPUNIT_ASSERT(NULL != plugins.attributePlugin.get());
	CPPUNIT_ASSERT(NULL != plugins.demPlugin.get());
	CPPUNIT_ASSERT(NULL != plugins.terrainPlugin.get());
}


void PluginsTest::testGetMesh() {
	auto shapeMesh = getMesh("easternOregon");
	CPPUNIT_ASSERT_EQUAL((unsigned)64755, shapeMesh.GetVertexCount());
	CPPUNIT_ASSERT_EQUAL((unsigned)142563, shapeMesh.GetIndexCount());

	shapeMesh = getMesh("chesapeakeBay");
	CPPUNIT_ASSERT(0 != shapeMesh.GetVertexCount());
	CPPUNIT_ASSERT(0 != shapeMesh.GetIndexCount());
}

void PluginsTest::testGetMeshAttribute() {
	auto shapeMesh = getMesh("easternOregon", "LULC_A");
	CPPUNIT_ASSERT_EQUAL((unsigned)64755, shapeMesh.GetVertexCount());
	CPPUNIT_ASSERT_EQUAL((unsigned)142563, shapeMesh.GetIndexCount());
	CPPUNIT_ASSERT(NULL != shapeMesh.AcquireColorArray());
	shapeMesh.ReleaseColorArray();

	shapeMesh = getMesh("chesapeakeBay", "Spatial_VolumetricSoilMoistureLayer");
	CPPUNIT_ASSERT_EQUAL((unsigned)49815, shapeMesh.GetVertexCount());
	CPPUNIT_ASSERT_EQUAL((unsigned)99687, shapeMesh.GetIndexCount());
	CPPUNIT_ASSERT(NULL != shapeMesh.AcquireColorArray());
	shapeMesh.ReleaseColorArray();
}
