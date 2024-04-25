cmake_minimum_required(VERSION 3.27)
project(win32_no_titlebar)

set(CMAKE_CXX_STANDARD 17)

find_library(DWMAPI_LIB Dwmapi)
add_executable(main WIN32 main.cpp)
add_executable(demo WIN32 docs_demo.cpp)
target_link_libraries(main PRIVATE ${DWMAPI_LIB})