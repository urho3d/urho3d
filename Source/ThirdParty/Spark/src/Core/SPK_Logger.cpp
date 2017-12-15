//
// SPARK particle engine
//
// Copyright (C) 2008-2011 - Julien Fryer - julienfryer@gmail.com
// Copyright (C) 2017 - Frederic Martin - fredakilla@gmail.com
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//

#include <fstream>
#include <ctime>

#include <SPARK_Core.h>

namespace SPK
{
	Logger* Logger::instance = NULL;

	const std::string Logger::PRIORITY_NAMES[] =
	{
		"DEBUG",
		"INFO",
		"WARNING",
		"ERROR",
		"FATAL ERROR",
	};

	Logger::Logger() :
		enabled(true),
#ifdef SPK_DEBUG
		priorityLevel(LOG_PRIORITY_DEBUG), // default priority level is DEBUG in debug
#else
		priorityLevel(LOG_PRIORITY_INFO), // default priority level is INFO in release
#endif
		innerStream(&std::cout),
		prefixFlag(LOG_PREFIX_TIME | LOG_PREFIX_LIB | LOG_PREFIX_PRIORITY)
	{}

	Logger& Logger::get()
	{
		static Logger instance;
		return instance;
	}

	Logger::Stream Logger::getStream(LogPriority priority,bool skipPrefix)
	{
		if (!skipPrefix && isEnabled() && priority >= getPriorityLevel())
			writePrefix(priority);

		return Stream(*innerStream,priority);
	}

	void Logger::writePrefix(LogPriority priority)
	{
		// Writes date and time
		if (prefixFlag & LOG_PREFIX_TIME)
		{
			time_t currentTime = std::time(NULL);
			tm* timeInfo = localtime(&currentTime);
			*innerStream << timeInfo->tm_year + 1900 << "/" 
				<< timeInfo->tm_mon + 1 << "/"
				<< timeInfo->tm_mday << " "
				<< timeInfo->tm_hour << ":"
				<< timeInfo->tm_min << ":"
				<< timeInfo->tm_sec << " - ";
		}

		// Writes the name of the library (SPARK)
		if (prefixFlag & LOG_PREFIX_LIB)
			*innerStream << "SPARK - ";

		// Writes the priority of the entry
		if (prefixFlag & LOG_PREFIX_PRIORITY)
			*innerStream << PRIORITY_NAMES[priority].c_str() << " - ";
	}

	Logger::Stream::Stream(std::ostream& innerStream,LogPriority priority) :
		innerStream(innerStream),
		priority(priority)
	{}
}
