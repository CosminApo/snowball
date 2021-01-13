#include <snowball/snowball.h>
#include <SDL.h>



struct Controller : public Component
{
    void onTick()
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

struct PlayerCollider : public Collider
{
    void onCollision()
    {
        std::cout << "Collision detected" << std::endl;
    }
};

struct MyButton : public UIElement
{
   void onTick()
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
    std::shared_ptr<Core> core = Core::initialize();	
    std::shared_ptr<Entity> pe = core->addEntity(); 

    std::shared_ptr<Entity> camera = core->addEntity();
    camera->addComponent<Camera>(true);
    camera->addComponent<Controller>();
    camera->getComponent<Camera>()->addRenderTexture("../curuthers/Whiskers_diffuse.png");

    std::shared_ptr<Entity> camera2 = core->addEntity();
    camera2->addComponent<Camera>();
 

    std::shared_ptr<Player> pc = pe->addComponent<Player>();
    pc->getEntity()->getComponent<Renderer>()->setShader("shader.glsl");
    pc->getEntity()->getComponent<Renderer>()->setModel("../curuthers/curuthers.obj");
    pc->getEntity()->getComponent<Renderer>()->setTexture("../curuthers/Whiskers_diffuse.png");
  //pe->addComponent<Controller>();
    pc->getEntity()->getComponent<SoundSource>()->setListener(camera->getComponent<Camera>());
    pe->addComponent<PlayerCollider>(true);

    std::shared_ptr<Entity> pe2 = core->addEntity();
    pe2->addComponent<Renderer>();
    pe2->getComponent<Renderer>()->setShader("shader.glsl");
    pe2->getComponent<Renderer>()->setModel("../curuthers/curuthers.obj");
    pe2->getComponent<Renderer>()->setTexture("../curuthers/Whiskers_diffuse.png");
    pe2->getComponent<Transform>()->getTransform()->setPosition(glm::vec3(5.f, 0.f, -10.f));
    pe2->addComponent<PlayerCollider>(true);

    std::shared_ptr<Entity> ui = core->addEntity();
    ui->addComponent<Renderer>();
    ui->getComponent<Renderer>()->setShader("shader.glsl");
    ui->addComponent<MyButton>(camera->getComponent<Camera>()->getRenderTexture(),"button.png",50,50,0,0);

    std::shared_ptr<Entity> uis = core->addEntity();
    uis->addComponent<Renderer>();
    uis->getComponent<Renderer>()->setShader("shader.glsl");
    uis->addComponent<MyButton>(camera->getComponent<Camera>()->getRenderTexture(), "button.png", 50, 50, 400,0);

    core->start();
    

  
	return 0;
}