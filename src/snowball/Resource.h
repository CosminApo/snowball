#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include <string> /* std::string */
#include "resourceManager.h" /* Used for hierarchy navigation */

namespace snowball 
{
	/**
	* \brief The base class for the Resources.
	* 
	* Resources are external data inputs that can be used by the engine in some way.
	* Example of Resources include: 3D Models, Textures and Sound clips.
	*/
	struct Resource
	{
		void load(const std::string _path); ///< Base Resource loading function that takes in a path.
		void load(); ///< Base Resource loading function.
		virtual void onLoad(const std::string _path);  ///< Function that handles events on load with a path. To be overwritten in child classes.
		virtual void onLoad(); ///< Function that handles events on load. To be overwritten in child classes.
		std::string getPath(); ///< Returns the path of the Resource loaded.
		void setRm(std::shared_ptr<ResourceManager> _rm); ///< Sets the Resource Manager this Resource is linked to.
		std::shared_ptr<ResourceManager> getRm(); ///< Returns the Resource Manager this Resource is linked to.

	private:
		std::string path; ///< Stores the path where this Resource can be found.
		std::weak_ptr<ResourceManager> rm; ///< Stores a reference to the Resource Manager this Resource is linked to. Used for hierarchy navigation.
	};
}

#endif