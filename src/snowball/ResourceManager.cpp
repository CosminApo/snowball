#include "ResourceManager.h"
namespace snowball
{
    std::shared_ptr<Core> ResourceManager::getCore()
    {
        return core.lock();
    }
    void ResourceManager::setSelf(std::shared_ptr<ResourceManager> _self)
    {
        self = _self;
    }
    void ResourceManager::setCore(std::shared_ptr<Core> _core)
    {
        core = _core;
    }
}