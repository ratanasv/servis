cmake_minimum_required(VERSION 2.6)
project(servis)
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_C_COMPILER "clang")

add_subdirectory(test)

file(GLOB SOURCES *.cpp)
add_executable(servis ${SOURCES})

if (APPLE)
    set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")
elseif (MSVC)
else (MSVC)
    set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libstdc++ -DHAVE_NETINET_IN_H -DHAVE_INTTYPES_H")
endif (APPLE)


#find_package(Threads REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/dependencies_h)
include_directories(${PROJECT_SOURCE_DIR}/dependencies_h/gen-cpp)


target_link_libraries(servis ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(servis libthrift.a)





