#include <snowball/snowball.h>
#include <SDL.h>


struct Player : Component
{
    void onInitialize() 
    {
        std::shared_ptr<Renderer> pc = getEntity()->addComponent<Renderer>();
        std::shared_ptr<SoundSource> sc = getEntity()->addComponent<SoundSource>("Jump3");
        getTransform()->setPosition(glm::vec3(0, 0, -10.f));
        sc->playSound();
    }  
    void onTick()
    {
        if (getEntity()->getCore()->getKeyboard()->getKey(SDLK_LEFT))
        {
            getTransform()->translate(glm::vec3(-0.01f, 0, 0));
        }
    }
};

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

int main()
{
    std::shared_ptr<Core> core = Core::initialize();	
    std::shared_ptr<Entity> pe = core->addEntity(); 
    std::shared_ptr<Player> pc = pe->addComponent<Player>();
    pc->getEntity()->getComponent<Renderer>()->setShader("shader.glsl");
    pc->getEntity()->getComponent<Renderer>()->setModel("../curuthers/curuthers.obj");
    pc->getEntity()->getComponent<Renderer>()->setTexture("../curuthers/Whiskers_diffuse.png");
  //pe->addComponent<Controller>();

    std::shared_ptr<Entity> camera = core->addEntity();
    camera->addComponent<Camera>();
    camera->addComponent<Controller>();

    std::shared_ptr<Entity> camera2 = core->addEntity();
    camera2->addComponent<Camera>();



    core->start();
    

  
	return 0;
}