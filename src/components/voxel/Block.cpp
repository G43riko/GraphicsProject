//
// Created by gabriel on 16.4.2017.
//

#include "Block.h"

Block::Block(int x, int y, int z, Chunk * parent, const BlockType type)
          : //translation(Matrix4f::initTranslation((x * BLOCK_SIZE_X) << 1, (y * BLOCK_SIZE_Y) << 1, (z * BLOCK_SIZE_Z) << 1)),
          type(type),
          x(x),
          y(y),
          z(z),
          parent(parent),
          color(getColorByType(type)){
    parent -> getWorld() -> blocks.push_back(this);
}

bool Block::isVisible(void){
//    if(!parent -> isTransparent(x + 1, y, z) &&
//       !parent -> isTransparent(x - 1, y, z) &&
//       !parent -> isTransparent(x, y + 1, z) &&
//       !parent -> isTransparent(x, y - 1, z) &&
//       !parent -> isTransparent(x, y, z + 1) &&
//       !parent -> isTransparent(x, y, z - 1)){
//        return false;
//    }
    return true;
}

void Block::setNeighbor(Block * block){
    if(IS_NULL(block)){
        return;
    }
    if(block -> x + 1 == x || (x == 0 && block -> x == MAX_BLOCKS_X - 1 && block -> y == y && block -> z == z)){
        xNeighborPlus = block;
        turnOffOption(X_PLUS);
        block -> xNeighborMinus = this;
        block -> turnOffOption(X_MINUS);
    }
    else if(block -> y + 1 == y || (y == 0 && block -> y == MAX_BLOCKS_Y - 1 && block -> x == x && block -> z == z)){
        yNeighborPlus = block;
        turnOffOption(Y_PLUS);
        block -> yNeighborMinus = this;
        block -> turnOffOption(Y_MINUS);
    }
    else if(block -> z + 1 == z || (z == 0 && block -> z == MAX_BLOCKS_Z - 1 && block -> y == y  && block -> x == x)){
        zNeighborPlus = block;
        turnOffOption(Z_PLUS);
        block -> zNeighborMinus = this;
        block -> turnOffOption(Z_MINUS);
    }
}