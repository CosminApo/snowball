#include "component.h" /* Included for inheritance */
#include <memory> /* smart pointers */
#include <glm/glm.hpp> /* glm::vec3*/
#include "glm/gtc/matrix_transform.hpp" /*  glm::rotate, glm::translate, glm::scale */

namespace snowball
{
	/**
	* \brief The class responsible for managing the position of the Entity.
	* 
	* This class stores the position of the Entity in the render space.
	* It provides the Model matrix used by the shader to translate the model coordinates
	* to model space.
	*/
	struct Transform : public Component
	{
		void onInitialize(); ///< Base initialize function inherited from Component. Used for creating the object.
		void translate(glm::vec3 _translation); ///< Moves the Entity in the direction provided.
		void rotate(glm::vec3 _rotation); ///< Rotates the Entity in the direction provided.
		glm::mat4 getModelMat(); ///< Returns the Model matrix stored.
		glm::vec3 getPosition(); ///< Returns the position stored.
		void setPosition(glm::vec3 _position); ///< Sets the position to a new value.
		void setScale(glm::vec3 _scale); ///< Sets the scale to a new value.
		void setRotation(glm::vec3 _rotation); ///< Sets the rotation to a new value.
	private:
		glm::mat4 model; ///< The Model matrix of the Entity. Where all the transformations are stored.
		glm::vec3 position; ///< Stores the position of the Entity.
		glm::vec3 scale; ///< Stores the scale of the Entity.
		glm::vec3 rotation; ///< Stores the rotation of the Entity.
	};
}