#include "component.h"
#include <memory>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

namespace snowball
{
	struct Transform : public Component
	{

		void onInitialize();

		void translate(glm::vec3 _translation);
		void rotate(glm::vec3 _rotation);


		glm::mat4 getModelMat();
		glm::vec3 getPosition();


		void setPosition(glm::vec3 _position);
		void setScale(glm::vec3 _scale);
		void setRotation(glm::vec3 _rotation);
	private:
		//model = translation*rotation*scale
		glm::mat4 model;

		//init to 1 to avoid * 0
		glm::vec3 position;
		glm::vec3 scale;
		glm::vec3 rotation;

	};
}