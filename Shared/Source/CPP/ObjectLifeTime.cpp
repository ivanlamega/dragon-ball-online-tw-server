#include <cstdlib>
#include <ObjectLifeTime.h>

namespace AKCore
{
	extern "C" void external_wrapper(void* p)
	{
		std::atexit((void(*)())p);
	}

	void at_exit(void(*func)())
	{
		external_wrapper((void*)func);
	}
}
