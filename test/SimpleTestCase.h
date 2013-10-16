#pragma once
#include <cppunit/extensions/HelperMacros.h>

/* 
* A test case that is designed to produce
* example errors and failures
*
*/

class SimpleTestCase : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( SimpleTestCase );
	CPPUNIT_TEST( testOne );
	CPPUNIT_TEST_SUITE_END();

protected:
	double m_value1;
	double m_value2;

public:
	void setUp();

protected:
	void testOne();
};