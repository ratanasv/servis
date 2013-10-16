#include <cppunit/config/SourcePrefix.h>
#include "SimpleTestCase.h"

CPPUNIT_TEST_SUITE_REGISTRATION( SimpleTestCase );


void SimpleTestCase::testOne()
{
	double result = m_value1 + m_value2;
	CPPUNIT_ASSERT( result == 6.0 );
}

