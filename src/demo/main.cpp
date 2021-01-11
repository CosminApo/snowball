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

int main()
{
    std::shared_ptr<Core> core = Core::initialize();	
    std::shared_ptr<Entity> pe = core->addEntity(); 

    std::shared_ptr<Entity> camera = core->addEntity();
    camera->addComponent<Camera>(true);
    camera->addComponent<Controller>();

    std::shared_ptr<Entity> camera2 = core->addEntity();
    camera2->addComponent<Camera>();
    camera2->getComponent<Camera>()->addRenderTexture("../curuthers/Whiskers_diffuse.png");

    std::shared_ptr<Player> pc = pe->addComponent<Player>();
    pc->getEntity()->getComponent<Renderer>()->setShader("shader.glsl");
    pc->getEntity()->getComponent<Renderer>()->setModel("../curuthers/curuthers.obj");
    pc->getEntity()->getComponent<Renderer>()->setTexture("../curuthers/Whiskers_diffuse.png");
  //pe->addComponent<Controller>();
    pc->getEntity()->getComponent<SoundSource>()->setListener(camera->getComponent<Camera>());

    std::shared_ptr<Entity> ui = core->addEntity();
    ui->addComponent<Renderer>();
    ui->getComponent<Renderer>()->setShader("shader.glsl");
    ui->addComponent<UIElement>(camera2->getComponent<Camera>()->getRenderTexture(),"../curuthers/Whiskers_diffuse.png",100,100,0,0);

    std::shared_ptr<Entity> uis = core->addEntity();
    uis->addComponent<Renderer>();
    uis->getComponent<Renderer>()->setShader("shader.glsl");
    uis->addComponent<UIElement>(camera2->getComponent<Camera>()->getRenderTexture(), "../curuthers/Whiskers_diffuse.png", 100, 100, 500,0);
    core->start();
    

  
	return 0;
}