//
// Created by gabriel on 25.9.2016.
//

#include "Input.h"


GLFWwindow * Input::window;
bool Input::lastKeys[NUM_KEY_CODES] = {false};
bool Input::keys[NUM_KEY_CODES] = {false};
bool Input::lastButtons[NUM_MOUSE_BUTTONS] = {false};
bool Input::buttons[NUM_MOUSE_BUTTONS] = {false};

int Input::KEY_W = 87;
int Input::KEY_A = 65;
int Input::KEY_S = 83;
int Input::KEY_D = 68;
int Input::KEY_Q = 81;
int Input::KEY_E = 69;

int Input::KEY_LSHIFT   = 16;
int Input::KEY_SPACE    = 32;