//
// Created by gabriel on 27.11.2016.
//

#ifndef GRAPHICSPROJECT_BALL_H
#define GRAPHICSPROJECT_BALL_H


#include <src/rendering/model/Entity.h>
#include "GameObject.h"

#define GRAVITY_EFFECT 0.8f
#define DEFRACTION_EFFECT 0.95f
#define BALL_SIZE 1


class Ball : public GameObject{
private:
    float size = BALL_SIZE;
    static std::vector<Ball*> balls;
public:
    inline Ball(PointerEntity object) : GameObject(object){
        balls.push_back(this);
    }
    inline void update(float delta){
        if(!getObject() -> isAlive()){
            return;
        }
        object -> getTransform() -> move(velocity * delta);
        object -> getTransform() -> getRotation() -> rotate(Vector3f(-velocity.z * 0.4f, 0.0f, velocity.x * 0.4f) * delta);
        checkCollision(this);
        //float DEFRACTION_EFFECT = 0.95f;
        velocity *= DEFRACTION_EFFECT * delta;
    }

    inline static bool checkCollision(Ball * el) {
        checkBorder(el->object->getTransform(), &el->velocity, el->size, Vector2f(-50, -50), Vector2f(100, 100));

        Vector3f * thisPos = el -> object ->getTransform() -> getPosition();

        for (Ball * b : balls) {
            Vector3f * ballPos = b -> object -> getTransform() -> getPosition();
            if (collision(*thisPos, *ballPos, el -> size)) {
//                b -> getObject() -> setAlive(false);
                Vector3f center = (*thisPos + *ballPos) / 2;
                b -> velocity.x -= (thisPos -> x - center.x);
                b -> velocity.z -= (thisPos -> z - center.z);

                el -> velocity.x -= ballPos -> x - center.x;
                el -> velocity.z -= ballPos -> z - center.z;
            }
        }
        return false;
    }

    inline static bool collision(Vector3f posA, Vector3f posB, float size){
        float dist = (posA - posB).length();
        return (dist <= size * 16) && (NEQ(dist, 0));

    }
    inline static void checkBorder(Transform * a, Vector3f * velocity, float size, Vector2f pos, Vector2f scale){
        Vector2f max = pos + scale;
        if (a -> getPosition() -> x + size > max.x) {
            a -> getPosition() -> x = max.x - size;
            velocity -> x = (float)-abs((int)velocity -> x);
        }
        if (a -> getPosition() -> x - size < pos.x) {
            a -> getPosition() -> x = pos.x + size;
            velocity -> x = (float)abs((int)velocity -> x);
        }
        if (a -> getPosition() -> z + size > max.y) {
            a -> getPosition() -> z = max.y - size;
            velocity -> z = (float)-abs((int)velocity -> z);
        }
        if (a -> getPosition() -> z - size < pos.y) {
            a -> getPosition() -> z = pos.y + size;
            velocity -> z = (float)abs((int)velocity -> z);
        }

    }
};

#endif //GRAPHICSPROJECT_BALL_H
