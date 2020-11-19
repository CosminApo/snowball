#ifndef SNOWBALL_COMPONENT_H
#define SNOWBALL_COMPONENT_H

#include <memory>

namespace snowball
{

    struct Entity;
    struct Core;

    /** 
    * \brief Provides the base class for the components.
    * More details
    */

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
        std::weak_ptr<Entity> entity; ///< KEKW
    };

}
//resource manager swap t to be resource and rs load can work
#endif