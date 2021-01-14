#include "resource.h"

namespace snowball
{
	void Resource::load(const std::string _path)
	{
		path = _path;
		onLoad(_path);
	}

	void Resource::load()
	{
		onLoad();
	}
	
	void Resource::onLoad(const std::string _path)
	{
	}
	void Resource::onLoad()
	{
	}
	std::string Resource::getPath()
	{
		return path;
	}
	void Resource::setRm(std::shared_ptr<ResourceManager> _rm)
	{
		rm = _rm;
	}
	std::shared_ptr<ResourceManager> Resource::getRm()
	{
		return rm.lock();
	}
}
