#include "resource.h"
#include "rend/rend.h"
#include <memory>


namespace snowball
{
	struct Texture : public Resource
	{
		void onLoad(const std::string _path);
		std::shared_ptr<rend::Texture> getTexture();

	private:
		std::shared_ptr<rend::Texture> tex;
	};
}