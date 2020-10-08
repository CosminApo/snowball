#include <memory>
#include <vector>

namespace snowball
{
	struct Entity;

	struct Core
	{
		static std::shared_ptr<Core> initialize(); //static to initialize without object
		std::shared_ptr<Entity> addEntity();
		void start();
	private:
		std::vector<std::shared_ptr<Entity>> entities;
	};
}