#include <string>
#include "resourceManager.h"


namespace snowball 
{
	struct Resource : public ResourceManager
	{
	private:
		std::string path;
		std::weak_ptr<ResourceManager> rm;
	};
}