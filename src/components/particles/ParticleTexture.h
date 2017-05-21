//
// Created by gabriel on 10.1.2017.
//

#ifndef GRAPHICSPROJECT_PARTICLETEXTURE_H
#define GRAPHICSPROJECT_PARTICLETEXTURE_H


#include <src/rendering/material/Texture2D.h>

class ParticleTexture {
    const PointerTexture2D _texture;
    const uint _rows;
    const uint _columns;
public:
    inline ParticleTexture(const PointerTexture2D& texture, uint rows, uint columns) :
            _texture(texture),
            _rows(rows),
            _columns(columns){}
    inline uint getRows(void) const{return _rows;}
    inline uint getColumns(void) const{return _columns;}
    inline PointerTexture2D getTexture(void) const{return _texture;}
    inline void setTextureOffset(Vector2f& offset, int index) const{
        const float column = (float)(index % _rows);
        const float row = (float)(index / _rows);
        offset.x = column / (float)_rows;
        offset.y = row / (float)_rows;
    }
};


#endif //GRAPHICSPROJECT_PARTICLETEXTURE_H
