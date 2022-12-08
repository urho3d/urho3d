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
/// \brief A class you can derive from to make it easier to represent every networked object with an integer.  This way you can refer to objects over the network.
///


#if !defined(__NETWORK_ID_GENERATOR)
#define      __NETWORK_ID_GENERATOR

#include "types.h"
#include "memoryoverride.h"
#include "Export.h"

namespace SLNet
{
/// Forward declarations
class NetworkIDManager;

typedef uint32_t NetworkIDType;

/// \brief Unique shared ids for each object instance
/// \details A class you can derive from to make it easier to represent every networked object with an integer.  This way you can refer to objects over the network.
/// One system should return true for IsNetworkIDAuthority() and the rest should return false.  When an object needs to be created, have the the one system create the object.
/// Then have that system send a message to all other systems, and include the value returned from GetNetworkID() in that packet.  All other systems should then create the same
/// class of object, and call SetNetworkID() on that class with the NetworkID in the packet.
/// \see the manual for more information on this.
class RAK_DLL_EXPORT NetworkIDObject
{
public:
	// Constructor.  NetworkIDs, if IsNetworkIDAuthority() is true, are created here.
	NetworkIDObject();

	// Destructor.  Used NetworkIDs, if any, are freed here.
	virtual ~NetworkIDObject();

	/// Sets the manager class from which to request unique network IDs
	/// Unlike previous versions, the NetworkIDObject relies on a manager class to provide IDs, rather than using statics,
	/// So you can have more than one set of IDs on the same system.
	virtual void SetNetworkIDManager( NetworkIDManager *manager);

	/// Returns what was passed to SetNetworkIDManager
	virtual NetworkIDManager * GetNetworkIDManager( void ) const;
	
	/// Returns the NetworkID that you can use to refer to this object over the network.
	/// \pre You must first call SetNetworkIDManager before using this function
	/// \retval UNASSIGNED_NETWORK_ID UNASSIGNED_NETWORK_ID is returned IsNetworkIDAuthority() is false and SetNetworkID() was not previously called.  This is also returned if you call this function in the constructor.
	/// \retval 0-65534 Any other value is a valid NetworkID.  NetworkIDs start at 0 and go to 65534, wrapping at that point.
	virtual NetworkID GetNetworkID( void );
	
	/// Sets the NetworkID for this instance.  Usually this is called by the clients and determined from the servers.  However, if you save multiplayer games you would likely use
	/// This on load as well.	
	virtual void SetNetworkID( NetworkID id );

	/// Your class does not have to derive from NetworkIDObject, although that is the easiest way to implement this.
	/// If you want this to be a member object of another class, rather than inherit, then call SetParent() with a pointer to the parent class instance.
	/// GET_OBJECT_FROM_ID will then return the parent rather than this instance.
	virtual void SetParent( void *_parent );

	/// Return what was passed to SetParent
	/// \return The value passed to SetParent, or 0 if it was never called.
	virtual void* GetParent( void ) const;
	
protected:

	/// The  network ID of this object
	// networkID is assigned when networkIDManager is set.
	NetworkID networkID;	
	NetworkIDManager *networkIDManager;

	/// The parent set by SetParent()
	void *parent;

	/// \internal, used by NetworkIDManager
	friend class NetworkIDManager;
	NetworkIDObject *nextInstanceForNetworkIDManager;
};

} // namespace SLNet

#endif
