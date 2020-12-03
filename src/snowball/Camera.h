#include "Component.h"

#include <rend/rend.h>

namespace snowball
{
	struct Camera : public Component
	{
		void onInitialize();
		rend::mat4 getView();
	};
}