/*
 *  Original work: Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 *
 *  Modified work: Copyright (c) 2016-2018, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code was modified by SLikeSoft. Modifications are licensed under the MIT-style
 *  license found in the license.txt file in the root directory of this source tree.
 */

/// \file FileList.h
///


#include "NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_FileOperations==1

#ifndef __FILE_LIST
#define __FILE_LIST

#include "Export.h"
#include "DS_List.h"
#include "memoryoverride.h"
#include "types.h"
#include "FileListNodeContext.h"
#include "string.h"

namespace SLNet
{
	class BitStream;
}

namespace SLNet
{
/// Forward declarations
class RakPeerInterface;
class FileList;


/// Represents once instance of a file
struct FileListNode
{
	/// Name of the file
	SLNet::RakString filename;

	/// Full path to the file, which may be different than filename
	SLNet::RakString fullPathToFile;

	/// File data (may be null if not ready)
	char *data;

	/// Length of \a data. May be greater than fileLength if prepended with a file hash
	BitSize_t dataLengthBytes;

	/// Length of the file
	unsigned fileLengthBytes;

	/// User specific data for whatever, describing this file.
	FileListNodeContext context; 

	/// If true, data and dataLengthBytes should be empty. This is just storing the filename
	bool isAReference;
};

/// Callback interface set with FileList::SetCallback() in case you want progress notifications when FileList::AddFilesFromDirectory() is called
class RAK_DLL_EXPORT FileListProgress
{
public:
	// GetInstance() and DestroyInstance(instance*)
	STATIC_FACTORY_DECLARATIONS(FileListProgress)

	FileListProgress() {}
	virtual ~FileListProgress() {}

	/// First callback called when FileList::AddFilesFromDirectory() starts
	virtual void OnAddFilesFromDirectoryStarted(FileList *fileList, char *dir) {
		(void) fileList;
		(void) dir;
	}

	/// Called for each directory, when that directory begins processing
	virtual void OnDirectory(FileList *fileList, char *dir, unsigned int directoriesRemaining) {
		(void) fileList;
		(void) dir;
		(void) directoriesRemaining;
	}

	/// Called for each file, when that file begins processing
	virtual void OnFile(FileList *fileList, char *dir, char *fileName, unsigned int fileSize) {
		(void) fileList;
		(void) dir;
		(void) fileName;
		(void) fileSize;
	}

	/// \brief This function is called when we are sending a file to a remote system.
	/// \param[in] fileName The name of the file being sent
	/// \param[in] fileLengthBytes How long the file is
	/// \param[in] offset The offset in bytes into the file that we are sending
	/// \param[in] bytesBeingSent How many bytes we are sending this push
	/// \param[in] done If this file is now done with this push
	/// \param[in] targetSystem Who we are sending to
	virtual void OnFilePush(const char *fileName, unsigned int fileLengthBytes, unsigned int offset, unsigned int bytesBeingSent, bool done, SystemAddress targetSystem, unsigned short setId)
	{
		(void) fileName;
		(void) fileLengthBytes;
		(void) offset;
		(void) bytesBeingSent;
		(void) done;
		(void) targetSystem;
        (void) setId;
	}

	/// \brief This function is called when all files have been read and are being transferred to a remote system
	virtual void OnFilePushesComplete( SystemAddress systemAddress, unsigned short setId )
	{
		(void) systemAddress;
        (void) setId;
	}

	/// \brief This function is called when a send to a system was aborted (probably due to disconnection)
	virtual void OnSendAborted( SystemAddress systemAddress )
	{
		(void) systemAddress;
	}
};

/// Implementation of FileListProgress to use RAKNET_DEBUG_PRINTF
class RAK_DLL_EXPORT FLP_Printf : public FileListProgress
{
public:
	// GetInstance() and DestroyInstance(instance*)
	STATIC_FACTORY_DECLARATIONS(FLP_Printf)

	FLP_Printf() {}
	virtual ~FLP_Printf() {}

	/// First callback called when FileList::AddFilesFromDirectory() starts
	virtual void OnAddFilesFromDirectoryStarted(FileList *fileList, char *dir);

	/// Called for each directory, when that directory begins processing
	virtual void OnDirectory(FileList *fileList, char *dir, unsigned int directoriesRemaining);

	/// \brief This function is called when all files have been transferred to a particular remote system
    virtual void OnFilePushesComplete( SystemAddress systemAddress, unsigned short setID );

	/// \brief This function is called when a send to a system was aborted (probably due to disconnection)
	virtual void OnSendAborted( SystemAddress systemAddress );
};

class RAK_DLL_EXPORT FileList
{
public:
	// GetInstance() and DestroyInstance(instance*)
	STATIC_FACTORY_DECLARATIONS(FileList)

	FileList();
	~FileList();
	/// \brief Add all the files at a given directory.
	/// \param[in] applicationDirectory The first part of the path. This is not stored as part of the filename.  Use \ as the path delineator.
	/// \param[in] subDirectory The rest of the path to the file. This is stored as a prefix to the filename
	/// \param[in] writeHash The first 4 bytes is a hash of the file, with the remainder the actual file data (should \a writeData be true)
	/// \param[in] writeData Write the contents of each file
	/// \param[in] recursive Whether or not to visit subdirectories
	/// \param[in] context User defined byte to store with each file. Use for whatever you want.
	void AddFilesFromDirectory(const char *applicationDirectory, const char *subDirectory, bool writeHash, bool writeData, bool recursive, FileListNodeContext context);

	/// Deallocate all memory
	void Clear(void);

	/// Write all encoded data into a bitstream
	void Serialize(SLNet::BitStream *outBitStream);

	/// Read all encoded data from a bitstream. Clear() is called before deserializing.
	bool Deserialize(SLNet::BitStream *inBitStream);

	/// \brief Given the existing set of files, search applicationDirectory for the same files.
	/// \details For each file that is missing or different, add that file to \a missingOrChangedFiles. Note: the file contents are not written, and only the hash if written if \a alwaysWriteHash is true
	/// alwaysWriteHash and neverWriteHash are optimizations to avoid reading the file contents to generate the hash if not necessary because the file is missing or has different lengths anyway.
	/// \param[in] applicationDirectory The first part of the path. This is not stored as part of the filename. Use \ as the path delineator.
	/// \param[out] missingOrChangedFiles Output list written to
	/// \param[in] alwaysWriteHash If true, and neverWriteHash is false, will hash the file content of the file on disk, and write that as the file data with a length of SHA1_LENGTH bytes. If false, if the file length is different, will only write the filename.
	/// \param[in] neverWriteHash If true, will never write the hash, even if available. If false, will write the hash if the file lengths are the same and it was forced to do a comparison.
	void ListMissingOrChangedFiles(const char *applicationDirectory, FileList *missingOrChangedFiles, bool alwaysWriteHash, bool neverWriteHash);

	/// \brief Return the files that need to be written to make \a input match this current FileList.
	/// \details Specify dirSubset to only consider files that start with this path
	/// specify remoteSubdir to assume that all filenames in input start with this path, so strip it off when comparing filenames.
	/// \param[in] input Full list of files
	/// \param[out] output Files that we need to match input
	/// \param[in] dirSubset If the filename does not start with this path, just skip this file.
	/// \param[in] remoteSubdir Remove this from the filenames of \a input when comparing to existing filenames.
	void GetDeltaToCurrent(FileList *input, FileList *output, const char *dirSubset, const char *remoteSubdir);

	/// \brief Assuming FileList contains a list of filenames presumably without data, read the data for these filenames
	/// \param[in] applicationDirectory Prepend this path to each filename. Trailing slash will be added if necessary. Use \ as the path delineator.
	/// \param[in] writeFileData True to read and store the file data. The first SHA1_LENGTH bytes will contain the hash if \a writeFileHash is true
	/// \param[in] writeFileHash True to read and store the hash of the file data. The first SHA1_LENGTH bytes will contain the hash if \a writeFileHash is true
	/// \param[in] removeUnknownFiles If a file does not exist on disk but is in the file list, remove it from the file list?
	void PopulateDataFromDisk(const char *applicationDirectory, bool writeFileData, bool writeFileHash, bool removeUnknownFiles);

	/// By default, GetDeltaToCurrent tags files as non-references, meaning they are assumed to be populated later
	/// This tags all files as references, required for IncrementalReadInterface to process them incrementally
	void FlagFilesAsReferences(void);

	/// \brief Write all files to disk, prefixing the paths with applicationDirectory
	/// \param[in] applicationDirectory path prefix
	void WriteDataToDisk(const char *applicationDirectory);

	/// \brief Add a file, given data already in memory.
	/// \param[in] filename Name of a file, optionally prefixed with a partial or complete path. Use \ as the path delineator.
	/// \param[in] fullPathToFile Full path to the file on disk
	/// \param[in] data Contents to write
	/// \param[in] dataLength length of the data, which may be greater than fileLength should you prefix extra data, such as the hash
	/// \param[in] fileLength Length of the file
	/// \param[in] context User defined byte to store with each file. Use for whatever you want.
	/// \param[in] isAReference Means that this is just a reference to a file elsewhere - does not actually have any data
	/// \param[in] takeDataPointer If true, do not allocate dataLength. Just take the pointer passed to the \a data parameter
	void AddFile(const char *filename, const char *fullPathToFile, const char *data, const unsigned dataLength, const unsigned fileLength, FileListNodeContext context, bool isAReference=false, bool takeDataPointer=false);

	/// \brief Add a file, reading it from disk.
	/// \param[in] filepath Complete path to the file, including the filename itself
	/// \param[in] filename filename to store internally, anything you want, but usually either the complete path or a subset of the complete path.
	/// \param[in] context User defined byte to store with each file. Use for whatever you want.
	void AddFile(const char *filepath, const char *filename, FileListNodeContext context);

	/// \brief Delete all files stored in the file list.
	/// \param[in] applicationDirectory Prefixed to the path to each filename.  Use \ as the path delineator.
	void DeleteFiles(const char *applicationDirectory);

	/// \brief Adds a callback to get progress reports about what the file list instances do.
	/// \param[in] cb A pointer to an externally defined instance of FileListProgress. This pointer is held internally, so should remain valid as long as this class is valid.
	void AddCallback(FileListProgress *cb);

	/// \brief Removes a callback
	/// \param[in] cb A pointer to an externally defined instance of FileListProgress that was previously added with AddCallback()
	void RemoveCallback(FileListProgress *cb);

	/// \brief Removes all callbacks
	void ClearCallbacks(void);

	/// Returns all callbacks added with AddCallback()
	/// \param[out] callbacks The list is set to the list of callbacks
	void GetCallbacks(DataStructures::List<FileListProgress*> &callbacks);

	// Here so you can read it, but don't modify it
	DataStructures::List<FileListNode> fileList;

	static bool FixEndingSlash(char *str);
	static bool FixEndingSlash(char *str, size_t strLength);
protected:
	DataStructures::List<FileListProgress*> fileListProgressCallbacks;
};

} // namespace SLNet

#endif

#endif // _RAKNET_SUPPORT_FileOperations
