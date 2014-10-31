cmake_minimum_required(VERSION 2.6)

project(spidev-lib)
set(CMAKE_CXX_FLAGS "-g -Wall")
set(CMAKE_C_FLAGS "-g -Wall")

include_directories(src/)


add_library(spidev-lib src/spidev_lib.c)
add_executable(
     spi-testc sample/spidev-testc.c
)
target_link_libraries( spi-testc spidev-lib)

add_library(spidev-lib++ src/spidev_lib++.cc)
add_executable(spi-testcpp sample/spidev-testcpp.cc)
target_link_libraries( spi-testcpp spidev-lib++ )

add_dependencies(spi-testcpp spidev-lib++)
add_dependencies(spi-testc spidev-lib)

INSTALL(TARGETS  spidev-lib  spidev-lib++
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
INSTALL( FILES src/spidev_lib.h DESTINATION include)
INSTALL( FILES src/spidev_lib++.h DESTINATION include)

