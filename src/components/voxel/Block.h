//
// Created by gabriel on 16.4.2017.
//

#ifndef GAMEENGINE_BLOCK_H
#define GAMEENGINE_BLOCK_H


#define BLOCK_SIZE_X 1
#define BLOCK_SIZE_Y 1
#define BLOCK_SIZE_Z 1

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
    void cleanUp(void){

    }

    Vector3f getAbsolutePosition(void);

    Vector4f getColor(void){
        return color;
    }

    void render(PointerRawModel model, PointerBasicShader shader){
        if(!isVisible()){
            return;
        }
        Vector3f position = getAbsolutePosition();
        shader -> updateUniform4f("color", getColor());

        shader -> updateUniform4m(TRANSFORMATION_MATRIX, Matrix4f::initRotation(0, 0, 0) * Matrix4f::initTranslation(position.x, position.y, position.z));
        glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);


        shader -> updateUniform4m(TRANSFORMATION_MATRIX, Matrix4f::initRotation(M_PI_2, 0, 0) * Matrix4f::initTranslation(position.x, position.y, position.z));
        glDrawElements(GL_TRIANGLES, model -> getVertexCount(), GL_UNSIGNED_INT, 0);
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
            case BlockType::white: return Vector4f(1, 1, 1, 1);
        }
    }

    void setUpVisibility(void){
        xNeighborPlus && xNeighborPlus->isVisible() ? turnOffOption(X_PLUS) : turnOnOption(X_PLUS);
        xNeighborMinus && xNeighborMinus->isVisible() ? turnOffOption(X_MINUS) : turnOnOption(X_MINUS);

        yNeighborPlus && yNeighborPlus->isVisible() ? turnOffOption(Y_PLUS) : turnOnOption(Y_PLUS);
        yNeighborMinus && yNeighborMinus->isVisible() ? turnOffOption(Y_MINUS) : turnOnOption(Y_MINUS);

        zNeighborPlus && zNeighborPlus->isVisible() ? turnOffOption(Z_PLUS) : turnOnOption(Z_PLUS);
        zNeighborMinus && zNeighborMinus->isVisible() ? turnOffOption(Z_MINUS) : turnOnOption(Z_MINUS);
    }
    void setNeighbor(Block * block){
        if(block -> x + 1 == x){
            xNeighborPlus = block;
            block -> xNeighborMinus = this;
        }
        else if(block -> y + 1 == y){
            yNeighborPlus = block;
            block -> yNeighborMinus = this;
        }
        else if(block -> z + 1 == z){
            zNeighborPlus = block;
            block -> zNeighborMinus = this;
        }
    }
    inline int getRenderOptions(void){return options;}
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
    Block * xNeighborPlus   = nullptr;
    Block * xNeighborMinus  = nullptr;
    Block * yNeighborPlus   = nullptr;
    Block * yNeighborMinus  = nullptr;
    Block * zNeighborPlus   = nullptr;
    Block * zNeighborMinus  = nullptr;
    int options = 0;
    Vector4f color;
    BlockType type;
    Chunk * parent;
    int x, y, z;
};


#endif //GAMEENGINE_BLOCK_H
