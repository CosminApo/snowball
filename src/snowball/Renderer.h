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
		void setModel(std::string _path);
		void setShader(std::string _path);
		void setTexture(std::string _path);

	private:
		std::shared_ptr<rend::Shader> shader;
		std::shared_ptr<rend::Mesh> shape; //TBA add resource type with mesh inside
											// maybe rename shape to model
		std::shared_ptr<rend::Texture> tex;

	};
}