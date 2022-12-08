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
/// \brief Message filter plugin. Assigns systems to FilterSets.  Each FilterSet limits what messages are allowed.  This is a security related plugin.
///

#include "NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_MessageFilter==1

#ifndef __MESSAGE_FILTER_PLUGIN_H
#define __MESSAGE_FILTER_PLUGIN_H

#include "types.h"
#include "PluginInterface2.h"
#include "DS_OrderedList.h"
#include "DS_Hash.h"
#include "Export.h"

/// MessageIdentifier (ID_*) values shoudln't go higher than this.  Change it if you do.
#define MESSAGE_FILTER_MAX_MESSAGE_ID 256

namespace SLNet
{
/// Forward declarations
class RakPeerInterface;

/// \internal Has to be public so some of the shittier compilers can use it.
int RAK_DLL_EXPORT MessageFilterStrComp( char *const &key,char *const &data );

/// \internal Has to be public so some of the shittier compilers can use it.
struct FilterSet
{
	bool banOnFilterTimeExceed;
	bool kickOnDisallowedMessage;
	bool banOnDisallowedMessage;
	SLNet::TimeMS disallowedMessageBanTimeMS;
	SLNet::TimeMS timeExceedBanTimeMS;
	SLNet::TimeMS maxMemberTimeMS;
	void (*invalidMessageCallback)(RakPeerInterface *peer, AddressOrGUID systemAddress, int filterSetID, void *userData, unsigned char messageID);
	void *disallowedCallbackUserData;
	void (*timeoutCallback)(RakPeerInterface *peer, AddressOrGUID systemAddress, int filterSetID, void *userData);
	void *timeoutUserData;
	int filterSetID;
	bool allowedIDs[MESSAGE_FILTER_MAX_MESSAGE_ID];
	DataStructures::OrderedList<SLNet::RakString, SLNet::RakString> allowedRPC4;
};

/// \internal Has to be public so some of the shittier compilers can use it.
int RAK_DLL_EXPORT FilterSetComp( const int &key, FilterSet * const &data );

/// \internal Has to be public so some of the shittier compilers can use it.
struct FilteredSystem
{
	FilterSet *filter;
	SLNet::TimeMS timeEnteredThisSet;
};

/// \defgroup MESSAGEFILTER_GROUP MessageFilter
/// \brief Remote incoming packets from unauthorized systems
/// \details
/// \ingroup PLUGINS_GROUP

/// \brief Assigns systems to FilterSets.  Each FilterSet limits what kinds of messages are allowed.
/// \details The MessageFilter plugin is used for security where you limit what systems can send what kind of messages.<BR>
/// You implicitly define FilterSets, and add allowed message IDs to these FilterSets.<BR>
/// You then add systems to these filters, such that those systems are limited to sending what the filters allows.<BR>
/// You can automatically assign systems to a filter.<BR>
/// You can automatically kick and possibly ban users that stay in a filter too long, or send the wrong message.<BR>
/// Each system is a member of either zero or one filters.<BR>
/// Add this plugin before any plugin you wish to filter (most likely just add this plugin before any other).
/// \ingroup MESSAGEFILTER_GROUP
class RAK_DLL_EXPORT MessageFilter : public PluginInterface2
{
public:

	// GetInstance() and DestroyInstance(instance*)
	STATIC_FACTORY_DECLARATIONS(MessageFilter)

	MessageFilter();
	virtual ~MessageFilter();

	// --------------------------------------------------------------------------------------------
	// User functions
	// --------------------------------------------------------------------------------------------

	/// Automatically add all new systems to a particular filter
	/// Defaults to -1
	/// \param[in] filterSetID Which filter to add new systems to.  <0 for do not add.
	void SetAutoAddNewConnectionsToFilter(int filterSetID);

	/// Allow a range of message IDs
	/// Always allowed by default: ID_CONNECTION_REQUEST_ACCEPTED through ID_DOWNLOAD_PROGRESS
	/// Usually you specify a range to make it easier to add new enumerations without having to constantly refer back to this function.
	/// \param[in] allow True to allow this message ID, false to disallow. By default, all messageIDs except the noted types are disallowed.  This includes messages from other plugins!
	/// \param[in] messageIDStart The first ID_* message to allow in the range.  Inclusive.
	/// \param[in] messageIDEnd The last ID_* message to allow in the range.  Inclusive.
	/// \param[in] filterSetID A user defined ID to represent a filter set.  If no filter with this ID exists, one will be created with default settings.
	void SetAllowMessageID(bool allow, int messageIDStart, int messageIDEnd,int filterSetID);

	/// Allow a specific RPC4 call
	/// \pre MessageFilter must be attached before RPC4
	/// \param[in] uniqueID Identifier passed to RegisterFunction()
	/// \param[in] filterSetID A user defined ID to represent a filter set.  If no filter with this ID exists, one will be created with default settings.
	void SetAllowRPC4(bool allow, const char* uniqueID, int filterSetID);

	/// What action to take on a disallowed message.  You can kick or not.  You can add them to the ban list for some time
	/// By default no action is taken.  The message is simply ignored.
	/// param[in] 0 for permanent ban, >0 for ban time in milliseconds.
	/// \param[in] kickOnDisallowed kick the system that sent a disallowed message.
	/// \param[in] banOnDisallowed ban the system that sent a disallowed message.  See \a banTimeMS for the ban duration
	/// \param[in] banTimeMS Passed to the milliseconds parameter of RakPeer::AddToBanList.
	/// \param[in] filterSetID A user defined ID to represent a filter set.  If no filter with this ID exists, one will be created with default settings.
	void SetActionOnDisallowedMessage(bool kickOnDisallowed, bool banOnDisallowed, SLNet::TimeMS banTimeMS, int filterSetID);

	/// Set a user callback to be called on an invalid message for a particular filterSet
	/// \param[in] filterSetID A user defined ID to represent a filter set.  If no filter with this ID exists, one will be created with default settings.
	/// \param[in] userData A pointer passed with the callback
	/// \param[in] invalidMessageCallback A pointer to a C function to be called back with the specified parameters.
	void SetDisallowedMessageCallback(int filterSetID, void *userData, void (*invalidMessageCallback)(RakPeerInterface *peer, AddressOrGUID addressOrGUID, int filterSetID, void *userData, unsigned char messageID));

	/// Set a user callback to be called when a user is disconnected due to SetFilterMaxTime
	/// \param[in] filterSetID A user defined ID to represent a filter set.  If no filter with this ID exists, one will be created with default settings.
	/// \param[in] userData A pointer passed with the callback
	/// \param[in] invalidMessageCallback A pointer to a C function to be called back with the specified parameters.
	void SetTimeoutCallback(int filterSetID, void *userData, void (*invalidMessageCallback)(RakPeerInterface *peer, AddressOrGUID addressOrGUID, int filterSetID, void *userData));

	/// Limit how long a connection can stay in a particular filterSetID. After this time, the connection is kicked and possibly banned.
	/// By default there is no limit to how long a connection can stay in a particular filter set.
	/// \param[in] allowedTimeMS How many milliseconds to allow a connection to stay in this filter set.
	/// \param[in] banOnExceed True or false to ban the system, or not, when \a allowedTimeMS is exceeded
	/// \param[in] banTimeMS Passed to the milliseconds parameter of RakPeer::AddToBanList.
	/// \param[in] filterSetID A user defined ID to represent a filter set.  If no filter with this ID exists, one will be created with default settings.
	void SetFilterMaxTime(int allowedTimeMS, bool banOnExceed, SLNet::TimeMS banTimeMS, int filterSetID);

	/// Get the filterSetID a system is using.  Returns -1 for none.
	/// \param[in] addressOrGUID The system we are referring to
	int GetSystemFilterSet(AddressOrGUID addressOrGUID);

	/// Assign a system to a filter set.
	/// Systems are automatically added to filter sets (or not) based on SetAutoAddNewConnectionsToFilter()
	/// This function is used to change the filter set a system is using, to add it to a new filter set, or to remove it from all existin filter sets.
	/// \param[in] addressOrGUID The system we are referring to
	/// \param[in] filterSetID A user defined ID to represent a filter set.  If no filter with this ID exists, one will be created with default settings.  If -1, the system will be removed from all filter sets.
	void SetSystemFilterSet(AddressOrGUID addressOrGUID, int filterSetID);

	/// Returns the number of systems subscribed to a particular filter set
	/// Using anything other than -1 for \a filterSetID is slow, so you should store the returned value.
	/// \param[in] filterSetID The filter set to limit to.  Use -1 for none (just returns the total number of filter systems in that case).
	unsigned GetSystemCount(int filterSetID) const;

	/// Returns the total number of filter sets.
	/// \return The total number of filter sets.
	unsigned GetFilterSetCount(void) const;

	/// Returns the ID of a filter set, by index
	/// \param[in] An index between 0 and GetFilterSetCount()-1 inclusive
	int GetFilterSetIDByIndex(unsigned index);

    /// Delete a FilterSet.  All systems formerly subscribed to this filter are now unrestricted.
	/// \param[in] filterSetID The ID of the filter set to delete.
	void DeleteFilterSet(int filterSetID);

	// --------------------------------------------------------------------------------------------
	// Packet handling functions
	// --------------------------------------------------------------------------------------------
	virtual void Update(void);
	virtual PluginReceiveResult OnReceive(Packet *packet);
	virtual void OnNewConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, bool isIncoming);
	virtual void OnClosedConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, PI2_LostConnectionReason lostConnectionReason );

protected:

	void Clear(void);
	void DeallocateFilterSet(FilterSet *filterSet);
	FilterSet* GetFilterSetByID(int filterSetID);
	void OnInvalidMessage(FilterSet *filterSet, AddressOrGUID systemAddress, unsigned char messageID);

	DataStructures::OrderedList<int, FilterSet*, FilterSetComp> filterList;
	// Change to guid
	DataStructures::Hash<AddressOrGUID, FilteredSystem, 2048, AddressOrGUID::ToInteger> systemList;

	int autoAddNewConnectionsToFilter;
	SLNet::Time whenLastTimeoutCheck;
};

} // namespace SLNet

#endif

#endif // _RAKNET_SUPPORT_*
