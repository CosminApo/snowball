#include <memory>
#include <vector>
#include <SDL.h>
#include <rend/rend.h>

namespace snowball
{
	struct Entity;
	struct Renderer;

	struct Core
	{
		friend struct ::snowball::Renderer;

		static std::shared_ptr<Core> initialize(); //static to initialize without object
		std::shared_ptr<Entity> addEntity();
		void start();
	private:
		SDL_Window* window;
		SDL_GLContext glContext;
		std::weak_ptr<Core> self;
		std::shared_ptr<rend::Context> context; //TODO inside contexts destructore, delete window and glContext
		std::vector<std::shared_ptr<Entity>> entities;
	};
}