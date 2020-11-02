#include <memory>
#include <vector>
#include <SDL.h>
#include <rend/rend.h>
#include "screen.h"


namespace snowball
{
	//forward declare to add components on entity creation
	struct Entity;
	struct Renderer;
	struct Transform;


	struct Core
	{
		friend struct ::snowball::Renderer;
		static std::shared_ptr<Core> initialize(); //static to initialize without object
		std::shared_ptr<Entity> addEntity();
		std::shared_ptr<Screen> getScreen();
		void start();
	private:
		/*SDL related*/
		SDL_Window* window;
		SDL_GLContext glContext;
		std::shared_ptr<Screen> sc;
		//////

		std::weak_ptr<Core> self; 
		std::shared_ptr<rend::Context> context; //TODO inside contexts destructor, delete window and glContext
		std::vector<std::shared_ptr<Entity>> entities;
	};
}