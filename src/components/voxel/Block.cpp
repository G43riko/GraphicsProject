//
// Created by gabriel on 16.4.2017.
//

#include "Block.h"

Block::Block(int x, int y, int z, Chunk * parent, BlockType type){
    this -> type = type;
    this -> parent = parent;
    this -> x = x;
    this -> y = y;
    this -> z = z;
    color = getColorByType(type);
    parent -> getWorld() -> blocks.push_back(this);
    //PointerEntity entity = createEntity(parent -> getWorld() -> getModel((int)random(0, 6)), getAbsolutePosition(), Vector3f(), Vector3f(1));
    //parent -> getWorld() -> getScene() ->addEntity(entity);
}

Vector3f Block::getAbsolutePosition(void){
    return parent -> getAbsoulePosition() + (Vector3f(x * BLOCK_SIZE_X, y * BLOCK_SIZE_Y, z * BLOCK_SIZE_Z) * 2);
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