cmake_minimum_required(VERSION 3.16)

project("Enmaniac Game Engine 2 Toolings")

# Common setting
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(EGE2Editor)
add_subdirectory(EGE2EditorPlugins)
