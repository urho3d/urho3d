/*
 *  Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 */

/// \file FormatString.h
///


#ifndef __FORMAT_STRING_H
#define __FORMAT_STRING_H

#include "Export.h"

extern "C" {
char * FormatString(const char *format, ...);
}
// Threadsafe
extern "C" {
char * FormatStringTS(char *output, const char *format, ...);
}


#endif

