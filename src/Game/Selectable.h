#include "Engine.h"

class Selectable : public Component
{
public:
	enum class Tag
	{
		UNIT,
		BUILDING
	};

	std::shared_ptr<Entity> pubEntity();

	void addTag(const Tag& _tag);
	bool hasTag(const Tag& _tag);

	bool isClicked(const SDL_Point& _clickPosition);

private:
	std::list<Tag> tags;
};
