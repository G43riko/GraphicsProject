//
// Created by gabriel on 22.9.2016.
//

#ifndef GRAPHICSPROJECT_GCONST_H
#define GRAPHICSPROJECT_GCONST_H

#define NO_INDEX -1

#define GRAVITY_EFFECT 0.8f
#define DEFRACTION_EFFECT 0.95f
#define BALL_SIZE 1

#define SKYBOX_SIZE 500

#define MAX_COLOR_VALUE 255

#define MIN_COLOR_TEXTURE_WIDTH 2;
#define MIN_COLOR_TEXTURE_HEIGHT 2

#define SHADOW_OFFSET 10.0f
#define SHADOW_DISTANCE 100.0f
#define DIR_UP {0.0f, 0.1f, 0.0f, 0.0f}
#define DIR_FORWARD {0.0f, 0.0f, -1.0f, 0.0f}


#define MODEL_VIEW_MOUSE_BUTTON_MOVE 0
#define MODEL_VIEW_MOUSE_BUTTON_ZOOM 1
#define MODEL_VIEW_MAX_ZOOM_SPEED 0.1f
#define MODEL_VIEW_MAX_MOVE_SPEED 6
#define MODEL_VIEW_MAX_DISTANCE 60
#define MODEL_VIEW_MIN_DISTANCE 6
#define MODEL_VIEW_ZOOM_SPEED 0.005f
#define MODEL_VIEW_REFRACTION 0.4f

#define FBO_DEPTH_NONE 0
#define FBO_DEPTH_TEXTURE 1
#define FBO_DEPTH_RENDER_BUFFER 2

#define SHADOW_MAP_SIZE 2048

#define THREAD_TITLE "objLoaderThread"

//TODO premenovať na SHADER_****
#define SHADOW_SHADER "shadowShader"
#define OBJECT_SHADER "objectShader"
#define POSTFX_SHADER "postFxShader"
#define PARTICLE_SHADER "particleShader"
#define DEFERRED_SHADER "deferredShader"

#define DEFAUL_MOVE_SPEED 1.0f
#define DEFAUL_ROT_SPEED 0.05f

#define MOUSE_LEFT_BUTTON 0

#define DEFAULT_WATER_SIZE 50
#define DEFAULT_WATER_HEIGHT 1.5f
#define WATER_VERTICES    { -1.0f, -1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f}
#define PARTICLE_VERTICES { -0.5f,  0.5f, -0.5f, -0.5f,  0.5f,  0.5f,  0.5f, -0.5f}
#define GUI_VERTICES      { -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f,  1.0f, -1.0f}
#define POST_FX_POSITIONS { -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f,  1.0f, -1.0f}
#define SCREEN_POINTS     { -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f,  1.0f, -1.0f}

#define WATER_REFLECTION_WIDTH 2560 //320 * 8
#define WATER_REFLECTION_HEIGHT 1440 //180 * 8
#define WATER_REFRACTION_WIDTH 1280
#define WATER_REFRACTION_HEIGHT 720

#define DEFAULT_TERRAIN_HEIGHT 0
#define VERTICAL_TERRAIN_OFFSET 1.0f

//TODO toto presunuť do messages
#define ERROR_MISSING_FILE "Missing file: "
#define ERROR_INITIAL_GLFW "Failed to initialize GLFW!"
#define ERROR_INITIAL_GLEW "Failed to initialize GLEW with OpenGL 3.3!"
#define ERROR_OPEN_GLFW_WINDOW "Failed to open GLFW window, your graphics card is probably only capable of OpenGL 2.1";
#define ERROR_COMPILE_SHADER(shader, error) "shader " + shader + " nebol skompilovany: " + error


#define EXTENSION_GEOMETRY ".geom"
#define EXTENSION_FRAGMENT ".frag"
#define EXTENSION_VERTEX ".vert"
#define EXTENSION_GLSL ".glsl"
#define EXTENSION_BLOCK ".block"
#define EXTENSION_CHUNK ".chunk"
//TODO premenovať na EXTENSION_****
#define MODELS_EXTENSION ".obj"
#define TEXTURES_EXTENSION ".png"

//TODO premenovať na FOLDER_****
#define TEXTURES_FOLDER "res/textures/"
#define SKIES_FOLDER "res/textures/skies/"
#define MODELS_FOLDER "res/models/"
#define SHADERS_FOLDER "res/shaders/"
#define INCLUDE_IDENTIFICATOR "#include"

#define DEFAULT_TITLE "GEngine"

#define DEFAULT_MATERIAL_SHINE_DUMPER 10
#define DEFAULT_MATERIAL_REFLECTIVITY 1

#define DEFAULT_AMBIENT_RED 1.0
#define DEFAULT_AMBIENT_GREEN 1.0
#define DEFAULT_AMBIENT_BLUE 1.0

#define DEFAULT_BACKGROUND_RED 0.0
#define DEFAULT_BACKGROUND_GREEN 0.0
#define DEFAULT_BACKGROUND_BLUE 0.0
#define DEFAULT_BACKGROUND_ALPHA 1.0

#define DEFAULT_CAMERA_FOV 70.0f
#define DEFAULT_CAMERA_NEAR_PLANE 0.1f
#define DEFAULT_CAMERA_FAR_PLANE 1000.0f
#define DEFAULT_CAMERA_POSITION {0, 0, 0}


#define UNIFORM_PLANE "plane"
#define UNIFORM_MATERIAL "material"
#define UNIFORM_CONTRAST "contrast"
#define UNIFORM_VIEW_MATRIX "viewMatrix"
#define UNIFORM_MODEL_MATRIX "modelMatrix"
#define UNIFORM_SHINE_DUMPER "shineDumper"
#define UNIFORM_REFLECTIVITY "reflectivity"
#define UNIFORM_TO_SHADOW_SPACE "toShadowSpace"
#define UNIFORM_CAMERA_POSITION "cameraPosition"
#define UNIFORM_MODEL_VIEW_MATRIX "modelViewMatrix"
#define UNIFORM_PROJECTION_MATRIX "projectionMatrix"
#define UNIFORM_TRANSFORMATION_MATRIX "transformationMatrix"

#define GRAVITY -1

#define RES_X_MIN 320
#define RES_Y_MIN 240
#define RES_X_DEFAULT 800
#define RES_Y_DEFAULT 600
#define RES_X_MAX 7680
#define RES_Y_MAX 4320

#endif //GRAPHICSPROJECT_GCONST_H
