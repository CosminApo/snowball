#include "resource.h"

namespace snowball
{
	void Resource::load(const std::string _path)
	{
		path = _path; // Store the path locally.
		onLoad(_path); // Call the on load function.
	}

	void Resource::load()
	{
		onLoad(); // Call the on load function.
	}
	
	/* Both the onLoad functions are empty since they have to be overwritten by child classes*/
	void Resource::onLoad(const std::string _path)
	{
	}
	void Resource::onLoad()
	{
	}
	std::string Resource::getPath()
	{
		return path; // Return the path of the Resource.
	}
	void Resource::setRm(std::shared_ptr<ResourceManager> _rm)
	{
		rm = _rm; // Set the Resource Manager.
	}
	std::shared_ptr<ResourceManager> Resource::getRm()
	{
		if (rm.lock() == NULL)
		{
			throw snowball::Exception("FATAL: Hierarchy broke!");
		}
		return rm.lock(); // Return the Resource Manager.
	}
}
