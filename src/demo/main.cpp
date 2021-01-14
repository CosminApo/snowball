#include <snowball/snowball.h>  /* Provides access to the engine */
#include <iostream> /* Console output */


/**
* \brief Example of a Controller class using keyboard input.  
* 
* This class uses the Keyboard Input manager provided by the engine to move an Entity.
*/
struct Controller : public Component
{
    void onTick() ///< Base tick function inherited from Component. Used for updates every frame.
    {
        if (getEntity()->getCore()->getKeyboard()->getKey(SDLK_a))
        {
            getTransform()->translate(glm::vec3(-0.1f, 0, 0));
        }
        if (getEntity()->getCore()->getKeyboard()->getKey(SDLK_d))
        {
            getTransform()->translate(glm::vec3(0.1f, 0, 0));
        }
        if (getEntity()->getCore()->getKeyboard()->getKey(SDLK_w))
        {
            getTransform()->translate(glm::vec3(0, 0, 0.1f));
        }
        if (getEntity()->getCore()->getKeyboard()->getKey(SDLK_s))
        {
            getTransform()->translate(glm::vec3(0, 0, -0.1f));
        }
        if (getEntity()->getCore()->getKeyboard()->getKey(SDLK_e))
        {
            getTransform()->rotate(glm::vec3(0.0f, 0.1f, 0));
        }
        if (getEntity()->getCore()->getKeyboard()->getKey(SDLK_q))
        {
            getTransform()->rotate(glm::vec3(0.0f, -0.1f, 0));
        }
    }
};

/**
* \brief Example of a Player Collider class.
*
* This class uses the Collider class to add a collider to an Entity and manage on collision events.
*/
struct PlayerCollider : public Collider
{
    void onCollision() ///< Function that handles events on collision. Inherited from Collider.
    {
        std::cout << "Collision detected" << std::endl;
    }
};

/**
* \brief Example of a Button class.
*
* This class uses the UI Element class to create an UI button and handle the on click events.
*/
struct MyButton : public UIElement
{
   void onTick() ///< Base tick function inherited from Component. Used for updates every frame.
    {
        if (getIsClicked())
        {
            std::cout << "Hello, I am a button \n";
            setIsClicked(false);
        }
    }
};

int main()
{
    std::shared_ptr<Core> core = Core::initialize(); // Instantiate the engine.
    std::shared_ptr<Entity> pe = core->addEntity(); //Create a new Entity.

    std::shared_ptr<Entity> camera = core->addEntity(); // Create a new Camera.
    camera->addComponent<Camera>(true); // Add the Camera component.
    camera->addComponent<Controller>(); // Add the Controller component.
    camera->getComponent<Camera>()->addRenderTexture(); // Add a Render Texture to the Camera component.

    std::shared_ptr<Entity> camera2 = core->addEntity(); // Create a new Camera.
    camera2->addComponent<Camera>(); // Add the Camera component.

    std::shared_ptr<Player> pc = pe->addComponent<Player>(); // Add the Player component.
    //NOTE: could use pe->getComponent(). This shows how the hierarchy works as well though.
    pc->getEntity()->getComponent<Renderer>()->setShader("shader.glsl"); // Add a Shader to the Renderer component.
    pc->getEntity()->getComponent<Renderer>()->setModel("../curuthers/curuthers.obj"); // Add a Model to the Renderer  component.
    pc->getEntity()->getComponent<Renderer>()->setTexture("../curuthers/Whiskers_diffuse.png"); // Add a Texture to the Renderer component.
    pc->getEntity()->getComponent<SoundSource>()->setListener(camera->getComponent<Camera>()); // Add a Listener to the Soundsource component.
    pe->addComponent<PlayerCollider>(true); // Add a Collider component.

    std::shared_ptr<Entity> pe2 = core->addEntity(); // Create a new Entity.
    pe2->addComponent<Renderer>(); // Add the Renderer component.
    pe2->getComponent<Renderer>()->setShader("shader.glsl"); // Add a Shader to the Renderer component.
    pe2->getComponent<Renderer>()->setModel("../curuthers/curuthers.obj"); // Add a Model to the Renderer  component.
    pe2->getComponent<Renderer>()->setTexture("../curuthers/Whiskers_diffuse.png"); // Add a Texture to the Renderer component.
    pe2->getComponent<Transform>()->getTransform()->setPosition(glm::vec3(5.f, 0.f, -10.f)); // Set the position of the Entity.
    pe2->addComponent<PlayerCollider>(true); // Add a Collider component.

    std::shared_ptr<Entity> ui = core->addEntity(); // Create a new Entity.
    ui->addComponent<Renderer>(); // Add the Renderer component.
    ui->getComponent<Renderer>()->setShader("shader.glsl"); // Add a Shader to the Renderer component.
    ui->addComponent<MyButton>(camera->getComponent<Camera>()->getRenderTexture(),"button.png",50,50,0,0); // Add the UI component.

    std::shared_ptr<Entity> uis = core->addEntity(); // Create a new Entity.
    uis->addComponent<Renderer>(); // Add the Renderer component.
    uis->getComponent<Renderer>()->setShader("shader.glsl"); // Add a Shader to the Renderer component.
    uis->addComponent<MyButton>(camera->getComponent<Camera>()->getRenderTexture(), "button.png", 50, 50, 400,0); // Add the UI component.

    core->start(); // Start the Engine
    

  
	return 0;
}