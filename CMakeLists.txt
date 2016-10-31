cmake_minimum_required(VERSION 3.5)
project(GraphicsProject)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#>>moje


#
# CONFIGURATION
#

# Basic CMake settings
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/_install)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Add custom target for installation in CLion

add_custom_target(run_install COMMAND ${CMAKE_MAKE_PROGRAM} install)

# Use generate_shader function to convert .glsl sources to C++ headers
include(shaders)

#
# DEPENDENCIES
#

# Set up external dependencies for Windows users
if (MINGW)
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${CMAKE_SOURCE_DIR}/dependencies/include/")
    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${CMAKE_SOURCE_DIR}/dependencies/lib/mingw")
elseif (MSVC)
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${CMAKE_SOURCE_DIR}/dependencies/include/")
    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${CMAKE_SOURCE_DIR}/dependencies/lib/vc2015")
    set(STRICT_COMPILE_FLAGS)
endif ()

# Warnings for Debug mode
option(USE_STRICT_COMPILE_WARNINGS "Use strict compilation warnings in debug mode." ON)
# These compile flags should apply for GCC and Clang compilers
set(STRICT_COMPILE_FLAGS "-Wpedantic -Wall -Wno-c++98-compat -Wfloat-equal -Wextra -Wsign-promo -Wsign-compare -Wconversion -Wno-sign-conversion -Wno-unused-parameter")
if (USE_STRICT_COMPILE_WARNINGS)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${STRICT_COMPILE_FLAGS}")
endif ()

# Find required packages
find_package(GLFW3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(OpenGL REQUIRED)

# Set default installation destination
if (NOT CMAKE_INSTALL_PREFIX)
    set(CMAKE_INSTALL_PREFIX "../_install")
endif ()

# PPGSO library
add_library(libGraphics STATIC
        src/lib/mesh.cpp
        src/lib/tiny_obj_loader.cpp
        src/lib/shader.cpp
        src/lib/texture.cpp
        res/textures/stoneFloor.png)
# Make sure GLM uses radians and static GLEW library
target_compile_definitions(libGraphics PUBLIC -DGLM_FORCE_RADIANS -DGLEW_STATIC )
# Link to GLFW, GLEW and OpenGL
target_link_libraries(libGraphics PUBLIC ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})
# Pass on include directories
target_include_directories(libGraphics PUBLIC
        src/lib
        res
        ${GLFW_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
        ${GLM_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR})
#<<moje

#>>zaciatok projektu
#####TUTO TREBA PRIDAŤ AK BUDE CHÝBAŤ UNDEFINED REFERENCE
set(GL_MAIN_SRC src/main.cpp
                src/utils/FileLoader.cpp
                src/utils/Maths.cpp
                src/utils/utils.cpp
                src/utils/Vertex.cpp
                src/utils/Matrix4f.cpp
                src/utils/Quaternion.cpp
                src/rendering/Camera.cpp
                src/rendering/material/Material.cpp
                src/rendering/model/Mesh.cpp
                src/rendering/model/RawModel.cpp
                src/rendering/model/Entity.cpp
                src/rendering/model/Transform.cpp
                src/rendering/model/MaterialedModel.cpp
                src/postProccessing/Fbo.cpp
                src/postProccessing/ImageRenderer.cpp
                src/rendering/shader/BasicShader.cpp
                src/postProccessing/ToFrameBufferRendering.cpp src/components/FreeMove.cpp src/static_libs/stb_image.h src/static_libs/stb_image.c src/static_libs/lodepng.cpp src/static_libs/lodepng.h)
add_executable(gl_main ${GL_MAIN_SRC})
target_link_libraries(gl_main libGraphics)
install(TARGETS gl_main DESTINATION .)
#<<koniec projektu

set(SOURCE_FILES    src/main.cpp
                    src/utils/Vectors.cpp
                    src/rendering/shader/BasicShader.cpp
                    src/utils/Logger.cpp
                    src/utils/FileLoader.cpp
                    src/rendering/shader/GuiShader.cpp
                    src/utils/Loader.cpp
                    src/rendering/model/RawModel.cpp
                    src/postProccessing/Screen.cpp
                    src/rendering/Renderer.cpp
                    src/rendering/model/MaterialedModel.cpp
                    src/rendering/model/Entity.cpp
                    src/utils/Maths.cpp
                    src/rendering/model/Transform.cpp
                    src/rendering/Camera.cpp
                    src/utils/Input.cpp
                    src/rendering/model/Mesh.cpp
                    src/rendering/shader/EntityShader.cpp
                    src/utils/Math.cpp src/rendering/shader/ObjectShader.cpp src/utils/Matrix4f.cpp src/utils/Matrix4f.h src/utils/Quaternion.cpp src/utils/Quaternion.h)

add_executable(GraphicsProject ${SOURCE_FILES})