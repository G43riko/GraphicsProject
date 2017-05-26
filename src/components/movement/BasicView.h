//
// Created by gabriel on 13.12.2016.
//

#ifndef GRAPHICSPROJECT_BASICVIEW_H
#define GRAPHICSPROJECT_BASICVIEW_H


class BasicView{
protected:
    PointerCamera camera = nullptr;
    GameObject * player = nullptr;
    float moveSpeed = DEFAUL_MOVE_SPEED;
    float rotSpeed = DEFAUL_ROT_SPEED;
public:
    enum Type{
        FPS_VIEW,
        TOP_VIEW,
        MODEL_VIEW,
        TPS_VIEW
    };
    inline float getMoveSpeed(void) const{return moveSpeed; }
    inline float getRotSpeed(void) const{return rotSpeed; }
    inline Type getType(void) const{return _type;}
    virtual ~BasicView(void){};
    BasicView(PointerCamera camera, GameObject * player, Type type) :
            camera(camera),
            player(player),
            _type(type){}
    virtual void cleanUp(void){};
    virtual void update(const float delta){};
private:
    const Type _type;
};

#endif //GRAPHICSPROJECT_BASICVIEW_H
