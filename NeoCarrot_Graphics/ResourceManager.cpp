#include "ResourceManager.h"

namespace graphics
{

ResourceManager::ResourceManager() 
	: _entityManager{std::make_unique<core::EntityManager<ModelFactory>>()}
{
}

}