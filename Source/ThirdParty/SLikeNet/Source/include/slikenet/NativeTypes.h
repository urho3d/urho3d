/*
 *  Original work: Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 *
 *  Modified work: Copyright (c) 2016, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code was modified by SLikeSoft. Modifications are licensed under the MIT-style
 *  license found in the license.txt file in the root directory of this source tree.
 */

#ifndef __NATIVE_TYPES_H
#define __NATIVE_TYPES_H

#if defined(__GNUC__) || defined(__GCCXML__) || defined(__SNC__) || defined(__S3E__)
#include <stdint.h>
#elif !defined(_STDINT_H) && !defined(_SN_STDINT_H) && !defined(_SYS_STDINT_H_) && !defined(_STDINT) && !defined(_MACHTYPES_H_) && !defined(_STDINT_H_)
	typedef unsigned char       uint8_t;
	typedef unsigned short      uint16_t;
	typedef unsigned __int32    uint32_t;
	typedef signed char         int8_t;
	typedef signed short        int16_t;
	typedef __int32				int32_t;
	typedef unsigned long long int    uint64_t;
	typedef signed long long   	int64_t;
#endif


#endif
