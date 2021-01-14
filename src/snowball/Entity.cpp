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
        return core.lock(); // Returns the Core structure linked to this Entity.
    }
}
