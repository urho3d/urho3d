/*
 *  Original work: Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 *
 *  Modified work: Copyright (c) 2016-2017, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code was modified by SLikeSoft. Modifications are licensed under the MIT-style
 *  license found in the license.txt file in the root directory of this source tree.
 */

#ifndef __RAKNET_TIME_H
#define __RAKNET_TIME_H

#include "NativeTypes.h"
#include "defines.h"

namespace SLNet {

// Define __GET_TIME_64BIT if you want to use large types for GetTime (takes more bandwidth when you transmit time though!)
// You would want to do this if your system is going to run long enough to overflow the millisecond counter (over a month)
#if __GET_TIME_64BIT==1
typedef uint64_t Time;
#define RAK_TIME_FORMAT_STRING "%llu"
typedef uint32_t TimeMS;
typedef uint64_t TimeUS;
#else
typedef uint32_t Time;
#define RAK_TIME_FORMAT_STRING "%u"
typedef uint32_t TimeMS;
typedef uint64_t TimeUS;
#endif

} // namespace SLNet

#endif
