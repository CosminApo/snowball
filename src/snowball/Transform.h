#include "component.h"
#include <memory>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

namespace snowball
{
	struct Transform : public Component
	{
		glm::mat4 getModelMat();
		void onInitialize();
		void setPosition(glm::vec3* _position);
		void setScale(glm::vec3* _scale);
		void setRotation(glm::vec3* _rotation);
	private:
		//model = translation*rotation*scale
		glm::mat4 model;

		//init to 1 to avoid * 0
		glm::vec3 position;
		glm::vec3 scale;
		glm::vec3 rotation;

	};
}