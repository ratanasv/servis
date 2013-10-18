file(GLOB SOURCES *.cpp)

add_executable(test ${SOURCES})

target_link_libraries(test libcppunit.a)
target_link_libraries(test ${VISTAS_SOURCE_DIR}/build/VISTAS\ Core/libCORE.a)
target_link_libraries(test ${VISTAS_SOURCE_DIR}/build/VISTAS\ Plugins/SHP3D/libSHP3D.a)
target_link_libraries(test ${VISTAS_SOURCE_DIR}/build/VISTAS\ Plugins/ENVISION/libENVISION.a)

