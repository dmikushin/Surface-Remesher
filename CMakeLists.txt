cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

project(surfremesh LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CUDA_STANDARD 17)

find_package(Boost REQUIRED)
find_package(CGAL REQUIRED)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(CUDA REQUIRED)

include_directories(include ${CUDA_INCLUDE_DIRS})

file(GLOB_RECURSE SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cu)

add_executable(${PROJECT_NAME} ${SRCS})

target_link_libraries(${PROJECT_NAME} Boost::boost Eigen3::Eigen CGAL::CGAL)
