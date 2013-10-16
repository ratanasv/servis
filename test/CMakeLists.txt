file(GLOB SOURCES *.cpp)

message("wtf=" ${SOURCES})
add_executable(test ${SOURCES})

target_link_libraries(test libcppunit.a)

