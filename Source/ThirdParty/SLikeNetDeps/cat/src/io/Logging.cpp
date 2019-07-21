/*
	Copyright (c) 2009-2010 Christopher A. Taylor.  All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:

	* Redistributions of source code must retain the above copyright notice,
	  this list of conditions and the following disclaimer.
	* Redistributions in binary form must reproduce the above copyright notice,
	  this list of conditions and the following disclaimer in the documentation
	  and/or other materials provided with the distribution.
	* Neither the name of LibCat nor the names of its contributors may be used
	  to endorse or promote products derived from this software without
	  specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
	ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
	LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
	CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
	SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
	INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
	CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
	ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
	POSSIBILITY OF SUCH DAMAGE.
*/

#include <cat/io/Logging.hpp>
#include <cat/io/Settings.hpp>
#include <cat/time/Clock.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <stdexcept>
using namespace std;
using namespace cat;

#if defined(CAT_OS_WINDOWS) || defined(CAT_OS_WINDOWS_CE)
# include <cat/port/WindowsInclude.hpp>
# include <process.h>
#endif

#if defined(CAT_ISA_X86)

#if defined(CAT_WORD_64) && defined(CAT_COMPILER_MSVC)
# define CAT_ARTIFICIAL_BREAKPOINT { ::DebugBreak(); }
#elif defined(CAT_ASM_INTEL)
# define CAT_ARTIFICIAL_BREAKPOINT { CAT_ASM_BEGIN int 3 CAT_ASM_END }
#elif defined(CAT_ASM_ATT)
# define CAT_ARTIFICIAL_BREAKPOINT { CAT_ASM_BEGIN "int $3" CAT_ASM_END }
#endif

#else
# define CAT_ARTIFICIAL_BREAKPOINT
#endif


static const char *const EVENT_NAME[5] = { "Inane", "Info", "Warn", "Oops", "Fatal" };
static const char *const SHORT_EVENT_NAME[5] = { ".", "I", "W", "!", "F" };


//// Free functions

region_string cat::HexDumpString(const void *vdata, u32 bytes)
{
    /* xxxx  xx xx xx xx xx xx xx xx  xx xx xx xx xx xx xx xx   aaaaaaaaaaaaaaaa*/

    const u8 *data = (const u8*)vdata;
    u32 ii, offset;

    char ascii[17];
    ascii[16] = 0;

    region_ostringstream oss;

    for (offset = 0; offset < bytes; offset += 16)
    {
        oss << endl << setfill('0') << hex << setw(4) << offset << "  ";

        for (ii = 0; ii < 16; ++ii)
        {
            if (ii == 8)
                oss << ' ';

            if (offset + ii < bytes)
            {
                u8 ch = data[offset + ii];

                oss << setw(2) << (u32)ch << ' ';
                ascii[ii] = (ch >= ' ' && ch <= '~') ? ch : '.';
            }
            else
            {
                oss << "   ";
                ascii[ii] = 0;
            }
        }

        oss << " " << ascii;
    }

    return oss.str();
}

void cat::FatalStop(const char *message)
{
	if (Logging::ii->IsService())
	{
		Logging::ii->WriteServiceLog(LVL_FATAL, message);
	}
	else
	{
		cerr << "Fatal Stop: " << message << endl;

#if defined(CAT_OS_WINDOWS)
		OutputDebugStringA(message);
#endif
	}

	CAT_ARTIFICIAL_BREAKPOINT;

	std::exit(EXIT_FAILURE);
}

void cat::DefaultLogCallback(EventSeverity severity, const char *source, region_ostringstream &msg)
{
	if (Logging::ii->IsService())
	{
		region_ostringstream oss;
		oss << "<" << source << "> " << msg.str() << endl;

		region_string result = oss.str();

		Logging::ii->WriteServiceLog(severity, result.c_str());
	}
	else
	{
		region_ostringstream oss;
		oss << "[" << Clock::format("%b %d %H:%M") << "] <" << source << "> " << msg.str() << endl;

		region_string result = oss.str();

		cout << result.c_str();

#if defined(CAT_OS_WINDOWS)
		OutputDebugStringA(result.c_str());
#endif
	}
}


//// Logging

Logging::Logging()
{
    _callback = &DefaultLogCallback;
    _log_threshold = LVL_INANE;
	_service = false;
}

void Logging::Initialize(EventSeverity min_severity)
{
    _log_threshold = min_severity;
}

void Logging::ReadSettings()
{
    _log_threshold = Settings::ii->getInt("Log.Threshold", _log_threshold);
}

void Logging::LogEvent(Recorder *recorder)
{
	_callback(recorder->_severity, recorder->_subsystem, recorder->_msg);
}

void Logging::EnableServiceMode(const char *service_name)
{
	_service = true;

#if defined(CAT_OS_WINDOWS)
	_event_source = RegisterEventSourceA(0, service_name);
#endif
}

void Logging::WriteServiceLog(EventSeverity severity, const char *line)
{
#if defined(CAT_OS_WINDOWS)
	if (_event_source)
	{
		WORD mode;
		switch (severity)
		{
		case LVL_INANE: mode = EVENTLOG_SUCCESS; break;
		case LVL_INFO: mode = EVENTLOG_INFORMATION_TYPE; break;
		case LVL_OOPS:
		case LVL_WARN: mode = EVENTLOG_WARNING_TYPE; break;
		case LVL_FATAL: mode = EVENTLOG_ERROR_TYPE; break;
		default: return;
		}

		ReportEventA(_event_source, mode, 0, mode, 0, 1, 0, &line, 0);
	}
#endif
}


//// Recorder

Recorder::Recorder(const char *subsystem, EventSeverity severity)
{
	_subsystem = subsystem;
	_severity = severity;
}

Recorder::~Recorder()
{
	Logging::ii->LogEvent(this);
}


//// Enforcer

Enforcer::Enforcer(const char *locus)
{
    oss << locus;
}

Enforcer::~Enforcer()
{
	std::string result = oss.str();

	FatalStop(result.c_str());
}
