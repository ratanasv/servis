#include <cppunit/config/SourcePrefix.h>
#include "SHP3DStartupTest.h"
#include <vistas/vistas.h>
#include <boost/tr1/memory.hpp>
#include <SHP3D.h>
#include <Envision.h>

using std::tr1::shared_ptr;

CPPUNIT_TEST_SUITE_REGISTRATION( SHP3DStartupTest );
const VI_String DATA_PREFIX = VI_String("/Users/ratanasv/Documents/data/");

void SHP3DStartupTest::testAll()
{
    shared_ptr<SHP3D> shp3dPlugin(new SHP3D());
    shared_ptr<EnvisionDataPlugin> envisionPlugin(new EnvisionDataPlugin());
    const VI_Path pathToShp = VI_Path(DATA_PREFIX + VI_String("eastern_oregon/idu3D.shp"));
    CPPUNIT_ASSERT(pathToShp.Exists());
    envisionPlugin->Set(pathToShp);
    CPPUNIT_ASSERT_EQUAL(8616, envisionPlugin->GetNumShapes());
    shp3dPlugin->SetData(envisionPlugin.get(), 0);
    auto attributeList = envisionPlugin->GetAttributes();
    for (auto it : attributeList) {
        fprintf(stderr, "%s\n", it.c_str());
    }
}


