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

/// \file HTTPConnection.h
/// \brief Contains HTTPConnection, used to communicate with web servers
///


#include "NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_HTTPConnection==1 && _RAKNET_SUPPORT_TCPInterface==1

#ifndef __HTTP_CONNECTION
#define __HTTP_CONNECTION

#include "Export.h"
#include "string.h"
#include "memoryoverride.h"
#include "types.h"
#include "DS_Queue.h"

namespace SLNet
{
/// Forward declarations
class TCPInterface;
struct SystemAddress;

/// \brief Use HTTPConnection to communicate with a web server.
/// \details Start an instance of TCPInterface via the Start() command.
/// Instantiate a new instance of HTTPConnection, and associate TCPInterface with the class in the constructor.
/// Use Post() to send commands to the web server, and ProcessDataPacket() to update the connection with packets returned from TCPInterface that have the system address of the web server
/// This class will handle connecting and reconnecting as necessary.
///
/// Note that only one Post() can be handled at a time. 
/// \deprecated, use HTTPConnection2
class RAK_DLL_EXPORT HTTPConnection
{
public:
	// GetInstance() and DestroyInstance(instance*)
	STATIC_FACTORY_DECLARATIONS(HTTPConnection)

    /// Returns a HTTP object associated with this tcp connection
    HTTPConnection();
    virtual ~HTTPConnection();

	/// \pre tcp should already be started
	void Init(TCPInterface *_tcp, const char *host, unsigned short port=80);

    /// Submit data to the HTTP server
    /// HTTP only allows one request at a time per connection
    ///
	/// \pre IsBusy()==false
    /// \param path the path on the remote server you want to POST to. For example "index.html"
    /// \param data A NULL terminated string to submit to the server
	/// \param contentType "Content-Type:" passed to post.
    void Post(const char *path, const char *data, const char *_contentType="application/x-www-form-urlencoded");

	/// Get a file from a webserver
	/// \param path the path on the remote server you want to GET from. For example "index.html"
	void Get(const char *path);
    
	/// Is there a Read result ready?
	bool HasRead(void) const;

    /// Get one result from the server
	/// \pre HasResult must return true
	SLNet::RakString Read(void);

	/// Call periodically to do time-based updates
	void Update(void);

	/// Returns the address of the server we are connected to
	SystemAddress GetServerAddress(void) const;

	/// Process an HTTP data packet returned from TCPInterface
	/// Returns true when we have gotten all the data from the HTTP server.
    /// If this returns true then it's safe to Post() another request
	/// Deallocate the packet as usual via TCPInterface
    /// \param packet NULL or a packet associated with our host and port
   void ProcessTCPPacket(Packet *packet);

    /// Results of HTTP requests.  Standard response codes are < 999
    /// ( define HTTP codes and our internal codes as needed )
    enum ResponseCodes { NoBody=1001, OK=200, Deleted=1002 };

	HTTPConnection& operator=(const HTTPConnection& rhs){(void) rhs; return *this;}
   
    /// Encapsulates a raw HTTP response and response code
    struct BadResponse
    {
    public:
		BadResponse() {code=0;}
        
        BadResponse(const unsigned char *_data, int _code)
            : data((const char *)_data), code(_code) {}
        
        BadResponse(const char *_data, int _code)
            : data(_data), code(_code) {}

		operator int () const { return code; }

		SLNet::RakString data;
		int code;  // ResponseCodes
    };

    /// Queued events of failed exchanges with the HTTP server
    bool HasBadResponse(int *code, SLNet::RakString *data);

	/// Returns false if the connection is not doing anything else
	bool IsBusy(void) const;

	/// \internal
	int GetState(void) const;

	struct OutgoingCommand
	{
		SLNet::RakString remotePath;
		SLNet::RakString data;
		SLNet::RakString contentType;
		bool isPost;
	};

	 DataStructures::Queue<OutgoingCommand> outgoingCommand;
	 OutgoingCommand currentProcessingCommand;

private:
    SystemAddress server;
    TCPInterface *tcp;
	SLNet::RakString host;
	unsigned short port;
	DataStructures::Queue<BadResponse> badResponses;

	enum ConnectionState
	{
		CS_NONE,
		CS_DISCONNECTING,
		CS_CONNECTING,
		CS_CONNECTED,
		CS_PROCESSING,
	} connectionState;

	SLNet::RakString incomingData;
	DataStructures::Queue<SLNet::RakString> results;

	void CloseConnection();
	
	/*
	enum { RAK_HTTP_INITIAL,
		RAK_HTTP_STARTING,
		RAK_HTTP_CONNECTING,
		RAK_HTTP_ESTABLISHED,
		RAK_HTTP_REQUEST_SENT,
		RAK_HTTP_IDLE } state;

    SLNet::RakString outgoing, incoming, path, contentType;
    void Process(Packet *packet); // the workhorse
    
    // this helps check the various status lists in TCPInterface
	typedef SystemAddress (TCPInterface::*StatusCheckFunction)(void);
	bool InList(StatusCheckFunction func);
	*/

};

} // namespace SLNet

#endif

#endif // _RAKNET_SUPPORT_*
