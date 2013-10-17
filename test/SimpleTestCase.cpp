#include <cppunit/config/SourcePrefix.h>
#include "SimpleTestCase.h"
#include <vistas/vistas.h>
#include <boost/tr1/memory.hpp>

using std::tr1::shared_ptr;

CPPUNIT_TEST_SUITE_REGISTRATION( SimpleTestCase );


void SimpleTestCase::testOne()
{
	VI_Path p("../bin/asdf");
	CPPUNIT_ASSERT(false == p.IsAbsolute());
	CPPUNIT_ASSERT(false == p.Exists());
    CPPUNIT_ASSERT(1 == 1);
}

