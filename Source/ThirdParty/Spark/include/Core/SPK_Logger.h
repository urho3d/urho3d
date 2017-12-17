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

#ifndef H_SPK_LOGGER
#define H_SPK_LOGGER

#include <iostream>
#include <cassert>

/**
* @def SPK_LOG_DEBUG(entry)
* @brief Logs a debug entry in the logger
* @param entry : the debug entry to log
*/

/**
* @def SPK_LOG_INFO(entry)
* @brief Logs a info entry in the logger
* @param entry : the info entry to log
*/

/**
* @def SPK_LOG_WARNING(entry)
* @brief Logs a warning entry in the logger
* @param entry : the warning entry to log
*/

/**
* @def SPK_LOG_ERROR(entry)
* @brief Logs an error entry in the logger
* @param entry : the error entry to log
*/

/**
* @def SPK_LOG_FATAL(entry)
* @brief Logs an fatal error entry in the logger
* @param entry : the fatal error entry to log
*/

/**
* @def SPK_ASSERT(condition,text)
* @brief Makes an assertion on the condition and logs an error if it fails
* @param condition : the condition of the assertion
* @param text : the error entry to log if the assertion fails
*/

#ifdef SPK_NO_LOG

#define SPK_LOG_DEBUG(entry) {}
#define SPK_LOG_INFO(entry) {}
#define SPK_LOG_WARNING(entry) {}
#define SPK_LOG_ERROR(entry) {}
#define SPK_LOG_FATAL(entry) {}
#define SPK_ASSERT(condition,text) { assert(condition); }

#else

#ifdef SPK_DEBUG
#define SPK_LOG_DEBUG(entry) {SPK::Logger::get().getStream(SPK::LOG_PRIORITY_DEBUG) << entry << "\n"; SPK::Logger::get().flush();}
#else
#define SPK_LOG_DEBUG(entry) {}
#endif
#define SPK_LOG_INFO(entry) {SPK::Logger::get().getStream(SPK::LOG_PRIORITY_INFO) << entry << "\n"; SPK::Logger::get().flush();}
#define SPK_LOG_WARNING(entry) {SPK::Logger::get().getStream(SPK::LOG_PRIORITY_WARNING) << entry << "\n"; SPK::Logger::get().flush();}
#define SPK_LOG_ERROR(entry) {SPK::Logger::get().getStream(SPK::LOG_PRIORITY_ERROR) << entry << "\n"; SPK::Logger::get().flush();}
#define SPK_LOG_FATAL(entry) {SPK::Logger::get().getStream(SPK::LOG_PRIORITY_FATAL) << entry << "\n"; SPK::Logger::get().flush();}

#define SPK_ASSERT(condition,text) \
{ \
	if (!(condition)) \
	{ \
		SPK_LOG_ERROR(text); \
	} \
	assert(condition); \
}

#endif

namespace SPK
{
	/** @brief Constants defining the priority of a logged entry */
	enum LogPriority
	{
		LOG_PRIORITY_DEBUG = 0,		/**< Debug priority (lower) */
		LOG_PRIORITY_INFO = 1,		/**< Info priority (standard) */
		LOG_PRIORITY_WARNING = 2,	/**< Warning priority (bad coding style that may not be fatal) */
		LOG_PRIORITY_ERROR = 3,		/**< Error priority (error that are very likely to cause a crash at some point) */
		LOG_PRIORITY_FATAL = 4,		/**< Fatal error priority (error due to inconsistency within the engine) */
	};

	/** @brief Constants defining the format of the prefix of each message */
	enum LogPrefix
	{
		LOG_PREFIX_NONE = 0,			/**< No prefix */
		LOG_PREFIX_TIME = 1 << 0,		/**< Prefixes log entries with the current date and time */
		LOG_PREFIX_LIB = 1 << 1,		/**< Prefixes log entries with the name of the lib ("SPARK") */
		LOG_PREFIX_PRIORITY = 1 << 2,	/**< Prefixes log entries with the priority of the entry */
	};

	/**
	* @brief Singleton class allowing to log messages
	*
	* The easiest way to log in message is to use the macros defined by the engine :
	* <ul>
	* <li>SPK_LOG_DEBUG(entry) : to log a debug information (for low level checks)</li>
	* <li>SPK_LOG_INFO(entry) : to log a standard information</li>
	* <li>SPK_LOG_WARNING(entry) : to log a warning</li>
	* <li>SPK_LOG_ERROR(entry) : to log an error which will most likely result to an immediate crash</li>
	* <li>SPK_LOG_FATAL(entry) : to log an fatal error due to an engine inconsistency. This must only be used by the engine</li>
	* </ul>
	* Those macros are shortcuts to a call to the logger. Moreover they flush the inner stream so that the entry is logged instantly.<br>
	* Some access to lower level methods are possible to be able to log message in a more precise way (getStream,flush...).<br>
	* <br>
	* 
	*/
	class SPK_PREFIX Logger
	{
	public :

		class Stream; // forward declaration

		////////////////////
		// static methods //
		////////////////////

		/**
		* @brief Returns the unique instance of logger
		* @return the instance of Logger
		*/
		static Logger& get();
	
		/////////////
		// Setters //
		/////////////

		/**
		* @brief Enables or not the logger
		*
		* If the logger is disabled, no message will be logged in.<br>
		* By default, the logger is enabled.
		*
		* @param enabled : true to enable the logger, false to disable it
		*/
		void setEnabled(bool enabled);

		/**
		* @brief Sets the priority level of the logger
		*
		* Only entries with a priority superior or equal to the logger priority level are logged in.
		* Bu default the priority level is PRIORITY_DEBUG in debug mode and PRIORITY_info in release mode.
		*
		* @param priorityLevel : the priority level of the logger
		*/
		void setPriorityLevel(LogPriority priorityLevel);

		/**
		* @brief Sets the inner stream of the logger
		*
		* This allows to modify the output stream (standard outputs, files, GUI elements...).
		* By default the inner stream of the logger is the standard output std::cout.
		*
		* @param stream : the inner stream of the logger
		*/
		void setStream(std::ostream& stream);

		/**
		* @brief Sets the prefix flag of the logger
		*
		* The prefix flag defines the format of the prefix of each entry logged in.<br>
		* It is defined by ORed values of the enumeration Prefix.<br>
		* By default the prefix flag is set to <i>LOG_PREFIX_TIME | LOG_PREFIX_LIB | LOG_PREFIX_PRIORITY</i>.
		*
		* @param prefixFlag : the prefix flag of the logger 
		*/
		void setPrefixFlag(int prefixFlag);

		/////////////
		// Getters //
		/////////////

		/**
		* @brief Tells whether the logger is enabled or not
		* @return true if the logger is enabled, false if it is disabled
		*/
		bool isEnabled() const;

		/**
		* @brief Gets the priority level of the logger
		* @return the priority level of the logger
		*/
		LogPriority getPriorityLevel() const;

		/**
		* @brief Gets the stream of the logger
		*
		* This methods allows to log in entries in a more flexible way 
		* than by using macros SPK_LOG_... or the method addEntry(Priority,const std::string&).<br>
		* Note that the stream returned is not the inner std::ostream but a wrapper above it.<br>
		* Each time this method is called, an entry prefix is added, unless the parameter skipPrefix is set to true.
		*
		* @param priority : the priority of the returned stream
		* @param skipPrefix : false to add a prefix to the stream, true not to
		* @return : a stream object used to log on entries
		*/
		Stream getStream(LogPriority priority,bool skipPrefix = false);

		/**
		* @brief Gets the prefix flag of the logger
		* @return the prefix flag of the logger
		*/
		int getPrefixFlag() const;
		
		///////////////
		// Interface //
		///////////////

		/**
		* @brief Logs in an entry to the logger
		* 
		* The entry is prefixed with the prefix, a new line instruction is called at the end
		* and the logger is then flushed.
		*
		* @param priority : the priority level of the entry
		* @param entry : the entry to log in
		*/
		void addEntry(LogPriority priority,const std::string& entry);

		/** @brief Flushes the logger (Immediately appends pending entries to the inner stream) */
		void flush();

		//////////////////
		// Nested class //
		//////////////////

		class Stream
		{
		friend Stream Logger::getStream(LogPriority,bool);

		public :

			template<typename T>
			Stream& operator<<(const T& entry);

		private :

			Stream(std::ostream& innerStream,LogPriority priority);

			std::ostream& innerStream;
			LogPriority priority;
		};

	private :

		static Logger* instance; // The unique instance of Logger

		static const size_t NB_PRIORITY_LEVELS = 5; // Number of priority levels
		static const std::string PRIORITY_NAMES[NB_PRIORITY_LEVELS]; // Names of priority levels

        bool enabled;
		LogPriority priorityLevel;
        std::ostream* innerStream;
		int prefixFlag;


		// private constructor and destructor (singleton pattern)
		Logger();
		~Logger(){}

		Logger(const Logger&); // Not used
		Logger& operator=(const Logger&); // Not used

		void writePrefix(LogPriority priority);
	};

	inline void Logger::setEnabled(bool enabled)
	{
		this->enabled = enabled;
	}

	inline void Logger::setPriorityLevel(LogPriority priorityLevel)
	{
		this->priorityLevel = priorityLevel;
	}

	inline void Logger::setStream(std::ostream& stream)
	{
		innerStream = &stream;
	}

	inline void Logger::setPrefixFlag(int prefixFlag)
	{
		this->prefixFlag = prefixFlag;
	}

	inline bool Logger::isEnabled() const
	{
		return enabled;
	}

	inline LogPriority Logger::getPriorityLevel() const
	{
		return priorityLevel;
	}

	inline int Logger::getPrefixFlag() const
	{
		return prefixFlag;
	}
	
	inline void Logger::addEntry(LogPriority priority,const std::string& entry)
	{
		getStream(priority) << entry.c_str() << "\n";
		flush();
	}

	inline void Logger::flush()
	{
		if (isEnabled()) innerStream->flush();
	}

	template <typename T> 
	Logger::Stream& Logger::Stream::operator<<(const T& entry)
	{
		if (Logger::get().isEnabled() && priority >= Logger::get().getPriorityLevel())
			innerStream << entry;
		return *this;
	}
}

#endif
