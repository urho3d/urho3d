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

#include "kNet/NetworkSimulator.h"
#include "kNet/MessageConnection.h"

namespace kNet
{

NetworkSimulator::NetworkSimulator()
:enabled(false),
packetLossRate(0),
constantPacketSendDelay(0),
uniformRandomPacketSendDelay(0),
owner(0),
corruptMessageId(0),
corruptToggleBitsRate(0),
corruptionType(CorruptDatagram),
corruptMinBits(0),
corruptMaxBits(0)
{
}

NetworkSimulator::~NetworkSimulator()
{
	if (queuedBuffers.size() > 0)
		LOG(LogError, "NetworkSimulator: Leaked %d buffers with improper NetworkSimulator teardown!", (int)queuedBuffers.size());
}

static float rand01() { return (float)rand() / (RAND_MAX+1); }

void NetworkSimulator::Free()
{
	if (!owner || !owner->GetSocket())
		return;

	for(size_t i = 0; i < queuedBuffers.size(); ++i)
		owner->GetSocket()->AbortSend(queuedBuffers[i].buffer);
	queuedBuffers.clear();
}

void NetworkSimulator::SubmitSendBuffer(kNet::OverlappedTransferBuffer *buffer, Socket *socket)
{
	if (rand01() < packetLossRate)
	{
		if (owner && owner->GetSocket())
			owner->GetSocket()->AbortSend(buffer);
		return; // Dropped this packet!
	}

	// Should we duplicate this packet?
	if (rand01() < packetDuplicationRate)
	{
		QueuedBuffer b;
		assert(socket);
        b.buffer = socket->BeginSend(buffer->bytesContains);
		if (b.buffer)
		{
			assert(b.buffer->buffer.len >= buffer->bytesContains);
			memcpy(b.buffer->buffer.buf, buffer->buffer.buf, buffer->bytesContains);
			b.buffer->bytesContains = buffer->bytesContains;

			// Should we corrupt the newly created copy?
			if (corruptionType == CorruptDatagram)
				MaybeCorruptBufferToggleBits(b.buffer->buffer.buf, b.buffer->bytesContains);

			b.timeUntilTransfer.StartMSecs(constantPacketSendDelay + (float)rand() * uniformRandomPacketSendDelay / RAND_MAX);
			queuedBuffers.push_back(b);
		}
	}

	// Should we corrupt this packet?
	if (corruptionType == CorruptDatagram)
		MaybeCorruptBufferToggleBits(buffer->buffer.buf, buffer->bytesContains);

	QueuedBuffer b;
	b.buffer = buffer;
	b.timeUntilTransfer.StartMSecs(constantPacketSendDelay + (float)rand() * uniformRandomPacketSendDelay / RAND_MAX);
	queuedBuffers.push_back(b);
}

void NetworkSimulator::Process()
{
	for(size_t i = 0; i < queuedBuffers.size(); ++i)
		if (queuedBuffers[i].timeUntilTransfer.Test())
		{
			if (owner && owner->GetSocket())
				owner->GetSocket()->EndSend(queuedBuffers[i].buffer);
			queuedBuffers.erase(queuedBuffers.begin() + i);
			--i;
		}
}

void NetworkSimulator::MaybeCorruptBufferToggleBits(void *buffer, size_t numBytes) const
{
	// Should corrupt this data?
	if (rand01() < corruptToggleBitsRate)
	{
		int numBitsToCorrupt = corruptMinBits + rand() * (corruptMaxBits - corruptMinBits + 1) / (RAND_MAX+1);
		for(int i = 0; i < numBitsToCorrupt; ++i)
		{
			int byteIndex = rand() * numBytes / (RAND_MAX+1);
			int bitIndex = rand() % 8;
			int bitMask = (1 << bitIndex);
			((char*)buffer)[byteIndex] ^= bitMask;
		}
	}
}

} // ~kNet
