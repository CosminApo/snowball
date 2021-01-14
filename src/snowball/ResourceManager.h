#pragma once

#include <vector>
#include <memory> /* smart pointer */
#include <string> /* std::string */
#include "Exception.h" /* Error handling */

namespace snowball
{
	// Forward declared structures.
	struct Resource;
	struct Core;
	/**
	* \brief The class responsible for managing Resource loading.
	* 
	* This class manages creating and loading in different Resources.
	* It also caches the Resources loaded in to prevent the same Resource from being
	* loaded in multiple times, which would waste memory.
	*/
	struct ResourceManager
	{		
		template <typename T> ///< Template function for loading a resourece stored at a specific path.
		std::shared_ptr<T> load(std::string _path)
		{
			/* Check if the resources was already loaded */
			for (size_t ri = 0; ri < resources.size(); ri++) // Loop through all the Resources loaded.
			{
				if (resources.at(ri)->getPath() == _path) // If the path of the Resource matches the one queried. 
				{
					std::shared_ptr<T> rtn = std::dynamic_pointer_cast<T>(resources.at(ri)); // Create a pointer to that Resource.
					if (rtn)
					{
						return rtn;
					}
				}
			}
			/* Create a new resource */
			std::shared_ptr<T> rs = std::make_shared<T>();  // Instantiate the new Resource.
			rs->setRm(self); // Set the Resource Manager reference to this one.
			rs->load(_path); // Load the Resource.

			resources.push_back(rs); // Add the Resource to the list of Resources loaded.
			return rs;				
		}
		template <typename T>
		std::shared_ptr<T> load()
		{
			/* Create a new resource */
			std::shared_ptr<T> rs = std::make_shared<T>();  // Instantiate the new Resource.
			rs->setRm(self); // Set the Resource Manager reference to this one.
			rs->load(); // Load the Resource.

			resources.push_back(rs); // Add the Resource to the list of Resources loaded.
			return rs;
		}
		void virtual onLoad(const std::string _path) {}; ///< Function that handles events on Load. To be overwritten by child classes.
		std::shared_ptr<Core> getCore(); ///< Returns a pointer to the Core object that this Resource Manager is linked to. 
		void setSelf(std::shared_ptr<ResourceManager> _self); ///< Set a smart pointer to itself.
		void setCore(std::shared_ptr<Core> _core); ///< Set a pointer to the Core object that this Resource Manager is linked to.
	private:
		std::vector<std::shared_ptr<Resource>> resources; ///< Stores a reference to each Resource loaded.
		std::weak_ptr<Core> core;  ///< Stores a reference to the Core structure this Resource Manager is linked to.
		std::shared_ptr<ResourceManager> self;  ///< Stores a smart pointer to itself. (Used as a better "this" keyword)
	};
}
