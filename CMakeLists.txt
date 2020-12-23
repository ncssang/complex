cmake_minimum_required(VERSION 3.4)

project(complex)

## Compile as C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## Compile with the highest warning level
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

## System dependencies
find_package(OpenCV REQUIRED)

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(geometry_transform src/geometry_transform.cpp src/complex.cpp)
# add_executable(test_youtube src/test_youtube.cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(geometry_transform ${OpenCV_LIBS})
