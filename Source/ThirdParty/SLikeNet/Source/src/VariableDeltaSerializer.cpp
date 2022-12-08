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

#include "slikenet/VariableDeltaSerializer.h"

using namespace SLNet;

VariableDeltaSerializer::VariableDeltaSerializer() {didComparisonThisTick=false;}
VariableDeltaSerializer::~VariableDeltaSerializer() {RemoveRemoteSystemVariableHistory();}

VariableDeltaSerializer::SerializationContext::SerializationContext() {variableHistoryIdentical=0; variableHistoryUnique=0;}
VariableDeltaSerializer::SerializationContext::~SerializationContext() {}

void VariableDeltaSerializer::OnMessageReceipt(RakNetGUID guid, uint32_t receiptId, bool messageArrived)
{
	// Module?
	if (messageArrived)
		FreeVarsAssociatedWithReceipt(guid, receiptId);
	else
		DirtyAndFreeVarsAssociatedWithReceipt(guid, receiptId);

}

void VariableDeltaSerializer::BeginUnreliableAckedSerialize(SerializationContext *context, RakNetGUID _guid, BitStream *_bitStream, uint32_t _sendReceipt)
{
	RakAssert(_guid!=UNASSIGNED_RAKNET_GUID);
	context->anyVariablesWritten=false;
	context->guid=_guid;
	context->bitStream=_bitStream;
	if (context->variableHistoryUnique==0)
		context->variableHistoryUnique=StartVariableHistoryWrite(_guid);
	context->variableHistory=context->variableHistoryUnique;
	context->sendReceipt=_sendReceipt;
	context->changedVariables = AllocChangedVariablesList();
	context->newSystemSend=false;
	context->serializationMode=UNRELIABLE_WITH_ACK_RECEIPT;
}

void VariableDeltaSerializer::BeginUniqueSerialize(SerializationContext *context, RakNetGUID _guid, BitStream *_bitStream)
{
	RakAssert(_guid!=UNASSIGNED_RAKNET_GUID);
	context->anyVariablesWritten=false;
	context->guid=_guid;
	context->bitStream=_bitStream;
	if (context->variableHistoryUnique==0)
		context->variableHistoryUnique=StartVariableHistoryWrite(_guid);
	context->variableHistory=context->variableHistoryUnique;
	context->newSystemSend=false;

	context->serializationMode=RELIABLE;
}


void VariableDeltaSerializer::BeginIdenticalSerialize(SerializationContext *context, bool _isFirstSendToRemoteSystem, BitStream *_bitStream)
{
	context->anyVariablesWritten=false;
	context->guid=UNASSIGNED_RAKNET_GUID;
	context->bitStream=_bitStream;
	context->serializationMode=RELIABLE;
	if (context->variableHistoryIdentical==0)
		context->variableHistoryIdentical=StartVariableHistoryWrite(UNASSIGNED_RAKNET_GUID);
	context->variableHistory=context->variableHistoryIdentical;
	context->newSystemSend=_isFirstSendToRemoteSystem;
}

void VariableDeltaSerializer::EndSerialize(SerializationContext *context)
{
	if (context->serializationMode==UNRELIABLE_WITH_ACK_RECEIPT)
	{
		if (context->anyVariablesWritten==false)
		{
			context->bitStream->Reset();
			FreeChangedVariablesList(context->changedVariables);
			return;
		}

		StoreChangedVariablesList(context->variableHistory, context->changedVariables, context->sendReceipt);
	}
	else
	{
		if (context->variableHistoryIdentical)
		{
			if (didComparisonThisTick==false)
			{
				didComparisonThisTick=true;
				identicalSerializationBs.Reset();

				if (context->anyVariablesWritten==false)
				{
					context->bitStream->Reset();
					return;
				}

				identicalSerializationBs.Write(context->bitStream);
				context->bitStream->ResetReadPointer();
			}
			else
			{
				context->bitStream->Write(&identicalSerializationBs);
				identicalSerializationBs.ResetReadPointer();
			}
		}
		else if (context->anyVariablesWritten==false)
		{
			context->bitStream->Reset();
			return;
		}
	}
}

void VariableDeltaSerializer::BeginDeserialize(DeserializationContext *context, BitStream *_bitStream)
{
	context->bitStream=_bitStream;
}

void VariableDeltaSerializer::EndDeserialize(DeserializationContext *context)
{
	(void) context;
}

void VariableDeltaSerializer::AddRemoteSystemVariableHistory(RakNetGUID guid)
{
	(void) guid;
}

void VariableDeltaSerializer::RemoveRemoteSystemVariableHistory(RakNetGUID guid)
{
	unsigned int idx,idx2;
	idx = GetVarsWrittenPerRemoteSystemListIndex(guid);
	if (idx==(unsigned int)-1)
		return;

	if (remoteSystemVariableHistoryList[idx]->guid==guid)
	{
		// Memory pool doesn't call destructor
		for (idx2=0; idx2 < remoteSystemVariableHistoryList[idx]->updatedVariablesHistory.Size(); idx2++)
		{
			FreeChangedVariablesList(remoteSystemVariableHistoryList[idx]->updatedVariablesHistory[idx2]);
		}

		delete remoteSystemVariableHistoryList[idx];
		remoteSystemVariableHistoryList.RemoveAtIndexFast(idx);
		return;
	}
}

int SLNet::VariableDeltaSerializer::UpdatedVariablesListPtrComp( const uint32_t &key, ChangedVariablesList* const &data )
{
	if (key<data->sendReceipt)
		return -1;
	if (key==data->sendReceipt)
		return 0;
	return 1;
}

void VariableDeltaSerializer::FreeVarsAssociatedWithReceipt(RakNetGUID guid, uint32_t receiptId)
{
	unsigned int idx, idx2;
	idx = GetVarsWrittenPerRemoteSystemListIndex(guid);
	if (idx==(unsigned int)-1)
		return;

	RemoteSystemVariableHistory* vprs = remoteSystemVariableHistoryList[idx];
	bool objectExists;
	idx2=vprs->updatedVariablesHistory.GetIndexFromKey(receiptId,&objectExists);
	if (objectExists)
	{
		// Free this history node
		FreeChangedVariablesList(vprs->updatedVariablesHistory[idx2]);
		vprs->updatedVariablesHistory.RemoveAtIndex(idx2);
	}
}

void VariableDeltaSerializer::DirtyAndFreeVarsAssociatedWithReceipt(RakNetGUID guid, uint32_t receiptId)
{
	unsigned int idx, idx2;
	idx = GetVarsWrittenPerRemoteSystemListIndex(guid);
	if (idx==(unsigned int)-1)
		return;

	RemoteSystemVariableHistory* vprs = remoteSystemVariableHistoryList[idx];
	bool objectExists;
	idx2=vprs->updatedVariablesHistory.GetIndexFromKey(receiptId,&objectExists);
	if (objectExists)
	{
		// 'Dirty' all variables sent this update, meaning they will be resent the next time Serialize() is called
		vprs->variableListDeltaTracker.FlagDirtyFromBitArray(vprs->updatedVariablesHistory[idx2]->bitField);

		// Free this history node
		FreeChangedVariablesList(vprs->updatedVariablesHistory[idx2]);
		vprs->updatedVariablesHistory.RemoveAtIndex(idx2);
	}
}
unsigned int VariableDeltaSerializer::GetVarsWrittenPerRemoteSystemListIndex(RakNetGUID guid)
{
	unsigned int idx;
	for (idx=0; idx < remoteSystemVariableHistoryList.Size(); idx++)
	{
		if (remoteSystemVariableHistoryList[idx]->guid==guid)
			return idx;
	}
	return (unsigned int) -1;
}
void VariableDeltaSerializer::RemoveRemoteSystemVariableHistory(void)
{
	unsigned int idx,idx2;
	for (idx=0; idx < remoteSystemVariableHistoryList.Size(); idx++)
	{
		for (idx2=0; idx2 < remoteSystemVariableHistoryList[idx]->updatedVariablesHistory.Size(); idx2++)
		{
			FreeChangedVariablesList(remoteSystemVariableHistoryList[idx]->updatedVariablesHistory[idx2]);
		}

		delete remoteSystemVariableHistoryList[idx];
	}
	remoteSystemVariableHistoryList.Clear(false,_FILE_AND_LINE_);
}

VariableDeltaSerializer::RemoteSystemVariableHistory* VariableDeltaSerializer::GetRemoteSystemVariableHistory(RakNetGUID guid)
{
	unsigned int rshli = GetRemoteSystemHistoryListIndex(guid);
	return remoteSystemVariableHistoryList[rshli];
}

VariableDeltaSerializer::ChangedVariablesList *VariableDeltaSerializer::AllocChangedVariablesList(void)
{
	VariableDeltaSerializer::ChangedVariablesList *p = updatedVariablesMemoryPool.Allocate(_FILE_AND_LINE_);
	p->bitWriteIndex=0;
	p->bitField[0]=0;
	return p;
}
void VariableDeltaSerializer::FreeChangedVariablesList(ChangedVariablesList *changedVariables)
{
	updatedVariablesMemoryPool.Release(changedVariables, _FILE_AND_LINE_);
}
void VariableDeltaSerializer::StoreChangedVariablesList(RemoteSystemVariableHistory *variableHistory, ChangedVariablesList *changedVariables, uint32_t sendReceipt)
{
	changedVariables->sendReceipt=sendReceipt;
	variableHistory->updatedVariablesHistory.Insert(changedVariables->sendReceipt,changedVariables,true,_FILE_AND_LINE_);
}

VariableDeltaSerializer::RemoteSystemVariableHistory *VariableDeltaSerializer::StartVariableHistoryWrite(RakNetGUID guid)
{
	RemoteSystemVariableHistory *variableHistory;

	unsigned int rshli = GetRemoteSystemHistoryListIndex(guid);
	if (rshli==(unsigned int) -1)
	{
		variableHistory = new RemoteSystemVariableHistory;
		variableHistory->guid=guid;
		remoteSystemVariableHistoryList.Push(variableHistory,_FILE_AND_LINE_);
	}
	else
	{
		variableHistory=remoteSystemVariableHistoryList[rshli];
	}

	variableHistory->variableListDeltaTracker.StartWrite();
	return variableHistory;
}
unsigned int VariableDeltaSerializer::GetRemoteSystemHistoryListIndex(RakNetGUID guid)
{
	// Find the variable tracker for the target system
	unsigned int idx;
	for (idx=0; idx < remoteSystemVariableHistoryList.Size(); idx++)
	{
		if (remoteSystemVariableHistoryList[idx]->guid==guid)
		{
			return idx;
		}
	}
	return (unsigned int) -1;
}

void VariableDeltaSerializer::OnPreSerializeTick(void)
{
	didComparisonThisTick=false;
}
