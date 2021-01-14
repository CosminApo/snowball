#include "Component.h" /* Included for inheritance */
#include <rend/rend.h> /* rend::RendTexture */

namespace snowball
{
	/**
	* \brief The class responsible for managing the cameras in the engine.
	* 
	* This class creates virtual cameras that the engine can use to simulate
	* points of view. It does this by providing a View Matrix to be used
	* in a OpenGL shader.
	*/
	struct Camera : public Component
	{
		void onInitialize(); ///< Base initialize function inherited from component.
		void onInitialize(bool _isMain); ///< Initialize function that lets the user set this camera as main camera.
		rend::mat4 getView(); ///< Generates and returns the view matrix.
		std::shared_ptr<rend::RenderTexture> getRenderTexture(); ///< Returns the Render Texture stored. Used for rendering on a specific target.
		void addRenderTexture(); //Creates a render texture, stores it in a member variable.

	private:
		std::shared_ptr<rend::RenderTexture> renderTexture; ///< Stores a render texture. Used for rendering on a specific target.
	}; 
}