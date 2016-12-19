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
#pragma once

/** @file EventArray.h
	@brief The class \ref kNet::EventArray EventArray. Allows listening to multiple events at once.*/

#include <vector>

// Urho3D: removed the KNET_UNIX definition
#ifndef _WIN32
#include <sys/select.h>
#endif

#include "Event.h"

namespace kNet
{

/// EventArray stores a list of events and allows the application to simultaneously wait for any of them to
/// become set. This object never calls Create() or Close() on any Event that is added to it.
class EventArray
{
public:
	/// Constructs an EventArray with an empty list of events.
	EventArray();

	/// Removes all the events added with AddEvent from this EventArray.
	void Clear();

	/// Adds the given event to the array. There is a limitation of maximum of 64 simultaneous Events that can be added
	/// to an array.
	void AddEvent(const Event &e);

	/// This status code is returned by Wait when none of the added events were triggered during the timeout period.
	static const int WaitTimedOut = -1;
	
	/// This status code is returned by Wait when the OS specified an error - the wait list most likely contains invalid entries.
	static const int WaitFailed = -2;

	/// Waits for any of the added events to be triggered. Returns the index of the signalled event, or
	/// EventArray::WaitTimedOut if none of the events triggered during the time period, or
	/// EventArray::WaitFailed if there were invalid event objects added in the array.
	int Wait(int msecs);

	/// Returns the number of events added to the array.
	int Size() const;

private:
	static const int maxEvents = 64; ///< WSAWaitForMultipleEvents has a built-in limit of 64 items, hence this value.
	int numAdded;

#ifdef _WIN32
	WSAEVENT events[maxEvents]; 

// Urho3D: removed the KNET_UNIX definition
#else
	fd_set readfds;
	fd_set writefds;
	int nfds;
	timeval tv;
	/// Cache a list of all added events here. This is to remember the order in which the events were added, so that
	/// we can correctly return the occurred event with the smallest index.
	std::vector<Event> cachedEvents;
#endif
};

} // ~kNet
