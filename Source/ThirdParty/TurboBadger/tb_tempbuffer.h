// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#ifndef TB_TEMP_BUFFER_H
#define TB_TEMP_BUFFER_H

namespace tb {

/** TBTempBuffer manages a buffer that will be deleted on destruction.

	The buffer size can grow by calling Reserve or Append, but it
	will never shrink during the lifetime of the object.
*/
class TBTempBuffer
{
public:
	TBTempBuffer();
	~TBTempBuffer();

	/** Make sure the buffer has at least size bytes.
		Returns false on OOM. */
	bool Reserve(int size);

	/** Get a pointer to the buffer data. */
	char *GetData() const { return m_data; }

	/** Return the size of the buffer in bytes. */
	int GetCapacity() const { return m_data_size; }

	/** Append data with size bytes at the end of the buffer and
		increase the append position with the same amount.
		Returns false on OOM. */
	bool Append(const char *data, int size);

	/** Increase the append position with size bytes without
		writing any data. This is useful if you want to write
		the data later and want to make sure space is reserved.
		Returns false on OOM. */
	bool AppendSpace(int size);

	/** Append a null terminated string (including the null termination)
		at the end of the buffer. The append position will be increased
		with the length of the text (excluding the null termination) so
		multiple calls will produce a concatenated null terminated string.
		Returns false on OOM. */
	bool AppendString(const char *str);

	/** Append a path without the ending filename.
		The buffer will be null terminated and the append position will be
		increased with the length of the path (excluding the null termination). */
	bool AppendPath(const char *full_path_and_filename);

	/** Set the position (in bytes) in the buffer where Append should write. */
	void SetAppendPos(int append_pos);

	/** Reset the append position to 0. */
	void ResetAppendPos() { m_append_pos = 0; }

	/** Return the current append position in in bytes. */
	int GetAppendPos() const { return m_append_pos; }
private:
	int GetAppendReserveSize(int needed_size) const;
	char *m_data;
	int m_data_size;
	int m_append_pos;
};

}; // namespace tb

#endif // TB_TEMP_BUFFER_H
