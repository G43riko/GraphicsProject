//
// Created by gabriel on 10.1.2017.
//

#ifndef GRAPHICSPROJECT_PARTICLETEXTURE_H
#define GRAPHICSPROJECT_PARTICLETEXTURE_H


#include <src/rendering/material/Texture2D.h>

class ParticleTexture {
public:
    PointerTexture2D texture;
    int rows;
    int columns;
    ParticleTexture(PointerTexture2D texture, int rows, int columns) : texture(texture), rows(rows), columns(columns){}
};
typedef std::shared_ptr<ParticleTexture> PointerParticleTexture;


#endif //GRAPHICSPROJECT_PARTICLETEXTURE_H
