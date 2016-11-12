//
// Created by gabriel on 15.10.2016.
//

#include "Screen.h"

std::vector<float> Screen::POINTS{-1, 1, -1, -1, 1, 1, 1, -1};
PointerRawModel Screen::MODEL = nullptr;
Screen::Screen(int width, int height, Loader loader) {
    MODEL = loader.loadToVao(POINTS, 2);
    frameRenderer = ToFrameBufferRendering(width, height);
    texture = frameRenderer.getTexture();
    position = Vector2f();
    scale = Vector2f(1);

//    setGreyscale(true);
    //setInvert(true);
    //setContrast(1);
    //setLevels(0);

}