cmake_minimum_required(VERSION 3.16)

project(WorkspacePlugin VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_library(${PROJECT_NAME} SHARED
    # Private
    Implementation/WorkspacePlugin.cpp
    Implementation/WorkspacePlugin.hpp

    # Public interface
    Interface/WorkspacePlugin_global.h

    # Resources
    Resources/resources.qrc
    Implementation/QmlStatusBar.hpp
    Implementation/QmlStatusBar.cpp
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
    WORKSPACEPLUGIN_EXPORT
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE Qt6::Quick
)

# Copy into application
# TAGE - find a way to determine name of the target and use it instead of ${PROJECT_NAME}.dll
add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND
    ${CMAKE_COMMAND} -E copy ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.dll ${EDITORAPP_OUTPUT_DIR}
    COMMENT
    "Copying artifacts for ${PROJECT_NAME}"
)
