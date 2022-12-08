/*
 *  Original work: Copyright (c) 2014, Oculus VR, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  RakNet License.txt file in the licenses directory of this source tree. An additional grant 
 *  of patent rights can be found in the RakNet Patents.txt file in the same directory.
 *
 *
 *  Modified work: Copyright (c) 2017, SLikeSoft UG (haftungsbeschränkt)
 *
 *  This source code was modified by SLikeSoft. Modifications are licensed under the MIT-style
 *  license found in the license.txt file in the root directory of this source tree.
 */
 
///
/// \file AutopatcherRepositoryInterface.h
/// \brief An interface used by AutopatcherServer to get the data necessary to run an autopatcher.
///


#ifndef __AUTOPATCHER_REPOSITORY_INTERFACE_H
#define __AUTOPATCHER_REPOSITORY_INTERFACE_H

#include "IncrementalReadInterface.h"
#include "SimpleMutex.h"

namespace SLNet
{
/// Forward declarations
class FileList;
class BitStream;

/// An interface used by AutopatcherServer to get the data necessary to run an autopatcher.  This is up to you to implement for custom repository solutions.
class AutopatcherRepositoryInterface : public IncrementalReadInterface
{
public:
	/// Get list of files added and deleted since a certain date.  This is used by AutopatcherServer and not usually explicitly called.
	/// \param[in] applicationName A null terminated string identifying the application
	/// \param[out] addedFiles A list of the current versions of filenames with hashes as their data that were created after \a sinceData
	/// \param[out] deletedFiles A list of the current versions of filenames that were deleted after \a sinceData
	/// \param[in] An input date, in whatever format your repository uses
	/// \param[out] currentDate The current server date, in whatever format your repository uses
	/// \return True on success, false on failure.
	virtual bool GetChangelistSinceDate(const char *applicationName, FileList *addedOrModifiedFilesWithHashData, FileList *deletedFiles, double sinceDate)=0;

	/// Get patches (or files) for every file in input, assuming that input has a hash for each of those files.
	/// \param[in] applicationName A null terminated string identifying the application
	/// \param[in] input A list of files with SHA1_LENGTH byte hashes to get from the database.
	/// \param[out] patchList You should return list of files with either the filedata or the patch.  This is a subset of \a input.  The context data for each file will be either PC_WRITE_FILE (to just write the file) or PC_HASH_WITH_PATCH (to patch).  If PC_HASH_WITH_PATCH, then the file contains a SHA1_LENGTH byte patch followed by the hash.  The datalength is patchlength + SHA1_LENGTH
	/// \param[out] currentDate The current server date, in whatever format your repository uses
	/// \return 1 on success, 0 on database failure, -1 on tried to download original unmodified file
	virtual int GetPatches(const char *applicationName, FileList *input, bool allowDownloadOfOriginalUnmodifiedFiles, FileList *patchList)=0;

	/// For the most recent update, return files that were patched, added, or deleted. For files that were patched, return both the patch in \a patchedFiles and the current version in \a updatedFiles
	/// \param[in,out] applicationName Name of the application to get patches for. If empty, uses the most recently updated application, and the string will be updated to reflect this name.
	/// \param[out] patchedFiles A list of patched files with op PC_HASH_2_WITH_PATCH. It has 2 hashes, the priorHash and the currentHash. The currentHash is checked on the client after patching for patch success. The priorHash is checked in AutopatcherServer::OnGetPatch() to see if the client is able to hash with the version they currently have
	/// \param[out] patchedFiles A list of new files. It contains the actual data in addition to the filename
	/// \param[out] addedOrModifiedFileHashes A list of file hashes that were either modified or new. This is returned to the client when replying to ID_AUTOPATCHER_CREATION_LIST, which tells the client what files have changed on the server since a certain date
	/// \param[out] deletedFiles A list of the current versions of filenames that were deleted in the most recent patch
	/// \param[out] whenPatched time in seconds since epoch when patched. Use time() function to get this in C
	/// \return true on success, false on failure
	virtual bool GetMostRecentChangelistWithPatches(
		SLNet::RakString &applicationName,
		FileList *patchedFiles,
		FileList *updatedFiles,
		FileList *addedOrModifiedFileHashes,
		FileList *deletedFiles,
		double *priorRowPatchTime,
		double *mostRecentRowPatchTime)=0;

	/// \return Whatever this function returns is sent from the AutopatcherServer to the AutopatcherClient when one of the above functions returns false.
	virtual const char *GetLastError(void) const=0;

	/// \return Passed to FileListTransfer::Send() as the _chunkSize parameter.
	virtual const int GetIncrementalReadChunkSize(void) const=0;
};

} // namespace SLNet

#endif

