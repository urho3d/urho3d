// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_system.h"

#ifdef TB_CLIPBOARD_WINDOWS

#include <Windows.h>
#include <stdio.h>

namespace tb {

// == TBClipboard =====================================

void TBClipboard::Empty()
{
	if (OpenClipboard(NULL))
	{
		EmptyClipboard();
		CloseClipboard();
	}
}

bool TBClipboard::HasText()
{
	bool has_text = false;
	if (OpenClipboard(NULL))
	{
		has_text =	IsClipboardFormatAvailable(CF_TEXT) ||
					IsClipboardFormatAvailable(CF_OEMTEXT) ||
					IsClipboardFormatAvailable(CF_UNICODETEXT);
		CloseClipboard();
	}
	return has_text;
}

bool TBClipboard::SetText(const char *text)
{
	if (OpenClipboard(NULL))
	{
		int num_wide_chars_needed = MultiByteToWideChar(CP_UTF8, 0, text, -1, NULL, 0);
		if (HGLOBAL hClipboardData = GlobalAlloc(GMEM_DDESHARE, num_wide_chars_needed * sizeof(wchar_t)))
		{
			LPWSTR pchData = (LPWSTR) GlobalLock(hClipboardData);
			MultiByteToWideChar(CP_UTF8, 0, text, -1, pchData, num_wide_chars_needed);
			GlobalUnlock(hClipboardData);

			EmptyClipboard();
			SetClipboardData(CF_UNICODETEXT, hClipboardData);
		}

		CloseClipboard();
		return true;
	}
	return false;
}

bool TBClipboard::GetText(TBStr &text)
{
	bool success = false;
	if (HasText() && OpenClipboard(NULL))
	{
		if (HANDLE hClipboardData = GetClipboardData(CF_UNICODETEXT))
		{
			wchar_t *pchData = (wchar_t*) GlobalLock(hClipboardData);
			int len = WideCharToMultiByte(CP_UTF8, 0, pchData, -1, NULL, 0, NULL, NULL);
			if (char *utf8 = new char[len])
			{
				WideCharToMultiByte(CP_UTF8, 0, pchData, -1, utf8, len, NULL, NULL);
				success = text.Set(utf8);
				delete [] utf8;
			}
			GlobalUnlock(hClipboardData);
		}
		CloseClipboard();
	}
	return success;
}

}; // namespace tb

#endif // TB_CLIPBOARD_WINDOWS
