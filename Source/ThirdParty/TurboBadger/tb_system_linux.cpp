// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_system.h"

#ifdef TB_SYSTEM_LINUX

#include <sys/time.h>
#include <stdio.h>

#ifdef TB_RUNTIME_DEBUG_INFO

void TBDebugOut(const char *str)
{
	printf("%s", str);
}

#endif // TB_RUNTIME_DEBUG_INFO

namespace tb {

// == TBSystem ========================================

double TBSystem::GetTimeMS()
{
	struct timeval now;
	gettimeofday( &now, NULL );
	return now.tv_usec/1000 + now.tv_sec*1000;
}

// Implementation currently done in port_glut.cpp.
// FIX: Implement here for linux-desktop/android/macos?
//void TBSystem::RescheduleTimer(double fire_time)
//{
//}

int TBSystem::GetLongClickDelayMS()
{
	return 500;
}

int TBSystem::GetPanThreshold()
{
	return 5 * GetDPI() / 96;
}

int TBSystem::GetPixelsPerLine()
{
	return 40 * GetDPI() / 96;
}

int TBSystem::GetDPI()
{
	// FIX: Implement!
	return 96;
}

}; // namespace tb

#endif // TB_SYSTEM_LINUX
