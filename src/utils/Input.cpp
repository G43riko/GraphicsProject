//
// Created by gabriel on 25.9.2016.
//

#include "Input.h"

Vector2f Input::windowCenter;
Vector2f Input::mouseScrollOffset;
Vector2f Input::mousePos;

bool Input::lastKeys[NUM_KEY_CODES] = {false};
bool Input::keys[NUM_KEY_CODES] = {false};
bool Input::lastButtons[NUM_MOUSE_BUTTONS] = {false};
bool Input::buttons[NUM_MOUSE_BUTTONS] = {false};
