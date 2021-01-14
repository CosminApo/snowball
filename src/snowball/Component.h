#ifndef SNOWBALL_COMPONENT_H
#define SNOWBALL_COMPONENT_H

#include <memory> /* smart pointers */

namespace snowball
{
    // Forward declared structures. 
    struct Entity;
    struct Core;
    struct Transform;
    /** 
    * \brief Provides the base class for the components.
    * 
    * The components part of the Entity - Components system. 
    * A Component adds a specific functionality to an Entity, for example the ability to be shown on screen, 
    * to be moved in the render space or to play sound. An Entity can have many Components 
    * and a Component can be part of many Entities.
    */
    struct Component
    {
        friend struct snowball::Entity; ///< Friends with Entity to access Entity pointer.

        void tick(); ///< Base tick function inherited from Entity. Used for updates every frame.
        void render(); ///< Base render function inherited from Entity. Used for rendering every frame.
        virtual void onTick(); ///< Function that handles events every tick. To be overwritten in child classes.
        virtual void onRender(); ///< Function that handles events every render. To be overwritten in child classes.

        virtual void onInitialize(); ///< Function that handles events on initialization. To be overwritten in child classes.

        std::shared_ptr<Entity> getEntity();  ///< Returns a pointer to the Entity structure this Component is linked to.
        std::shared_ptr<Core> getCore(); ///< Returns a pointer to the Core structure linked to the Enitity that this Component is attached to.
        std::shared_ptr<Transform> getTransform(); ///< Shortcut function to access the Transform Component.

    private:
        std::weak_ptr<Entity> entity; ///< Stores the Entity structure this Component is linked to. 
    };
    
}
#endif