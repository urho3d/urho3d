/*
 *  Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 *
 *  Modified work: Copyright (c) 2017-2018, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code was modified by SLikeSoft. Modifications are licensed under the MIT-style
 *  license found in the license.txt file in the root directory of this source tree.
 */

// Defines kept here for backwards compatibility with RAKNET 4.081/4.082.
// Usage of these defines is deprecated. Please switch to using SLIKENET version defines.
#define RAKNET_VERSION "4.082"
#define RAKNET_VERSION_NUMBER 4.082
#define RAKNET_VERSION_NUMBER_INT 4082
#define RAKNET_DATE "7/26/2017"

#define SLIKENET_VERSION "0.1.2"
#define SLIKENET_VERSION_NUMBER 0.1.2
#define SLIKENET_VERSION_NUMBER_INT 000102
#define SLIKENET_DATE "05/06/2018"

// What compatible protocol version RakNet is using. When this value changes, it indicates this version of RakNet cannot connection to an older version.
// ID_INCOMPATIBLE_PROTOCOL_VERSION will be returned on connection attempt in this case
#define RAKNET_PROTOCOL_VERSION 6
