#ifndef COMPONENT_H
#define COMPONENT_H

#include <memory>

class Core;
class Entity;

class Component
{
	friend class Entity;

protected:
	std::shared_ptr<Entity> getEntity();
	std::shared_ptr<Core> getCore();

private:
	virtual void onUpdate() {}
	virtual void onDraw() {}

	std::weak_ptr<Entity> entity;
};

#endif // COMPONENT_H
