#include "resource.h" /* Included for inheritance */
#include "rend/rend.h" /* rend::Mesh */
#include <memory> /* smart pointers */


namespace snowball
{
	/**
	* \brief The class responsible for loading 3D / 2D models. 
	* 
	* This class acts as a wrapper around the model loader of Rend. It allows the user to load 
	* a model by specifying the path of the .obj file. 
	*/
	struct Model : public Resource
	{
		void onLoad(const std::string _path); ///< Base loading function inherited from Resource. 
		std::shared_ptr<rend::Mesh> getModel(); ///< Returns the model stored. 

	private:
		std::shared_ptr<rend::Mesh> model;  ///< Stores a reference to a Rend Mesh, used to store the 3D model. 
	};
}