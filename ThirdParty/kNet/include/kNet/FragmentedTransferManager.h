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
#pragma once

/** @file FragmentedTransferManager.h
	@brief The classes \ref kNet::FragmentedSendManager FragmentedSendManager and 
	\ref kNet::FragmentedSendManager FragmentedReceiveManager. For managing partial transfers. */

#include <vector>
#include <list>

namespace kNet
{

class NetworkMessage;

/// @internal Manages the allocation of transferIDs to fragmented message transfers and tracks which of the fragments have
/// successfully been sent over to the receiver.
class FragmentedSendManager
{
public:
	struct FragmentedTransfer
	{
		int id;

		/// The total number of fragments in this message.
		size_t totalNumFragments;

		std::list<NetworkMessage*> fragments;

		void AddMessage(NetworkMessage *message);

		/// Returns true if the given message was part of this transfer (which now got removed).
		bool RemoveMessage(NetworkMessage *message);
	};

	typedef std::list<FragmentedTransfer> TransferList;
	TransferList transfers;

	/// Returns a new FragmentedTransfer. A transferID for this transfer will not have been allocated here.
	/// When sending the message is finished, call FreeFragmentedTransfer.
	FragmentedTransfer *AllocateNewFragmentedTransfer();
	void RemoveMessage(FragmentedTransfer *transfer, NetworkMessage *message);

	/// @return True if the allocation succeeded, false otherwise.
	bool AllocateFragmentedTransferID(FragmentedTransfer &transfer);

	void FreeAllTransfers();

private:
	void FreeFragmentedTransfer(FragmentedTransfer *transfer);
};

/// @internal Receives message fragments and assembles fragments to complete messages when they are finished.
class FragmentedReceiveManager
{
public:
	struct ReceiveFragment
	{
		int fragmentIndex;

		std::vector<char> data;
	};

	struct ReceiveTransfer
	{
		int transferID;

		int numTotalFragments;

		std::vector<ReceiveFragment> fragments;
	};

	std::vector<ReceiveTransfer> transfers;

	void NewFragmentStartReceived(int transferID, int numTotalFragments, const char *data, size_t numBytes);
	bool NewFragmentReceived(int transferID, int fragmentNumber, const char *data, size_t numBytes);
	void AssembleMessage(int transferID, std::vector<char> &assembledData);
	void FreeMessage(int transferID);
};

} // ~kNet
