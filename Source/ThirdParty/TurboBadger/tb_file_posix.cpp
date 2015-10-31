// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_system.h"

#ifdef TB_FILE_POSIX

#include <stdio.h>

namespace tb {

class TBPosixFile : public TBFile
{
public:
	TBPosixFile(FILE *f) : file(f) {}
	virtual ~TBPosixFile() { fclose(file); }

	virtual long Size()
	{
		long oldpos = ftell(file);
		fseek(file, 0, SEEK_END);
		long num_bytes = ftell(file);
		fseek(file, oldpos, SEEK_SET);
		return num_bytes;
	}
	virtual size_t Read(void *buf, size_t elemSize, size_t count)
	{
		return fread(buf, elemSize, count, file);
	}
private:
	FILE *file;
};

// static
TBFile *TBFile::Open(const char *filename, TBFileMode mode)
{
	FILE *f = nullptr;
	switch (mode)
	{
	case MODE_READ:
		f = fopen(filename, "rb");
		break;
	default:
		break;
	}
	if (!f)
		return nullptr;
	TBPosixFile *tbf = new TBPosixFile(f);
	if (!tbf)
		fclose(f);
	return tbf;
}

}; // namespace tb

#endif // TB_FILE_POSIX
