#include "resource.h"
#include "rend/rend.h"
#include <memory>


namespace snowball
{
	struct RenderTexture : public Resource
	{
		void onLoad(const std::string _path);
		std::shared_ptr<rend::RenderTexture> getTexture();

	private:
		std::shared_ptr<rend::RenderTexture> tex;
	};
}