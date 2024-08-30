cmake_minimum_required(VERSION 3.16)

project(OptFlow)

include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(SDL2 REQUIRED)
if(SDL2_FOUND)
  include_directories(${SDL2_INCLUDE_DIRS})
  link_libraries(${SDL2_LIBRARIES})
endif()

find_package(HDF5 REQUIRED COMPONENTS CXX)
if(HDF5_FOUND)
  include_directories(${HDF5_INCLUDE_DIRS})
  link_libraries(${HDF5_LIBRARIES})
endif()

add_executable(optflow main.cpp src/read_h5_events.cpp src/stream_events.cpp src/gui.cpp)

target_link_libraries(optflow ${HDF5_LIBRARIES})
target_link_libraries(optflow ${SDL2_LIBRARIES})
