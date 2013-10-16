file(GLOB SOURCES *.cpp)

add_executable(test ${SOURCES})

include_directories(${PROJECT_SOURCE_DIR}/dependencies_h)
include_directories(${PROJECT_SOURCE_DIR}/dependencies_h/gen-cpp)
if (MSVC)
    include_directories(${PROJECT_SOURCE_DIR}/../cppunit-1.12.1/include)
    include_directories(${PROJECT_SOURCE_DIR}/../thrift-0.9.0)
endif (MSVC)


target_link_libraries(test libcppunit.a)

