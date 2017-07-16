//
// Created by gabriel on 24.5.2017.
//

#ifndef GAMEENGINE_MODELVIEW_H
#define GAMEENGINE_MODELVIEW_H

#include <src/rendering/Camera.h>
#include "BasicView.h"

#define MODEL_VIEW_MIN_PITCH -M_PI_2
#define MODEL_VIEW_MAX_PITCH M_PI_2

class ModelView : public BasicView{
    float _yaw = 0;
    float _pitch = 0;
    const Vector3f _center;
    Vector2f _lastMousePosition = Input::getMousePosition();
    float _distance;
    Vector2f _velocity;
    float _zoomVelocity;

    inline void updatePos(const Vector2f& deltaPos){
        const bool rotY = NEZ(deltaPos.x);
        const bool rotX = NEZ(deltaPos.y);

        if(rotY){
            const float dist = TO_RADIANS(deltaPos.x);
            _yaw -= dist;
            camera -> getTransform() -> rotate(Vector3f(0, 1, 0), -dist);
        }

        if(rotX){
            const float dist = TO_RADIANS(deltaPos.y);
            const float newPitch = _pitch + dist;
            if(GBETWEEN(newPitch, MODEL_VIEW_MIN_PITCH, MODEL_VIEW_MAX_PITCH)){
                _pitch = newPitch;
                camera -> getTransform() -> rotate(camera -> getTransform() -> getRotation().getRight(), -dist);
            }
        }
        if (NEZ(rotY) || NEZ(rotX) || NEZ(_zoomVelocity)) {
            camera ->getTransform() -> getPosition().set(_center.x + SINF(_yaw) * COSF(_pitch) * _distance,
                                                         _center.y + SINF(_pitch) * _distance,
                                                         _center.z + COSF(_yaw) * COSF(_pitch) * _distance);
        }
    }

    inline void checkVelocity(void){
        if(_velocity.length() > MODEL_VIEW_MAX_MOVE_SPEED){
            _velocity.normalize() *= MODEL_VIEW_MAX_MOVE_SPEED;
        }
        if(_zoomVelocity > MODEL_VIEW_MAX_ZOOM_SPEED){
            _zoomVelocity = MODEL_VIEW_MAX_ZOOM_SPEED;
        }
    }
public:
    inline ModelView(PointerCamera camera,  const Vector3f& center = Vector3f(), float distance = 50) :
            BasicView(camera, player, BasicView::Type::MODEL_VIEW),
            _center(center),
            _distance(distance){
        rotSpeed = 1;
        update(1.0f);
        camera ->getTransform() -> getPosition().set(_center.x + SINF(_yaw) * COSF(_pitch) * _distance,
                                                     _center.y + SINF(_pitch) * _distance,
                                                     _center.z + COSF(_yaw) * COSF(_pitch) * _distance);
    }
    inline void update(const float delta){
        if(Input::getMouseDown(MODEL_VIEW_MOUSE_BUTTON_MOVE)){
            _lastMousePosition = Input::getMousePosition();
        }
        else if(Input::isButtonDown(MODEL_VIEW_MOUSE_BUTTON_MOVE)){
            const Vector2f deltaPos = Input::getMousePosition() - _lastMousePosition;

            updatePos(deltaPos);
            _lastMousePosition = Input::getMousePosition();
        }
    }
    inline void update2(const float delta){
        if(Input::getMouseDown(MODEL_VIEW_MOUSE_BUTTON_MOVE) || Input::getMouseDown(MODEL_VIEW_MOUSE_BUTTON_ZOOM)){
            _lastMousePosition = Input::getMousePosition();
        }
        else if(Input::isButtonDown(MODEL_VIEW_MOUSE_BUTTON_MOVE)){
            Vector2f deltaPos = (Input::getMousePosition() - _lastMousePosition);

            if(deltaPos.length() > 0){
                deltaPos.normalize();
                _velocity += deltaPos * getRotSpeed();
            }
            _lastMousePosition = Input::getMousePosition();

            checkVelocity();
        }
        else if(Input::isButtonDown(MODEL_VIEW_MOUSE_BUTTON_ZOOM)){
            const float yOffset = Input::getMousePosition().y - _lastMousePosition.y;

            if(NEZ(yOffset)){
                _zoomVelocity -= yOffset * MODEL_VIEW_ZOOM_SPEED;
            }
            _lastMousePosition = Input::getMousePosition();
            checkVelocity();
        }
        else{
            if(NEZ(_velocity.x)){
                if(GABS(_velocity.x) < MODEL_VIEW_REFRACTION){
                    _velocity.x = 0;
                }
                else{
                    _velocity.x += _velocity.x < 0 ? MODEL_VIEW_REFRACTION : -MODEL_VIEW_REFRACTION;
                }
            }

            if(NEZ(_velocity.y)){
                if(GABS(_velocity.y) < MODEL_VIEW_REFRACTION){
                    _velocity.y = 0;
                }
                else {
                    _velocity.y += _velocity.y < 0 ? MODEL_VIEW_REFRACTION : -MODEL_VIEW_REFRACTION;
                }
            }
            if(NEZ(_zoomVelocity)){
                if(GABS(_zoomVelocity) < MODEL_VIEW_REFRACTION){
                    _zoomVelocity = 0;
                }
                else {
                    _zoomVelocity += _zoomVelocity < 0 ? MODEL_VIEW_REFRACTION : -MODEL_VIEW_REFRACTION;
                }
            }

            checkVelocity();
        }
        _distance += _zoomVelocity;
        _distance = GCLAMP(_distance, MODEL_VIEW_MIN_DISTANCE, MODEL_VIEW_MAX_DISTANCE);

        updatePos(_velocity);
    }
};
#endif //GAMEENGINE_MODELVIEW_H
