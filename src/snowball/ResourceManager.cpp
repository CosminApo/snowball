#include "ResourceManager.h"
namespace snowball
{
    std::shared_ptr<Core> ResourceManager::getCore()
    {
        return core.lock(); // Return the Core reference stored.
    }
    void ResourceManager::setSelf(std::shared_ptr<ResourceManager> _self)
    {
        self = _self; // Store the reference to itself.
    }
    void ResourceManager::setCore(std::shared_ptr<Core> _core)
    {
        core = _core; // Store the reference to the linked Core.
    }
}