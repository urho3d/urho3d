/*
 *  Original work: Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 *
 *  Modified work: Copyright (c) 2017, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code was modified by SLikeSoft. Modifications are licensed under the MIT-style
 *  license found in the license.txt file in the root directory of this source tree.
 */

/// \file
/// \brief Ready event plugin.  This enables a set of systems to create a signal event, set this signal as ready or unready, and to trigger the event when all systems are ready
///


#include "NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_ReadyEvent==1

#ifndef __READY_EVENT_H
#define __READY_EVENT_H

#include "PluginInterface2.h"
#include "DS_OrderedList.h"

namespace SLNet {

class RakPeerInterface;

/// \defgroup READY_EVENT_GROUP ReadyEvent
/// \brief Peer to peer synchronized ready and unready events
/// \details
/// \ingroup PLUGINS_GROUP

/// \ingroup READY_EVENT_GROUP
/// Returns the status of a remote system when querying with ReadyEvent::GetReadyStatus
enum ReadyEventSystemStatus
{
	/// ----------- Normal states ---------------
	/// The remote system is not in the wait list, and we have never gotten a ready or complete message from it.
	/// This is the default state for valid events
	RES_NOT_WAITING,
	/// We are waiting for this remote system to call SetEvent(thisEvent,true).
	RES_WAITING,
	/// The remote system called SetEvent(thisEvent,true), but it still waiting for other systems before completing the ReadyEvent.
	RES_READY,
	/// The remote system called SetEvent(thisEvent,true), and is no longer waiting for any other systems.
	/// This remote system has completed the ReadyEvent
	RES_ALL_READY,

		/// Error code, we couldn't look up the system because the event was unknown
	RES_UNKNOWN_EVENT,
};

/// \brief Peer to peer synchronized ready and unready events
/// \details For peer to peer networks in a fully connected mesh.<BR>
/// Solves the problem of how to tell if all peers, relative to all other peers, are in a certain ready state.<BR>
/// For example, if A is connected to B and C, A may see that B and C are ready, but does not know if B is ready to C, or vice-versa.<BR>
/// This plugin uses two stages to solve that problem, first, everyone I know about is ready. Second, everyone I know about is ready to everyone they know about.<BR>
/// The user will get ID_READY_EVENT_SET and ID_READY_EVENT_UNSET as the signal flag is set or unset<BR>
/// The user will get ID_READY_EVENT_ALL_SET when all systems are done waiting for all other systems, in which case the event is considered complete, and no longer tracked.<BR>
/// \sa FullyConnectedMesh2
/// \ingroup READY_EVENT_GROUP
class ReadyEvent : public PluginInterface2
{
public:
	// GetInstance() and DestroyInstance(instance*)
	STATIC_FACTORY_DECLARATIONS(ReadyEvent)

	// Constructor
	ReadyEvent();

	// Destructor
	virtual ~ReadyEvent();

	// --------------------------------------------------------------------------------------------
	// User functions
	// --------------------------------------------------------------------------------------------
	/// Sets or updates the initial ready state for our local system.
	/// If eventId is an unknown event the event is created.
	/// If eventId was previously used and you want to reuse it, call DeleteEvent first, or else you will keep the same event signals from before
	/// Systems previously or later added through AddToWaitList() with the same \a eventId when isReady=true will get ID_READY_EVENT_SET
	/// Systems previously added through AddToWaitList with the same \a eventId will get ID_READY_EVENT_UNSET
	/// For both ID_READY_EVENT_SET and ID_READY_EVENT_UNSET, eventId is encoded in bytes 1 through 1+sizeof(int)
	/// \param[in] eventId A user-defined identifier to wait on. This can be a sequence counter, an event identifier, or anything else you want.
	/// \param[in] isReady True to signal we are ready to proceed with this event, false to unsignal
	/// \return False if event status is ID_READY_EVENT_FORCE_ALL_SET, or if we are setting to a status we are already in (no change). Otherwise true
	bool SetEvent(int eventId, bool isReady);

	/// When systems can call SetEvent() with isReady==false, it is possible for one system to return true from IsEventCompleted() while the other systems return false
	/// This can occur if a system SetEvent() with isReady==false while the completion message is still being transmitted.
	/// If your game has the situation where some action should be taken on all systems when IsEventCompleted() is true for any system, then call ForceCompletion() when the action begins.
	/// This will force all systems to return true from IsEventCompleted().
	/// \param[in] eventId A user-defined identifier to immediately set as completed
	void ForceCompletion(int eventId);

	/// Deletes an event.  We will no longer wait for this event, and any systems that we know have set the event will be forgotten.
	/// Call this to clear memory when events are completed and you know you will never need them again.
	/// \param[in] eventId A user-defined identifier
	/// \return True on success. False (failure) on unknown eventId
	bool DeleteEvent(int eventId);

	/// Returns what was passed to SetEvent()
	/// \return The value of isReady passed to SetEvent(). Also returns false on unknown event.
	bool IsEventSet(int eventId);

	/// Returns if the event is about to be ready and we are negotiating the final packets.
	/// This will usually only be true for a very short time, after which IsEventCompleted should return true.
	/// While this is true you cannot add to the wait list, or SetEvent() isReady to false anymore.
	/// \param[in] eventId A user-defined identifier
	/// \return True if any other system has completed processing. Will always be true if IsEventCompleted() is true
	bool IsEventCompletionProcessing(int eventId) const;

	/// Returns if the wait list is a subset of the completion list.
	/// Call this after all systems you want to wait for have been added with AddToWaitList
	/// If you are waiting for a specific number of systems (such as players later connecting), also check GetRemoteWaitListSize(eventId) to be equal to 1 less than the total number of participants.
	/// \param[in] eventId A user-defined identifier
	/// \return True on completion. False (failure) on unknown eventId, or the set is not completed.
	bool IsEventCompleted(int eventId) const;

	/// Returns if this is a known event.
	/// Events may be known even if we never ourselves referenced them with SetEvent, because other systems created them via ID_READY_EVENT_SET.
	/// \param[in] eventId A user-defined identifier
	/// \return true if we have this event, false otherwise
	bool HasEvent(int eventId);

	/// Returns the total number of events stored in the system.
	/// \return The total number of events stored in the system.
	unsigned GetEventListSize(void) const;

	/// Returns the event ID stored at a particular index.  EventIDs are stored sorted from least to greatest.
	/// \param[in] index Index into the array, from 0 to GetEventListSize()
	/// \return The event ID stored at a particular index
	int GetEventAtIndex(unsigned index) const;

	/// Adds a system to wait for to signal an event before considering the event complete and returning ID_READY_EVENT_ALL_SET.
	/// As we add systems, if this event was previously set to true with SetEvent, these systems will get ID_READY_EVENT_SET.
	/// As these systems disconnect (directly or indirectly through the router) they are removed.
	/// \note If the event completion process has already started, you cannot add more systems, as this would cause the completion process to fail
	/// \param[in] eventId A user-defined number previously passed to SetEvent that has not yet completed
	/// \param[in] guid An address to wait for event replies from.  Pass UNASSIGNED_SYSTEM_ADDRESS for all currently connected systems. Until all systems in this list have called SetEvent with this ID and true, and have this system in the list, we won't get ID_READY_EVENT_COMPLETE
	/// \return True on success, false on unknown eventId (this should be considered an error)
	bool AddToWaitList(int eventId, RakNetGUID guid);
	
	/// Removes systems from the wait list, which should have been previously added with AddToWaitList
	/// \note Systems that directly or indirectly disconnect from us are automatically removed from the wait list
	/// \param[in] guid The system to remove from the wait list. Pass UNASSIGNED_RAKNET_GUID for all currently connected systems.
	/// \return True on success, false on unknown eventId (this should be considered an error)
	bool RemoveFromWaitList(int eventId, RakNetGUID guid);

	/// Returns if a particular system is waiting on a particular event.
	/// \param[in] eventId A user-defined identifier
	/// \param[in] guid The system we are checking up on
	/// \return True if this system is waiting on this event, false otherwise.
	bool IsInWaitList(int eventId, RakNetGUID guid);
	
	/// Returns the total number of systems we are waiting on for this event.
	/// Does not include yourself
	/// \param[in] eventId A user-defined identifier
	/// \return The total number of systems we are waiting on for this event.
	unsigned GetRemoteWaitListSize(int eventId) const;

	/// Returns the system address of a system at a particular index, for this event.
	/// \param[in] eventId A user-defined identifier
	/// \param[in] index Index into the array, from 0 to GetWaitListSize()
	/// \return The system address of a system at a particular index, for this event.
	RakNetGUID GetFromWaitListAtIndex(int eventId, unsigned index) const;
		
	/// For a remote system, find out what their ready status is (waiting, signaled, complete).
	/// \param[in] eventId A user-defined identifier
	/// \param[in] guid Which system we are checking up on
	/// \return The status of this system, for this particular event. \sa ReadyEventSystemStatus
	ReadyEventSystemStatus GetReadyStatus(int eventId, RakNetGUID guid);

	/// This channel will be used for all RakPeer::Send calls
	/// \param[in] newChannel The channel to use for internal RakPeer::Send calls from this system.  Defaults to 0.
	void SetSendChannel(unsigned char newChannel);

	// ---------------------------- ALL INTERNAL AFTER HERE ----------------------------
	/// \internal
	/// Status of a remote system
	struct RemoteSystem
	{
		MessageID lastSentStatus, lastReceivedStatus;
		RakNetGUID rakNetGuid;
	};
	static int RemoteSystemCompByGuid( const RakNetGUID &key, const RemoteSystem &data );
	/// \internal
	/// An event, with a set of systems we are waiting for, a set of systems that are signaled, and a set of systems with completed events
	struct ReadyEventNode
	{
		int eventId; // Sorted on this
		MessageID eventStatus;
		DataStructures::OrderedList<RakNetGUID,RemoteSystem,ReadyEvent::RemoteSystemCompByGuid> systemList;
	};
	static int ReadyEventNodeComp( const int &key, ReadyEvent::ReadyEventNode * const &data );


protected:
	// --------------------------------------------------------------------------------------------
	// Packet handling functions
	// --------------------------------------------------------------------------------------------
	virtual PluginReceiveResult OnReceive(Packet *packet);
	virtual void OnClosedConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, PI2_LostConnectionReason lostConnectionReason );
	virtual void OnRakPeerShutdown(void);
	
	void Clear(void);
	/*
	bool AnyWaitersCompleted(unsigned eventIndex) const;
	bool AllWaitersCompleted(unsigned eventIndex) const;
	bool AllWaitersReady(unsigned eventIndex) const;
	void SendAllReady(unsigned eventId, RakNetGUID guid);
	void BroadcastAllReady(unsigned eventIndex);
	void SendReadyStateQuery(unsigned eventId, RakNetGUID guid);
	void BroadcastReadyUpdate(unsigned eventIndex);
	bool AddToWaitListInternal(unsigned eventIndex, RakNetGUID guid);
	bool IsLocked(unsigned eventIndex) const;
	bool IsAllReadyByIndex(unsigned eventIndex) const;
	*/

	void SendReadyStateQuery(unsigned eventId, RakNetGUID guid);
	void SendReadyUpdate(unsigned eventIndex, unsigned systemIndex, bool forceIfNotDefault);
	void BroadcastReadyUpdate(unsigned eventIndex, bool forceIfNotDefault);
	void RemoveFromAllLists(RakNetGUID guid);
	void OnReadyEventQuery(Packet *packet);
	void PushCompletionPacket(unsigned eventId);
	bool AddToWaitListInternal(unsigned eventIndex, RakNetGUID guid);
	void OnReadyEventForceAllSet(Packet *packet);
	void OnReadyEventPacketUpdate(Packet *packet);
	void UpdateReadyStatus(unsigned eventIndex);
	bool IsEventCompletedByIndex(unsigned eventIndex) const;
	unsigned CreateNewEvent(int eventId, bool isReady);
	bool SetEventByIndex(int eventIndex, bool isReady);

	DataStructures::OrderedList<int, ReadyEventNode*, ReadyEvent::ReadyEventNodeComp> readyEventNodeList;
	unsigned char channel;
};

} // namespace SLNet

#endif

#endif // _RAKNET_SUPPORT_*
