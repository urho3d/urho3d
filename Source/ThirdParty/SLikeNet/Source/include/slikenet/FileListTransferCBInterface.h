/*
 *  Original work: Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 *
 *  Modified work: Copyright (c) 2016-2017, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code was modified by SLikeSoft. Modifications are licensed under the MIT-style
 *  license found in the license.txt file in the root directory of this source tree.
 */

/// \file FileListTransferCBInterface.h
///


#ifndef __FILE_LIST_TRANSFER_CALLBACK_INTERFACE_H
#define __FILE_LIST_TRANSFER_CALLBACK_INTERFACE_H

#include "memoryoverride.h"
#include "FileListNodeContext.h"

namespace SLNet
{

/// \brief Used by FileListTransfer plugin as a callback for when we get a file.
/// \details You get the last file when fileIndex==numberOfFilesInThisSet
/// \sa FileListTransfer
class FileListTransferCBInterface
{
public:
	// Note: If this structure is changed the struct in the swig files need to be changed as well
	struct OnFileStruct
	{
		/// \brief The index into the set of files, from 0 to numberOfFilesInThisSet
		unsigned fileIndex;

		/// \brief The name of the file
		char fileName[512];

		/// \brief The data pointed to by the file
		char *fileData;

		/// \brief The amount of data to be downloaded for this file
		BitSize_t byteLengthOfThisFile;

		/// \brief How many bytes of this file has been downloaded
		BitSize_t bytesDownloadedForThisFile;

		/// \brief Files are transmitted in sets, where more than one set of files can be transmitted at the same time.
		/// \details This is the identifier for the set, which is returned by FileListTransfer::SetupReceive
		unsigned short setID;

		/// \brief The number of files that are in this set.
		unsigned numberOfFilesInThisSet;

		/// \brief The total length of the transmitted files for this set, after being uncompressed
		unsigned byteLengthOfThisSet;

		/// \brief The total length, in bytes, downloaded for this set.
		unsigned bytesDownloadedForThisSet;

		/// \brief User data passed to one of the functions in the FileList class.
		/// \details However, on error, this is instead changed to one of the enumerations in the PatchContext structure.
		FileListNodeContext context;

		/// \brief Who sent this file
		SystemAddress senderSystemAddress;

		/// \brief Who sent this file. Not valid when using TCP, only RakPeer (UDP)
		RakNetGUID senderGuid;
	};

	// Note: If this structure is changed the struct in the swig files need to be changed as well
	struct FileProgressStruct
	{
		/// \param[out] onFileStruct General information about this file, such as the filename and the first \a partLength bytes. You do NOT need to save this data yourself. The complete file will arrive normally.
		OnFileStruct *onFileStruct;
		/// \param[out] partCount The zero based index into partTotal. The percentage complete done of this file is 100 * (partCount+1)/partTotal
		unsigned int partCount;
		/// \param[out] partTotal The total number of parts this file was split into. Each part will be roughly the MTU size, minus the UDP header and RakNet headers
		unsigned int partTotal;
		/// \param[out] dataChunkLength How many bytes long firstDataChunk and iriDataChunk are
		unsigned int dataChunkLength;
		/// \param[out] firstDataChunk The first \a partLength of the final file. If you store identifying information about the file in the first \a partLength bytes, you can read them while the download is taking place. If this hasn't arrived yet, firstDataChunk will be 0
		char *firstDataChunk;
		/// \param[out] iriDataChunk If the remote system is sending this file using IncrementalReadInterface, then this is the chunk we just downloaded. It will not exist in memory after this callback. You should either store this to disk, or in memory. If it is 0, then the file is smaller than one chunk, and will be held in memory automatically
		char *iriDataChunk;
		/// \param[out] iriWriteOffset Offset in bytes from the start of the file for the data pointed to by iriDataChunk
		unsigned int iriWriteOffset;
		/// \param[out] Who sent this file
		SystemAddress senderSystemAddress;
		/// \param[out] Who sent this file. Not valid when using TCP, only RakPeer (UDP)
		RakNetGUID senderGuid;
		/// \param[in] allocateIrIDataChunkAutomatically If true, then RakNet will hold iriDataChunk for you and return it in OnFile. Defaults to true
		bool allocateIrIDataChunkAutomatically;
	};

	struct DownloadCompleteStruct
	{
		/// \brief Files are transmitted in sets, where more than one set of files can be transmitted at the same time.
		/// \details This is the identifier for the set, which is returned by FileListTransfer::SetupReceive
		unsigned short setID;

		/// \brief The number of files that are in this set.
		unsigned numberOfFilesInThisSet;

		/// \brief The total length of the transmitted files for this set, after being uncompressed
		unsigned byteLengthOfThisSet;

		/// \brief Who sent this file
		SystemAddress senderSystemAddress;

		/// \brief Who sent this file. Not valid when using TCP, only RakPeer (UDP)
		RakNetGUID senderGuid;
	};

	FileListTransferCBInterface() {}
	virtual ~FileListTransferCBInterface() {}

	/// \brief Got a file.
	/// \details This structure is only valid for the duration of this function call.
	/// \return Return true to have RakNet delete the memory allocated to hold this file for this function call.
	virtual bool OnFile(OnFileStruct *onFileStruct)=0;

	/// \brief Got part of a big file internally in RakNet
	/// \details This is called in one of two circumstances: Either the transport layer is returning ID_PROGRESS_NOTIFICATION, or you got a block via IncrementalReadInterface
	/// If the transport layer is returning ID_PROGRESS_NOTIFICATION (see RakPeer::SetSplitMessageProgressInterval()) then FileProgressStruct::iriDataChunk will be 0.
	/// If this is a block via IncrementalReadInterface, then iriDataChunk will point to the block just downloaded.
	/// If not using IncrementalReadInterface, then you only care about partCount and partTotal to tell how far the download has progressed. YOu can use firstDataChunk to read the first part of the file if desired. The file is usable when you get the OnFile callback.
	/// If using IncrementalReadInterface and you let RakNet buffer the files in memory (default), then it is the same as above. The file is usable when you get the OnFile callback.
	/// If using IncrementalReadInterface and you do not let RakNet buffer the files in memory, then set allocateIrIDataChunkAutomatically to false. Write the file to disk whenever you get OnFileProgress and iriDataChunk is not 0, and ignore OnFile.
	virtual void OnFileProgress(FileProgressStruct *fps)=0;

	/// \brief Called while the handler is active by FileListTransfer
	/// \details Return false when you are done with the class.
	/// At that point OnDereference will be called and the class will no longer be maintained by the FileListTransfer plugin.
	virtual bool Update(void) {return true;}

	/// \brief Called when the download is completed.
	/// \details If you are finished with this class, return false.
	/// At that point OnDereference will be called and the class will no longer be maintained by the FileListTransfer plugin.
	/// Otherwise return true, and Update will continue to be called.
	virtual bool OnDownloadComplete(DownloadCompleteStruct *dcs) {(void) dcs; return false;}

	/// \brief This function is called when this instance is about to be dereferenced by the FileListTransfer plugin.
	/// \details Update will no longer be called.
	/// It will will be deleted automatically if true was passed to FileListTransfer::SetupReceive::deleteHandler
	/// Otherwise it is up to you to delete it yourself.
	virtual void OnDereference(void) {}
};

} // namespace SLNet

#endif

