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

/// \file FileListTransfer.h
/// \brief A plugin to provide a simple way to compress and incrementally send the files in the FileList structure.
///


#include "NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_FileListTransfer==1 && _RAKNET_SUPPORT_FileOperations==1

#ifndef __FILE_LIST_TRANFER_H
#define __FILE_LIST_TRANFER_H

#include "types.h"
#include "Export.h"
#include "PluginInterface2.h"
#include "DS_Map.h"
#include "types.h"
#include "PacketPriority.h"
#include "memoryoverride.h"
#include "FileList.h"
#include "DS_Queue.h"
#include "SimpleMutex.h"
#include "ThreadPool.h"

namespace SLNet
{
/// Forward declarations
class IncrementalReadInterface;
class FileListTransferCBInterface;
class FileListProgress;
struct FileListReceiver;

/// \defgroup FILE_LIST_TRANSFER_GROUP FileListTransfer
/// \brief A plugin to provide a simple way to compress and incrementally send the files in the FileList structure.
/// \details
/// \ingroup PLUGINS_GROUP

/// \brief A plugin to provide a simple way to compress and incrementally send the files in the FileList structure.
/// \details Similar to the DirectoryDeltaTransfer plugin, except that it doesn't send deltas based on pre-existing files or actually write the files to disk.
///
/// Usage:
/// Call SetupReceive to allow one file set to arrive.  The value returned by FileListTransfer::SetupReceive()<BR>
/// is the setID that is allowed.<BR>
/// It's up to you to transmit this value to the other system, along with information indicating what kind of files you want to get.<BR>
/// The other system should then prepare a FileList and call FileListTransfer::Send(), passing the return value of FileListTransfer::SetupReceive()<BR>
/// as the \a setID parameter to FileListTransfer::Send()
/// \ingroup FILE_LIST_TRANSFER_GROUP
class RAK_DLL_EXPORT FileListTransfer : public PluginInterface2
{
public:

	// GetInstance() and DestroyInstance(instance*)
	STATIC_FACTORY_DECLARATIONS(FileListTransfer)

	FileListTransfer();
	virtual ~FileListTransfer();

	/// \brief Optionally start worker threads when using _incrementalReadInterface for the Send() operation
	/// \param[in] numThreads how many worker threads to start
	/// \param[in] threadPriority Passed to the thread creation routine. Use THREAD_PRIORITY_NORMAL for Windows. For Linux based systems, you MUST pass something reasonable based on the thread priorities for your application.
	void StartIncrementalReadThreads(int numThreads, int threadPriority=-99999);
	
	/// \brief Allows one corresponding Send() call from another system to arrive.
	/// \param[in] handler The class to call on each file
	/// \param[in] deleteHandler True to delete the handler when it is no longer needed.  False to not do so.
	/// \param[in] allowedSender Which system to allow files from.
	/// \return A set ID value, which should be passed as the \a setID value to the Send() call on the other system.  This value will be returned in the callback and is unique per file set.  Returns 65535 on failure (not connected to sender)
    unsigned short SetupReceive(FileListTransferCBInterface *handler, bool deleteHandler, SystemAddress allowedSender);

	/// \brief Send the FileList structure to another system, which must have previously called SetupReceive().
	/// \param[in] fileList A list of files.  The data contained in FileList::data will be sent incrementally and compressed among all files in the set
	/// \param[in] rakPeer The instance of RakNet to use to send the message. Pass 0 to use the instance the plugin is attached to
	/// \param[in] recipient The address of the system to send to
	/// \param[in] setID The return value of SetupReceive() which was previously called on \a recipient
	/// \param[in] priority Passed to RakPeerInterface::Send()
	/// \param[in] orderingChannel Passed to RakPeerInterface::Send()
	/// \param[in] _incrementalReadInterface If a file in \a fileList has no data, _incrementalReadInterface will be used to read the file in chunks of size \a chunkSize
	/// \param[in] _chunkSize How large of a block of a file to read/send at once. Large values use more memory but transfer slightly faster.
	void Send(FileList *fileList, SLNet::RakPeerInterface *rakPeer, SystemAddress recipient, unsigned short setID, PacketPriority priority, char orderingChannel, IncrementalReadInterface *_incrementalReadInterface=0, unsigned int _chunkSize=262144*4*16);

	/// Return number of files waiting to go out to a particular address
	unsigned int GetPendingFilesToAddress(SystemAddress recipient);

	/// \brief Stop a download.
	void CancelReceive(unsigned short inSetId);

	/// \brief Remove all handlers associated with a particular system address.
	void RemoveReceiver(SystemAddress systemAddress);

	/// \brief Is a handler passed to SetupReceive still running?
	bool IsHandlerActive(unsigned short inSetId);

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

	/// \internal For plugin handling
	virtual PluginReceiveResult OnReceive(Packet *packet);
	/// \internal For plugin handling
	virtual void OnRakPeerShutdown(void);
	/// \internal For plugin handling
	virtual void OnClosedConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, PI2_LostConnectionReason lostConnectionReason );
	/// \internal For plugin handling
	virtual void Update(void);

protected:
	bool DecodeSetHeader(Packet *packet);
	bool DecodeFile(Packet *packet, bool fullFile);

	void Clear(void);

	void OnReferencePush(Packet *packet, bool fullFile);
	void OnReferencePushAck(Packet *packet);
	void SendIRIToAddress(SystemAddress systemAddress, unsigned short inSetId);

	DataStructures::Map<unsigned short, FileListReceiver*> fileListReceivers;
	unsigned short setId;
	DataStructures::List<FileListProgress*> fileListProgressCallbacks;

	struct FileToPush
	{
		FileListNode fileListNode;
		PacketPriority packetPriority;
		char orderingChannel;
		unsigned int currentOffset;
		////unsigned short setID;
		unsigned int setIndex;
		IncrementalReadInterface *incrementalReadInterface;
		unsigned int chunkSize;
	};
	struct FileToPushRecipient
	{
		unsigned int refCount;
		SimpleMutex refCountMutex;
		void DeleteThis(void);
		void AddRef(void);
		void Deref(void);

		SystemAddress systemAddress;
		unsigned short setId;

		//// SimpleMutex filesToPushMutex;
		DataStructures::Queue<FileToPush*> filesToPush;
	};
	DataStructures::List< FileToPushRecipient* > fileToPushRecipientList;
	SimpleMutex fileToPushRecipientListMutex;
	void RemoveFromList(FileToPushRecipient *ftpr);

	struct ThreadData
	{
		FileListTransfer *fileListTransfer;
		SystemAddress systemAddress;
		unsigned short setId;
	};

	ThreadPool<ThreadData, int> threadPool;

	friend int SendIRIToAddressCB(FileListTransfer::ThreadData threadData, bool *returnOutput, void* perThreadData);
};

} // namespace SLNet

#endif

#endif // _RAKNET_SUPPORT_*
