file(GLOB SOURCES *.cpp)

add_executable(test ${SOURCES})

target_link_libraries(test libcppunit.a)
target_link_libraries(test ${PROJECT_SOURCE_DIR}/../vbin/VISTAS\ Core/libCORE.a)

