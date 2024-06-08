cmake_minimum_required(VERSION 3.10)
project(VideoToAscii)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(vta main.cpp)
target_link_libraries(vta ${OpenCV_LIBS})

install(TARGETS vta DESTINATION /usr/local/bin)
