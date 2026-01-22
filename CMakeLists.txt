cmake_minimum_required(VERSION 3.10)

project(test C)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)
pkg_check_modules(POPPLER REQUIRED poppler-glib)

add_executable(main
    main.c
    home.c
    allFiles.c
    reader.c
)

target_include_directories(main PRIVATE ${GTK4_INCLUDE_DIRS} ${POPPLER_INCLUDE_DIRS})
target_link_libraries(main PRIVATE ${GTK4_LIBRARIES} ${POPPLER_LIBRARIES})
target_compile_definitions(main PRIVATE ${GTK4_DEFINITIONS} ${POPPLER_DEFINITIONS})
