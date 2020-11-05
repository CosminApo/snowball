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
			for (size_t ci = 0; ci < resources.size(); ci++)
			{
				if (resources.at(ci)->getPath() == _path)
				{
					std::shared_ptr<T> rtn = std::dynamic_pointer_cast<T>(components.at(ci));
					return rtn;
				}
			}
			//if it wasnt then load it
			std::shared_ptr<Resource> rs = std::make_shared<Resource>();

			if (rs->onLoad(_path) == 0)
			{
				//add to list only if loaded
				resources.push_back(rs);
			}			
		}

		void virtual onLoad(const std::string _path) {};

	private:
		std::vector<std::shared_ptr<Resource>> resources;
		std::weak_ptr<Core> core;

	};
}