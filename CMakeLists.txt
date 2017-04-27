cmake_minimum_required(VERSION 3.5)
project(GameEngine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")

#
# CONFIGURATION
#

# Basic CMake settings
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/_install)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Add custom target for installation in CLion

# add_custom_target(run_install COMMAND ${CMAKE_MAKE_PROGRAM} install)

# Use generate_shader function to convert .glsl sources to C++ headers
# include(shaders)

#
# DEPENDENCIES
#

#>>>>>>GTK
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})
#<<<<<<<<GTK

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

MACRO(CREATE_LIBRARY NAME)
    ADD_LIBRARY(${NAME} SHARED ${ARGN})
    SET_TARGET_PROPERTIES(${NAME} PROPERTIES
            CLEAN_DIRECT_OUTPUT 1
            )

    ADD_LIBRARY(${NAME}_static STATIC ${ARGN})
    SET_TARGET_PROPERTIES(${NAME}_static PROPERTIES
            OUTPUT_NAME ${NAME}
            CLEAN_DIRECT_OUTPUT 1
            )

    INSTALL(TARGETS ${NAME} ${NAME}_static
            ARCHIVE DESTINATION lib
            LIBRARY DESTINATION lib
            )
ENDMACRO(CREATE_LIBRARY)


# Find required packages
find_package(GLFW3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(OpenGL REQUIRED)

# Set default installation destination
if (NOT CMAKE_INSTALL_PREFIX)
    set(CMAKE_INSTALL_PREFIX "../_install")
endif ()

set(MY_LIBRARIES_SRC
        src/static_libs/lodepng.cpp
        src/static_libs/stb_image.c
        )


#>>zaciatok projektu
#####TUTO TREBA PRIDAŤ AK BUDE CHÝBAŤ UNDEFINED REFERENCE
set(GL_MAIN_SRC
        src/main.cpp
        src/utils/Input.cpp
        src/rendering/Renderer.cpp
        src/components/entities/EntityMaster.cpp
        src/components/Master.cpp
        src/components/particles/ParticleManager.cpp
        src/components/particles/ParticleMaster.cpp
        src/components/particles/ParticleSystemSimple.cpp
        src/components/shadows/ShadowMaster.cpp
        src/components/water/WaterMaster.cpp
        src/GUI/GtkIntroGui.cpp
        src/rendering/material/TextureManager.cpp
        src/rendering/model/Mesh.cpp
        src/rendering/shader/BasicShader.cpp
        src/utils/FileLoader.cpp
        src/utils/MousePicker.cpp
        src/rendering/WindowManager.cpp
        src/utils/Vectors.cpp
        src/components/voxel/World.cpp
        src/components/voxel/Chunk.cpp
        src/components/voxel/Block.cpp
        src/components/voxel/VoxelMaster.cpp)

add_executable(MainEngine ${GL_MAIN_SRC})

#file(GLOB_RECURSE HDRS ${CMAKE_SOURCE_DIR}/src/*.h)
#file(GLOB_RECURSE SRCS ${CMAKE_SOURCE_DIR}/src/*.c ${CMAKE_SOURCE_DIR}/src/*.cpp)
#add_executable(MainEngine ${HDRS} ${SRCS})


add_library(MyLibrary STATIC ${MY_LIBRARIES_SRC})
target_link_libraries(MainEngine MyLibrary)

# Make sure GLM uses radians and static GLEW library
target_compile_definitions(MainEngine PUBLIC -DGLM_FORCE_RADIANS -DGLEW_STATIC )

target_include_directories(MainEngine PUBLIC
#        src/lib
#        res
        ${GLFW_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
        ${GLM_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}
#        ${CMAKE_CURRENT_BINARY_DIR}
        ${GTK3_INCLUDE_DIRS})
target_link_libraries(MainEngine ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES} ${GTK3_LIBRARIES})
install(TARGETS MainEngine DESTINATION .)
#<<koniec projektu
