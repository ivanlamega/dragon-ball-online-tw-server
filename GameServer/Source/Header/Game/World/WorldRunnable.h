#ifndef __WORLDRUNNABLE_H
#define __WORLDRUNNABLE_H

#include <Threading.h>

/// Heartbeat thread for the World
class WorldRunnable : public AKCore::Runnable
{
public:
	void run() override;
};
#endif
/// @}
