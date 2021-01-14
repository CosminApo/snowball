#include "Resource.h" /* Included for inheritance */
#include "rend/rend.h" /* rend::Shader */


namespace snowball
{
	/**
	* \brief The class responsible for loading Shaders.
	* 
	* This class acts as a wrapper around the shader loader of Rend. It allows the user to load 
	* a shader by specifying the path of the file. 
	*/
	struct Shader : public Resource
	{
		void onLoad(const std::string _path);  ///< Base loading function inherited from Resource.
		std::shared_ptr<rend::Shader> getShader(); ///< Returns the shader stored.
	private:
		std::shared_ptr<rend::Shader> shader; ///< Stores the shader created. Used in rendering.
	};
}