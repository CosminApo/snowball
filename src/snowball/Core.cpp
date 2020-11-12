#include "core.h"
#include "entity.h"

namespace snowball
{

	std::shared_ptr<Core> snowball::Core::initialize()
	{
		std::shared_ptr<Core> rtn = std::make_shared<Core>();
		rtn->self = rtn;
		rtn->sc = std::make_shared<Screen>();
		rtn->rm = std::make_shared<ResourceManager>();
		rtn->kb = std::make_shared<Keyboard>();
		rtn->window = SDL_CreateWindow("Snowball", //title
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, //pos
			rtn->sc->getWindow_Height(), rtn->sc->getWindow_Width(),  //scale
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN| SDL_WINDOW_RESIZABLE); //flags

		if (!rtn->window)
		{
			throw rend::Exception("Failed to create window");
		}

		rtn->glContext = SDL_GL_CreateContext(rtn->window);

		if (!rtn->glContext)
		{
			throw rend::Exception("Failed to create OpenGL context");
		}

		rtn->context = rend::Context::initialize();

		// Open the default device 
		rtn->device = alcOpenDevice(NULL);
		if (!rtn->device)
		{
	  		throw rend::Exception("Failed to open default sound device");
		}
		
		rtn->alContext = alcCreateContext(rtn->device, NULL);
		if (!rtn->alContext)
		{
			alcCloseDevice(rtn->device);
			throw rend::Exception("Failed to create sound context");
		}
		if (!alcMakeContextCurrent(rtn->alContext))
		{
			alcDestroyContext(rtn->alContext);
			alcCloseDevice(rtn->device);
			throw rend::Exception("Failed to make context current");
		}

		//todo close this at the end

		return rtn;
	}
	std::shared_ptr<Entity> Core::addEntity()
	{
		std::shared_ptr<Entity> rtn = std::make_shared<Entity>();
		rtn->core = self;
		rtn->self = rtn;
		std::shared_ptr<Transform> tc = rtn->addComponent<Transform>();
		entities.push_back(rtn);
		return rtn;
	}
	std::shared_ptr<Screen> Core::getScreen()
	{
		return sc;
	}
	std::shared_ptr<ResourceManager> Core::getRm()
	{
		return self.lock()->rm;
	}
	std::shared_ptr<Keyboard> Core::getKeyboard()
	{
		return self.lock()->kb;
	}
	void Core::start()
	{		
		bool running = true;
		SDL_Event e = { 0 };
		while (running)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					running = false;
				}
				else if (e.type == SDL_KEYDOWN)
				{
					kb->keys.push_back(e.key.keysym.sym);
				}
				else if (e.type == SDL_KEYUP)
				{
					kb->deleteKey(e.key.keysym.sym);
				}
			}
			for (size_t ei = 0; ei < entities.size(); ei++)
			{
				entities.at(ei)->tick();
			}

			glClearColor(0.3f, 0.4f, 0.8f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			for (size_t ei = 0; ei < entities.size(); ei++)
			{
				entities.at(ei)->render();
			}

			SDL_GL_SwapWindow(window);
		}
	}
}
