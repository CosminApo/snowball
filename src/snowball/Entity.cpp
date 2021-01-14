#include "entity.h"
namespace snowball
{
    void Entity::tick()
    {
        for (size_t ci = 0; ci < components.size(); ci++) // Loop through all the Components.
        {
            components.at(ci)->tick(); // Call the tick function for each Component.
        } 
    }
	void Entity::render()
	{
        for (size_t ci = 0; ci < components.size(); ci++) // Loop through all the Components.
        {
            components.at(ci)->render(); // Call the render function for each Component.
        }
	}
    std::shared_ptr<Core> Entity::getCore()
    {
        if (core.lock() == NULL)
        {
            throw snowball::Exception("FATAL: Hierarchy broke!");
        }
        return core.lock(); // Returns the Core structure linked to this Entity.
    }
    bool Entity::getCollider()
    {
        return hasCollider; // Returns whether this Entity has a Collider.
    }
    void Entity::setCollider(bool _flag)
    {
        hasCollider = _flag;  // Enables / Disables the Collider flag.
    }
}
