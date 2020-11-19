#include <vector>
#include "component.h"
#include <memory>
#include "transform.h"
#include <string>


namespace snowball
{
	struct Component;
	struct Core;

	struct Entity
	{

		friend struct ::snowball::Core;

		template <typename T>
		std::shared_ptr<T> addComponent()
		{
			std::shared_ptr<T> rtn = std::make_shared<T>();
			rtn->entity = self;
			components.push_back(rtn);

			rtn->onInitialize();

			return rtn;
		}

		template <typename T>
		std::shared_ptr<T> addComponent(const std::string& _path)
		{
			std::shared_ptr<T> rtn = std::make_shared<T>();
			rtn->entity = self;
			components.push_back(rtn);

			rtn->onInitialize(_path);

			return rtn;
		}


		template <typename T>
		std::shared_ptr<T> getComponent()
		{
			//use it by making a shared ptr to store it in
			for (size_t ci = 0; ci < components.size(); ci++)
			{
				std::shared_ptr<T> rtn = std::dynamic_pointer_cast<T>(components.at(ci));
				if (rtn)
				{
					return rtn;
				}
			}
			//add exception
			abort();
		}
		
		void tick();
		void render();
		

		std::shared_ptr<Core> getCore();

	private:
		std::vector<std::shared_ptr<Component>> components;
		std::weak_ptr<Core> core;
		std::weak_ptr<Entity> self;

	};
}

