cmake_minimum_required(VERSION 3.10)

project(test C)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

add_executable(test test.c)
add_executable(test2 test2.c)

target_include_directories(test PRIVATE ${GTK4_INCLUDE_DIRS})

target_link_libraries(test PRIVATE ${GTK4_LIBRARIES})

target_compile_definitions(test PRIVATE ${GTK4_DEFINITIONS})
