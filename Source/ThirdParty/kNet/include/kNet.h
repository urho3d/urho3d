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
#pragma once

/** @file kNet.h
	@brief The main file of kNet that #includes all the commonly used headers for the the 
	       client application. This file is ideal to be added to a PCH. If you are not using a PCH,
	       #including the individual files when necessary is most likely faster. */

#include "kNetBuildConfig.h"
#include "kNetFwd.h"

#ifdef _WIN32
#include "kNet/win32/WS2Include.h"
#endif

#include "kNet/Clock.h"
#include "kNet/DataDeserializer.h"
#include "kNet/DataSerializer.h"
#include "kNet/EndPoint.h"
#include "kNet/Event.h"
#include "kNet/EventArray.h"
#include "kNet/IMessageHandler.h"
#include "kNet/INetworkServerListener.h"
#include "kNet/Lockable.h"
#include "kNet/MaxHeap.h"
#include "kNet/MessageConnection.h"
#include "kNet/MessageListParser.h"
#include "kNet/NetException.h"
#include "kNet/Network.h"
#include "kNet/NetworkLogging.h"
#include "kNet/NetworkMessage.h"
#include "kNet/NetworkServer.h"
#include "kNet/PolledTimer.h"
#include "kNet/SerializationStructCompiler.h"
#include "kNet/SerializedDataIterator.h"
#include "kNet/SharedPtr.h"
#include "kNet/Socket.h"
#include "kNet/Sort.h"
#include "kNet/Thread.h"
#include "kNet/Types.h"
#include "kNet/VLEPacker.h"
#include "kNet/WaitFreeQueue.h"
#include "kNet/64BitAllocDebugger.h"

#ifdef KNET_USE_QT
#include "kNet/qt/NetworkDialog.h"
#include "kNet/qt/MessageConnectionDialog.h"
#endif
