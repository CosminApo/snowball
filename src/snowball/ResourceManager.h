#pragma once

#include <vector>
#include <memory>
#include <string>


namespace snowball
{
	struct Resource;
	struct Core;
	struct ResourceManager
	{		

		template <typename T>
		std::shared_ptr<T> load(std::string _path)
		{
			//check if the resources was already loaded
			for (size_t ri = 0; ri < resources.size(); ri++)
			{
				if (resources.at(ri)->getPath() == _path)
				{
					std::shared_ptr<T> rtn = std::dynamic_pointer_cast<T>(resources.at(ri));
					if (rtn)
					{
						return rtn;
					}
				}
			}
			//if it wasnt then load it
			std::shared_ptr<T> rs = std::make_shared<T>();

			//TBF add to list only if loaded
			rs->setRm(self);
			rs->load(_path);

			resources.push_back(rs);
			return rs;				
		}

		template <typename T>
		std::shared_ptr<T> load()
		{
			//if it wasnt then load it
			std::shared_ptr<T> rs = std::make_shared<T>();

			//TBF add to list only if loaded
			rs->setRm(self);
			rs->load();

			resources.push_back(rs);
			return rs;
		}

		void virtual onLoad(const std::string _path) {};
		std::shared_ptr<Core> getCore();
		void setSelf(std::shared_ptr<ResourceManager> _self);
		void setCore(std::shared_ptr<Core> _core);
	private:
		std::vector<std::shared_ptr<Resource>> resources;
		std::weak_ptr<Core> core;
		std::shared_ptr<ResourceManager> self;

	};
}
