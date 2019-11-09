# Specify the minimum version for CMake

cmake_minimum_required(VERSION "3.0.0")

# Project's name

project(ephem VERSION "0.7.0")
# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ./bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

configure_file(${PROJECT_SOURCE_DIR}/config.hpp.in ${PROJECT_SOURCE_DIR}/config.hpp)


include_directories(${PROJECT_SOURCE_DIR}/../../lib/src)
add_executable(			ephem ephem.cpp CAAPrintValue.cpp CAAObserveTarget.cpp FK5_1.cpp FK6.cpp)

target_compile_options (ephem PRIVATE -std=c++0x -O3 -g0 -Wall -c -fmessage-length=0)
target_link_libraries(	ephem boost_date_time.a boost_program_options.a aaplus.a)

