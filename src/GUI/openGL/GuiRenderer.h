//
// Created by gabriel on 24.5.2017.
//

#ifndef GAMEENGINE_GUIRENDERER_H
#define GAMEENGINE_GUIRENDERER_H

#include <src/utils/math/objects/Vectors.h>

class GuiRenderer{
    BasicShader * shader;
    const PointerRawModel model;
public:
    inline GuiRenderer(BasicShader * shader, const PointerRawModel model) : shader(shader), model(model){};

    void renderRect(const Vector2f& position, const Vector2f& scale, uint texture, float opacity = 1) const{
        glBindTexture(GL_TEXTURE_2D, texture);
        shader -> updateUniform4m(UNIFORM_TRANSFORMATION_MATRIX, Maths::createTransformationMatrix(position, scale));
        glDrawArrays(GL_TRIANGLE_STRIP, 0, model -> getVertexCount());
    }
};

#endif //GAMEENGINE_GUIRENDERER_H
