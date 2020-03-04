#ifndef COMPONENT_H
#define COMPONENT_H

#include <memory>

class Core;
class Entity;
struct SDL_Renderer;

class Component
{
	friend class Entity;

protected:
	std::shared_ptr<Entity> getEntity();
	std::shared_ptr<Core> getCore();

private:
	virtual void onStart() {}
	virtual void onUpdate() {}
	virtual void onDraw(SDL_Renderer* _renderer) {}

	std::weak_ptr<Entity> entity;
};

#endif // COMPONENT_H
