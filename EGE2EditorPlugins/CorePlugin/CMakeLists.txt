cmake_minimum_required(VERSION 3.16)

project(CorePlugin VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_library(${PROJECT_NAME} SHARED
    # Private
    Implementation/CorePlugin.cpp
    Implementation/CorePlugin.hpp
    Implementation/Project/Project.cpp
    Implementation/Project/ProjectFactory.cpp

    # Public interface
    Interface/CorePlugin_global.h
    Interface/Project/Project.hpp
    Interface/Project/ProjectFactory.hpp

    # Resources
#    Resources/resources.qrc
 #   Implementation/QmlStatusBar.hpp
  #  Implementation/QmlStatusBar.cpp
)

target_include_directories (${PROJECT_NAME}
    PUBLIC
    Interface

    PRIVATE
    Implementation
    ${EDITORAPP_INCLUDE_DIR}
)

target_compile_definitions (${PROJECT_NAME}
    PRIVATE
    COREPLUGIN_EXPORT
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE Qt6::Quick
)

# Copy into application
add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND
    ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}.xml ${EDITORAPP_OUTPUT_DIR}
    COMMENT
    "Copying artifacts for ${PROJECT_NAME}"
)

# TAGE - find a way to determine name of the target and use it instead of ${PROJECT_NAME}.dll
add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND
    ${CMAKE_COMMAND} -E copy ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.dll ${EDITORAPP_OUTPUT_DIR}
    COMMENT
    "Copying artifacts for ${PROJECT_NAME}"
)
