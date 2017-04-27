//
// Created by gabriel on 16.4.2017.
//

#ifndef GAMEENGINE_BLOCK_H
#define GAMEENGINE_BLOCK_H


#define BLOCK_SIZE_X 1
#define BLOCK_SIZE_Y 1
#define BLOCK_SIZE_Z 1

#define VISIBLE_ALL 63
#define VISIBLE_NONE 0

#include <src/utils/Vectors.h>
#include <src/rendering/shader/BasicShader.h>
#include <src/rendering/model/RawModel.h>

enum BlockType { red, green, blue, yellow, magenta, aqua, white, black};
#include "Chunk.h"

class Chunk;

class Block {
public:
    const static unsigned char X_PLUS   = 0x01; // hex for 0000 0001
    const static unsigned char X_MINUS  = 0x02; // hex for 0000 0010
    const static unsigned char Y_PLUS   = 0x04; // hex for 0000 0100
    const static unsigned char Y_MINUS  = 0x08; // hex for 0000 1000
    const static unsigned char Z_PLUS   = 0x10; // hex for 0001 0000
    const static unsigned char Z_MINUS  = 0x20; // hex for 0010 0000
    Block(int x, int y, int z, Chunk * parent, BlockType type);

    void show(void);
    inline void cleanUp(void) const{
        if(xNeighborPlus){ xNeighborPlus -> xNeighborMinus = nullptr; }
        if(xNeighborMinus){ xNeighborMinus -> xNeighborPlus = nullptr; }
        if(yNeighborPlus){ yNeighborPlus -> yNeighborMinus = nullptr; }
        if(yNeighborMinus){ yNeighborMinus -> yNeighborPlus = nullptr; }
        if(zNeighborPlus){ zNeighborPlus -> zNeighborMinus = nullptr; }
        if(zNeighborMinus){ zNeighborMinus -> zNeighborPlus = nullptr; }
    }

//    Vector3f getAbsolutePosition(void);

    Vector4f getColor(void){
        return color;
    }

    bool isVisible(void);
    inline static Vector4f getColorByType(BlockType type){
        switch (type){
            case BlockType::yellow: return Vector4f(1, 1, 0, 1);
            case BlockType::aqua: return Vector4f(0, 1, 1, 1);
            case BlockType::magenta: return Vector4f(1, 0, 1, 1);
            case BlockType::red: return Vector4f(1, 0, 0, 1);
            case BlockType::green: return Vector4f(0, 1, 0, 1);
            case BlockType::blue: return Vector4f(0, 0, 1, 1);
            case BlockType::black: return Vector4f(0, 0, 0, 1);
            default: return Vector4f(1, 1, 1, 1);
        }
    }

    inline void setUpVisibility(void){
        xNeighborPlus && xNeighborPlus->isVisible() ? turnOffOption(X_PLUS) : turnOnOption(X_PLUS);
        xNeighborMinus && xNeighborMinus->isVisible() ? turnOffOption(X_MINUS) : turnOnOption(X_MINUS);

        yNeighborPlus && yNeighborPlus->isVisible() ? turnOffOption(Y_PLUS) : turnOnOption(Y_PLUS);
        yNeighborMinus && yNeighborMinus->isVisible() ? turnOffOption(Y_MINUS) : turnOnOption(Y_MINUS);

        zNeighborPlus && zNeighborPlus->isVisible() ? turnOffOption(Z_PLUS) : turnOnOption(Z_PLUS);
        zNeighborMinus && zNeighborMinus->isVisible() ? turnOffOption(Z_MINUS) : turnOnOption(Z_MINUS);
    }
    void setNeighbor(Block * block);
    inline int getRenderOptions(void){return options;}
    inline Matrix4f * getTranslation(void){return &translation;}
    inline Vector3f getScale(void){return scale;}
    inline Vector3f getAbsolutePos(void){return Vector3f(((x * BLOCK_SIZE_X) << 1) - ((scale.getXi() - 1) * BLOCK_SIZE_X),
                                                         ((y * BLOCK_SIZE_Y) << 1) - ((scale.getYi() - 1) * BLOCK_SIZE_Y),
                                                         ((z * BLOCK_SIZE_Z) << 1) - ((scale.getZi() - 1) * BLOCK_SIZE_Z)); }
private:
    inline void turnOnOption(unsigned char val){
        options |= val;
    }
    inline void turnOffOption(unsigned char val){
        options &= ~val;
    }
    inline void toggleOption(unsigned char val){
        options ^= val;
    }
    Vector3f scale          = Vector3f(1, 1, 1);
    Matrix4f translation;
    Block * xNeighborPlus   = nullptr;
    Block * xNeighborMinus  = nullptr;
    Block * yNeighborPlus   = nullptr;
    Block * yNeighborMinus  = nullptr;
    Block * zNeighborPlus   = nullptr;
    Block * zNeighborMinus  = nullptr;
    int options = VISIBLE_ALL;
    const BlockType type;
    const int x, y, z;
    Chunk * parent;
    const Vector4f color;
};


#endif //GAMEENGINE_BLOCK_H
