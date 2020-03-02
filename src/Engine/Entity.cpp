#include "Component.h"
#include "Entity.h"

std::shared_ptr<Core> Entity::getCore()
{
	return core.lock();
}

void Entity::update()
{
	for (auto it = components.begin(); it != components.end(); ++it)
	{
		(*it)->onUpdate();
	}
}

void Entity::draw(SDL_Renderer* _renderer)
{
	for (auto it = components.begin(); it != components.end(); ++it)
	{
		(*it)->onDraw(_renderer);
	}
}
