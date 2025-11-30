cmake_minimum_required(VERSION 3.10)
project(termux-api)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    TurHelper.cpp
    Turfs.cpp
)

add_library(Tkernel SHARED ${SOURCES})

target_include_directories(Tkernel PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

set_target_properties(Tkernel PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)


if(MSVC)
    target_compile_options(Tkernel PRIVATE /W4)
else()
    target_compile_options(Tkernel PRIVATE -Wall -Wextra -Wpedantic -fPIC)
endif()

install(TARGETS Tkernel
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)