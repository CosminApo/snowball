#include "core.h"

namespace snowball
{
	std::shared_ptr<Core> snowball::Core::initialize()
	{
		std::shared_ptr<Core> rtn = std::make_shared<Core>();
		return rtn;
	}
}

