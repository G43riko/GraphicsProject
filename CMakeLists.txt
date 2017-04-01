cmake_minimum_required(VERSION 3.5)
project(GraphicsProject)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")

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
target_link_libraries(libGraphics PUBLIC ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES} ${GTK3_LIBRARIES})
# Pass on include directories
target_include_directories(libGraphics PUBLIC
        src/lib
        res
        ${GLFW_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
        ${GLM_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
        ${GTK3_INCLUDE_DIRS})
#<<moje





#>>zaciatok projektu
#####TUTO TREBA PRIDAŤ AK BUDE CHÝBAŤ UNDEFINED REFERENCE
set(GL_MAIN_SRC src/main.cpp
        src/core/BasicEngine.h
        src/utils/Input.cpp
        src/rendering/Renderer.cpp
        src/utils/Loader.cpp
        src/components/postProccessing/Screen.cpp

        src/components/entities/EntityManager.cpp
        src/components/entities/EntityManager.h
        src/components/entities/EntityMaster.cpp
        src/components/entities/EntityMaster.h
        src/components/FreeMove.cpp
        src/components/gui/GuiMaster.cpp
        src/components/gui/GuiMaster.h
        src/components/KeyFrame.cpp
        src/components/KeyFrame.h
        src/components/lights/DirectionalLight.cpp
        src/components/lights/DirectionalLight.h
        src/components/lights/PointLight.cpp
        src/components/lights/SpotLight.cpp
        src/components/lights/SpotLight.h
        src/components/Master.cpp
        src/components/Master.h
        src/components/movement/BasicView.h
        src/components/movement/FpsView.cpp
        src/components/movement/FpsView.h
        src/components/movement/TopView.cpp
        src/components/movement/TopView.h
        src/components/Object.cpp
        src/components/Object.h
        src/components/particles/Particle.cpp
        src/components/particles/Particle.h
        src/components/particles/ParticleManager.cpp
        src/components/particles/ParticleManager.h
        src/components/particles/ParticleMaster.cpp
        src/components/particles/ParticleMaster.h
        src/components/particles/ParticleSystemComplex.cpp
        src/components/particles/ParticleSystemComplex.h
        src/components/particles/ParticleSystemSimple.cpp
        src/components/particles/ParticleSystemSimple.h
        src/components/particles/ParticleTexture.cpp
        src/components/particles/ParticleTexture.h
        src/components/postProccessing/Fbo.cpp
        src/components/postProccessing/Filter.cpp
        src/components/postProccessing/Filter.h
        src/components/postProccessing/ImageRenderer.cpp
        src/components/postProccessing/PostFxMaster.cpp
        src/components/postProccessing/PostFxMaster.h
        src/components/postProccessing/ToFrameBufferRendering.cpp
        src/components/shadows/ShadowBox.cpp
        src/components/shadows/ShadowBox.h
        src/components/shadows/ShadowFrameBuffer.cpp
        src/components/shadows/ShadowFrameBuffer.h
        src/components/shadows/ShadowMaster.cpp
        src/components/shadows/ShadowMaster.h
        src/components/sky/SkyBoxMaster.cpp
        src/components/sky/SkyBoxMaster.h
        src/components/terrain/HeightGenerator.cpp
        src/components/terrain/HeightGenerator.h
        src/components/terrain/HeightsGenerator.h
        src/components/terrain/Terrain.cpp
        src/components/terrain/Terrain.h
        src/components/water/WaterFrameBuffer.cpp
        src/components/water/WaterFrameBuffer.h
        src/components/water/WaterMaster.cpp
        src/components/water/WaterMaster.h
        src/core/BasicApplication.h
        src/core/BasicCamera.h
        src/core/BasicRenderer.h
        src/core/BasicScene.h
        src/core/GameComponent.cpp
        src/core/GameComponent.h
        src/core/GameObject.cpp
        src/core/GameObject.h
        src/core/MainApplication.cpp
        src/core/MainApplication.h
        src/core/MainRenderer.cpp
        src/core/MainRenderer.h
        src/game/Animation.cpp
        src/game/Animation.h
        src/game/Arrow.cpp
        src/game/Arrow.h
        src/game/Ball.cpp
        src/game/Ball.h
        src/game/Environment.cpp
        src/game/Environment.h
        src/game/GameObject.h
        src/game/Scene.cpp
        src/GUI/BasicGtkGui.cpp
        src/GUI/BasicGtkGui.h
        src/GUI/componentsGui/GtkLight.h
        src/GUI/componentsGui/GtkPostFx.h
        src/GUI/componentsGui/GtkRenderer.h
        src/GUI/componentsGui/GtkScene.h
        src/GUI/componentsGui/GtkWater.h
        src/GUI/GtkHandler.h
        src/GUI/GtkIntroGui.cpp
        src/GUI/GtkIntroGui.h
        src/GUI/MainGui.h
        src/rendering/Camera.cpp
        src/rendering/material/CubeTexture.cpp
        src/rendering/material/CubeTexture.h
        src/rendering/material/Material.cpp
        src/rendering/material/TextureManager.cpp
        src/rendering/material/TextureManager.h
        src/rendering/model/Entity.cpp
        src/rendering/model/MaterialedModel.cpp
        src/rendering/model/Mesh.cpp
        src/rendering/model/RawModel.cpp
        src/rendering/RendererInterface.h
        src/rendering/RenderMastersManager.h
        src/rendering/RenderOptions.h
        src/rendering/RenderUtil.cpp
        src/rendering/RenderUtil.h
        src/rendering/shader/BasicShader.cpp
        src/static_libs/lodepng.cpp
        src/static_libs/lodepng.h
        src/static_libs/stb_image.c
        src/static_libs/stb_image.h
        src/static_libs/tiny_obj_loader.h
        src/utils/FileLoader.cpp
        src/utils/Maths.cpp
        src/utils/Matrix4f.cpp
        src/utils/MousePicker.cpp
        src/utils/MousePicker.h
        src/utils/Quaternion.cpp
        src/utils/Transform.cpp
        src/utils/utils.cpp
        src/utils/Vertex.cpp
        src/rendering/WindowManager.cpp
        src/utils/Vectors.cpp
        src/rendering/material/Texture2D.cpp
        )
add_executable(gl_main ${GL_MAIN_SRC})
target_link_libraries(gl_main libGraphics)
install(TARGETS gl_main DESTINATION .)
#<<koniec projektu

set(SOURCE_FILES    src/main.cpp
                    src/rendering/shader/BasicShader.cpp
                    src/utils/Logger.cpp
                    src/utils/FileLoader.cpp
                    src/rendering/shader/GuiShader.cpp
                    src/rendering/model/RawModel.cpp
                    src/rendering/model/MaterialedModel.cpp
                    src/rendering/model/Entity.cpp
                    src/utils/Maths.cpp
        src/utils/Transform.cpp
                    src/rendering/Camera.cpp
                    src/rendering/model/Mesh.cpp
                    src/rendering/shader/EntityShader.cpp
        src/rendering/shader/ObjectShader.cpp src/utils/Matrix4f.cpp src/utils/Matrix4f.h src/utils/Quaternion.cpp src/utils/Quaternion.h src/components/gui/GuiTexture.cpp src/components/gui/GuiTexture.h src/rendering/shader/VerticalBlurShader.cpp src/rendering/shader/HorizontalBlurShader.cpp src/rendering/shader/CombineShader.cpp src/rendering/shader/ColorShader.cpp src/rendering/shader/SkyBoxShader.cpp src/rendering/shader/SkyBoxRenderer.cpp src/rendering/shader/SkyBoxRenderer.h src/rendering/shader/ParticleShader.cpp src/utils/ResourcesManager.h src/rendering/shader/ShadowShader.cpp src/rendering/shader/WaterShader.cpp src/rendering/shader/DeferredShader.cpp src/rendering/shader/WireframeShader.cpp )

add_executable(GraphicsProject ${SOURCE_FILES})