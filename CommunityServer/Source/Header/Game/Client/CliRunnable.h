#ifndef __CLIRUNNABLE_H
#define __CLIRUNNABLE_H

#include <Threading.h>

/// Command Line Interface handling thread
class CliRunnable : public AKCore::Runnable
{
public:
	void run() override;
};
#endif
/// @}
