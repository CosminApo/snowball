#include <memory>
#include <vector>
#include <SDL.h>
#include <rend/rend.h>
#include "screen.h"
#include <AL/al.h>
#include <AL/alc.h>
#include "resourceManager.h"
#include "keyboard.h"

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
		std::shared_ptr<ResourceManager> getRm();
		std::shared_ptr<Keyboard> getKeyboard();
		void start();
	private:
		/*SDL related*/
		SDL_Window* window;
		SDL_GLContext glContext;
		std::shared_ptr<Screen> sc;
		//////

		/*Sound related (OPENAL)*/
		ALCdevice* device;
		ALCcontext* alContext;

		/////

		std::shared_ptr<Keyboard> kb;
		std::shared_ptr<ResourceManager> rm;
		std::weak_ptr<Core> self; 
		std::shared_ptr<rend::Context> context; //TODO inside contexts destructor, delete window and glContext
		std::vector<std::shared_ptr<Entity>> entities;
	};
}