cmake_minimum_required(VERSION 3.16)

project(OptFlow)

include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(HDF5 REQUIRED COMPONENTS CXX)

if(HDF5_FOUND)
  include_directories(${HDF5_INCLUDE_DIRS})
  link_libraries(${HDF5_LIBRARIES})
endif()

add_executable(optflow main.cpp src/read_h5_events.cpp src/stream_events.cpp)

target_link_libraries(optflow ${HDF5_LIBRARIES})
