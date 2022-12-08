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

#include "slikenet/NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_FileListTransfer==1 && _RAKNET_SUPPORT_FileOperations==1

#include "slikenet/FileListTransfer.h"
#include "slikenet/DS_HuffmanEncodingTree.h"
#include "slikenet/FileListTransferCBInterface.h"
#include "slikenet/StringCompressor.h"
#include "slikenet/FileList.h"
#include "slikenet/DS_Queue.h"
#include "slikenet/MessageIdentifiers.h"
#include "slikenet/types.h"
#include "slikenet/peerinterface.h"
#include "slikenet/statistics.h"
#include "slikenet/IncrementalReadInterface.h"
#include "slikenet/assert.h"
#include "slikenet/alloca.h"

namespace SLNet
{

struct FLR_MemoryBlock
{
	char *flrMemoryBlock;
};

struct FileListReceiver
{
	FileListReceiver();
	~FileListReceiver();
	FileListTransferCBInterface *downloadHandler;
	SystemAddress allowedSender;
	unsigned short setID;
	unsigned setCount;
	unsigned setTotalCompressedTransmissionLength;
	unsigned setTotalFinalLength;
	unsigned setTotalDownloadedLength;
	bool gotSetHeader;
	bool deleteDownloadHandler;
	bool isCompressed;
	int  filesReceived;
	DataStructures::Map<unsigned int, FLR_MemoryBlock> pushedFiles;

	// Notifications
	unsigned int partLength;

};

} // namespace SLNet

using namespace SLNet;

FileListReceiver::FileListReceiver() {filesReceived=0; setTotalDownloadedLength=0; partLength=1; DataStructures::Map<unsigned int, FLR_MemoryBlock>::IMPLEMENT_DEFAULT_COMPARISON();}
FileListReceiver::~FileListReceiver() {
	unsigned int i=0;
	for (i=0; i < pushedFiles.Size(); i++)
		rakFree_Ex(pushedFiles[i].flrMemoryBlock, _FILE_AND_LINE_ );
}

STATIC_FACTORY_DEFINITIONS(FileListTransfer,FileListTransfer)

void FileListTransfer::FileToPushRecipient::DeleteThis(void)
{
////	filesToPushMutex.Lock();
	for (unsigned int j=0; j < filesToPush.Size(); j++)
		SLNet::OP_DELETE(filesToPush[j],_FILE_AND_LINE_);
////	filesToPushMutex.Unlock();
	SLNet::OP_DELETE(this,_FILE_AND_LINE_);
}
void FileListTransfer::FileToPushRecipient::AddRef(void)
{
	refCountMutex.Lock();
	++refCount;
	refCountMutex.Unlock();
}
void FileListTransfer::FileToPushRecipient::Deref(void)
{
	refCountMutex.Lock();
	--refCount;
	if (refCount==0)
	{
		refCountMutex.Unlock();
		DeleteThis();
		return;
	}
	refCountMutex.Unlock();
}
FileListTransfer::FileListTransfer()
{
	setId=0;
	DataStructures::Map<unsigned short, FileListReceiver*>::IMPLEMENT_DEFAULT_COMPARISON();
}
FileListTransfer::~FileListTransfer()
{
	threadPool.StopThreads();
	Clear();
}
void FileListTransfer::StartIncrementalReadThreads(int numThreads, int threadPriority)
{
	(void) threadPriority;

	threadPool.StartThreads(numThreads, 0);
}
unsigned short FileListTransfer::SetupReceive(FileListTransferCBInterface *handler, bool deleteHandler, SystemAddress allowedSender)
{
	if (rakPeerInterface && rakPeerInterface->GetConnectionState(allowedSender)!=IS_CONNECTED)
		return (unsigned short)-1;
	FileListReceiver *receiver;

	if (fileListReceivers.Has(setId))
	{
		receiver=fileListReceivers.Get(setId);
		receiver->downloadHandler->OnDereference();
		if (receiver->deleteDownloadHandler)
			SLNet::OP_DELETE(receiver->downloadHandler, _FILE_AND_LINE_);
		SLNet::OP_DELETE(receiver, _FILE_AND_LINE_);
		fileListReceivers.Delete(setId);
	}

	unsigned short oldId;
	receiver = SLNet::OP_NEW<FileListReceiver>( _FILE_AND_LINE_ );
	RakAssert(handler);
	receiver->downloadHandler=handler;
	receiver->allowedSender=allowedSender;
	receiver->gotSetHeader=false;
	receiver->deleteDownloadHandler=deleteHandler;
	receiver->setID=setId;
	fileListReceivers.Set(setId, receiver);
	oldId=setId;
	if (++setId==(unsigned short)-1)
		setId=0;
	return oldId;
}

void FileListTransfer::Send(FileList *fileList, SLNet::RakPeerInterface *rakPeer, SystemAddress recipient, unsigned short setID, PacketPriority priority, char orderingChannel, IncrementalReadInterface *_incrementalReadInterface, unsigned int _chunkSize)
{
	for (unsigned int flpcIndex=0; flpcIndex < fileListProgressCallbacks.Size(); flpcIndex++)
		fileList->AddCallback(fileListProgressCallbacks[flpcIndex]);

	unsigned int i, totalLength;
	SLNet::BitStream outBitstream;
	bool sendReference;
	const char *dataBlocks[2];
	int lengths[2];
	totalLength=0;
	for (i=0; i < fileList->fileList.Size(); i++)
	{
		const FileListNode &fileListNode = fileList->fileList[i];
		totalLength+=fileListNode.dataLengthBytes;
	}

	// Write the chunk header, which contains the frequency table, the total number of files, and the total number of bytes
	bool anythingToWrite;
	outBitstream.Write((MessageID)ID_FILE_LIST_TRANSFER_HEADER);
	outBitstream.Write(setID);
	anythingToWrite=fileList->fileList.Size()>0;
	outBitstream.Write(anythingToWrite);
	if (anythingToWrite)
	{
		outBitstream.WriteCompressed(fileList->fileList.Size());
		outBitstream.WriteCompressed(totalLength);

		if (rakPeer)
			rakPeer->Send(&outBitstream, priority, RELIABLE_ORDERED, orderingChannel, recipient, false);
		else
			SendUnified(&outBitstream, priority, RELIABLE_ORDERED, orderingChannel, recipient, false);

		DataStructures::Queue<FileToPush*> filesToPush;
	
		for (i=0; i < fileList->fileList.Size(); i++)
		{
			sendReference = fileList->fileList[i].isAReference && _incrementalReadInterface!=0;
			if (sendReference)
			{
				FileToPush *fileToPush = SLNet::OP_NEW<FileToPush>(_FILE_AND_LINE_);
				fileToPush->fileListNode.context=fileList->fileList[i].context;
				fileToPush->setIndex=i;
				fileToPush->fileListNode.filename=fileList->fileList[i].filename;
				fileToPush->fileListNode.fullPathToFile=fileList->fileList[i].fullPathToFile;
				fileToPush->fileListNode.fileLengthBytes=fileList->fileList[i].fileLengthBytes;
				fileToPush->fileListNode.dataLengthBytes=fileList->fileList[i].dataLengthBytes;
				//	fileToPush->systemAddress=recipient;
				//fileToPush->setID=setID;
				fileToPush->packetPriority=priority;
				fileToPush->orderingChannel=orderingChannel;
				fileToPush->currentOffset=0;
				fileToPush->incrementalReadInterface=_incrementalReadInterface;
				fileToPush->chunkSize=_chunkSize;
				filesToPush.Push(fileToPush,_FILE_AND_LINE_);
			}
			else
			{
				outBitstream.Reset();
				outBitstream.Write((MessageID)ID_FILE_LIST_TRANSFER_FILE);
				outBitstream << fileList->fileList[i].context;
				// outBitstream.Write(fileList->fileList[i].context);
				outBitstream.Write(setID);
				StringCompressor::Instance()->EncodeString(fileList->fileList[i].filename, 512, &outBitstream);

				outBitstream.WriteCompressed(i);
				outBitstream.WriteCompressed(fileList->fileList[i].dataLengthBytes); // Original length in bytes

				outBitstream.AlignWriteToByteBoundary();

				dataBlocks[0]=(char*) outBitstream.GetData();
				lengths[0]=outBitstream.GetNumberOfBytesUsed();
				dataBlocks[1]=fileList->fileList[i].data;
				lengths[1]=fileList->fileList[i].dataLengthBytes;
				SendListUnified(dataBlocks,lengths,2,priority, RELIABLE_ORDERED, orderingChannel, recipient, false);
			}
		}

		if (filesToPush.IsEmpty()==false)
		{
			FileToPushRecipient *ftpr;

			fileToPushRecipientListMutex.Lock();
			for (i=0; i < fileToPushRecipientList.Size(); i++)
			{
				if (fileToPushRecipientList[i]->systemAddress==recipient && fileToPushRecipientList[i]->setId==setId)
				{
// 					ftpr=fileToPushRecipientList[i];
// 					ftpr->AddRef();
// 					break;
					RakAssert("setId already in use for this recipient" && 0);
				}
			}
			fileToPushRecipientListMutex.Unlock();

			//if (ftpr==0)
			//{
				ftpr = SLNet::OP_NEW<FileToPushRecipient>(_FILE_AND_LINE_);
				ftpr->systemAddress=recipient;
				ftpr->setId=setID;
				ftpr->refCount=2; // Allocated and in the list
				fileToPushRecipientList.Push(ftpr, _FILE_AND_LINE_);
			//}
			while (filesToPush.IsEmpty()==false)
			{
				////ftpr->filesToPushMutex.Lock();
				ftpr->filesToPush.Push(filesToPush.Pop(), _FILE_AND_LINE_);
				////ftpr->filesToPushMutex.Unlock();
			}
			// ftpr out of scope
			ftpr->Deref();
			SendIRIToAddress(recipient, setID);
			return;
		}
		else
		{
			for (unsigned int flpcIndex=0; flpcIndex < fileListProgressCallbacks.Size(); flpcIndex++)
				fileListProgressCallbacks[flpcIndex]->OnFilePushesComplete(recipient, setID);
		}
	}
	else
	{
		for (unsigned int flpcIndex=0; flpcIndex < fileListProgressCallbacks.Size(); flpcIndex++)
			fileListProgressCallbacks[flpcIndex]->OnFilePushesComplete(recipient, setID);

		if (rakPeer)
			rakPeer->Send(&outBitstream, priority, RELIABLE_ORDERED, orderingChannel, recipient, false);
		else
			SendUnified(&outBitstream, priority, RELIABLE_ORDERED, orderingChannel, recipient, false);
	}
}

bool FileListTransfer::DecodeSetHeader(Packet *packet)
{
	bool anythingToWrite=false;
	unsigned short setID;
	SLNet::BitStream inBitStream(packet->data, packet->length, false);
	inBitStream.IgnoreBits(8);
	inBitStream.Read(setID);
	FileListReceiver *fileListReceiver;
	if (fileListReceivers.Has(setID)==false)
	{
		// If this assert hits you didn't call SetupReceive
#ifdef _DEBUG
		RakAssert(0);
#endif
		return false;
	}
	fileListReceiver=fileListReceivers.Get(setID);
	if (fileListReceiver->allowedSender!=packet->systemAddress)
	{
#ifdef _DEBUG
		RakAssert(0);
#endif
		return false;
	}

#ifdef _DEBUG
	RakAssert(fileListReceiver->gotSetHeader==false);
#endif

	inBitStream.Read(anythingToWrite);

	if (anythingToWrite)
	{
		inBitStream.ReadCompressed(fileListReceiver->setCount);
		if (inBitStream.ReadCompressed(fileListReceiver->setTotalFinalLength))
		{
			fileListReceiver->setTotalCompressedTransmissionLength=fileListReceiver->setTotalFinalLength;
			fileListReceiver->gotSetHeader=true;
			return true;
		}

	}
	else
	{
		FileListTransferCBInterface::DownloadCompleteStruct dcs;
		dcs.setID=fileListReceiver->setID;
		dcs.numberOfFilesInThisSet=fileListReceiver->setCount;
		dcs.byteLengthOfThisSet=fileListReceiver->setTotalFinalLength;
		dcs.senderSystemAddress=packet->systemAddress;
		dcs.senderGuid=packet->guid;

		if (fileListReceiver->downloadHandler->OnDownloadComplete(&dcs)==false)
		{
			fileListReceiver->downloadHandler->OnDereference();
			fileListReceivers.Delete(setID);
			if (fileListReceiver->deleteDownloadHandler)
				SLNet::OP_DELETE(fileListReceiver->downloadHandler, _FILE_AND_LINE_);
			SLNet::OP_DELETE(fileListReceiver, _FILE_AND_LINE_);
		}

		return true;
	}

	return false;
}

bool FileListTransfer::DecodeFile(Packet *packet, bool isTheFullFile)
{
	FileListTransferCBInterface::OnFileStruct onFileStruct;
	SLNet::BitStream inBitStream(packet->data, packet->length, false);
	inBitStream.IgnoreBits(8);

	onFileStruct.senderSystemAddress=packet->systemAddress;
	onFileStruct.senderGuid=packet->guid;

	unsigned int partCount=0;
	unsigned int partTotal=0;
	unsigned int partLength=0;
	onFileStruct.fileData=0;
	if (isTheFullFile==false)
	{
		// Disable endian swapping on reading this, as it's generated locally in ReliabilityLayer.cpp
		inBitStream.ReadBits( (unsigned char* ) &partCount, BYTES_TO_BITS(sizeof(partCount)), true );
		inBitStream.ReadBits( (unsigned char* ) &partTotal, BYTES_TO_BITS(sizeof(partTotal)), true );
		inBitStream.ReadBits( (unsigned char* ) &partLength, BYTES_TO_BITS(sizeof(partLength)), true );
		inBitStream.IgnoreBits(8);
		// The header is appended to every chunk, which we continue to read after this statement flrMemoryBlock
	}
	inBitStream >> onFileStruct.context;
	// inBitStream.Read(onFileStruct.context);
	inBitStream.Read(onFileStruct.setID);
	FileListReceiver *fileListReceiver;
	if (fileListReceivers.Has(onFileStruct.setID)==false)
	{
		return false;
	}
	fileListReceiver=fileListReceivers.Get(onFileStruct.setID);
	if (fileListReceiver->allowedSender!=packet->systemAddress)
	{
#ifdef _DEBUG
		RakAssert(0);
#endif
		return false;
	}

#ifdef _DEBUG
	RakAssert(fileListReceiver->gotSetHeader==true);
#endif

	if (StringCompressor::Instance()->DecodeString(onFileStruct.fileName, 512, &inBitStream)==false)
	{
#ifdef _DEBUG
		RakAssert(0);
#endif
		return false;
	}

	inBitStream.ReadCompressed(onFileStruct.fileIndex);
	inBitStream.ReadCompressed(onFileStruct.byteLengthOfThisFile);

	onFileStruct.numberOfFilesInThisSet=fileListReceiver->setCount;
	onFileStruct.byteLengthOfThisSet=fileListReceiver->setTotalFinalLength;

	if (isTheFullFile)
	{
		onFileStruct.bytesDownloadedForThisFile=onFileStruct.byteLengthOfThisFile;
		fileListReceiver->setTotalDownloadedLength+=onFileStruct.byteLengthOfThisFile;
		onFileStruct.bytesDownloadedForThisSet=fileListReceiver->setTotalDownloadedLength;
	}
	else
	{
		onFileStruct.bytesDownloadedForThisFile=partLength*partCount;
		onFileStruct.bytesDownloadedForThisSet=fileListReceiver->setTotalDownloadedLength+onFileStruct.bytesDownloadedForThisFile;
	}

	// User callback for this file.
	if (isTheFullFile)
	{
		inBitStream.AlignReadToByteBoundary();
		onFileStruct.fileData = (char*) rakMalloc_Ex( (size_t) onFileStruct.byteLengthOfThisFile, _FILE_AND_LINE_ );
		inBitStream.Read((char*)onFileStruct.fileData, onFileStruct.byteLengthOfThisFile);

		FileListTransferCBInterface::FileProgressStruct fps;
		fps.onFileStruct=&onFileStruct;
		fps.partCount=1;
		fps.partTotal=1;
		fps.dataChunkLength=onFileStruct.byteLengthOfThisFile;
		fps.firstDataChunk=onFileStruct.fileData;
		fps.iriDataChunk=onFileStruct.fileData;
		fps.allocateIrIDataChunkAutomatically=true;
		fps.iriWriteOffset=0;
		fps.senderSystemAddress=packet->systemAddress;
		fps.senderGuid=packet->guid;
		fileListReceiver->downloadHandler->OnFileProgress(&fps);

		// Got a complete file
		// Either we are using IncrementalReadInterface and it was a small file or
		// We are not using IncrementalReadInterface
		if (fileListReceiver->downloadHandler->OnFile(&onFileStruct))
			rakFree_Ex(onFileStruct.fileData, _FILE_AND_LINE_ );

		fileListReceiver->filesReceived++;

		// If this set is done, free the memory for it.
		if ((int) fileListReceiver->setCount==fileListReceiver->filesReceived)
		{
			FileListTransferCBInterface::DownloadCompleteStruct dcs;
			dcs.setID=fileListReceiver->setID;
			dcs.numberOfFilesInThisSet=fileListReceiver->setCount;
			dcs.byteLengthOfThisSet=fileListReceiver->setTotalFinalLength;
			dcs.senderSystemAddress=packet->systemAddress;
			dcs.senderGuid=packet->guid;

			if (fileListReceiver->downloadHandler->OnDownloadComplete(&dcs)==false)
			{
				fileListReceiver->downloadHandler->OnDereference();
				if (fileListReceiver->deleteDownloadHandler)
					SLNet::OP_DELETE(fileListReceiver->downloadHandler, _FILE_AND_LINE_);
				fileListReceivers.Delete(onFileStruct.setID);
				SLNet::OP_DELETE(fileListReceiver, _FILE_AND_LINE_);
			}
		}

	}
	else
	{
		inBitStream.AlignReadToByteBoundary();

		char *firstDataChunk;
		unsigned int unreadBits = inBitStream.GetNumberOfUnreadBits();
		unsigned int unreadBytes = BITS_TO_BYTES(unreadBits);
		firstDataChunk=(char*) inBitStream.GetData()+BITS_TO_BYTES(inBitStream.GetReadOffset());

		FileListTransferCBInterface::FileProgressStruct fps;
		fps.onFileStruct=&onFileStruct;
		fps.partCount=partCount;
		fps.partTotal=partTotal;
		fps.dataChunkLength=unreadBytes;
		fps.firstDataChunk=firstDataChunk;
		fps.iriDataChunk=0;
		fps.allocateIrIDataChunkAutomatically=true;
		fps.iriWriteOffset=0;
		fps.senderSystemAddress=packet->systemAddress;
		fps.senderGuid=packet->guid;

		// Remote system is sending a complete file, but the file is large enough that we get ID_PROGRESS_NOTIFICATION from the transport layer
		fileListReceiver->downloadHandler->OnFileProgress(&fps);

	}

	return true;
}
PluginReceiveResult FileListTransfer::OnReceive(Packet *packet)
{
	switch (packet->data[0]) 
	{
	case ID_FILE_LIST_TRANSFER_HEADER:
		DecodeSetHeader(packet);
		return RR_STOP_PROCESSING_AND_DEALLOCATE;
	case ID_FILE_LIST_TRANSFER_FILE:
		DecodeFile(packet, true);
		return RR_STOP_PROCESSING_AND_DEALLOCATE;
	case ID_FILE_LIST_REFERENCE_PUSH:
		OnReferencePush(packet, true);
		return RR_STOP_PROCESSING_AND_DEALLOCATE;
	case ID_FILE_LIST_REFERENCE_PUSH_ACK:
		OnReferencePushAck(packet);
		return RR_STOP_PROCESSING_AND_DEALLOCATE;
	case ID_DOWNLOAD_PROGRESS:
		if (packet->length>sizeof(MessageID)+sizeof(unsigned int)*3)
		{
			if (packet->data[sizeof(MessageID)+sizeof(unsigned int)*3]==ID_FILE_LIST_TRANSFER_FILE)
			{
				DecodeFile(packet, false);
				return RR_STOP_PROCESSING_AND_DEALLOCATE;
			}
			if (packet->data[sizeof(MessageID)+sizeof(unsigned int)*3]==ID_FILE_LIST_REFERENCE_PUSH)
			{
				OnReferencePush(packet, false);
				return RR_STOP_PROCESSING_AND_DEALLOCATE;
			}
		}
		break;
	}

	return RR_CONTINUE_PROCESSING;
}
void FileListTransfer::OnRakPeerShutdown(void)
{
	threadPool.StopThreads();
	threadPool.ClearInput();
	Clear();	
}
void FileListTransfer::Clear(void)
{
	unsigned i;
	for (i=0; i < fileListReceivers.Size(); i++)
	{
		fileListReceivers[i]->downloadHandler->OnDereference();
		if (fileListReceivers[i]->deleteDownloadHandler)
			SLNet::OP_DELETE(fileListReceivers[i]->downloadHandler, _FILE_AND_LINE_);
		SLNet::OP_DELETE(fileListReceivers[i], _FILE_AND_LINE_);
	}
	fileListReceivers.Clear();

	fileToPushRecipientListMutex.Lock();
	for (i=0; i < fileToPushRecipientList.Size(); i++)
	{
		FileToPushRecipient *ftpr = fileToPushRecipientList[i];
		// Taken out of the list
		ftpr->Deref();
	}
	fileToPushRecipientList.Clear(false,_FILE_AND_LINE_);
	fileToPushRecipientListMutex.Unlock();

	//filesToPush.Clear(false, _FILE_AND_LINE_);
}
void FileListTransfer::OnClosedConnection(const SystemAddress &systemAddress, RakNetGUID rakNetGUID, PI2_LostConnectionReason lostConnectionReason )
{
	(void) lostConnectionReason;
	(void) rakNetGUID;

	RemoveReceiver(systemAddress);
}
void FileListTransfer::CancelReceive(unsigned short inSetId)
{
	if (fileListReceivers.Has(inSetId)==false)
	{
#ifdef _DEBUG
		RakAssert(0);
#endif
		return;
	}
	FileListReceiver *fileListReceiver=fileListReceivers.Get(inSetId);
	fileListReceiver->downloadHandler->OnDereference();
	if (fileListReceiver->deleteDownloadHandler)
		SLNet::OP_DELETE(fileListReceiver->downloadHandler, _FILE_AND_LINE_);
	SLNet::OP_DELETE(fileListReceiver, _FILE_AND_LINE_);
	fileListReceivers.Delete(inSetId);
}
void FileListTransfer::RemoveReceiver(SystemAddress systemAddress)
{
	unsigned i;
	i=0;
	threadPool.LockInput();
	while (i < threadPool.InputSize())
	{
		if (threadPool.GetInputAtIndex(i).systemAddress==systemAddress)
		{
			threadPool.RemoveInputAtIndex(i);
		}
		else
			i++;
	}
	threadPool.UnlockInput();

	i=0;
	while (i < fileListReceivers.Size())
	{
		if (fileListReceivers[i]->allowedSender==systemAddress)
		{
			fileListReceivers[i]->downloadHandler->OnDereference();
			if (fileListReceivers[i]->deleteDownloadHandler)
				SLNet::OP_DELETE(fileListReceivers[i]->downloadHandler, _FILE_AND_LINE_);
			SLNet::OP_DELETE(fileListReceivers[i], _FILE_AND_LINE_);
			fileListReceivers.RemoveAtIndex(i);
		}
		else
			i++;
	}

	fileToPushRecipientListMutex.Lock();
	i=0;
	while (i < fileToPushRecipientList.Size())
	{
		if (fileToPushRecipientList[i]->systemAddress==systemAddress)
		{
			FileToPushRecipient *ftpr = fileToPushRecipientList[i];

			// Tell the user that this recipient was lost
			for (unsigned int flpcIndex=0; flpcIndex < fileListProgressCallbacks.Size(); flpcIndex++)
				fileListProgressCallbacks[flpcIndex]->OnSendAborted(ftpr->systemAddress);

			fileToPushRecipientList.RemoveAtIndex(i);
			// Taken out of the list
			ftpr->Deref();
		}
		else
		{
			i++;
		}
	}
	fileToPushRecipientListMutex.Unlock();
}
bool FileListTransfer::IsHandlerActive(unsigned short inSetId)
{
	return fileListReceivers.Has(inSetId);
}
void FileListTransfer::AddCallback(FileListProgress *cb)
{
	if (cb==0)
		return;

	if (fileListProgressCallbacks.GetIndexOf(cb)==(unsigned int) -1)
		fileListProgressCallbacks.Push(cb, _FILE_AND_LINE_);
}
void FileListTransfer::RemoveCallback(FileListProgress *cb)
{
	unsigned int idx = fileListProgressCallbacks.GetIndexOf(cb);
	if (idx!=(unsigned int) -1)
		fileListProgressCallbacks.RemoveAtIndex(idx);
}
void FileListTransfer::ClearCallbacks(void)
{
	fileListProgressCallbacks.Clear(true, _FILE_AND_LINE_);
}
void FileListTransfer::GetCallbacks(DataStructures::List<FileListProgress*> &callbacks)
{
	callbacks = fileListProgressCallbacks;
}

void FileListTransfer::Update(void)
{
	unsigned i;
	i=0;
	while (i < fileListReceivers.Size())
	{
		if (fileListReceivers[i]->downloadHandler->Update()==false)
		{
			fileListReceivers[i]->downloadHandler->OnDereference();
			if (fileListReceivers[i]->deleteDownloadHandler)
				SLNet::OP_DELETE(fileListReceivers[i]->downloadHandler, _FILE_AND_LINE_);
			SLNet::OP_DELETE(fileListReceivers[i], _FILE_AND_LINE_);
			fileListReceivers.RemoveAtIndex(i);
		}
		else
			i++;
	}
}
void FileListTransfer::OnReferencePush(Packet *packet, bool isTheFullFile)
{
	SLNet::BitStream refPushAck;
	if (isTheFullFile==false)
	{
		// 12/23/09 Why do I care about ID_DOWNLOAD_PROGRESS for reference pushes?
		// 2/16/2012 I care because a reference push is 16 megabytes by default. Also, if it is the last file "if (ftpr->filesToPush.Size()<2)" or total file size exceeds smallFileTotalSize it always sends a reference push.
//		return;
	}

	FileListTransferCBInterface::OnFileStruct onFileStruct;
	SLNet::BitStream inBitStream(packet->data, packet->length, false);
	inBitStream.IgnoreBits(8);

	unsigned int partCount=0;
	unsigned int partTotal=1;
	unsigned int partLength=0;
	onFileStruct.fileData=0;
	if (isTheFullFile==false)
	{
		// Disable endian swapping on reading this, as it's generated locally in ReliabilityLayer.cpp
		inBitStream.ReadBits( (unsigned char* ) &partCount, BYTES_TO_BITS(sizeof(partCount)), true );
		inBitStream.ReadBits( (unsigned char* ) &partTotal, BYTES_TO_BITS(sizeof(partTotal)), true );
		inBitStream.ReadBits( (unsigned char* ) &partLength, BYTES_TO_BITS(sizeof(partLength)), true );
		inBitStream.IgnoreBits(8);
		// The header is appended to every chunk, which we continue to read after this statement flrMemoryBlock
	}

	inBitStream >> onFileStruct.context;
	inBitStream.Read(onFileStruct.setID);

	// This is not a progress notification, it is actually the entire packet
	if (isTheFullFile==true)
	{
		refPushAck.Write((MessageID)ID_FILE_LIST_REFERENCE_PUSH_ACK);
		refPushAck.Write(onFileStruct.setID);
		SendUnified(&refPushAck,HIGH_PRIORITY, RELIABLE, 0, packet->systemAddress, false);
	}

	// inBitStream.Read(onFileStruct.context);
	FileListReceiver *fileListReceiver;
	if (fileListReceivers.Has(onFileStruct.setID)==false)
	{
		return;
	}
	fileListReceiver=fileListReceivers.Get(onFileStruct.setID);
	if (fileListReceiver->allowedSender!=packet->systemAddress)
	{
#ifdef _DEBUG
		RakAssert(0);
#endif
		return;
	}

#ifdef _DEBUG
	RakAssert(fileListReceiver->gotSetHeader==true);
#endif

	if (StringCompressor::Instance()->DecodeString(onFileStruct.fileName, 512, &inBitStream)==false)
	{
#ifdef _DEBUG
		RakAssert(0);
#endif
		return;
	}

	inBitStream.ReadCompressed(onFileStruct.fileIndex);
	inBitStream.ReadCompressed(onFileStruct.byteLengthOfThisFile);
	unsigned int offset;
	unsigned int chunkLength;
	inBitStream.ReadCompressed(offset);
	inBitStream.ReadCompressed(chunkLength);

	bool lastChunk=false;
	inBitStream.Read(lastChunk);
	bool finished = lastChunk && isTheFullFile;

	if (isTheFullFile==false)
		fileListReceiver->partLength=partLength;

	FLR_MemoryBlock mb;
	if (fileListReceiver->pushedFiles.Has(onFileStruct.fileIndex)==false)
	{
		if (onFileStruct.byteLengthOfThisFile <= SLNET_MAX_RETRIEVABLE_FILESIZE)
			mb.flrMemoryBlock = (char*)rakMalloc_Ex(onFileStruct.byteLengthOfThisFile, _FILE_AND_LINE_);
		else
			mb.flrMemoryBlock = nullptr;
		fileListReceiver->pushedFiles.SetNew(onFileStruct.fileIndex, mb);
	}
	else
	{
		mb=fileListReceiver->pushedFiles.Get(onFileStruct.fileIndex);
	}
	
	unsigned int unreadBits = inBitStream.GetNumberOfUnreadBits();
	unsigned int unreadBytes = BITS_TO_BYTES(unreadBits);
	unsigned int amountToRead;
	if (isTheFullFile)
		amountToRead=chunkLength;
	else
		amountToRead=unreadBytes;

	inBitStream.AlignReadToByteBoundary();

	FileListTransferCBInterface::FileProgressStruct fps;

	if (isTheFullFile)
	{
		if (mb.flrMemoryBlock)
		{
			// Either the very first block, or a subsequent block and allocateIrIDataChunkAutomatically was true for the first block
			memcpy(mb.flrMemoryBlock+offset, inBitStream.GetData()+BITS_TO_BYTES(inBitStream.GetReadOffset()), amountToRead);
			fps.iriDataChunk=mb.flrMemoryBlock+offset;
		}
		else
		{
			// In here mb.flrMemoryBlock is null
			// This means the first block explicitly deallocated the memory, and no blocks will be permanently held by RakNet
			fps.iriDataChunk=(char*) inBitStream.GetData()+BITS_TO_BYTES(inBitStream.GetReadOffset());
		}

		onFileStruct.bytesDownloadedForThisFile=offset+chunkLength;
		fileListReceiver->setTotalDownloadedLength+=chunkLength;
		onFileStruct.bytesDownloadedForThisSet=fileListReceiver->setTotalDownloadedLength;
	}
	else
	{
		onFileStruct.bytesDownloadedForThisFile=offset+partLength*partCount;
		onFileStruct.bytesDownloadedForThisSet=fileListReceiver->setTotalDownloadedLength+partCount*partLength;
		fps.iriDataChunk=(char*) inBitStream.GetData()+BITS_TO_BYTES(inBitStream.GetReadOffset());
	}

	onFileStruct.numberOfFilesInThisSet=fileListReceiver->setCount;
//	onFileStruct.setTotalCompressedTransmissionLength=fileListReceiver->setTotalCompressedTransmissionLength;
	onFileStruct.byteLengthOfThisSet=fileListReceiver->setTotalFinalLength;
	// Note: mb.flrMemoryBlock may be null here
	onFileStruct.fileData=mb.flrMemoryBlock;
	onFileStruct.senderSystemAddress=packet->systemAddress;
	onFileStruct.senderGuid=packet->guid;

	unsigned int totalNotifications;
	unsigned int currentNotificationIndex;
	if (chunkLength==0 || chunkLength==onFileStruct.byteLengthOfThisFile)
		totalNotifications=1;
	else
		totalNotifications = onFileStruct.byteLengthOfThisFile / chunkLength + 1;

	if (chunkLength==0)
		currentNotificationIndex = 0;
	else
		currentNotificationIndex = offset / chunkLength; 

	fps.onFileStruct=&onFileStruct;
	fps.partCount=currentNotificationIndex;
	fps.partTotal=totalNotifications;
	fps.dataChunkLength=amountToRead;
	fps.firstDataChunk=mb.flrMemoryBlock;
	fps.allocateIrIDataChunkAutomatically=true;
	fps.onFileStruct->fileData=mb.flrMemoryBlock;
	fps.iriWriteOffset=offset;
	fps.senderSystemAddress=packet->systemAddress;
	fps.senderGuid=packet->guid;

	if (finished)
	{
		char *oldFileData=fps.onFileStruct->fileData;
		if (fps.partCount==0)
			fps.firstDataChunk=fps.iriDataChunk;
		if (fps.partTotal==1)
			fps.onFileStruct->fileData=fps.iriDataChunk;
		fileListReceiver->downloadHandler->OnFileProgress(&fps);

		// Incremental read interface sent us a file chunk
		// This is the last file chunk we were waiting for to consider the file done
		if (fileListReceiver->downloadHandler->OnFile(&onFileStruct))
			rakFree_Ex(oldFileData, _FILE_AND_LINE_ );
		fileListReceiver->pushedFiles.Delete(onFileStruct.fileIndex);

		fileListReceiver->filesReceived++;

		// If this set is done, free the memory for it.
		if ((int) fileListReceiver->setCount==fileListReceiver->filesReceived)
		{
			FileListTransferCBInterface::DownloadCompleteStruct dcs;
			dcs.setID=fileListReceiver->setID;
			dcs.numberOfFilesInThisSet=fileListReceiver->setCount;
			dcs.byteLengthOfThisSet=fileListReceiver->setTotalFinalLength;
			dcs.senderSystemAddress=packet->systemAddress;
			dcs.senderGuid=packet->guid;

			if (fileListReceiver->downloadHandler->OnDownloadComplete(&dcs)==false)
			{
				fileListReceiver->downloadHandler->OnDereference();
				fileListReceivers.Delete(onFileStruct.setID);
				if (fileListReceiver->deleteDownloadHandler)
					SLNet::OP_DELETE(fileListReceiver->downloadHandler, _FILE_AND_LINE_);
				SLNet::OP_DELETE(fileListReceiver, _FILE_AND_LINE_);
			}
		}
	}
	else
	{
		if (isTheFullFile)
		{
			// 12/23/09 Don't use OnReferencePush anymore, just use OnFileProgress
			fileListReceiver->downloadHandler->OnFileProgress(&fps);

			if (fps.allocateIrIDataChunkAutomatically==false)
			{
				rakFree_Ex(fileListReceiver->pushedFiles.Get(onFileStruct.fileIndex).flrMemoryBlock, _FILE_AND_LINE_ );
				fileListReceiver->pushedFiles.Get(onFileStruct.fileIndex).flrMemoryBlock=0;
			}
		}
		else
		{
			// This is a download progress notification for a file chunk using incremental read interface
			// We don't have all the data for this chunk yet

			totalNotifications = onFileStruct.byteLengthOfThisFile / fileListReceiver->partLength + 1;
			if (isTheFullFile==false)
				currentNotificationIndex = (offset+partCount*fileListReceiver->partLength) / fileListReceiver->partLength ;
			else
				currentNotificationIndex = (offset+chunkLength) / fileListReceiver->partLength ;
			unreadBytes = onFileStruct.byteLengthOfThisFile - ((currentNotificationIndex+1) * fileListReceiver->partLength);
			fps.partCount=currentNotificationIndex;
			fps.partTotal=totalNotifications;

// 2/19/2013 Why was this check here? It prevent smaller progress notifications
//			if (rakPeerInterface)
			{
				// Thus chunk is incomplete
				fps.iriDataChunk=0;

				fileListReceiver->downloadHandler->OnFileProgress(&fps);
			}
		}
	}
}
namespace SLNet
{

/*
SendIRIToAddress - executes from Send(). =
1, Find the recipient to send for
2. Send ID_FILE_LIST_TRANSFER_FILE for each small file in the queue of ifles to be sent
3. If the file we are working on is done, remove it from the list
4. Send ID_FILE_LIST_REFERENCE_PUSH for the file we are working on

File sender:
ID_FILE_LIST_REFERENCE_PUSH sent from end of SendIRIToAddressCB

Recipient:
send ID_FILE_LIST_REFERENCE_PUSH_ACK sent from OnReferencePush() when 2nd parameter is true.

File sender:
Got ID_FILE_LIST_REFERENCE_PUSH_ACK. Calls OnReferencePushAck, calls SendIRIToAddress, calls SendIRIToAddressCB
*/

int SendIRIToAddressCB(FileListTransfer::ThreadData threadData, bool *returnOutput, void* perThreadData)
{
	(void) perThreadData;

	FileListTransfer *fileListTransfer = threadData.fileListTransfer;
	SystemAddress systemAddress = threadData.systemAddress;
	unsigned short setId = threadData.setId;
	*returnOutput=false;

	// Was previously using GetStatistics to get outgoing buffer size, but TCP with UnifiedSend doesn't have this
	unsigned int bytesRead;	
	const char *dataBlocks[2];
	int lengths[2];
	unsigned int smallFileTotalSize=0;
	SLNet::BitStream outBitstream;
	unsigned int ftpIndex;

	fileListTransfer->fileToPushRecipientListMutex.Lock();
	for (ftpIndex=0; ftpIndex < fileListTransfer->fileToPushRecipientList.Size(); ftpIndex++)
	{
		FileListTransfer::FileToPushRecipient *ftpr = fileListTransfer->fileToPushRecipientList[ftpIndex];
		// Referenced by both ftpr and list
		ftpr->AddRef();

		fileListTransfer->fileToPushRecipientListMutex.Unlock();

		if (ftpr->systemAddress==systemAddress && ftpr->setId==setId)
		{
			FileListTransfer::FileToPush *ftp;
			////ftpr->filesToPushMutex.Lock();
			ftp = ftpr->filesToPush.Pop();
			////ftpr->filesToPushMutex.Unlock();

			// Read and send chunk. If done, delete at this index
			void *buff = rakMalloc_Ex(ftp->chunkSize, _FILE_AND_LINE_);
			if (buff==0)
			{
				////ftpr->filesToPushMutex.Lock();
				ftpr->filesToPush.PushAtHead(ftp,0,_FILE_AND_LINE_);
				////ftpr->filesToPushMutex.Unlock();

				ftpr->Deref();
				notifyOutOfMemory(_FILE_AND_LINE_);
				return 0;
			}

			// Read the next file chunk
			bytesRead=ftp->incrementalReadInterface->GetFilePart(ftp->fileListNode.fullPathToFile, ftp->currentOffset, ftp->chunkSize, buff, ftp->fileListNode.context);

			bool done = ftp->fileListNode.dataLengthBytes == ftp->currentOffset+bytesRead;
			while (done && ftp->currentOffset==0 && smallFileTotalSize<ftp->chunkSize)
			{
				////ftpr->filesToPushMutex.Lock();
				// The reason for 2 is that ID_FILE_LIST_REFERENCE_PUSH gets ID_FILE_LIST_REFERENCE_PUSH_ACK. WIthout ID_FILE_LIST_REFERENCE_PUSH_ACK, SendIRIToAddressCB would not be called again
				if (ftpr->filesToPush.Size()<2)
				{
					////ftpr->filesToPushMutex.Unlock();
					break;
				}
				////ftpr->filesToPushMutex.Unlock();

				// Send all small files at once, rather than wait for ID_FILE_LIST_REFERENCE_PUSH. But at least one ID_FILE_LIST_REFERENCE_PUSH must be sent
				outBitstream.Reset();
				outBitstream.Write((MessageID)ID_FILE_LIST_TRANSFER_FILE);
				// outBitstream.Write(ftp->fileListNode.context);
				outBitstream << ftp->fileListNode.context;
				outBitstream.Write(setId);
				StringCompressor::Instance()->EncodeString(ftp->fileListNode.filename, 512, &outBitstream);
				outBitstream.WriteCompressed(ftp->setIndex);
				outBitstream.WriteCompressed(ftp->fileListNode.dataLengthBytes); // Original length in bytes
				outBitstream.AlignWriteToByteBoundary();
				dataBlocks[0]=(char*) outBitstream.GetData();
				lengths[0]=outBitstream.GetNumberOfBytesUsed();
				dataBlocks[1]=(const char*) buff;
				lengths[1]=bytesRead;

				fileListTransfer->SendListUnified(dataBlocks,lengths,2,ftp->packetPriority, RELIABLE_ORDERED, ftp->orderingChannel, systemAddress, false);

				// LWS : fixed freed pointer reference
//				unsigned int chunkSize = ftp->chunkSize;
				SLNet::OP_DELETE(ftp,_FILE_AND_LINE_);
				smallFileTotalSize+=bytesRead;
				//done = bytesRead!=ftp->chunkSize;
				////ftpr->filesToPushMutex.Lock();
				ftp = ftpr->filesToPush.Pop();
				////ftpr->filesToPushMutex.Unlock();

				bytesRead=ftp->incrementalReadInterface->GetFilePart(ftp->fileListNode.fullPathToFile, ftp->currentOffset, ftp->chunkSize, buff, ftp->fileListNode.context);
				done = ftp->fileListNode.dataLengthBytes == ftp->currentOffset+bytesRead;
			}


			outBitstream.Reset();
			outBitstream.Write((MessageID)ID_FILE_LIST_REFERENCE_PUSH);
			// outBitstream.Write(ftp->fileListNode.context);
			outBitstream << ftp->fileListNode.context;
			outBitstream.Write(setId);
			StringCompressor::Instance()->EncodeString(ftp->fileListNode.filename, 512, &outBitstream);
			outBitstream.WriteCompressed(ftp->setIndex);
			outBitstream.WriteCompressed(ftp->fileListNode.dataLengthBytes); // Original length in bytes
			outBitstream.WriteCompressed(ftp->currentOffset);
			ftp->currentOffset+=bytesRead;
			outBitstream.WriteCompressed(bytesRead);
			outBitstream.Write(done);

			for (unsigned int flpcIndex=0; flpcIndex < fileListTransfer->fileListProgressCallbacks.Size(); flpcIndex++)
				fileListTransfer->fileListProgressCallbacks[flpcIndex]->OnFilePush(ftp->fileListNode.filename, ftp->fileListNode.fileLengthBytes, ftp->currentOffset-bytesRead, bytesRead, done, systemAddress, setId);

			dataBlocks[0]=(char*) outBitstream.GetData();
			lengths[0]=outBitstream.GetNumberOfBytesUsed();
			dataBlocks[1]=(char*) buff;
			lengths[1]=bytesRead;
			//rakPeerInterface->SendList(dataBlocks,lengths,2,ftp->packetPriority, RELIABLE_ORDERED, ftp->orderingChannel, ftp->systemAddress, false);
			char orderingChannel = ftp->orderingChannel;
			PacketPriority packetPriority = ftp->packetPriority;

			// Mutex state: FileToPushRecipient (ftpr) has AddRef. fileToPushRecipientListMutex not locked.
			if (done)
			{
				// Done
				//unsigned short setId = ftp->setID;
				SLNet::OP_DELETE(ftp,_FILE_AND_LINE_);

				////ftpr->filesToPushMutex.Lock();
				if (ftpr->filesToPush.Size()==0)
				{
					////ftpr->filesToPushMutex.Unlock();

					for (unsigned int flpcIndex=0; flpcIndex < fileListTransfer->fileListProgressCallbacks.Size(); flpcIndex++)
						fileListTransfer->fileListProgressCallbacks[flpcIndex]->OnFilePushesComplete(systemAddress, setId);

					// Remove ftpr from fileToPushRecipientList
					fileListTransfer->RemoveFromList(ftpr);
				}
				else
				{
					////ftpr->filesToPushMutex.Unlock();
				}
			}
			else
			{
				////ftpr->filesToPushMutex.Lock();
				ftpr->filesToPush.PushAtHead(ftp,0,_FILE_AND_LINE_);
				////ftpr->filesToPushMutex.Unlock();
			}
			// ftpr out of scope
			ftpr->Deref();

			// 2/12/2012 Moved this line at after the if (done) block above.
			// See http://www.jenkinssoftware.com/forum/index.php?topic=4768.msg19738#msg19738
			fileListTransfer->SendListUnified(dataBlocks,lengths,2, packetPriority, RELIABLE_ORDERED, orderingChannel, systemAddress, false);

			rakFree_Ex(buff, _FILE_AND_LINE_ );
			return 0;
		}
		else
		{
			ftpr->Deref();
			fileListTransfer->fileToPushRecipientListMutex.Lock();
		}
	}

	fileListTransfer->fileToPushRecipientListMutex.Unlock();

	return 0;
}
}
void FileListTransfer::SendIRIToAddress(SystemAddress systemAddress, unsigned short inSetId)
{
	ThreadData threadData;
	threadData.fileListTransfer=this;
	threadData.systemAddress=systemAddress;
	threadData.setId= inSetId;

	if (threadPool.WasStarted())
	{
		threadPool.AddInput(SendIRIToAddressCB, threadData);
	}
	else
	{
		bool doesNothing;
		SendIRIToAddressCB(threadData, &doesNothing, 0);
	}
}
void FileListTransfer::OnReferencePushAck(Packet *packet)
{
	SLNet::BitStream inBitStream(packet->data, packet->length, false);
	inBitStream.IgnoreBits(8);
	unsigned short curSetId;
	inBitStream.Read(curSetId);
	SendIRIToAddress(packet->systemAddress, curSetId);
}
void FileListTransfer::RemoveFromList(FileToPushRecipient *ftpr)
{
	fileToPushRecipientListMutex.Lock();
	for (unsigned int i=0; i < fileToPushRecipientList.Size(); i++)
	{
		if (fileToPushRecipientList[i]==ftpr)
		{
			fileToPushRecipientList.RemoveAtIndex(i);
			// List no longer references
			ftpr->Deref();
			fileToPushRecipientListMutex.Unlock();
			return;
		}
	}
	fileToPushRecipientListMutex.Unlock();
}
unsigned int FileListTransfer::GetPendingFilesToAddress(SystemAddress recipient)
{
	fileToPushRecipientListMutex.Lock();
	for (unsigned int i=0; i < fileToPushRecipientList.Size(); i++)
	{
		if (fileToPushRecipientList[i]->systemAddress==recipient)
		{
			unsigned int size = fileToPushRecipientList[i]->filesToPush.Size();
			fileToPushRecipientListMutex.Unlock();
			return size;
		}
	}
	fileToPushRecipientListMutex.Unlock();
	
	return 0;
}

#endif // _RAKNET_SUPPORT_*
