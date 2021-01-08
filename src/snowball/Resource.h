#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include <string>
#include "resourceManager.h"


namespace snowball 
{
	struct Resource
	{
		void load(const std::string _path);
		virtual void onLoad(const std::string _path);
		std::string getPath();
		void setRm(std::shared_ptr<ResourceManager> _rm);
		std::shared_ptr<ResourceManager> getRm();

	private:
		std::string path;
		std::weak_ptr<ResourceManager> rm;
	};
}

#endif