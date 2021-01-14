#include <memory> /* smart pointers */
#include <vector> /* std::vector */
#include <SDL.h> /* Output window creation and management */
#include <rend/rend.h> /* rend::context */
#include "screen.h" /* Output window properties */
#include <AL/al.h> /* Loading in sound */
#include <AL/alc.h> /* Loading in sound */
#include "resourceManager.h" /* Managing resources used*/
#include "keyboard.h" /* Managing Keyboard input */
#include "Exception.h" /* Handling exceptions */
#include "Mouse.h" /* Managing Mouse input */

namespace snowball
{
	// Forward declared structures.
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
		friend struct ::snowball::Renderer; ///< Friends with Renderer to access Rend Context.
		friend struct ::snowball::Model; ///< Friends with Model to access Rend Context.
		friend struct ::snowball::Shader; ///< Friends with Shader to access Rend Context.
		friend struct ::snowball::Texture; ///< Friends with Texture to access Rend Context.
		friend struct ::snowball::RenderTexture; ///< Friends with RenderTexture to access Rend Context.
		friend struct ::snowball::Camera; ///< Friends with Camera to access the list of cameras.

		static std::shared_ptr<Core> initialize(); ///< Function responsible for initializing all the member variables and components.
		std::shared_ptr<Entity> addEntity(); ///< Creates a new Entity and adds it to the list of entities.
		std::shared_ptr<Screen> getScreen(); ///< Returns the current Screen (target output).
		std::shared_ptr<ResourceManager> getRm(); ///< Returns the Resource manager.
		std::shared_ptr<Keyboard> getKeyboard(); ///< Returns the Keyboard manager.
		std::shared_ptr<Camera> getCamera(); ///< Returns the current camera.
		void setMainCamera(std::shared_ptr<Camera> _cam); ///< Sets one of the cameras to be the main camera.
		void start(); ///< Starts the engine.
		void checkButtonPressed(); ///< Checks if a button is currently pressed.
		void addButton(std::shared_ptr<UIElement> _btn); ///< Adds a button to the list of buttons.
		void handleCollision(); ///< Handles collision checks.
		bool checkXCollision(std::shared_ptr<Entity> _e1, std::shared_ptr<Entity> _e2); ///< Checks for collision in the X axis.
		bool checkYCollision(std::shared_ptr<Entity> _e1, std::shared_ptr<Entity> _e2); ///< Checks for collision in the Y axis.
		bool checkZCollision(std::shared_ptr<Entity> _e1, std::shared_ptr<Entity> _e2); ///< Checks for collision in the Z axis.

	private:
		/* Rendering */
		SDL_Window* window; ///< Stores a reference to the SDL window. Raw pointer used because of SDL.
		SDL_GLContext glContext; ///< Stores the current OpenGL context to draw to.
		std::shared_ptr<Screen> sc; ///< Stores a reference to the Screen component. 
		std::shared_ptr<rend::Context> context; ///< Stores a reference to the current Rend Context.

		/* Sound */
		ALCcontext* alContext; ///< Stores a reference to the OpenAL context. Raw pointer used because of OpenAL.
		ALCdevice* device; ///< Stores a reference to the OpenAL sound device. Raw pointer used because of OpenAL.

		/* Input */
		std::shared_ptr<Mouse> mouse; ///< Stores a reference to the Mouse Input manager.
		std::shared_ptr<Keyboard> kb; ///< Stores a reference to the Keyboard Input manager.

		/* Scene Management */
		std::vector<std::weak_ptr<Camera>> cameras; ///< Stores a reference to the list of Cameras currently in the scene.
		std::vector<std::shared_ptr<Entity>> entities; ///< Stores a reference to the list of Entities currently in the scene.
		std::vector<std::shared_ptr<UIElement>> buttons; ///< Stores a reference to the list of UIElements currently in the scene.

		std::weak_ptr<Camera> currentCam; ///< Stores a reference to the current camera in use.
		std::weak_ptr<Core> self; ///< Stores a smart pointer to itself. (Used as a better "this" keyword)
		std::shared_ptr<ResourceManager> rm; ///< Stores a reference to the Resource manager.

	};
}