/* Copyright 2010 Jukka Jylänki

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License. */
#pragma once

/** @file Datagram.h
	@brief The struct \ref kNet::Datagram Datagram. */

namespace kNet
{

static const unsigned long cDatagramBufferSize = 3 * 512;

/// @internal Datagram stores the raw data of a received UDP datagram.
struct Datagram
{
	unsigned char data[cDatagramBufferSize];

	unsigned long size;
};

} // ~kNet
