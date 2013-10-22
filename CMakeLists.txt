cmake_minimum_required(VERSION 2.6)
project(servis)

set(VISTAS_SOURCE_DIR ${PROJECT_SOURCE_DIR}/../scidb-vistas)

include_directories(${PROJECT_SOURCE_DIR}/dependencies_h)
include_directories(${PROJECT_SOURCE_DIR}/dependencies_h/gen-cpp)
include_directories(/usr/local/include /usr/include)
link_directories(/usr/local/lib /usr/lib)


if (MSVC)
    include_directories(${PROJECT_SOURCE_DIR}/../cppunit-1.12.1/include)
    include_directories(${PROJECT_SOURCE_DIR}/../thrift-0.9.0/include)
endif (MSVC)


set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_C_COMPILER "clang")
if (APPLE)
    set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libstdc++")
elseif (MSVC)
else (MSVC)
    set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libstdc++ -DHAVE_NETINET_IN_H -DHAVE_INTTYPES_H")
endif (APPLE)

add_subdirectory(test)

file(GLOB SOURCES *.cpp *.h)
add_executable(servis ${SOURCES})

find_package(Threads REQUIRED)

target_link_libraries(servis ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(servis thrift)
target_link_libraries(servis CORE)
target_link_libraries(servis SHP3D)
target_link_libraries(servis ENVISION)





