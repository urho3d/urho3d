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

/** @file Event.h
	@brief The class \ref kNet::Event Event. Provides a mechanism for inter-thread signalling. */

#ifdef _WIN32
#include "win32/WS2Include.h"
#endif

namespace kNet
{

enum EventWaitType
{
	EventWaitInvalid, ///< This event is uninitialized.
	EventWaitDummy, ///< The event to be waited on is a dummy event. Used to keep the index numbers straight, to avoid a O(n) pass through the whole event wait list.
	EventWaitSignal, ///< The event to be waited on is not a socket-based event, but an application-triggered signal event.
	EventWaitRead, ///< The event to be waited on is a socket read event.
	EventWaitWrite ///< The event to be waited on is a socket write event.
};

/// Event is an inter-thread synchronization primitive that can be in one of two states: Set or Cleared. 
/** A thread can avoid busy-waiting on a condition by using an Event to represent the triggering of that condition
	and calling its \ref kNet::Event::Wait "Wait()" function to observe when the condition occurs.

	Network socket read and write availability can be represented as an Event as well. The \ref kNet::EventArray 
	EventArray class can be used to wait on list of events. This allows a mixture of socket and application events to
	be handled using a single select() call.

	To create a new event, call \ref kNet::CreateNewEvent CreateNewEvent with the wait type of EventWaitSignal.

	The Event class does not follow RAII or data sharing patterns to avoid thread-safety issues. Therefore it is important
	to note that:
	- The default ctor initializes a "null" event - one that is not initialized.
	- The default copy-ctor copies the event. The two events will be the same, i.e. does not matter which of them to wait or signal.
	- The default assignment operator also copies the event, but does NOT free up the internal data used by the old event. When
	  assigning over an Event that is not needed any more, call \ref kNet::Event::Close "Close()" on that event.
	- The default destructor of an Event does NOT delete the event. Before letting the last copy of an Event go out of scope,
	  manually call \ref kNet::Event::Close "Close()" on that Event.

	This class represents a WSAEVENT on Windows, and socket or a pipe on unix. */
class Event
{
public:
	/// Creates a null event. Call Event::Create to initialize the event.
	Event();
	// Does not delete the event. Call Event::Close() when you don't need it anymore.
//	~Event();

	/// Initializes the event to a new instance. If the Event was previously initialized, does *not* Close
	/// the old instance.
	void Create(EventWaitType type);

	/// Deinitializes the Event. If there exists any copies of this Event, their state will be undefined.
	void Close();

	/// Returns true if this event is uninitialized.
	bool IsNull() const;

	/// Returns true if this event is not null.
	bool IsValid() const;

	/// Clears the event, i.e. sets it to "0".
	void Reset();

	/// Sets the event, i.e. sets it to "1".
	void Set();

	/// Returns true if the event is in set state.
	bool Test() const;

	/// Returns true if the event was set, or got set during the timeout period, or returns false if the event
	/// was not set before the timeout occurred.
	bool Wait(unsigned long msecs) const;

	/// Returns the underlying type of the event, specifying what kind of system object is being represented by this event.
	EventWaitType Type() const { return type; }

private:
	EventWaitType type;

#ifdef _WIN32
public:
	WSAEVENT wsaEvent;

	/// Wraps the given WSAEVENT into this event.
	explicit Event(WSAEVENT wsaEvent, EventWaitType eventType);
// Urho3D: removed the KNET_UNIX definition
#else
public:
	int fd[2]; // fd[0] is used for reading, fd[1] for writing.

	/// Wraps the given socket file descriptor into this event.
	explicit Event(int /*SOCKET*/ fd, EventWaitType eventType);

#endif
};

/// Creates and returns a new event.
Event CreateNewEvent(EventWaitType type);

} // ~kNet
