#include "Component.h"

#include <rend/rend.h>

namespace snowball
{
	struct Camera : public Component
	{
		void onInitialize();
		void onInitialize(bool _isMain);
		rend::mat4 getView();
		std::shared_ptr<rend::RenderTexture> getRenderTexture();
		void addRenderTexture(std::string _path);

	private:
		std::shared_ptr<rend::RenderTexture> renderTexture;
	};
}