#include <memory>


namespace snowball
{
	struct Core
	{
		static std::shared_ptr<Core> initialize(); //static to initialize without object
	};
}