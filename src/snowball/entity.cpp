#include "entity.h"
namespace snowball
{
    void Entity::tick()
    {
        for (size_t ci = 0; ci < components.size(); ci++)
        {
            //components.at(ci)->tick();
        }
    }
}
