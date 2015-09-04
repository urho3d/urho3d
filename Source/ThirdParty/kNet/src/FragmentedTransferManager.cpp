/* Copyright The kNet Project.

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
	fragments.push_back(message);
	message->transfer = this;
}

bool FragmentedSendManager::FragmentedTransfer::RemoveMessage(NetworkMessage *message)
{
	for(std::list<NetworkMessage*>::iterator iter = fragments.begin(); iter != fragments.end(); ++iter)
		if (*iter == message)
		{
			message->transfer = 0;
			fragments.erase(iter);
			KNET_LOG(LogVerbose, "Removing message with seqnum %d (fragnum %d) from transfer ID %d (%p).", (int)message->messageNumber, (int)message->fragmentIndex, id, this);
			return true;
		}
	return false;
}

FragmentedSendManager::FragmentedTransfer *FragmentedSendManager::AllocateNewFragmentedTransfer()
{
	transfers.push_back(FragmentedTransfer());
	FragmentedTransfer *transfer = &transfers.back();
	transfer->id = -1;
	transfer->totalNumFragments = 0;

	KNET_LOG(LogObjectAlloc, "Allocated new fragmented transfer %p.", transfer);

	return transfer;
}

void FragmentedSendManager::FreeFragmentedTransfer(FragmentedTransfer *transfer)
{
	// Remove all references from any NetworkMessages to this structure.
	for(std::list<NetworkMessage*>::iterator iter = transfer->fragments.begin(); iter != transfer->fragments.end(); ++iter)
		(*iter)->transfer = 0;

	for(TransferList::iterator iter = transfers.begin(); iter != transfers.end(); ++iter)
		if (&*iter == transfer)
		{
			transfers.erase(iter);
			KNET_LOG(LogObjectAlloc, "Freed fragmented transfer ID=%d, numFragments: %d (%p).", transfer->id, (int)transfer->totalNumFragments, transfer);
			return;
		}
	KNET_LOG(LogError, "Tried to free a fragmented send struct that didn't exist!");
}

void FragmentedSendManager::RemoveMessage(FragmentedTransfer *transfer, NetworkMessage *message)
{
	bool success = transfer->RemoveMessage(message);
	if (!success)
	{
		KNET_LOG(LogError, "Tried to remove a nonexisting message from a fragmented send struct!");
		return;
	}

	if (transfer->fragments.size() == 0)
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
		for(TransferList::iterator iter = transfers.begin(); iter != transfers.end(); ++iter)
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

	KNET_LOG(LogObjectAlloc, "Allocated a transferID %d to a transfer of %d fragments.", transfer.id, (int)transfer.totalNumFragments);

	return true;
}

void FragmentedSendManager::FreeAllTransfers()
{
	while(!transfers.empty())
		FreeFragmentedTransfer(&transfers.front());
}

void FragmentedReceiveManager::NewFragmentStartReceived(int transferID, int numTotalFragments, const char *data, size_t numBytes)
{
	assert(data);
	KNET_LOG(LogVerbose, "Received a fragmentStart of size %db (#total fragments %d) for a transfer with ID %d.", (int)numBytes, numTotalFragments, transferID);

	if (numBytes == 0 || numTotalFragments <= 1)
	{
		KNET_LOG(LogError, "Discarding degenerate fragmentStart of size %db and numTotalFragments=%db!", (int)numBytes, numTotalFragments);
		return;
	}

	for(size_t i = 0; i < transfers.size(); ++i)
		if (transfers[i].transferID == transferID)
		{
			KNET_LOG(LogError, "An existing transfer with ID %d existed! Deleting it.", transferID);
			transfers.erase(transfers.begin() + i);
			--i;
		}

	transfers.push_back(ReceiveTransfer());
	ReceiveTransfer &transfer = transfers.back();
	transfer.transferID = transferID;
	transfer.numTotalFragments = numTotalFragments;

	///\todo Can optimize by passing the pre-searched transfer struct.
	NewFragmentReceived(transferID, 0, data, numBytes);
}

bool FragmentedReceiveManager::NewFragmentReceived(int transferID, int fragmentNumber, const char *data, size_t numBytes)
{
	KNET_LOG(LogVerbose, "Received a fragment of size %db (index %d) for a transfer with ID %d.", (int)numBytes, fragmentNumber, transferID);

	if (numBytes == 0)
	{
		KNET_LOG(LogError, "Discarding fragment of size 0!");
		return false;
	}

	for(size_t i = 0; i < transfers.size(); ++i)
		if (transfers[i].transferID == transferID)
		{
			ReceiveTransfer &transfer = transfers[i];

			for(size_t j = 0; j < transfer.fragments.size(); ++j)
				if (transfer.fragments[j].fragmentIndex == fragmentNumber)
				{
					KNET_LOG(LogError, "A fragment with fragmentNumber %d already exists for transferID %d. Discarding the new fragment! Old size: %db, discarded size: %db",
						fragmentNumber, transferID, (int)transfer.fragments[j].data.size(), (int)numBytes);
					return false;
				}

			transfer.fragments.push_back(ReceiveFragment());
			ReceiveFragment &fragment = transfer.fragments.back();
			fragment.fragmentIndex = fragmentNumber;
			fragment.data.insert(fragment.data.end(), data, data + numBytes);

			if (transfer.fragments.size() >= (size_t)transfer.numTotalFragments)
			{
				KNET_LOG(LogData, "Finished receiving a fragmented transfer that consisted of %d fragments (transferID=%d).",
					(int)transfer.fragments.size(), transfer.transferID);
				return true;
			}
			else
				return false;
		}
	KNET_LOG(LogError, "Received a fragment of size %db (index %d) for a transfer with ID %d, but that transfer had not been initiated!",
		(int)numBytes, fragmentNumber, transferID);
	return false;
}

void FragmentedReceiveManager::AssembleMessage(int transferID, std::vector<char> &assembledData)
{
	for(size_t i = 0; i < transfers.size(); ++i)
		if (transfers[i].transferID == transferID)
		{
			ReceiveTransfer &transfer = transfers[i];
			size_t totalSize = 0;

			for(size_t j = 0; j < transfer.fragments.size(); ++j)
				totalSize += transfer.fragments[j].data.size();

			assembledData.resize(totalSize);

			///\todo Sort by fragmentIndex.
			
			size_t offset = 0;
			for(size_t j = 0; j < transfer.fragments.size(); ++j)
			{
				assert(transfer.fragments[j].data.size() > 0);
				memcpy(&assembledData[offset], &transfer.fragments[j].data[0], transfer.fragments[j].data.size());
				offset += transfer.fragments[j].data.size();
				assert(offset <= assembledData.size());
			}
		}
}

void FragmentedReceiveManager::FreeMessage(int transferID)
{
	for(size_t i = 0; i < transfers.size(); ++i)
		if (transfers[i].transferID == transferID)
		{
			transfers.erase(transfers.begin() + i);
			return;
		}
}

} // ~kNet
