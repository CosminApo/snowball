#include "screen.h"
namespace snowball
{
	int Screen::getWindow_Height()
	{
		return window_height;
	}

	int Screen::getWindow_Width()
	{
		return window_width;
	}

	glm::mat4 Screen::getProjMat()
	{
		proj = glm::perspective(
			glm::radians(90.0f), // The vertical Field of View, in radians: the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
			(float)( window_width / window_height),       // Aspect Ratio. Depends on the size of your window. 
			0.1f,              // Near clipping plane.
			100.0f             // Far clipping plane. 
		);
		return proj;
	}
	glm::mat4 Screen::getOrthoMat()
	{
		proj = glm::ortho(
			0.0f,
			(float)(window_width),
			0.0f,
			(float)(window_height),
			-100.1f,
			100.f
		);
		return proj;
	}
}
