cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -ffast-math -funsafe-math-optimizations")

project(OptFlow)

include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(SDL2 REQUIRED)
if(SDL2_FOUND)
  include_directories(OptFlow ${SDL2_INCLUDE_DIRS})
  #link_libraries(${SDL2})
endif()

find_package(HDF5 REQUIRED COMPONENTS CXX)
if(HDF5_FOUND)
  include_directories(${HDF5_INCLUDE_DIRS})
  link_libraries(${HDF5_LIBRARIES})
endif()

find_package(OpenMP)

add_executable(optflow main.cpp
  src/read_h5_events.cpp
  src/stream_events.cpp
  src/gui.cpp
  src/data_utils.cpp
  src/opt_flow.cpp
  src/viz.cpp)

target_link_libraries(optflow ${HDF5_LIBRARIES})
target_link_libraries(optflow ${SDL2_LIBRARIES})
target_link_libraries(optflow -lffi)
target_link_libraries(optflow OpenMP::OpenMP_CXX)

