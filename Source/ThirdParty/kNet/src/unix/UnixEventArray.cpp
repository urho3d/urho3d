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

/** @file UnixEventArray.cpp
	@brief */

#include <cassert>
#include <utility>

#include <sys/time.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#include "kNet/EventArray.h"
#include "kNet/Thread.h"
#include "kNet/NetworkLogging.h"

using namespace std;

namespace kNet
{

EventArray::EventArray()
{
	Clear();
}

int EventArray::Size() const
{
	return cachedEvents.size();
}

void EventArray::Clear()
{
	FD_ZERO(&readfds);
	FD_ZERO(&writefds);
	nfds = -1;
	numAdded = 0;
	cachedEvents.clear();
}

void EventArray::AddEvent(const Event &e)
{
	if (e.IsNull())
	{
		KNET_LOG(LogError, "Error: Tried to add a null event to event array at index %d!", numAdded);
		return;
	}
	assert(numAdded < maxEvents);

	switch(e.Type())
	{
	case EventWaitInvalid:
		KNET_LOG(LogError, "Error: Tried to add an invalid event to a wait event array!");
		return;
	case EventWaitRead:
	case EventWaitSignal:
		FD_SET(e.fd[0], &readfds);
		nfds = max(nfds, e.fd[0]+1);
		assert(nfds > 0);
		break;
	case EventWaitWrite: // The Event represents write-availability of the socket, in which case, e.fd[0] is the socket (e.fd[1] is left unused)
		FD_SET(e.fd[0], &writefds);
		nfds = max(nfds, e.fd[0]+1);
		assert(nfds > 0);
	default:
		break;
	}

	// No need to add dummy events to select(), but need to add them to the cached events list to keep
	// the indices matching.
	cachedEvents.push_back(e);
	++numAdded;
}

int EventArray::Wait(int msecs)
{
	if (numAdded == 0)
	{
		KNET_LOG(LogError, "EventArray::Wait failed! Tried to wait for an empty array of events! (EventArray=0x%p)", this);
		return WaitFailed;
	}

	// If we have added some number of events to the event array, but nfds == -1, it means we are waiting on a set
	// of dummy events, which are always false. In that case, sleep for a small arbitrary duration and return a timeout.
	// Note that it's a bad idea to wait for the full msecs delay, since it can be very large, and would effectively 
	// stall this thread.
	if (nfds == -1)
	{
		if (msecs > 0)
			Thread::Sleep(min(msecs, 10)); // Arbitrary max sleep 10 msecs.
		return WaitTimedOut;
	}

	tv.tv_sec = msecs / 1000;
	tv.tv_usec = (msecs - tv.tv_sec * 1000) * 1000;

	int ret = select(nfds, &readfds, &writefds, NULL, &tv); // http://linux.die.net/man/2/select
	if (ret == -1)
	{
		KNET_LOG(LogError, "EventArray::Wait(%d, %p, %p, NULL, {%d, %d}: select() failed on an array of %d events: %s(%d)", 
			(int)nfds, &readfds, &writefds, (int)tv.tv_sec, (int)tv.tv_usec,
			numAdded,
			strerror(errno), (int)errno);
		return WaitFailed;
	}

	// select returns the number of sockets in the descriptors that remained in triggered state.
	// If 0, no sockets triggered, and the wait timed out.
	if (ret == 0)
		return WaitTimedOut;
	else if (ret < 0)
	{
		KNET_LOG(LogError, "EventArray::Wait: select() returned a negative value, which it shouldn't!");
		return WaitFailed;
	}

	for(int i = 0; i < cachedEvents.size(); ++i)
		switch(cachedEvents[i].Type())
		{
		case EventWaitRead:
		case EventWaitSignal:
			if (FD_ISSET(cachedEvents[i].fd[0], &readfds))
				return i;
			break;
		case EventWaitWrite:
			if (FD_ISSET(cachedEvents[i].fd[0], &writefds))
				return i;
		default:
			break; // The dummy events are skipped over.
		}

	KNET_LOG(LogError, "EventArray::Wait error! No events were set, but select() returned a positive value!");
	return WaitFailed;
}

} // ~kNet
