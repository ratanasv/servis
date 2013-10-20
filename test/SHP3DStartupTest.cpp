#include <cppunit/config/SourcePrefix.h>
#include "SHP3DStartupTest.h"
#include <vistas/vistas.h>
#include <boost/tr1/memory.hpp>
#include <SHP3D.h>

using std::tr1::shared_ptr;

CPPUNIT_TEST_SUITE_REGISTRATION( SHP3DStartupTest );


void SHP3DStartupTest::testAll()
{
    shared_ptr<SHP3D> shp3dPlugin(new SHP3D());
}

