cmake_minimum_required(VERSION 3.1)

project(pvuni_converter VERSION 0.0.2)

set(JSON_BuildTests OFF CACHE INTERNAL "")

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(main src/main.cpp)

target_include_directories(main PUBLIC src/include)

add_subdirectory(vendor/json)
target_link_libraries(main nlohmann_json::nlohmann_json)
target_link_libraries(main ${VTK_LIBRARIES})