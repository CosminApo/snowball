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
		rtn->rm->setSelf(rtn->rm);
		rtn->rm->setCore(rtn);
		rtn->kb = std::make_shared<Keyboard>();
		rtn->window = SDL_CreateWindow("Snowball", //title
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, //pos
			rtn->sc->getWindow_Height(), rtn->sc->getWindow_Width(),  //scale
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN| SDL_WINDOW_RESIZABLE); //flags

		if (!rtn->window)
		{
			throw snowball::Exception("Failed to create window");
		}

		rtn->glContext = SDL_GL_CreateContext(rtn->window);

		if (!rtn->glContext)
		{
			throw snowball::Exception("Failed to create OpenGL context");
		}

		rtn->context = rend::Context::initialize();

		// Open the default device 
		rtn->device = alcOpenDevice(NULL);
		if (!rtn->device)
		{
	  		throw snowball::Exception("Failed to open default sound device");
		}
		
		rtn->alContext = alcCreateContext(rtn->device, NULL);
		if (!rtn->alContext)
		{
			alcCloseDevice(rtn->device);
			throw snowball::Exception("Failed to create sound context");
		}
		if (!alcMakeContextCurrent(rtn->alContext))
		{
			alcDestroyContext(rtn->alContext);
			alcCloseDevice(rtn->device);
			throw snowball::Exception("Failed to make context current");
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
	std::shared_ptr<Camera> Core::getCamera()
	{
		return currentCam.lock();
	}
	std::shared_ptr<Camera> Core::getSCamera()
	{
		return cameras.at(0).lock();
	}
	void Core::setMainCamera(std::shared_ptr<Camera> _cam)
	{
		currentCam = _cam;
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
					kb->downKeys.push_back(e.key.keysym.sym);
				}
				else if (e.type == SDL_KEYUP)
				{
					kb->deleteKey(e.key.keysym.sym);
					kb->upKeys.push_back(e.key.keysym.sym);
				}
			}
			for (size_t ei = 0; ei < entities.size(); ei++)
			{
				entities.at(ei)->tick();
			}

			glClearColor(0.3f, 0.4f, 0.8f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //for future camera tech, clear screen after activating render buffer
			glViewport(0,0, sc->getWindow_Width(),sc->getWindow_Height());
			for (size_t ci = 0; ci < cameras.size(); ci++) //tbc iterator
			{
				currentCam = cameras.at(ci);
				glClear(GL_DEPTH_BUFFER_BIT); //for future camera tech, clear screen after activating render buffer

				for (size_t ei = 0; ei < entities.size(); ei++)
				{
					entities.at(ei)->render();
				}
				glViewport(0, 0, 200, 200);

			}

		

			SDL_GL_SwapWindow(window);

			//Clean keyboard at end of frame
			kb->downKeys.clear();
			kb->upKeys.clear();

		}
	}

}

