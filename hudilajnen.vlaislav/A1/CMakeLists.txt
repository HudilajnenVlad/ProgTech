cmake_minimum_required(VERSION 3.15)
project(spbspu-labs-2020-904-3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wold-style-cast")

add_executable(spbspu-labs-2020-904-3 main.cpp base-types.hpp shape.hpp circle.hpp circle.cpp rectangle.cpp rectangle.hpp )

find_package(Boost 1.72.0 REQUIRED)
include_directories (SYSTEM ${Boost_INCLUDE_DIRS})

target_link_libraries (spbspu-labs-2020-904-3_A1 ${Boost_LIBRARIES})

add_executable(boost_test rectangle.cpp circle.cpp)