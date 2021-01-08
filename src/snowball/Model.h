#include "resource.h"
#include "rend/rend.h"
#include <memory>


namespace snowball
{
	struct Model : public Resource
	{
		void onLoad(const std::string _path);
		std::shared_ptr<rend::Mesh> getModel();

	private:
		std::shared_ptr<rend::Mesh> model; 
	};
}