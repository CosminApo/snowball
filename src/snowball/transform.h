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
		void setRotationAngle(float* _rotationAngle);
		void setScale(glm::vec3* _scale);

	private:
		//model = translation*rotation*scale
		glm::mat4 model;

		//init to 1 to avoid * 0
		glm::vec3 position;
		float rotationAngle;
		glm::vec3 rotationAxis; //rotate around y by default
		glm::vec3 scale;

	};
}