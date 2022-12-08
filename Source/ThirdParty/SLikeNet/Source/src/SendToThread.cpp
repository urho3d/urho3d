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

#include "slikenet/SendToThread.h"
#ifdef USE_THREADED_SEND
#include "slikenet/thread.h"
#include "slikenet/InternalPacket.h"
#include "slikenet/GetTime.h"

#if USE_SLIDING_WINDOW_CONGESTION_CONTROL!=1
#include "slikenet/CCRakNetUDT.h"
#else
#include "slikenet/CCRakNetSlidingWindow.h"
#endif

using namespace SLNet;

int SendToThread::refCount=0;
DataStructures::ThreadsafeAllocatingQueue<SendToThread::SendToThreadBlock> SendToThread::objectQueue;
ThreadPool<SendToThread::SendToThreadBlock*,SendToThread::SendToThreadBlock*> SendToThread::threadPool;

SendToThread::SendToThreadBlock* SendToWorkerThread(SendToThread::SendToThreadBlock* input, bool *returnOutput, void* perThreadData)
{
	(void) perThreadData;
	*returnOutput=false;
//	SLNet::TimeUS *mostRecentTime=(SLNet::TimeUS *)input->data;
//	*mostRecentTime=SLNet::GetTimeUS();
	SocketLayer::SendTo(input->s, input->data, input->dataWriteOffset, input->systemAddress, _FILE_AND_LINE_);
	SendToThread::objectQueue.Push(input);
	return 0;
}
SendToThread::SendToThread()
{
}
SendToThread::~SendToThread()
{

}
void SendToThread::AddRef(void)
{
	if (++refCount==1)
	{
		threadPool.StartThreads(1,0);
	}
}
void SendToThread::Deref(void)
{
	if (refCount>0)
	{
		if (--refCount==0)
		{
			threadPool.StopThreads();
			RakAssert(threadPool.NumThreadsWorking()==0);

			unsigned i;
			SendToThreadBlock* info;
			for (i=0; i < threadPool.InputSize(); i++)
			{
				info = threadPool.GetInputAtIndex(i);
				objectQueue.Push(info);
			}
			threadPool.ClearInput();
			objectQueue.Clear(_FILE_AND_LINE_);
		}
	}
}
SendToThread::SendToThreadBlock* SendToThread::AllocateBlock(void)
{
	SendToThread::SendToThreadBlock *b;
	b=objectQueue.Pop();
	if (b==0)
		b=objectQueue.Allocate(_FILE_AND_LINE_);
	return b;
}
void SendToThread::ProcessBlock(SendToThread::SendToThreadBlock* threadedSend)
{
	RakAssert(threadedSend->dataWriteOffset>0 && threadedSend->dataWriteOffset<=MAXIMUM_MTU_SIZE-UDP_HEADER_SIZE);
	threadPool.AddInput(SendToWorkerThread,threadedSend);
}
#endif
