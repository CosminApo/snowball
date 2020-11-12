#include <string>
#include "resourceManager.h"


namespace snowball 
{
	struct Resource
	{
		void load(const std::string _path);
		virtual void onLoad(const std::string _path);
		std::string getPath();
	private:
		std::string path;
		std::weak_ptr<ResourceManager> rm;
	};
}