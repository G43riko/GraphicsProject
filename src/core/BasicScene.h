//
// Created by gabriel on 14.1.2017.
//

#ifndef GRAPHICSPROJECT_BASICSCENE_H
#define GRAPHICSPROJECT_BASICSCENE_H

class BasicScene{
public:
    virtual ~BasicScene(){};
    virtual void cleanUp(void) = 0;
    virtual void update(float delta) = 0;
//    virtual void addEntity(PointerEntity entity){};
//    virtual void addLight(PointerLight entity){};
    //createParticle
    //createSystem
};

#endif //GRAPHICSPROJECT_BASICSCENE_H
