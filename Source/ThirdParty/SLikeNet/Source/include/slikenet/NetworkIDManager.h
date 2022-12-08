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
///


#ifndef __NETWORK_ID_MANAGER_H
#define __NETWORK_ID_MANAGER_H

#include "types.h"
#include "Export.h"
#include "memoryoverride.h"
#include "NetworkIDObject.h"
#include "Rand.h"

namespace SLNet
{

/// Increase this value if you plan to have many persistent objects
/// This value must match on all systems
#define NETWORK_ID_MANAGER_HASH_LENGTH 1024

/// This class is simply used to generate a unique number for a group of instances of NetworkIDObject
/// An instance of this class is required to use the ObjectID to pointer lookup system
/// You should have one instance of this class per game instance.
/// Call SetIsNetworkIDAuthority before using any functions of this class, or of NetworkIDObject
class RAK_DLL_EXPORT NetworkIDManager
{
public:
	// GetInstance() and DestroyInstance(instance*)
	STATIC_FACTORY_DECLARATIONS(NetworkIDManager)

	NetworkIDManager();
	virtual ~NetworkIDManager(void);

	/// Returns the parent object, or this instance if you don't use a parent.
	/// Supports NetworkIDObject anywhere in the inheritance hierarchy
	/// \pre You must first call SetNetworkIDManager before using this function
	template <class returnType>
	returnType GET_OBJECT_FROM_ID(NetworkID x) {
		NetworkIDObject *nio = GET_BASE_OBJECT_FROM_ID(x);
		if (nio==0)
			return 0;
		if (nio->GetParent())
			return (returnType) nio->GetParent();
		return (returnType) nio;
	}

	// Stop tracking all NetworkID objects
	void Clear(void);

	/// \internal
	NetworkIDObject *GET_BASE_OBJECT_FROM_ID(NetworkID x);

protected:
	/// \internal
	void TrackNetworkIDObject(NetworkIDObject *networkIdObject);
	void StopTrackingNetworkIDObject(NetworkIDObject *networkIdObject);

	friend class NetworkIDObject;

	NetworkIDObject *networkIdHash[NETWORK_ID_MANAGER_HASH_LENGTH];
	unsigned int NetworkIDToHashIndex(NetworkID networkId);
	uint64_t startingOffset;
	/// \internal
	NetworkID GetNewNetworkID(void);

};

} // namespace SLNet

#endif
