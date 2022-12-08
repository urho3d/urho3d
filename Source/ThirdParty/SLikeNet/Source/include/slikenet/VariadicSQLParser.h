/*
 *  Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 */

#ifndef __VARIADIC_SQL_PARSER_H
#define __VARIADIC_SQL_PARSER_H

#include "DS_List.h"

#include <stdarg.h>

namespace VariadicSQLParser
{
	struct IndexAndType
	{
		unsigned int strIndex;
		unsigned int typeMappingIndex;
	};
	const char* GetTypeMappingAtIndex(int i);
	void GetTypeMappingIndices( const char *format, DataStructures::List<IndexAndType> &indices );
	// Given an SQL string with variadic arguments, allocate argumentBinary and argumentLengths, and hold the parameters in binary format
	// Last 2 parameters are out parameters
	void ExtractArguments( va_list argptr, const DataStructures::List<IndexAndType> &indices, char ***argumentBinary, int **argumentLengths );
	void FreeArguments(const DataStructures::List<IndexAndType> &indices, char **argumentBinary, int *argumentLengths);
}


#endif
