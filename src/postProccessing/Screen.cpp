//
// Created by gabriel on 15.10.2016.
//

#include "Screen.h"

std::vector<float> Screen::POINTS{-1, 1, -1, -1, 1, 1, 1, -1};
PointerRawModel Screen::MODEL = nullptr;
Screen::Screen(int width, int height, Loader loader) {
    MODEL = loader.loadToVAO(POINTS, 2);
    frameRenderer = new ToFrameBufferRendering(width, height);
    texture = frameRenderer -> getTexture();
    position = new Vector2f();
    scale = new Vector2f(1);

}