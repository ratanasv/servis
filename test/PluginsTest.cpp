#include <cppunit/config/SourcePrefix.h>
#include "PluginsTest.h"
#include <vistas/vistas.h>
#include <boost/tr1/memory.hpp>
#include <SHP3D.h>
#include <Envision.h>
#include <ESRIGridASCII.h>
#include <TerrainAndColor.h>
#include <vector>

using std::tr1::shared_ptr;
using std::vector;

CPPUNIT_TEST_SUITE_REGISTRATION( PluginsTest );
#ifdef MACOSX
const VI_String DATA_PREFIX = VI_String("/Users/ratanasv/Documents/data/");
#else
const VI_String DATA_PREFIX = VI_String("/home/ubuntu/data/");
#endif


void PluginsTest::testSHP3D()
{
    shared_ptr<SHP3D> shp3dPlugin(new SHP3D());
    shared_ptr<EnvisionDataPlugin> envisionPlugin(new EnvisionDataPlugin());
    const VI_Path pathToShp = VI_Path(DATA_PREFIX + VI_String("easternOregon/idu3D.shp"));
    CPPUNIT_ASSERT(pathToShp.Exists());
    envisionPlugin->Set(pathToShp);
    CPPUNIT_ASSERT_EQUAL(8616, envisionPlugin->GetNumShapes());
    shp3dPlugin->SetData(envisionPlugin.get(), 0);
    shp3dPlugin->SetAttribute(VI_String("LULC_A"));
	auto shapeMesh = shp3dPlugin->GetMesh();
	CPPUNIT_ASSERT_EQUAL((unsigned)64755, shapeMesh.GetVertexCount());
	CPPUNIT_ASSERT_EQUAL((unsigned)142563, shapeMesh.GetIndexCount());
}

void PluginsTest::testESRIGrid()
{
	shared_ptr<VI_DataPlugin> dataPlugin(new ESRIGridPlugin());
	const VI_Path pathToData(DATA_PREFIX + VI_String("chesapeakeBay/Spatial_VolumetricSoilMoistureLayer_1_3_2003_1.asc"));
	CPPUNIT_ASSERT(pathToData.Exists());
	dataPlugin->Set(pathToData);

	shared_ptr<VI_DataPlugin> demPlugin(new ESRIGridPlugin());
	const VI_Path pathToDEM(DATA_PREFIX + VI_String("chesapeakeBay/Chesapeake_10mDEM.asc"));
	CPPUNIT_ASSERT(pathToDEM.Exists());
	demPlugin->Set(pathToDEM);

	shared_ptr<VI_VizPlugin3D> vizPlugin(new TerrainPlugin());
	vizPlugin->SetData(demPlugin.get(), 0); //for DEM
	vizPlugin->SetData(dataPlugin.get(), 1);
	vizPlugin->Refresh();

	auto terrainMesh = vizPlugin->GetMesh();
	CPPUNIT_ASSERT(terrainMesh.GetVertexCount() != 0);
	CPPUNIT_ASSERT(terrainMesh.GetIndexCount() != 0);
}



