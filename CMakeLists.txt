cmake_minimum_required(VERSION 3.10)

project(VehicleSimulation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

add_executable(VehicleSim main.cpp Vehicle.cpp Vehicle.h)

find_package(Threads REQUIRED)
target_link_libraries(VehicleSim PRIVATE Threads::Threads)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(VehicleSim PRIVATE -Wall -Wextra -Wpedantic)
elseif(MSVC)
    target_compile_options(VehicleSim PRIVATE /W4)
endif()

install(TARGETS VehicleSim DESTINATION bin)

message(STATUS "Configuring VehicleSimulation project")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Pthreads library found: ${Threads_FOUND}")