/* Copyright The kNet Project.

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

/** @file NetworkLogging.h
	@brief The LOG and LOGUSER macros. Provides an unified mechanism for logging. */

// From http://cnicholson.net/2009/03/stupid-c-tricks-dowhile0-and-c4127/
#ifdef _MSC_VER
#define MULTI_LINE_MACRO_BEGIN do { \
	__pragma(warning(push)) \
	__pragma(warning(disable:4127))

#define MULTI_LINE_MACRO_END \
	} while(0) \
	__pragma(warning(pop))

#else

#define MULTI_LINE_MACRO_BEGIN do {
#define MULTI_LINE_MACRO_END } while(0)

#endif

namespace kNet
{

/// A bitfield type that describes single or multiple log channels (each bit represents a channel).
typedef unsigned int LogChannel;

namespace
{
const LogChannel LogUser = 1;        ///< This log channel is free to use for user-level application messages.
const LogChannel LogInfo = 2;        ///< Successful connects and disconnects.
const LogChannel LogError = 4;       ///< All connection-related errors.
const LogChannel LogObjectAlloc = 8; ///< For debugging: prints information about object allocations an deallocations.
const LogChannel LogData = 16;       ///< For debugging: dumps information about in- and outbound packet data.
const LogChannel LogVerbose = 32;    ///< For debugging: Print detailed internal information.
const LogChannel LogWaits = 64;      ///< Logs all long performance-related waits (thread/mutex blocks) that occur in the system.
}

/// Prints a variadic line to log.
/// @param logChannel The log channel to print to. This variable must have exactly one bit set, and is ANDed against
///                   the currently active channels that can be set with a call to kNet::SetLogChannels.
/// @param filename The C++ file from which the log message occurs, pass in __FILE__.
/// @param lineNumber Pass in __LINE__.
/// @param msg The printf-style message format specifier for the text to print.
void TimeOutputDebugStringVariadic(LogChannel logChannel, const char *filename, int lineNumber, const char *msg, ...);

/// Prints a message to the log. Same as kNet::TimeOutputDebugStringVariadic, but does not use printf formatting.
void TimeOutputDebugString(LogChannel logChannel, const char *filename, int lineNumber, const char *msg);

/// Sets the currently enabled log channels. Pass in a bitwise OR of the log channels you want to enable.
/// If you pass in 0, all logging is disabled. By default, only the channel LogChannelUser is enabled.
void SetLogChannels(LogChannel logChannel);

/// Returns the currently active log channels.
LogChannel GetLogChannels();

/// Returns true if the specified log channel is not suppressed.
bool IsLogChannelActive(LogChannel channel);

/// Sets the output for log messages. By default all logging is output to std::cout. Setting a log file
/// redirects all logging to that file. Calling this function with a null filename pointer restores
/// logging to target std::cout.
void SetLogFile(const char *filename);

/// When called, sets the runtime to print out all memory leaks at program exit time. Win32-only. On
/// linux, this is a no-op.
void EnableMemoryLeakLoggingAtExit();

} // ~kNet

/// Prints out a variadic message to the log channel User.
#define KNET_LOGUSER(msg, ...) \
	MULTI_LINE_MACRO_BEGIN \
		if (kNet::IsLogChannelActive(LogUser)) \
			kNet::TimeOutputDebugStringVariadic(LogUser, __FILE__, __LINE__, msg, ##__VA_ARGS__); \
	MULTI_LINE_MACRO_END

#ifdef KNET_LOGGING_SUPPORT_ENABLED

/// Prints out a variadic message to the given log channel.
#define KNET_LOG(channel, msg, ...) \
	MULTI_LINE_MACRO_BEGIN \
		if (kNet::IsLogChannelActive(channel)) \
			kNet::TimeOutputDebugStringVariadic(channel, __FILE__, __LINE__, msg, ##__VA_ARGS__); \
	MULTI_LINE_MACRO_END

#else

/// If kNet logging is disabled, KNET_LOG() macro is a no-op. This avoids having to evaluate the arguments of the
/// KNET_LOG() call, which improves performance.
#define KNET_LOG(...) ((void)0)

#endif
