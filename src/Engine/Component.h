#ifndef COMPONENT_H
#define COMPONENT_H

#include <memory>

class Core;
class Entity;

class Component
{
public:
	virtual void onUpdate() {}
	virtual void onDraw() {}

protected:
	std::shared_ptr<Entity> getEntity();
	std::shared_ptr<Core> getCore();

private:
	std::weak_ptr<Entity> entity;
};

#endif // COMPONENT_H
