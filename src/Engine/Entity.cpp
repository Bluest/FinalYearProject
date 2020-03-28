#include "Component.h"
#include "Entity.h"

void Entity::addTag(const std::string& _tag)
{
	tags.push_back(_tag);
}

bool Entity::hasTag(const std::string& _tag)
{
	for (auto it = tags.begin(); it != tags.end(); ++it)
	{
		if (*it == _tag)
		{
			return true;
		}
	}

	return false;
}

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
