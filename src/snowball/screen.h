#include <memory>
#include <iostream>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

namespace snowball
{
	struct Screen
	{
		int getWindow_Height();
		int getWindow_Width();
		glm::mat4 getProjMat();
	private:
		//sdl window params
		int window_width = 800; 
		int window_height = 800; 

		glm::mat4 proj;
	};
}