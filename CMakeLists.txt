cmake_minimum_required(VERSION 3.26)
project(match_three)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "D:/Code/C++/qt6/qt6-static/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

include_directories(src)

add_executable(match_three main.cpp
        src/match_three/match_three.cpp
        src/match_three/match_three.ui
        src/gamefield/table.cpp
        src/gamefield/gamefield.cpp
        src/figure/figure_generator.hpp
        src/figure/figure.hpp
        src/figure/figure.cpp)

target_link_libraries(match_three
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

file(COPY
        src/gamefield/gamefield.h
        src/gamefield/table.h
        DESTINATION ${PROJECT_NAME}_autogen/include)
