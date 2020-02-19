#include <list>
#include <memory>

class Unit;

class Faction
{
public:
	void createUnit(/*Type, position*/);

private:
	std::list<std::shared_ptr<Unit>> units;
	//std::list<std::shared_ptr<Building>> buildings;
};
