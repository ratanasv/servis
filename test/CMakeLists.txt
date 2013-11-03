file(GLOB SOURCES *.cpp *.h)
include_directories(${PROJECT_SOURCE_DIR})

add_executable(test ${SOURCES})

target_link_libraries(test cppunit)
target_link_libraries(test CORE)
target_link_libraries(test SHP3D)
target_link_libraries(test ENVISION)
target_link_libraries(test TANDC)
target_link_libraries(test ESRIGRID)
target_link_libraries(test servisLibForTesting)

