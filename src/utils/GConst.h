//
// Created by gabriel on 22.9.2016.
//

#ifndef GRAPHICSPROJECT_GCONST_H
#define GRAPHICSPROJECT_GCONST_H

constexpr int   NO_INDEX = -1;

constexpr float GRAVITY_EFFECT = 0.8f;
constexpr float DEFRACTION_EFFECT = 0.95f;
constexpr int   BALL_SIZE = 1;

constexpr int   SKYBOX_SIZE = 500;

constexpr int   MAX_COLOR_VALUE = 255;

constexpr int   MIN_COLOR_TEXTURE_WIDTH = 2;
constexpr int   MIN_COLOR_TEXTURE_HEIGHT = 2;

constexpr float SHADOW_OFFSET = 10.0f;
constexpr float SHADOW_DISTANCE = 100.0f;

#define DIR_UP {0.0f, 0.1f, 0.0f, 0.0f}
#define DIR_FORWARD {0.0f, 0.0f, -1.0f, 0.0f}


constexpr int   MODEL_VIEW_MOUSE_BUTTON_MOVE    = 0;
constexpr int   MODEL_VIEW_MOUSE_BUTTON_ZOOM    = 1;
constexpr float MODEL_VIEW_MAX_ZOOM_SPEED       = 0.1f;
constexpr int   MODEL_VIEW_MAX_MOVE_SPEED       = 6;
constexpr int   MODEL_VIEW_MAX_DISTANCE         = 60;
constexpr int   MODEL_VIEW_MIN_DISTANCE         = 6;
constexpr float MODEL_VIEW_ZOOM_SPEED           = 0.005f;
constexpr float MODEL_VIEW_REFRACTION           = 0.4f;

constexpr int   FBO_DEPTH_NONE           = 0;
constexpr int   FBO_DEPTH_TEXTURE       = 1;
constexpr int   FBO_DEPTH_RENDER_BUFFER = 2;

constexpr int SHADOW_MAP_SIZE = 2048;

#define THREAD_TITLE "objLoaderThread"

//TODO premenovať na SHADER_****
#define SHADOW_SHADER "shadowShader"
#define OBJECT_SHADER "objectShader"
#define POSTFX_SHADER "postFxShader"
#define PARTICLE_SHADER "particleShader"
#define DEFERRED_SHADER "deferredShader"

constexpr float DEFAUL_MOVE_SPEED = 1.0f;
constexpr float DEFAUL_ROT_SPEED = 0.05f;

constexpr int MOUSE_LEFT_BUTTON = 0;

constexpr int DEFAULT_WATER_SIZE = 50;
constexpr float DEFAULT_WATER_HEIGHT = 1.5f;
#define WATER_VERTICES    { -1.0f, -1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f}
#define PARTICLE_VERTICES { -0.5f,  0.5f, -0.5f, -0.5f,  0.5f,  0.5f,  0.5f, -0.5f}
#define GUI_VERTICES      { -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f,  1.0f, -1.0f}
#define POST_FX_POSITIONS { -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f,  1.0f, -1.0f}
#define SCREEN_POINTS     { -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f,  1.0f, -1.0f}


constexpr int DEFAULT_TERRAIN_HEIGHT = 0;
constexpr float VERTICAL_TERRAIN_OFFSET = 1.0f;

//TODO toto presunuť do messages
#define ERROR_MISSING_FILE "Missing file: "
#define ERROR_INITIAL_GLFW "Failed to initialize GLFW!"
#define ERROR_INITIAL_GLEW "Failed to initialize GLEW with OpenGL 3.3!"
#define ERROR_OPEN_GLFW_WINDOW "Failed to open GLFW window, your graphics card is probably only capable of OpenGL 2.1"
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


//WINDOWS
constexpr int CONTENT_ATTRIBUTES_MINOR_VERSION = 3;
constexpr int CONTENT_ATTRIBUTES_MAJOR_VERSION = 3;
constexpr int ANTI_ALIASING_LEVEL = 0;
constexpr int STENCIL_BITS = 8;
constexpr int DEPTH_BITS = 24;
constexpr int SAMPLES = 4;

constexpr int DEFAULT_MATERIAL_SHINE_DUMPER = 10;
constexpr int DEFAULT_MATERIAL_REFLECTIVITY = 1;

constexpr float DEFAULT_AMBIENT_RED     = 1.0;
constexpr float DEFAULT_AMBIENT_GREEN   = 1.0;
constexpr float DEFAULT_AMBIENT_BLUE    = 1.0;

constexpr float DEFAULT_CAMERA_FOV          = 70.0f;
constexpr float DEFAULT_CAMERA_NEAR_PLANE   = 0.1f;
constexpr float DEFAULT_CAMERA_FAR_PLANE    = 1000.0f;
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

constexpr int GRAVITY = -1;

constexpr int RES_X_MIN     = 320;
constexpr int RES_Y_MIN     = 240;
constexpr int RES_X_DEFAULT = 800;
constexpr int RES_Y_DEFAULT = 600;
constexpr int RES_X_MAX     = 7680;
constexpr int RES_Y_MAX     = 4320;

#endif //GRAPHICSPROJECT_GCONST_H

namespace Const{
    namespace Default{
        constexpr float BACKGROUND_RED      = 0.0;
        constexpr float BACKGROUND_GREEN    = 0.0;
        constexpr float BACKGROUND_BLUE     = 0.0;
        constexpr float BACKGROUND_ALPHA    = 1.0;
    }
    namespace Water{
        constexpr int REFLECTION_WIDTH = 2560; //320 * 8
        constexpr int REFLECTION_HEIGHT = 1440; //180 * 8
        constexpr int REFRACTION_WIDTH = 1280;
        constexpr int REFRACTION_HEIGHT = 720;
    }
}
