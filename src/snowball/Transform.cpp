#include "transform.h"


namespace snowball
{
    glm::mat4 Transform::getModelMat()
    {  
        model = glm::mat4(1.0f); // Reset the model matrix.

        /*NOTE: Order of operations matters*/
        /*Apply the rotations*/
        model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.f, 0.f));
        model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.f, 0.f));
        model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.f, 1.f));

        model = glm::translate(model, position); // Apply the translation.

        model = glm::scale(model, scale); // Apply the scaling.
        return model;
    }
    glm::vec3 Transform::getPosition()
    {
        return position; // Returns the stored position.
    }
    void Transform::onInitialize()
    {
        scale = glm::vec3(1, 1, 1);
        position = glm::vec3(0,0,0);
    }
   
    void Transform::setPosition(glm::vec3 _position)
    {
        position = _position; // Set the position to a new value.
    }


    void Transform::setScale(glm::vec3 _scale)
    {
        scale = _scale; // Set the scale to a new value.
    }

    void Transform::setRotation(glm::vec3 _rotation)
    {
        rotation = _rotation; // Set the rotation to a new value.
    }

    void Transform::rotate(glm::vec3 _rotation)
    {
        rotation += _rotation; // Adds to the rotation.
    }

    void Transform::translate(glm::vec3 _translation)
    {
        /* Adds to the position a value converted to model space */
        glm::vec4 fwd = getTransform()->getModelMat() * glm::vec4(_translation, 0); 
        position += glm::vec3(fwd);
    }

    
}
