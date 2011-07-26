/* Copyright 2010 Jukka Jylänki

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License. */

/** @file FragmentedTransferManager.cpp
	@brief */

// Modified by Lasse Öörni for Urho3D

#include <cstring>

#ifdef KNET_USE_BOOST
#include <boost/thread/thread.hpp>
#endif

#include "kNet/DebugMemoryLeakCheck.h"

#include "kNet/MessageConnection.h"
#include "kNet/FragmentedTransferManager.h"
#include "kNet/NetworkLogging.h"


using namespace std;

namespace kNet
{

void FragmentedSendManager::FragmentedTransfer::AddMessage(NetworkMessage *message)
{
	fragments.Push(message);
	message->transfer = this;
}

bool FragmentedSendManager::FragmentedTransfer::RemoveMessage(NetworkMessage *message)
{
	for(List<NetworkMessage*>::Iterator iter = fragments.Begin(); iter != fragments.End(); ++iter)
		if (*iter == message)
		{
			message->transfer = 0;
			fragments.Erase(iter);
			LOG(LogVerbose, "Removing message with seqnum %d (fragnum %d) from transfer ID %d (%p).", (int)message->messageNumber, (int)message->fragmentIndex, id, this);
			return true;
		}
	return false;
}

FragmentedSendManager::FragmentedTransfer *FragmentedSendManager::AllocateNewFragmentedTransfer()
{
	transfers.Push(FragmentedTransfer());
	FragmentedTransfer *transfer = &transfers.Back();
	transfer->id = -1;
	transfer->totalNumFragments = 0;

	LOG(LogObjectAlloc, "Allocated new fragmented transfer %p.", transfer);

	return transfer;
}

void FragmentedSendManager::FreeFragmentedTransfer(FragmentedTransfer *transfer)
{
	// Remove all references from any NetworkMessages to this structure.
	for(List<NetworkMessage*>::Iterator iter = transfer->fragments.Begin(); iter != transfer->fragments.End(); ++iter)
		(*iter)->transfer = 0;

	for(TransferList::Iterator iter = transfers.Begin(); iter != transfers.End(); ++iter)
		if (&*iter == transfer)
		{
			transfers.Erase(iter);
			LOG(LogObjectAlloc, "Freed fragmented transfer ID=%d, numFragments: %d (%p).", transfer->id, (int)transfer->totalNumFragments, transfer);
			return;
		}
	LOG(LogError, "Tried to free a fragmented send struct that didn't exist!");
}

void FragmentedSendManager::RemoveMessage(FragmentedTransfer *transfer, NetworkMessage *message)
{
	bool success = transfer->RemoveMessage(message);
	if (!success)
	{
		LOG(LogError, "Tried to remove a nonexisting message from a fragmented send struct!");
		return;
	}

	if (transfer->fragments.Size() == 0)
		FreeFragmentedTransfer(transfer);
}

bool FragmentedSendManager::AllocateFragmentedTransferID(FragmentedTransfer &transfer)
{
	assert(transfer.id == -1); // The FragmentedTransfer object must not have a previously allocated transfer ID at all.

	// We start allocating the ID's from number 1, and the number 0 is never used, so that we get some redundancy in the protocol
	// and are able to detect badly formed input.
	int transferID = 1;

	///\todo Maintain a sorted order in Insert() instead of doing a search here - better for performance.
	bool used = true;
	while(used)
	{
		used = false;
		for(TransferList::Iterator iter = transfers.Begin(); iter != transfers.End(); ++iter)
		{
			if (iter->id == transferID)
			{
				++transferID;
				used = true;
			}
		}
	}
	if (transferID >= 256)
		return false;
	transfer.id = transferID;

	LOG(LogObjectAlloc, "Allocated a transferID %d to a transfer of %d fragments.", transfer.id, (int)transfer.totalNumFragments);

	return true;
}

void FragmentedSendManager::FreeAllTransfers()
{
	while(transfers.Size() > 0)
		FreeFragmentedTransfer(&transfers.Front());
}

void FragmentedReceiveManager::NewFragmentStartReceived(int transferID, int numTotalFragments, const char *data, size_t numBytes)
{
	assert(data);
	LOG(LogVerbose, "Received a fragmentStart of size %db (#total fragments %d) for a transfer with ID %d.", (int)numBytes, numTotalFragments, transferID);

	if (numBytes == 0 || numTotalFragments <= 1)
	{
		LOG(LogError, "Discarding degenerate fragmentStart of size %db and numTotalFragments=%db!", (int)numBytes, numTotalFragments);
		return;
	}

	for(size_t i = 0; i < transfers.Size(); ++i)
		if (transfers[i].transferID == transferID)
		{
			LOG(LogError, "An existing transfer with ID %d existed! Deleting it.", transferID);
			transfers.Erase(transfers.Begin() + i);
			--i;
		}

	transfers.Push(ReceiveTransfer());
	ReceiveTransfer &transfer = transfers.Back();
	transfer.transferID = transferID;
	transfer.numTotalFragments = numTotalFragments;

	///\todo Can optimize by passing the pre-searched transfer struct.
	NewFragmentReceived(transferID, 0, data, numBytes);
}

bool FragmentedReceiveManager::NewFragmentReceived(int transferID, int fragmentNumber, const char *data, size_t numBytes)
{
	LOG(LogVerbose, "Received a fragment of size %db (index %d) for a transfer with ID %d.", (int)numBytes, fragmentNumber, transferID);

	if (numBytes == 0)
	{
		LOG(LogError, "Discarding fragment of size 0!");
		return false;
	}

	for(size_t i = 0; i < transfers.Size(); ++i)
		if (transfers[i].transferID == transferID)
		{
			ReceiveTransfer &transfer = transfers[i];

			for(size_t j = 0; j < transfer.fragments.Size(); ++j)
				if (transfer.fragments[j].fragmentIndex == fragmentNumber)
				{
					LOG(LogError, "A fragment with fragmentNumber %d already exists for transferID %d. Discarding the new fragment! Old size: %db, discarded size: %db",
						fragmentNumber, transferID, (int)transfer.fragments[j].data.Size(), (int)numBytes);
					return false;
				}

			transfer.fragments.Push(ReceiveFragment());
			ReceiveFragment &fragment = transfer.fragments.Back();
			fragment.fragmentIndex = fragmentNumber;
			fragment.data.Insert(fragment.data.End(), data, data + numBytes);

			if (transfer.fragments.Size() >= (size_t)transfer.numTotalFragments)
			{
				LOG(LogData, "Finished receiving a fragmented transfer that consisted of %d fragments (transferID=%d).",
					(int)transfer.fragments.Size(), transfer.transferID);
				return true;
			}
			else
				return false;
		}
	LOG(LogError, "Received a fragment of size %db (index %d) for a transfer with ID %d, but that transfer had not been initiated!",
		(int)numBytes, fragmentNumber, transferID);
	return false;
}

void FragmentedReceiveManager::AssembleMessage(int transferID, PODVector<char> &assembledData)
{
	for(size_t i = 0; i < transfers.Size(); ++i)
		if (transfers[i].transferID == transferID)
		{
			ReceiveTransfer &transfer = transfers[i];
			size_t totalSize = 0;

			for(size_t j = 0; j < transfer.fragments.Size(); ++j)
				totalSize += transfer.fragments[j].data.Size();

			assembledData.Resize(totalSize);

			///\todo Sort by fragmentIndex.
			
			size_t offset = 0;
			for(size_t j = 0; j < transfer.fragments.Size(); ++j)
			{
				assert(transfer.fragments[j].data.Size() > 0);
				memcpy(&assembledData[offset], &transfer.fragments[j].data[0], transfer.fragments[j].data.Size());
				offset += transfer.fragments[j].data.Size();
				assert(offset <= assembledData.Size());
			}
		}
}

void FragmentedReceiveManager::FreeMessage(int transferID)
{
	for(size_t i = 0; i < transfers.Size(); ++i)
		if (transfers[i].transferID == transferID)
		{
			transfers.Erase(transfers.Begin() + i);
			return;
		}
}

} // ~kNet
