#include "Component.h"
#include "Entity.h"

void Entity::start()
{
	for (auto it = components.begin(); it != components.end(); ++it)
	{
		(*it)->onStart();
	}
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

std::shared_ptr<Core> Entity::getCore()
{
	return core.lock();
}
