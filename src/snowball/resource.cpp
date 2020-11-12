#include "resource.h"

namespace snowball
{
	void Resource::load(const std::string _path)
	{
		path = _path;
		onLoad(_path);
	}
	
	void Resource::onLoad(const std::string _path)
	{
	}
	std::string Resource::getPath()
	{
		return path;
	}
}
