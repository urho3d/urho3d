/* Copyright The kNet Project.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License. */

/** @file W32EventArray.cpp
	@brief */

#include <cassert>

#include "kNet/DebugMemoryLeakCheck.h"

#include "kNet/EventArray.h"
#include "kNet/NetworkLogging.h"

namespace kNet
{

EventArray::EventArray()
:numAdded(0)
{
}

void EventArray::Clear()
{
	numAdded = 0;
}

int EventArray::Size() const
{
	return numAdded;
}

void EventArray::AddEvent(const Event &e)
{
	if (e.IsNull())
	{
		KNET_LOG(LogError, "EventArray::AddEvent: Error! Tried to add a null event to event array at index %d!", numAdded);
		return;
	}
	if (numAdded >= maxEvents)
	{
		KNET_LOG(LogError, "EventArray::AddEvent: Error! Tried to add too many events to event array! (max: %d)", numAdded);
		return;
	}
	assert(numAdded < maxEvents);
	events[numAdded++] = e.wsaEvent;
}

int EventArray::Wait(int msecs)
{
	if (numAdded == 0)
		return WaitFailed;

	DWORD ret = WSAWaitForMultipleEvents(numAdded, events, FALSE, msecs, TRUE);
	if (ret >= WSA_WAIT_EVENT_0 && ret < WSA_WAIT_EVENT_0 + numAdded)
		return ret - WSA_WAIT_EVENT_0;
	else if (ret == WSA_WAIT_TIMEOUT)
		return WaitTimedOut;
	else
	{
		KNET_LOG(LogError, "EventArray::Wait: WSAWaitForMultipleEvents failed with error code %d (WSAGetLastError: %d)!", (int)ret, (int)WSAGetLastError());
		for(int i = 0; i < numAdded; ++i)
			if (WSAWaitForMultipleEvents(1, events+i, FALSE, 0, FALSE) == WSA_WAIT_FAILED)
				KNET_LOG(LogError, "EventArray::Wait: EventArray event at index %d is not valid!", i);

		return WaitFailed;
	}
}

} // ~kNet
