#include "transform.h"

namespace snowball
{
    glm::mat4 Transform::getModelMat()
    {  
        //model = translation*rotation*scale
        model = glm::translate(model, position); 


        model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.f, 0.f));
        model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.f, 0.f));
        model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.f, 1.f));

        model = glm::scale(model, scale);
        return model;
    }
    void Transform::onInitialize()
    {
        position = glm::vec3(0);
        scale = glm::vec3(1.f);
        model = glm::mat4(1.0f);
        rotation = glm::vec3(1.f);
    }

    void Transform::setPosition(glm::vec3* _position)
    {
        position = *_position;
    }


    void Transform::setScale(glm::vec3* _scale)
    {
        scale = *_scale;
    }

    void Transform::setRotation(glm::vec3* _rotation)
    {
        rotation = *_rotation;
    }

}
