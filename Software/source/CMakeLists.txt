project(GPSParser)

include_directories(../lib)

add_executable(GPSParser main.cpp MYNMEAParser.cpp MYNMEAParser.h)

target_link_libraries(GPSParser parserlib)