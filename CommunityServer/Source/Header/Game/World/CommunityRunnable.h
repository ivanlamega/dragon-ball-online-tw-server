#ifndef __COMMUNITYRUNNABLE_H
#define __COMMUNITYRUNNABLE_H

#include <Threading.h>

/// Heartbeat thread for the World
class CommunityRunnable : public AKCore::Runnable
{
public:
	void run() override;
};
#endif
/// @}
