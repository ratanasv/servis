#pragma once
#include <cppunit/extensions/HelperMacros.h>

/*
* A test case that is designed to produce
* example errors and failures
*
*/

class SHP3DStartupTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( SHP3DStartupTest );
	CPPUNIT_TEST( testAll );
	CPPUNIT_TEST_SUITE_END();

protected:
	void testAll();
};
