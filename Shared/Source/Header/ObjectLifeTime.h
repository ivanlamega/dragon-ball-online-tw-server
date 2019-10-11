#ifndef AKCORE_OBJECTLIFETIME_H
#define AKCORE_OBJECTLIFETIME_H

#include <stdexcept>
#include <Define.h>

typedef void(*Destroyer)(void);

namespace AKCore
{
	void at_exit(void(*func)());

	template<class T>
	class ObjectLifeTime
	{
	public:

		static void ScheduleCall(void(*destroyer)())
		{
			at_exit(destroyer);
		}

		DECLSPEC_NORETURN static void OnDeadReference() ATTR_NORETURN;
	};

	template <class T>
	void ObjectLifeTime<T>::OnDeadReference()           // We don't handle Dead Reference for now
	{
		throw std::runtime_error("Dead Reference");
	}
}

#endif
