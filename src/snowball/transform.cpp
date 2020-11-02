#include "transform.h"

namespace snowball
{
    glm::mat4 Transform::getModelMat()
    {  
        //model = translation*rotation*scale
        model = glm::translate(model, position); 
        model = glm::scale(model, scale);
        model = glm::rotate(model, glm::radians(rotationAngle), rotationAxis);
        return model;
    }
    void Transform::onInitialize()
    {
        position = glm::vec3(0);
        rotationAngle = 0.f;
        rotationAxis = glm::vec3(0.0f, 1.0f, 0.f); //rotate around y by default
        scale = glm::vec3(1.f);
    }

    void Transform::setPosition(glm::vec3* _position)
    {
        position = *_position;
    }

    void Transform::setRotationAngle(float* _rotationAngle)
    {
        rotationAngle = *_rotationAngle;
    }

    void Transform::setScale(glm::vec3* _scale)
    {
        scale = *_scale;
    }

}
