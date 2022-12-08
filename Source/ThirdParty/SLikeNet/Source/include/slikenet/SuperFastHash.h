/*
 *  Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 */

#ifndef __SUPER_FAST_HASH_H
#define __SUPER_FAST_HASH_H

#include <stdio.h>
#include "NativeTypes.h"

// From http://www.azillionmonkeys.com/qed/hash.html
// Author of main code is Paul Hsieh 
// I just added some convenience functions
// Also note http://burtleburtle.net/bob/hash/doobs.html, which shows that this is 20% faster than the one on that page but has more collisions

uint32_t SuperFastHash (const char * data, int length);
uint32_t SuperFastHashIncremental (const char * data, int len, unsigned int lastHash );
uint32_t SuperFastHashFile (const char * filename);
uint32_t SuperFastHashFilePtr (FILE *fp);

#endif
