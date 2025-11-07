cmake_minimum_required(VERSION 3.16)
project(PRT7Decoder CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

add_executable(prt7
    src/main.cpp
    src/SerialPortWin32.cpp
    src/Tramas.cpp
    src/RotorDeMapeo.cpp
    src/ListaDeCarga.cpp
)

if (MSVC)
  target_compile_options(prt7 PRIVATE /W4 /permissive-)
else()
  target_compile_options(prt7 PRIVATE -Wall -Wextra -Wpedantic)
endif()

install(TARGETS prt7 RUNTIME DESTINATION bin)
