#include "resource.h"
#include "rend/rend.h"
#include <memory>


namespace snowball
{
	struct RenderTexture : public Resource
	{
		void onLoad();
		std::shared_ptr<rend::RenderTexture> getTexture();

	private:
		std::shared_ptr<rend::RenderTexture> tex;
	};
}