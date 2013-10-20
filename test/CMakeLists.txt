file(GLOB SOURCES *.cpp *.h)

add_executable(test ${SOURCES})

target_link_libraries(test cppunit)
target_link_libraries(test CORE)
target_link_libraries(test SHP3D)
target_link_libraries(test ENVISION)

