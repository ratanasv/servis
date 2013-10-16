#include <cppunit/config/SourcePrefix.h>
#include "SimpleTestCase.h"

CPPUNIT_TEST_SUITE_REGISTRATION( SimpleTestCase );


void SimpleTestCase::testOne()
{
	CPPUNIT_ASSERT( 6.0 == 6.0 );
}

