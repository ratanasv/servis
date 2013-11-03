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
	CPPUNIT_TEST( testInitDataPlugin );
	CPPUNIT_TEST( testGetAllFilesInFolder );
	CPPUNIT_TEST( testDoesContainSHPFile );
	CPPUNIT_TEST( testGetPathToDEMFile );
	CPPUNIT_TEST( testGetPathToESRIGridFile );
	CPPUNIT_TEST( testGetPathToESRIGridFile );
	CPPUNIT_TEST( testInitENVISIONPlugins );
	CPPUNIT_TEST( testInitVELMAPlugins );
	CPPUNIT_TEST( testGetMeshAttribute );
	CPPUNIT_TEST_SUITE_END();

protected:
	void testInitDataPlugin();

	void testGetAllFilesInFolder();
	void testDoesContainSHPFile();
	void testGetPathToSHPFile();
	void testGetPathToDEMFile();
	void testGetPathToESRIGridFile();

	void testInitENVISIONPlugins();
	void testInitVELMAPlugins();

	void testGetMesh();
	void testGetMeshAttribute();

};
