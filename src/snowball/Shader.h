#include "Resource.h"
#include "rend/rend.h"


namespace snowball
{
	struct Shader : public Resource
	{
		void onLoad(const std::string _path);
		std::shared_ptr<rend::Shader> getShader();

	private:
		std::shared_ptr<rend::Shader> shader;
	};
}