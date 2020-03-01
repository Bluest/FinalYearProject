#include "Engine.h"

int main(int argc, char* argv[])
{
	std::shared_ptr<Core> core = Core::init(500, 500);
	core->run();

	return 0;
}
