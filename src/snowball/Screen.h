#include <memory> /* smart pointers */
#include <glm/glm.hpp> /* glm::mat4 */
#include "glm/gtc/matrix_transform.hpp" /* glm::ortho, glm::perspective */

namespace snowball
{
	/**
	* \brief The class responsible for managing the main rendering output target.
	* 
	* This class stores information about the window created by SDL. It also provides
	* the projection matrix used by the shader to translate the model coordinates to Clip space.
	*/
	struct Screen
	{
		int getWindow_Height(); ///< Returns the height of the output window.
		int getWindow_Width(); ///< Returns the width of the output window.
		glm::mat4 getProjMat(); ///< Creates and returns a Perspective projection matrix.
		glm::mat4 getOrthoMat(); ///< Creates and returns an Orthographic projection matrix.
	private:
		int window_width = 800; ///< Stores the width of the output window.
		int window_height = 800; ///< Stores the height of the output window.
		glm::mat4 proj; ///< Stores the current projection matrix.
	};
}