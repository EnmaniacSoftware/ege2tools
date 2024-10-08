cmake_minimum_required(VERSION 3.16)

project(E2EEditorApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(${PROJECT_NAME}
    # Private
    Implementation/main.cpp
    Implementation/Application.cpp
    Implementation/Application.hpp
    Implementation/Plugins/PluginsManager.cpp

    # Public interface
    Interface/Plugins/Plugin.hpp
    Interface/Plugins/PluginsManager.hpp
)

target_include_directories (${PROJECT_NAME}
  PUBLIC
    Interface
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE Qt6::Quick
)

# Export variables for plugins
set(EDITORAPP_NAME ${PROJECT_NAME} CACHE INTERNAL "")
set(EDITORAPP_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR} CACHE INTERNAL "")
set(EDITORAPP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Interface CACHE INTERNAL "")

message("Exports:")
message("")
message("EDITORAPP_NAME:        ${EDITORAPP_NAME}")
message("EDITORAPP_OUTPUT_DIR:  ${EDITORAPP_OUTPUT_DIR}")
message("EDITORAPP_INCLUDE_DIR: ${EDITORAPP_INCLUDE_DIR}")
message("")

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
# set_target_properties(${PROJECT_NAME} PROPERTIES
# #    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appEGE2Tools
#     MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#     MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#     MACOSX_BUNDLE TRUE
#     WIN32_EXECUTABLE TRUE
# )


# message (${CMAKE_INSTALL_LIBDIR})
# include(GNUInstallDirs)
# install(TARGETS ${PROJECT_NAME}
#     BUNDLE DESTINATION .
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )
