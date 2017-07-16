cmake_minimum_required(VERSION 3.5)
project(GameEngine)

#SET(CMAKE_CXX_FLAGS "-std=c++17")
#SET(CMAKE_CXX_FLAGS "-lBulletCollision -I /usr/local/include/bullet")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lfreetype")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread -lm -fPIC -lGL -lGLU")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lsfml-graphics -lsfml-window -lsfml-system")
SET(CMAKE_EXE_LINKER_FLAGS "-v")

#
# CONFIGURATION
#

# Basic CMake settings
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/_install)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Add custom target for installation in CLion

# DEPENDENCIES
#>>>>>>GTK
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})
#<<<<<<<<GTK

#>>>>>>FREETYPE
find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})
#link_directories(${FREETYPE_LIBRARY_DIRS})
#<<<<<<<<FREETYPE


#>>>>>>SFML
find_package(SFML REQUIRED system window graphics network audio)
#include_directories(${SFML_INCLUDE_DIRS})
link_directories(${SFML_LIBRARY_DIRS})
#<<<<<<<<SFML

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
        src/components/shadows/ShadowMaster.cpp
        src/components/water/WaterMaster.cpp
        src/GUI/GtkIntroGui.cpp
        src/rendering/material/TextureManager.cpp
        src/utils/resources/FileLoader.cpp
        src/utils/MousePicker.cpp
        src/rendering/WindowManager.cpp
        src/utils/math/objects/Vectors.cpp
        src/components/voxel_old/World_old.cpp
        src/components/voxel_old/Chunk_old.cpp
        src/components/voxel_old/Block.cpp
        src/components/voxel/VoxelMaster.cpp
        src/physics/Collider.cpp
        src/utils/GLogger.h src/utils/GConsole.h src/core/SfmlEngine.h src/components/voxel/chunks/ChunkSection.h)

add_executable(MainEngine ${GL_MAIN_SRC})

add_library(MyLibrary STATIC ${MY_LIBRARIES_SRC})
target_link_libraries(MainEngine MyLibrary)

# Make sure GLM uses radians and static GLEW library
target_compile_definitions(MainEngine PUBLIC -DGLM_FORCE_RADIANS -DGLEW_STATIC )

target_include_directories(MainEngine PUBLIC
        ${GLFW_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
        ${GLM_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}
        ${GTK3_INCLUDE_DIRS})

target_link_libraries(MainEngine
        ${GLFW_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${OPENGL_LIBRARIES}
#        ${FREETYPE_LIBRARIES}
        ${GTK3_LIBRARIES}
        ${SFML_LIBRARIES})
install(TARGETS MainEngine DESTINATION .)
#<<koniec projektu
