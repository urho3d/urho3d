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

#include "defines.h"

#if defined(_WIN32) && !(defined(__GNUC__)  || defined(__GCCXML__)) && !defined(_RAKNET_LIB) && defined(_RAKNET_DLL)
#define RAK_DLL_EXPORT __declspec(dllexport)
#else
#define RAK_DLL_EXPORT  
#endif

#define STATIC_FACTORY_DECLARATIONS(x) static x* GetInstance(void); \
static void DestroyInstance( x *i);

#define STATIC_FACTORY_DEFINITIONS(x,y) x* x::GetInstance(void) {return SLNet::OP_NEW<y>( _FILE_AND_LINE_ );} \
void x::DestroyInstance( x *i) {SLNet::OP_DELETE(( y* ) i, _FILE_AND_LINE_);}
