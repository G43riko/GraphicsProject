//
// Created by gabriel on 27.11.2016.
//

#ifndef GRAPHICSPROJECT_BALL_H
#define GRAPHICSPROJECT_BALL_H


#include <src/rendering/model/Entity.h>
#include "GameObject.h"

class Ball : public GameObject{
    static float GRAVITY_EFFECT;
    static float DEFRACTION_EFFECT;

public:
    constexpr static float size = 1;
    static std::vector<Ball*> balls;
    Ball(PointerEntity object);
    void update(float);

    static bool checkCollision(Ball * el) {
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

    static bool collision(Vector3f posA, Vector3f posB, float size){
        float dist = (posA - posB).getLength();
        return (dist <= size * 16) && (NEQ(dist, 0));

    }
    static void checkBorder(Transform * a, Vector3f * velocity, float size, Vector2f pos, Vector2f scale){
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
