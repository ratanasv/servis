#include <cppunit/config/SourcePrefix.h>
#include "SHP3DStartupTest.h"
#include <vistas/vistas.h>
#include <boost/tr1/memory.hpp>
#include <SHP3D.h>
#include <Envision.h>
#include <vector>

using std::tr1::shared_ptr;
using std::vector;

CPPUNIT_TEST_SUITE_REGISTRATION( SHP3DStartupTest );
#ifdef MACOSX
const VI_String DATA_PREFIX = VI_String("/Users/ratanasv/Documents/data/");
#else
const VI_String DATA_PREFIX = VI_String("/home/ubuntu/data/");
#endif


void SHP3DStartupTest::testAll()
{
    shared_ptr<SHP3D> shp3dPlugin(new SHP3D());
    shared_ptr<EnvisionDataPlugin> envisionPlugin(new EnvisionDataPlugin());
    const VI_Path pathToShp = VI_Path(DATA_PREFIX + VI_String("eastern_oregon/idu3D.shp"));
    CPPUNIT_ASSERT(pathToShp.Exists());
    envisionPlugin->Set(pathToShp);
    CPPUNIT_ASSERT_EQUAL(8616, envisionPlugin->GetNumShapes());
    shp3dPlugin->SetData(envisionPlugin.get(), 0);
    shp3dPlugin->SetAttribute(VI_String("LULC_A"));
	auto shapeMesh = shp3dPlugin->GetMesh();
	CPPUNIT_ASSERT_EQUAL((unsigned)64755, shapeMesh.GetVertexCount());
	CPPUNIT_ASSERT_EQUAL((unsigned)142563, shapeMesh.GetIndexCount());
}


