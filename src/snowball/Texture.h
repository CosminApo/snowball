#include "resource.h" /* Included for inheritance*/
#include "rend/rend.h" /* rend::Texture */
#include <memory> /* smart pointers */

namespace snowball
{
	/**
	* \brief The class responsible for loading textures.
	*
	* This class acts as a wrapper around the texture loader of Rend. It allows the user to load
	* a texture by specifying the path of the file.
	*/
	struct Texture : public Resource
	{
		void onLoad(const std::string _path); ///< Base loading function inherited from Resource. 
		std::shared_ptr<rend::Texture> getTexture(); ///< Returns the texture stored. 

	private:
		std::shared_ptr<rend::Texture> tex; ///< Stores a reference to a Rend Texture, used to store the texture data. 
	};
}