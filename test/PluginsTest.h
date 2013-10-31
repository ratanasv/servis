#pragma once
#include <cppunit/extensions/HelperMacros.h>

/*
* A test case that is designed to produce
* example errors and failures
*
*/

class PluginsTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( PluginsTest );
	CPPUNIT_TEST( testSHP3D );
	CPPUNIT_TEST( testESRIGrid );
	CPPUNIT_TEST_SUITE_END();

protected:
	void testSHP3D();
	void testESRIGrid();
};
