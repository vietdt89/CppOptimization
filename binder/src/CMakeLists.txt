cmake_minimum_required(VERSION 3.0)

project(binder-demo)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_library(ProtobufShared protobuf)

add_subdirectory(binder-control)
add_subdirectory(libs)
add_subdirectory(servicemanager)

add_subdirectory(services/config-service/interface)
add_subdirectory(services/config-service/bin)
add_subdirectory(services/app-service/interface)
add_subdirectory(services/app-service/bin)
add_subdirectory(test)
add_subdirectory(logging)

