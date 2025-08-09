cmake_minimum_required(VERSION 3.16)

set(CMAKE_PREFIX_PATH "C:/Qt/6.9.1/msvc2022_64/lib/cmake/Qt6")

project(InterpolatorProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

add_executable(${PROJECT_NAME}
    main.cpp
    interpolator.h
    mainwindow.h mainwindow.cpp
    firsttaskwidget.h firsttaskwidget.cpp
    secondtaskwidget.h secondtaskwidget.cpp
    shapes.h
    vertexhandle.h vertexhandle.cpp
    polygonitem.h polygonitem.cpp
    thirdtaskwidget.h thirdtaskwidget.cpp

)

target_link_libraries(${PROJECT_NAME} Qt6::Core Qt6::Widgets)
