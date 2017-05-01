//
// Created by gabriel on 22.9.2016.
//

#ifndef GRAPHICSPROJECT_CONST_H
#define GRAPHICSPROJECT_CONST_H

#define ERROR_MISSING_FILE "Missing file: "
#define ERROR_INITIAL_GLFW "Failed to initialize GLFW!"
#define ERROR_INITIAL_GLEW "Failed to initialize GLEW with OpenGL 3.3!"
#define ERROR_OPEN_GLFW_WINDOW "Failed to open GLFW window, your graphics card is probably only capable of OpenGL 2.1";
#define ERROR_COMPILE_SHADER(shader, error) "shader " + shader + " nebol skompilovany: " + error

#define EXTENSION_FRAGMENT ".frag"
#define EXTENSION_VERTEX ".vert"
#define EXTENSION_GEOMETRY ".geom"

#define TEXTURES_FOLDER "res/textures/"
#define MODELS_FOLDER "res/models/"
#define SHADERS_FOLDER "res/shaders/"
#define MODELS_EXTENSION ".obj"
#define TEXTURES_EXTENSION ".png"

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
#define DEFAULT_CAMERA_POSITION 0, 0, 0



#define VIEW_MATRIX "viewMatrix"
#define CAMERA_POSITION "cameraPosition"
#define PROJECTION_MATRIX "projectionMatrix"
#define TRANSFORMATION_MATRIX "transformationMatrix"

#define GRAVITY -1

#define RES_X_MIN 320
#define RES_Y_MIN 240
#define RES_X_DEFAULT 800
#define RES_Y_DEFAULT 600
#define RES_X_MAX 7680
#define RES_Y_MAX 4320

#endif //GRAPHICSPROJECT_CONST_H
