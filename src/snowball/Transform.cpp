#include "transform.h"


namespace snowball
{
    glm::mat4 Transform::getModelMat()
    {  
        model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.f, 0.f));
        model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.f, 0.f));
        model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.f, 1.f));
        model = glm::translate(model, position);

        model = glm::scale(model, scale);
        return model;
    }
    glm::vec3 Transform::getPosition()
    {
        return position;
    }
    void Transform::onInitialize()
    {
        scale = glm::vec3(1, 1, 1);
 
    }
   
    void Transform::setPosition(glm::vec3 _position)
    {
        position = _position;    
    }


    void Transform::setScale(glm::vec3 _scale)
    {
        scale = _scale;
    }

    void Transform::setRotation(glm::vec3 _rotation)
    {
        rotation = _rotation;
    }

    void Transform::rotate(glm::vec3 _rotation)
    {
        rotation += _rotation;
    }

    void Transform::translate(glm::vec3 _translation)
    {
        glm::vec4 fwd = getTransform()->getModelMat() * glm::vec4(_translation, 0);
        position += glm::vec3(fwd);
    }

    
}
