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
        std::shared_ptr<Renderer> pc = getEntity()->addComponent<Renderer>(); // Add a renderer component

        sc = getEntity()->addComponent<SoundSource>("Jump3"); // Add a soundsource component.
        sc->setDirectional(true); // Enable directional sound.
        getTransform()->setPosition(glm::vec3(0, 0, -10.f)); // Move the object back a bit.
    }
    void Player::onTick()
    {
        /* Handle some keyboard inputs to move the player around and play sound. */
        if (getEntity()->getCore()->getKeyboard()->getKey(SDLK_LEFT))
        {
            getTransform()->translate(glm::vec3(-0.05f, 0, 0));
        }
        if (getEntity()->getCore()->getKeyboard()->getKey(SDLK_RIGHT))
        {
            getTransform()->translate(glm::vec3(+0.05f, 0, 0));
        }
        if (getEntity()->getCore()->getKeyboard()->getKey(SDLK_UP))
        {
            getTransform()->translate(glm::vec3(0, +0.05f, 0));
        }
        if (getEntity()->getCore()->getKeyboard()->getKey(SDLK_DOWN))
        {
            getTransform()->translate(glm::vec3(0, -0.05f, 0));
        }
        if (getEntity()->getCore()->getKeyboard()->getKey(SDLK_RSHIFT))
        {
            getTransform()->translate(glm::vec3(0, 0, +0.05f));
        }
        if (getEntity()->getCore()->getKeyboard()->getKey(SDLK_RCTRL))
        {
            getTransform()->translate(glm::vec3(0, 0, -0.05f));
        }
        if (getEntity()->getCore()->getKeyboard()->getKey(SDLK_p))
        {
            sc->playSound();
        }

    }
}