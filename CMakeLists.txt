cmake_minimum_required(VERSION 2.6)
project(servis)

include_directories(${PROJECT_SOURCE_DIR}/dependencies_h)
include_directories(${PROJECT_SOURCE_DIR}/dependencies_h/gen-cpp)
include_directories(/usr/local/include /usr/include)
link_directories(/usr/local/lib /usr/lib)


add_definitions(-DVISTAS_SERVER)
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    add_definitions(-DMACOSX)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")


set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_C_COMPILER "clang")
if (APPLE)
    set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libstdc++")
elseif (MSVC)
else (MSVC)
    set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libstdc++ -DHAVE_NETINET_IN_H -DHAVE_INTTYPES_H")
endif (APPLE)

file(GLOB SOURCES *.cpp *.h)
add_executable(servis ${SOURCES})
add_library(servisLibForTesting ${SOURCES})

find_package(Threads REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)

target_link_libraries(servis ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(servis thrift)
target_link_libraries(servis CORE)
target_link_libraries(servis SHP3D)
target_link_libraries(servis ENVISION)
target_link_libraries(servis TANDC)
target_link_libraries(servis ESRIGRID)
target_link_libraries(servis ${Boost_LIBRARIES})

add_subdirectory(test)




