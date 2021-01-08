#include "Player.h"
#include "Renderer.h"
#include "Entity.h"
#include "SoundSource.h"
#include "Core.h"
#include "Camera.h"


namespace snowball
{
    std::shared_ptr<SoundSource> sc;

    void Player::onInitialize()
    {
        std::shared_ptr<Renderer> pc = getEntity()->addComponent<Renderer>();

        sc = getEntity()->addComponent<SoundSource>("Jump3");
        sc->setDirectional(true);
        getTransform()->setPosition(glm::vec3(0, 0, -10.f));

    }

    void Player::onTick()
    {
        if (getEntity()->getCore()->getKeyboard()->getKey(SDLK_LEFT))
        {
            getTransform()->translate(glm::vec3(-0.05f, 0, 0));
        }
        if (getEntity()->getCore()->getKeyboard()->getKey(SDLK_RIGHT))
        {
            getTransform()->translate(glm::vec3(+0.05f, 0, 0));
        }
        if (getEntity()->getCore()->getKeyboard()->getKey(SDLK_p))
        {
            sc->playSound();
        }

    }
}