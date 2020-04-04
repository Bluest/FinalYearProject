#include <list>
#include <memory>
#include <string>

#include "glm/vec3.hpp"

class Component;
class Core;
struct SDL_Renderer;

struct Transform
{
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
};

class Entity
{
	friend class Core;

public:
	template <typename T>
	std::shared_ptr<T> addComponent()
	{
		std::shared_ptr<T> component = std::make_shared<T>();
		component->entity = self;
		component->onInit();
		components.push_back(component);

		return component;
	}

	template <class T>
	std::shared_ptr<T> getComponent()
	{
		std::shared_ptr<T> component;

		for (auto it = components.begin(); it != components.end(); ++it)
		{
			component = std::dynamic_pointer_cast<T>(*it);
			if (component)
			{
				return component;
			}
		}

		return nullptr;
	}

	void addTag(const std::string& _tag);
	bool hasTag(const std::string& _tag);

	void destroy();

	std::shared_ptr<Core> getCore();

	Transform transform;

private:
	void start();
	void update();
	void draw(SDL_Renderer* _renderer);

	std::weak_ptr<Entity> self;
	std::weak_ptr<Core> core;
	std::list<std::shared_ptr<Component>> components;
	std::list<std::string> tags;
	bool destroyed;
};
