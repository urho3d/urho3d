// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#ifndef TB_SYSTEM_H
#define TB_SYSTEM_H

#include "tb_core.h"
#include "tb_str.h"

#ifdef TB_RUNTIME_DEBUG_INFO
void TBDebugOut(const char *str);
#define TBDebugPrint(str, ...) { tb::TBStr tmp; tmp.SetFormatted(str, __VA_ARGS__); TBDebugOut(tmp); }
#else
#define TBDebugOut(str) ((void)0)
#define TBDebugPrint(str, ...) ((void)0)
#endif

namespace tb {

// == Platform interface ===================================================

/** TBSystem is porting interface for the underlaying OS. */
class TBSystem
{
public:
	/** Get the system time in milliseconds since some undefined epoch. */
	static double GetTimeMS();

	/** Called when the need to call TBMessageHandler::ProcessMessages has changed due to changes in the
		message queue. fire_time is the new time is needs to be called.
		It may be 0 which means that ProcessMessages should be called asap (but NOT from this call!)
		It may also be TB_NOT_SOON which means that ProcessMessages doesn't need to be called. */
	static void RescheduleTimer(double fire_time);

	/** Get how many milliseconds it should take after a touch down event should generate a long click
		event. */
	static int GetLongClickDelayMS();

	/** Get how many pixels of dragging should start panning scrollable widgets. */
	static int GetPanThreshold();

	/** Get how many pixels a typical line is: The length that should be scrolled when turning a mouse
		wheel one notch. */
	static int GetPixelsPerLine();

	/** Get Dots Per Inch for the main screen. */
	static int GetDPI();
};

/** TBClipboard is a porting interface for the clipboard. */
class TBClipboard
{
public:
	/** Empty the contents of the clipboard. */
	static void Empty();

	/** Return true if the clipboard currently contains text. */
	static bool HasText();

	/** Set the text of the clipboard in UTF-8 format. */
	static bool SetText(const char *text);

	/** Get the text from the clipboard in UTF-8 format.
		Returns true on success. */
	static bool GetText(TBStr &text);
};

/** TBFile is a porting interface for file access. */
class TBFile
{
public:
	enum TBFileMode { MODE_READ };
	static TBFile *Open(const char *filename, TBFileMode mode);

	virtual ~TBFile() {}
	virtual long Size() = 0;
	virtual size_t Read(void *buf, size_t elemSize, size_t count) = 0;
};

}; // namespace tb

#endif // TB_SYSTEM_H
