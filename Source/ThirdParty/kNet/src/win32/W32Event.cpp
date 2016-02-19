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

/** @file W32Event.cpp
	@brief */
#ifdef _WIN32

#include <cassert>

#include "kNet/DebugMemoryLeakCheck.h"

#include "kNet/Event.h"
#include "kNet/NetworkLogging.h"

namespace kNet
{

Event::Event()
:wsaEvent(NULL), type(EventWaitInvalid)
{
}

Event::Event(WSAEVENT wsaEvent_, EventWaitType type_)
:wsaEvent(wsaEvent_), type(type_)
{
}

Event CreateNewEvent(EventWaitType type)
{
	Event e;
	e.Create(type);
	assert(e.IsValid());
	return e;
}

void Event::Create(EventWaitType type_)
{
	type = type_;
	wsaEvent = WSACreateEvent();
}

void Event::Close()
{
	WSACloseEvent(wsaEvent);
	wsaEvent = NULL;
}

bool Event::IsNull() const
{
	return wsaEvent == NULL;
}

void Event::Reset()
{
	if (wsaEvent == NULL)
		KNET_LOG(LogError, "Event::Reset called on a null event!");
	else
		WSAResetEvent(wsaEvent);
}

void Event::Set()
{
	if (wsaEvent == NULL)
		KNET_LOG(LogError, "Event::Set called on a null event!");
	else
		WSASetEvent(wsaEvent);
}

bool Event::Test() const
{
	return Wait(0);
}

/// Returns true if the event was set during this time, or false if timout occurred.
bool Event::Wait(unsigned long msecs) const
{
	if (wsaEvent == NULL)
		return false;

	DWORD ret = WSAWaitForMultipleEvents(1, &wsaEvent, TRUE, msecs, TRUE);
	return ret == WSA_WAIT_EVENT_0;
}

bool Event::IsValid() const
{
	if (IsNull())
		return false;

	DWORD ret = WSAWaitForMultipleEvents(1, &wsaEvent, TRUE, 0, FALSE);
	return ret != WSA_WAIT_FAILED;
}

} // ~kNet

#endif // ~_WIN32
