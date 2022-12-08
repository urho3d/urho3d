/*
 *  Copyright (c) 2014, Oculus VR, Inc.
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
/// \brief \b Reference counted object. Very simple class for quick and dirty uses.
///



#ifndef __REF_COUNTED_OBJ_H
#define __REF_COUNTED_OBJ_H

#include "memoryoverride.h"

/// World's simplest class :)
class RefCountedObj
{
	public:
		RefCountedObj() {refCount=1;}
		virtual ~RefCountedObj() {}
		void AddRef(void) {refCount++;}
		void Deref(void) {if (--refCount==0) SLNet::OP_DELETE(this, _FILE_AND_LINE_);}
		int refCount;
};

#endif
