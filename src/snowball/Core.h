#include <memory>
#include <vector>
#include <SDL.h>
#include <rend/rend.h>
#include "screen.h"
#include <AL/al.h>
#include <AL/alc.h>
#include "resourceManager.h"
#include "keyboard.h"
#include "Exception.h"
#include "Mouse.h"

namespace snowball
{
	//forward declare to add components on entity creation
	struct Entity;
	struct Renderer;
	struct Transform;
	struct Camera;
	struct Model;
	struct Shader;
	struct Texture;
	struct RenderTexture;
	struct UIElement;
/**
* \brief The core of the engine.
* 
* This is the class that contains references to all the parts
* needed to get the engine working, such as a renderer, keyboard manager etc.
* It also handles the main execution loop.
*/

	struct Core
	{
		friend struct ::snowball::Renderer;
		friend struct ::snowball::Model;
		friend struct ::snowball::Shader;
		friend struct ::snowball::Texture;
		friend struct ::snowball::RenderTexture;
		friend struct ::snowball::UIElement;

		static std::shared_ptr<Core> initialize(); //static to initialize without object
		std::shared_ptr<Entity> addEntity();
		std::shared_ptr<Screen> getScreen();
		std::shared_ptr<ResourceManager> getRm();
		std::shared_ptr<Keyboard> getKeyboard();
		std::shared_ptr<Camera> getCamera();
		std::shared_ptr<Camera> getSCamera();
		void setMainCamera(std::shared_ptr<Camera> _cam);
		void start();
		void checkButtonPressed();
		void addButton(std::shared_ptr<UIElement> _btn);
	private:

		friend struct snowball::Camera;

		/*SDL related*/
		SDL_Window* window;
		SDL_GLContext glContext;
		std::shared_ptr<Screen> sc;
		//////

		/*Sound related (OPENAL)*/
		ALCdevice* device;
		ALCcontext* alContext;

		/////
		std::vector<std::weak_ptr<Camera>> cameras;
		std::weak_ptr<Camera> currentCam;
		std::shared_ptr<Keyboard> kb;
		std::shared_ptr<ResourceManager> rm;
		std::weak_ptr<Core> self; 
		std::shared_ptr<rend::Context> context; //TODO inside contexts destructor, delete window and glContext
		std::vector<std::shared_ptr<Entity>> entities;
		std::shared_ptr<Mouse> mouse;
		std::vector<std::shared_ptr<UIElement>> buttons;
	};
}