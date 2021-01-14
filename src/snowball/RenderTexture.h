#include "resource.h" /* Included for inheritance */
#include "rend/rend.h" /* rend::RenderTexture */
#include <memory> /* smart pointers */

namespace snowball
{
	/**
	* \brief The class responsible for generating Render Textures.
	* 
	* This class acts as a wrapper around the render texture generator of Rend.
	* Render Textures are used as custom render outputs, useful for features such as GUI.
	*/
	struct RenderTexture : public Resource
	{
		void onLoad(); ///< Base loading function inherited from Resource. 
		std::shared_ptr<rend::RenderTexture> getTexture(); ///< Returns the stored Render Texture.
	private:
		std::shared_ptr<rend::RenderTexture> tex; ///< Stores the Render Texture.
	};
}