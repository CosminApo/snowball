#include "screen.h"
namespace snowball
{
	int Screen::getWindow_Height()
	{
		return window_height; // Return the stored window height.
	}

	int Screen::getWindow_Width()
	{
		return window_width; // Return the stored window width.
	}

	glm::mat4 Screen::getProjMat()
	{
		proj = glm::perspective(
			glm::radians(90.0f),					// The vertical Field of View, in radians: the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
			(float)( window_width / window_height), // Aspect Ratio. Depends on the size of your window. 
			0.1f,								    // Near clipping plane.
			100.0f								    // Far clipping plane. 
		);
		return proj;
	}
	glm::mat4 Screen::getOrthoMat()
	{
		proj = glm::ortho(
			0.0f,						// Minimum X coordinate.
			(float)(window_width),		// Maximum X coordinate.
			(float)(window_height),		// Minimum Y coordinate.
			0.0f,						// Maximum Y coordinate.
			-100.1f,					// Near clipping plane.
			100.f						// Far clipping plane.
		);
		return proj;
	}
}
