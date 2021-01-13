#include "core.h"
#include "entity.h"
#include "UIElement.h"
#include "Collider.h"
#include "Renderer.h"
#include "Button.h"

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
		rtn->mouse = std::make_shared<Mouse>();

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
				else if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					int x, y;
					SDL_GetMouseState(&x, &y);
					mouse->setXpos(x);
					mouse->setYpos(y);
					checkButtonPressed();
				}
			}
			for (size_t ei = 0; ei < entities.size(); ei++)
			{
				entities.at(ei)->tick();
			}

			handleCollision();

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

	void Core::checkButtonPressed()
	{
		int x = mouse->getXpos();
		int y = mouse->getYpos();
		for (std::vector<std::shared_ptr<UIElement>>::iterator btn = buttons.begin(); btn != buttons.end(); btn++)
		{
			if (x > (*btn)->getXpos() && x < (*btn)->getXpos() + (*btn)->getWidth()*2)
			{
				if (y > (*btn)->getYpos()  && y < (*btn)->getYpos() + (*btn)->getHeight()*2)
				{
					(*btn)->setIsClicked(true);
				}
			}
		}
	}

	void Core::addButton(std::shared_ptr<UIElement> _btn)
	{
		buttons.push_back(_btn);
	}

	void Core::handleCollision()
	{
		for (size_t et = 0; et < entities.size(); et++) //et = Entity tested
		{
			if (entities.at(et)->getComponent<Collider>())
			{
				if (entities.at(et)->getComponent<Collider>()->getCollision()) //if et has collision
				{
					for (size_t eq = 0; eq < entities.size(); eq++) //eq = entity Queried
					{
						if (et != eq)
						{
							if (entities.at(eq)->getComponent<Collider>())
							{
								if (entities.at(eq)->getComponent<Collider>()->getCollision()) //check against all other entities with collision
								{
									if (checkXCollision(entities.at(et), entities.at(eq)))
									{
										if (checkYCollision(entities.at(et), entities.at(eq)))
										{
											if (checkZCollision(entities.at(et), entities.at(eq)))
											{
												entities.at(et)->getComponent<Collider>()->onCollision();
											}		
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	bool Core::checkXCollision(std::shared_ptr<Entity> _e1, std::shared_ptr<Entity> _e2)
	{
		bool rtn = false;

		float et_posX = _e1->getComponent<Transform>()->getPosition().x;
		float et_width = _e1->getComponent<Renderer>()->getShape()->getWidth();

		float eq_posX = _e2->getComponent<Transform>()->getPosition().x;
		float eq_width = _e2->getComponent<Renderer>()->getShape()->getWidth();

		if (et_posX - et_width/2 < eq_posX + eq_width/2)
		{
			if (et_posX + et_width/2 > eq_posX - eq_width/2)
			{
				rtn = true;		
			}
		}

		return rtn;
	}

	bool Core::checkYCollision(std::shared_ptr<Entity> _e1, std::shared_ptr<Entity> _e2)
	{
		bool rtn = false;
		float et_posY = _e1->getComponent<Transform>()->getPosition().y;
		float et_height = _e1->getComponent<Renderer>()->getShape()->getWidth();

		float eq_posY = _e2->getComponent<Transform>()->getPosition().y;
		float eq_height = _e2->getComponent<Renderer>()->getShape()->getWidth();

		if (et_posY + et_height > eq_posY - eq_height)
		{
			if (et_posY - et_height < eq_posY + eq_height)
			{
				rtn = true;
			}
		}
		return rtn;
	}

	bool Core::checkZCollision(std::shared_ptr<Entity> _e1, std::shared_ptr<Entity> _e2)
	{
		bool rtn = false;
		float et_posZ = _e1->getComponent<Transform>()->getPosition().z;
		float et_depth = _e1->getComponent<Renderer>()->getShape()->getDepth();

		float eq_posZ = _e2->getComponent<Transform>()->getPosition().z;
		float eq_depth = _e2->getComponent<Renderer>()->getShape()->getDepth();

		if (et_posZ + et_depth/2 > eq_posZ - eq_depth/2)
		{
			if (et_posZ - et_depth/2 < eq_posZ + eq_depth/2)
			{
				rtn = true;
			}
		}
		return rtn;
	}

}

