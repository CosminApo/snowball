#include "component.h"
#include <rend/rend.h>
#include <memory>
#include <iostream>

namespace snowball
{
	struct Renderer : public Component
	{
		void onInitialize();
		void onRender();

	private:
		std::shared_ptr<rend::Shader> shader;
		std::shared_ptr<rend::Mesh> shape; //TBA add resource type with mesh inside

	};
}