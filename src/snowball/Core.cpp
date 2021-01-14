#include "core.h"
#include "entity.h"
#include "UIElement.h"
#include "Collider.h"
#include "Renderer.h"

namespace snowball
{
	std::shared_ptr<Core> snowball::Core::initialize()
	{
		std::shared_ptr<Core> rtn = std::make_shared<Core>(); // Create a new Core.
		rtn->self = rtn; // Set a reference to itself.
		rtn->sc = std::make_shared<Screen>(); // Initialize the Screen member.

		rtn->rm = std::make_shared<ResourceManager>(); // Initialize the Resource Manager member.
		rtn->rm->setSelf(rtn->rm); // Set the Self pointer of the Resource Manager.
		rtn->rm->setCore(rtn); // Set the Core pointer of the Resource Manager.

		rtn->kb = std::make_shared<Keyboard>(); // Initialize the Keyboard input manager.
		rtn->mouse = std::make_shared<Mouse>(); // Initialize the Mouse input manager.

		rtn->window = SDL_CreateWindow(									  //Create a new SDL window.
			"Snowball",												      // Title of the window.
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,		      // Position of the window.
			rtn->sc->getWindow_Height(), rtn->sc->getWindow_Width(),      // Scale of the window.
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN| SDL_WINDOW_RESIZABLE);  // SDL flags.
		if (!rtn->window) // Error checking.
		{
			throw snowball::Exception("Failed to create window");
		}

		rtn->glContext = SDL_GL_CreateContext(rtn->window); //Create a new OpenGL context.
		if (!rtn->glContext) // Error checking.
		{
			throw snowball::Exception("Failed to create OpenGL context");
		}

		rtn->context = rend::Context::initialize(); // Create a new Rend context.

		rtn->device = alcOpenDevice(NULL); // Open the default sound device.
		if (!rtn->device) // Error checking.
		{
	  		throw snowball::Exception("Failed to open default sound device");
		}
		
		rtn->alContext = alcCreateContext(rtn->device, NULL); //Create a new OpenAL context.
		if (!rtn->alContext) // Error checking.
		{
			alcCloseDevice(rtn->device);
			throw snowball::Exception("Failed to create sound context");
		}
		if (!alcMakeContextCurrent(rtn->alContext)) // Enable OpenAL context and check for errors.
		{
			alcDestroyContext(rtn->alContext);
			alcCloseDevice(rtn->device);
			throw snowball::Exception("Failed to make context current");
		}

		return rtn;
	}
	std::shared_ptr<Entity> Core::addEntity()
	{
		std::shared_ptr<Entity> rtn = std::make_shared<Entity>(); // Create a new Entity.
		rtn->core = self; // Set the Core pointer of the Entity.
		rtn->self = rtn; // Set the Self pointer of the Entity.
		std::shared_ptr<Transform> tc = rtn->addComponent<Transform>(); // By default, add a Transform component.
		entities.push_back(rtn); //Add the Entity to the list of Entities.
		return rtn;
	}
	std::shared_ptr<Screen> Core::getScreen()
	{
		return sc; // Return the stored Screen.
	}
	std::shared_ptr<ResourceManager> Core::getRm()
	{
		return self.lock()->rm; // Return the stored Resource Manager.
	}
	std::shared_ptr<Keyboard> Core::getKeyboard()
	{
		return self.lock()->kb; // Return the stored Keyboard input manager.
	}
	std::shared_ptr<Camera> Core::getCamera()
	{
		return currentCam.lock(); // Return the current camera.
	}
	void Core::setMainCamera(std::shared_ptr<Camera> _cam)
	{
		currentCam = _cam; // Sets the main camera.
	}
	void Core::start()
	{		
		bool running = true; // Set that its running. 
		SDL_Event e = { 0 }; // Used to store SDL events.
		while (running)
		{
			/* Handle SDL events */
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

			for (size_t ei = 0; ei < entities.size(); ei++) // Loop through all the entities.
			{
				entities.at(ei)->tick(); // Call the tick function.
			}

			handleCollision(); // Handle any collision.

			glClearColor(0.3f, 0.4f, 0.8f, 1.0f); // Clear the screen.
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the buffer.
			glViewport(0,0, sc->getWindow_Width(),sc->getWindow_Height()); // Set the viewport.
			for (size_t ci = 0; ci < cameras.size(); ci++) // Loop through all the cameras.
			{
				currentCam = cameras.at(ci); // Set the current camera.
				glClear(GL_DEPTH_BUFFER_BIT); // Clear the depth buffer.

				for (size_t ei = 0; ei < entities.size(); ei++) // Loop through all the entities.
				{
					entities.at(ei)->render(); // Call the render function.
				}
				glViewport(0, 0, 200, 200); // Set a different view port for the second camera.
			}

			SDL_GL_SwapWindow(window); // Refresh window.

			/*Clean keyboard inputs at end of frame*/
			kb->downKeys.clear();
			kb->upKeys.clear();
		}
	}

	void Core::checkButtonPressed()
	{
		int x = mouse->getXpos(); // Get the current X position of the cursor.
		int y = mouse->getYpos(); // Get the current Y position of the cursor.
		for (std::vector<std::shared_ptr<UIElement>>::iterator btn = buttons.begin(); btn != buttons.end(); btn++) // Loop through all the UI elements.
		{
			if (x > (*btn)->getXpos() && x < (*btn)->getXpos() + (*btn)->getWidth()*2) // Check if the X coordinates match.
			{
				if (y > (*btn)->getYpos()  && y < (*btn)->getYpos() + (*btn)->getHeight()*2) // Check if the Y coordinates match.
				{
					(*btn)->setIsClicked(true);
				}
			}
		}
	}

	void Core::addButton(std::shared_ptr<UIElement> _btn)
	{
		buttons.push_back(_btn); // Add a new button.
	}

	void Core::handleCollision()
	{
		for (size_t et = 0; et < entities.size(); et++) // Loop through all the entities of the scene.
		{
			if (entities.at(et)->getCollider()) // Get those with a collider.
			{
				if (entities.at(et)->getComponent<Collider>()->getCollision()) // Check if collision is enabled.
				{
					for (size_t eq = 0; eq < entities.size(); eq++) // Loop through all the entities.
					{
						if (et != eq) // If its not testing against itself.
						{
							if (entities.at(eq)->getCollider()) // If the other entity has a collider.
							{
								if (entities.at(eq)->getComponent<Collider>()->getCollision()) // Check if collision is enabled.
								{
									if (CollisionUTILS::checkXCollision(entities.at(et), entities.at(eq))) // Check for collision in the X axis.
									{
										if (CollisionUTILS::checkYCollision(entities.at(et), entities.at(eq))) // Check for collision in the Y axis.
										{
											if (CollisionUTILS::checkZCollision(entities.at(et), entities.at(eq))) // Check for collision in the Z axis.
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


}

