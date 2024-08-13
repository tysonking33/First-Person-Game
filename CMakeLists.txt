cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(OpenGLTemplate CXX)

#===========================================================================================
# OPTIONAL LIBRARIES
#
# The following libraries can be pulled down and added to the project by turning the
# desired options on. Open an issue for additional default support.
# See: https://github.com/Hoshiningen/OpenGL-Template/issues

set(ENABLE_ASSIMP ON CACHE BOOL "Add Open Asset Import Library (assimp) to the project" FORCE)

#===========================================================================================
# GLAD CONFIGURATION
#
# Configure GLAD loader generation variables (lines below pulled from the GLAD top-level
# CMakeLists.txt file, with slight modifications.
# Refer to https://github.com/Dav1dde/glad for more information)

set(GLAD_OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}" CACHE STRING "Output directory" FORCE)
set(GLAD_PROFILE "core" CACHE STRING "OpenGL profile" FORCE)
set(GLAD_API "gl=3.3" CACHE STRING "API type/version pairs, like \"gl=3.2,gles=\", no version means latest" FORCE)
set(GLAD_GENERATOR "c" CACHE STRING "Language to generate the binding for" FORCE)
set(GLAD_EXTENSIONS "" CACHE STRING "Path to extensions file or comma separated list of extensions, if missing all extensions are included" FORCE)
set(GLAD_SPEC "gl" CACHE STRING "Name of the spec" FORCE)
set(GLAD_ALL_EXTENSIONS OFF CACHE BOOL "Include all extensions instead of those specified by GLAD_EXTENSIONS" FORCE)
set(GLAD_NO_LOADER OFF CACHE BOOL "No loader" FORCE)
set(GLAD_REPRODUCIBLE OFF CACHE BOOL "Reproducible build" FORCE)

#===========================================================================================

set_property(GLOBAL PROPERTY USE_FOLDERS ON)


# Set directory paths
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/includes)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../includes)

set(SOURCES 
    ${SOURCE_DIR}/Camera.cpp
    ${SOURCE_DIR}/Game.cpp
    ${SOURCE_DIR}/Math_Utils.cpp
    ${SOURCE_DIR}/Player.cpp
    ${SOURCE_DIR}/Renderer.cpp
    ${SOURCE_DIR}/Shader.cpp
    ${SOURCE_DIR}/Main.cpp
)

# Add all header files
set(headers
    ${INCLUDE_DIR}/Camera.h
    ${INCLUDE_DIR}/Game.h
    ${INCLUDE_DIR}/Math_Utils.h
    ${INCLUDE_DIR}/Player.h
    ${INCLUDE_DIR}/Renderer.h
    ${INCLUDE_DIR}/Shader.h
    ${INCLUDE_DIR}/stb_image.h

)

add_executable(opengl-template ${SOURCES})

# Perform dependency linkage
include(${CMAKE_DIR}/LinkGLFW.cmake)
LinkGLFW(opengl-template PRIVATE)

include(${CMAKE_DIR}/LinkGLAD.cmake)
LinkGLAD(opengl-template PRIVATE)

find_package(OpenGL REQUIRED)
if (OpenGL_FOUND)
    target_include_directories(opengl-template PRIVATE ${OPENGL_INCLUDE_DIRS})
    target_link_libraries(opengl-template PRIVATE ${OPENGL_LIBRARIES})
else()
    message(FATAL_ERROR "OpenGL was not found on the system")
endif()

set(ZLIB_ROOT "/usr/lib/x86_64-linux-gnu/libz.so.1.2.11")
include(${CMAKE_CURRENT_LIST_DIR}/cmake/LinkASSIMP.cmake)

# Handle the optional libraries
if (ENABLE_ASSIMP)
    include(${CMAKE_DIR}/LinkASSIMP.cmake)
    LinkASSIMP(opengl-template PRIVATE)
endif()

# Enable C++17
set_target_properties(opengl-template PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# Set project folders
set_target_properties(opengl-template PROPERTIES FOLDER ${PROJECT_NAME})

# Link GLM
include(${CMAKE_DIR}/LinkGLM.cmake)
LinkGLM(opengl-template PRIVATE)
