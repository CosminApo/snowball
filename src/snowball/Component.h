#ifndef SNOWBALL_COMPONENT_H
#define SNOWBALL_COMPONENT_H

#include <memory>

namespace snowball
{

    struct Entity;
    struct Core;

    struct Component
    {
        friend struct snowball::Entity;

        void tick();
        void render();
        virtual void onTick();
        virtual void onRender();

        virtual void onInitialize();

        std::shared_ptr<Entity> getEntity();
        std::shared_ptr<Core> getCore();

    private:
        std::weak_ptr<Entity> entity;
    };

}
//resource manager swap t to be resource and rs load can work
#endif