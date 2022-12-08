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

#include "slikenet/NativeFeatureIncludes.h"
#if _RAKNET_SUPPORT_Rackspace==1 && _RAKNET_SUPPORT_TCPInterface==1

#include "slikenet/Rackspace.h"
#include "slikenet/string.h"
#include "slikenet/TCPInterface.h"

using namespace SLNet;

Rackspace::Rackspace()
{
	tcpInterface=0;
}

Rackspace::~Rackspace()
{

}

void Rackspace::AddEventCallback(Rackspace2EventCallback *callback)
{
	unsigned int idx = eventCallbacks.GetIndexOf(callback);
	if (idx == (unsigned int)-1)
		eventCallbacks.Push(callback,_FILE_AND_LINE_);
}
void Rackspace::RemoveEventCallback(Rackspace2EventCallback *callback)
{
	unsigned int idx = eventCallbacks.GetIndexOf(callback);
	if (idx != (unsigned int)-1)
		eventCallbacks.RemoveAtIndex(idx);
}
void Rackspace::ClearEventCallbacks(void)
{
	eventCallbacks.Clear(true, _FILE_AND_LINE_);
}
SystemAddress Rackspace::Authenticate(TCPInterface *_tcpInterface, const char *_authenticationURL, const char *_rackspaceCloudUsername, const char *_apiAccessKey)
{
	unsigned int index = GetOperationOfTypeIndex(RO_CONNECT_AND_AUTHENTICATE);
	if (index!=(unsigned int)-1)
	{
		// In progress
		return operations[index].connectionAddress;
	}

	tcpInterface=_tcpInterface;

	rackspaceCloudUsername=_rackspaceCloudUsername;
	apiAccessKey=_apiAccessKey;

	unsigned int i;

	RackspaceOperation ro;
	ro.type=RO_CONNECT_AND_AUTHENTICATE;
	ro.isPendingAuthentication=false;

	RakAssert(tcpInterface->WasStarted());
	ro.connectionAddress=tcpInterface->Connect(_authenticationURL,443,true);
	if (ro.connectionAddress==UNASSIGNED_SYSTEM_ADDRESS)
	{
		for (i=0; i < eventCallbacks.Size(); i++)
			eventCallbacks[i]->OnConnectionAttemptFailure(RO_CONNECT_AND_AUTHENTICATE, _authenticationURL);

		return UNASSIGNED_SYSTEM_ADDRESS;
	}

#if OPEN_SSL_CLIENT_SUPPORT==1
	tcpInterface->StartSSLClient(ro.connectionAddress);
#endif

	SLNet::RakString command(
		"GET /v1.0 HTTP/1.1\n"
		"Host: %s\n"
		"X-Auth-User: %s\n"
		"X-Auth-Key: %s\n\n"
		,_authenticationURL, _rackspaceCloudUsername, _apiAccessKey);
	tcpInterface->Send(command.C_String(), (unsigned int) command.GetLength(), ro.connectionAddress, false);

	operations.Insert(ro,_FILE_AND_LINE_);
	return ro.connectionAddress;
}

const char * Rackspace::EventTypeToString(RackspaceEventType eventType)
{
	switch (eventType)
	{		
		case RET_Success_200:
			return "Success_200";
		case RET_Success_201:
			return "Success_201";
		case RET_Success_202:
			return "Success_202";
		case RET_Success_203:
			return "Success_203";
		case RET_Success_204:
			return "Success_204";
		case RET_Cloud_Servers_Fault_500:
			return "Cloud_Servers_Fault_500";
		case RET_Service_Unavailable_503:
			return "Service_Unavailable_503";
		case RET_Unauthorized_401:
			return "Unauthorized_401";
		case RET_Bad_Request_400:
			return "Bad_Request_400";
		case RET_Over_Limit_413:
			return "Over_Limit_413";
		case RET_Bad_Media_Type_415:
			return "Bad_Media_Type_415";
		case RET_Item_Not_Found_404:
			return "Item_Not_Found_404";
		case RET_Build_In_Progress_409:
			return "Build_In_Progress_409";
		case RET_Resize_Not_Allowed_403:
			return "Resize_Not_Allowed_403";
		case RET_Connection_Closed_Without_Reponse:
			return "Connection_Closed_Without_Reponse";
		case RET_Unknown_Failure:
			return "Unknown_Failure";
	}
	return "Unknown event type (bug)";
}
void Rackspace::AddOperation(RackspaceOperationType type, SLNet::RakString httpCommand, SLNet::RakString operation, SLNet::RakString xml)
{
	RackspaceOperation ro;
	ro.type=type;
	ro.httpCommand=httpCommand;
	ro.operation=operation;
	ro.xml=xml;
	ro.isPendingAuthentication=HasOperationOfType(RO_CONNECT_AND_AUTHENTICATE);
	if (ro.isPendingAuthentication==false)
	{
		if (ExecuteOperation(ro))
			operations.Insert(ro,_FILE_AND_LINE_);
	}
	else
		operations.Insert(ro,_FILE_AND_LINE_);
}
void Rackspace::ListServers(void)
{
	AddOperation(RO_LIST_SERVERS, "GET", "servers", "");
}
void Rackspace::ListServersWithDetails(void)
{
	AddOperation(RO_LIST_SERVERS_WITH_DETAILS, "GET", "servers/detail", "");
}
void Rackspace::CreateServer(SLNet::RakString name, SLNet::RakString imageId, SLNet::RakString flavorId)
{
	SLNet::RakString xml(
		"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
		"<server xmlns=\"http://docs.rackspacecloud.com/servers/api/v1.0\" name=\"%s\" imageId=\"%s\" flavorId=\"%s\">"
		"</server>"
		,name.C_String() ,imageId.C_String(), flavorId.C_String());
	AddOperation(RO_CREATE_SERVER, "POST", "servers", xml);
}
void Rackspace::GetServerDetails(SLNet::RakString serverId)
{
	AddOperation(RO_GET_SERVER_DETAILS, "GET", SLNet::RakString("servers/%s", serverId.C_String()), "");
}
void Rackspace::UpdateServerNameOrPassword(SLNet::RakString serverId, SLNet::RakString newName, SLNet::RakString newPassword)
{
	if (newName.IsEmpty() && newPassword.IsEmpty())
		return;
	SLNet::RakString xml(
		"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
		"<server xmlns=\"http://docs.rackspacecloud.com/servers/api/v1.0\""
		);
	if (newName.IsEmpty()==false)
		xml += SLNet::RakString(" name=\"%s\"", newName.C_String());
	if (newPassword.IsEmpty()==false)
		xml += SLNet::RakString(" adminPass=\"%s\"", newPassword.C_String());
	xml += " />";
	AddOperation(RO_UPDATE_SERVER_NAME_OR_PASSWORD, "PUT", SLNet::RakString("servers/%s", serverId.C_String()), xml);
}
void Rackspace::DeleteServer(SLNet::RakString serverId)
{
	AddOperation(RO_DELETE_SERVER, "DELETE", SLNet::RakString("servers/%s", serverId.C_String()), "");
}
void Rackspace::ListServerAddresses(SLNet::RakString serverId)
{
	AddOperation(RO_LIST_SERVER_ADDRESSES, "GET", SLNet::RakString("servers/%s/ips", serverId.C_String()), "");
}
void Rackspace::ShareServerAddress(SLNet::RakString serverId, SLNet::RakString ipAddress)
{
	AddOperation(RO_SHARE_SERVER_ADDRESS, "PUT", SLNet::RakString("servers/%s/ips/public/%s", serverId.C_String(), ipAddress.C_String()), "");
}
void Rackspace::DeleteServerAddress(SLNet::RakString serverId, SLNet::RakString ipAddress)
{
	AddOperation(RO_DELETE_SERVER_ADDRESS, "DELETE", SLNet::RakString("servers/%s/ips/public/%s", serverId.C_String(), ipAddress.C_String()), "");
}
void Rackspace::RebootServer(SLNet::RakString serverId, SLNet::RakString rebootType)
{
	SLNet::RakString xml(
		"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
		"<reboot xmlns=\"http://docs.rackspacecloud.com/servers/api/v1.0\" type=\"%s\""
		"/>",
		rebootType.C_String());

	AddOperation(RO_REBOOT_SERVER, "POST", SLNet::RakString("servers/%s/action", serverId.C_String()), xml);
}
void Rackspace::RebuildServer(SLNet::RakString serverId, SLNet::RakString imageId)
{
	SLNet::RakString xml(
		"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
		"<rebuild xmlns=\"http://docs.rackspacecloud.com/servers/api/v1.0\" imageId=\"%s\""
		"/>",
		imageId.C_String());

	AddOperation(RO_REBUILD_SERVER, "POST", SLNet::RakString("servers/%s/action", serverId.C_String()), xml);
}
void Rackspace::ResizeServer(SLNet::RakString serverId, SLNet::RakString flavorId)
{
	SLNet::RakString xml(
		"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
		"<resize xmlns=\"http://docs.rackspacecloud.com/servers/api/v1.0\" flavorId=\"%s\""
		"/>",
		flavorId.C_String());

	AddOperation(RO_RESIZE_SERVER, "POST", SLNet::RakString("servers/%s/action", serverId.C_String()), xml);
}
void Rackspace::ConfirmResizedServer(SLNet::RakString serverId)
{
	SLNet::RakString xml(
		"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
		"<confirmResize xmlns=\"http://docs.rackspacecloud.com/servers/api/v1.0\" "
		"/>");
	AddOperation(RO_CONFIRM_RESIZED_SERVER, "POST", SLNet::RakString("servers/%s/action", serverId.C_String()), xml);
}
void Rackspace::RevertResizedServer(SLNet::RakString serverId)
{
	SLNet::RakString xml(
		"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
		"<revertResize xmlns=\"http://docs.rackspacecloud.com/servers/api/v1.0\" "
		"/>");
	AddOperation(RO_REVERT_RESIZED_SERVER, "POST", SLNet::RakString("servers/%s/action", serverId.C_String()), xml);
}
void Rackspace::ListFlavors(void)
{
	AddOperation(RO_LIST_FLAVORS, "GET", "flavors", "");
}
void Rackspace::GetFlavorDetails(SLNet::RakString flavorId)
{
	AddOperation(RO_GET_FLAVOR_DETAILS, "GET", SLNet::RakString("flavors/%s", flavorId.C_String()), "");
}
void Rackspace::ListImages(void)
{
	AddOperation(RO_LIST_IMAGES, "GET", "images", "");
}
void Rackspace::CreateImage(SLNet::RakString serverId, SLNet::RakString imageName)
{
	SLNet::RakString xml(
		"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
		"<image xmlns=\"http://docs.rackspacecloud.com/servers/api/v1.0\" name=\"%s\" serverId=\"%s\""
		"/>",
		imageName.C_String(),serverId.C_String());

	AddOperation(RO_CREATE_IMAGE, "POST", "images", xml);
}
void Rackspace::GetImageDetails(SLNet::RakString imageId)
{
	AddOperation(RO_GET_IMAGE_DETAILS, "GET", SLNet::RakString("images/%s", imageId.C_String()), "");
}
void Rackspace::DeleteImage(SLNet::RakString imageId)
{
	AddOperation(RO_DELETE_IMAGE, "DELETE", SLNet::RakString("images/%s", imageId.C_String()), "");
}
void Rackspace::ListSharedIPGroups(void)
{
	AddOperation(RO_LIST_SHARED_IP_GROUPS, "GET", "shared_ip_groups", "");
}
void Rackspace::ListSharedIPGroupsWithDetails(void)
{
	AddOperation(RO_LIST_SHARED_IP_GROUPS_WITH_DETAILS, "GET", "shared_ip_groups/detail", "");
}
void Rackspace::CreateSharedIPGroup(SLNet::RakString name, SLNet::RakString optionalServerId)
{
	SLNet::RakString xml(
		"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
		"<sharedIpGroup xmlns=\"http://docs.rackspacecloud.com/servers/api/v1.0\" name=\"%s\">", name.C_String());
		if (optionalServerId.IsEmpty()==false)
			xml+= SLNet::RakString("<server id=\"%s\"/>", optionalServerId.C_String());
		xml+="</sharedIpGroup>";

	AddOperation(RO_CREATE_SHARED_IP_GROUP, "POST", "shared_ip_groups", xml);
}
void Rackspace::GetSharedIPGroupDetails(SLNet::RakString groupId)
{
	AddOperation(RO_GET_SHARED_IP_GROUP_DETAILS, "GET", SLNet::RakString("shared_ip_groups/%s", groupId.C_String()), "");
}
void Rackspace::DeleteSharedIPGroup(SLNet::RakString groupId)
{
	AddOperation(RO_DELETE_SHARED_IP_GROUP, "DELETE", SLNet::RakString("shared_ip_groups/%s", groupId.C_String()), "");
}
void Rackspace::OnClosedConnection(SystemAddress systemAddress)
{
	if (systemAddress==UNASSIGNED_SYSTEM_ADDRESS)
		return;

	unsigned int i, operationsIndex;
	operationsIndex=0;
	while (operationsIndex < operations.Size())
	{
		if (operations[operationsIndex].isPendingAuthentication==false && operations[operationsIndex].connectionAddress==systemAddress)
		{
			RackspaceOperation ro = operations[operationsIndex];
			operations.RemoveAtIndex(operationsIndex);

			SLNet::RakString packetDataString = ro.incomingStream;
			const char *packetData = packetDataString.C_String();

			char resultCodeStr[32];
			int resultCodeInt;

			RackspaceEventType rackspaceEventType;
			char *result;
			result=strstr((char*) packetData, "HTTP/1.1 ");
			if (result!=0)
			{
				result+=strlen("HTTP/1.1 ");
				for (i=0; i < sizeof(resultCodeStr)-1 && result[i] && result[i]>='0' && result[i]<='9'; i++)
					resultCodeStr[i]=result[i];
				resultCodeStr[i]=0;
				resultCodeInt=atoi(resultCodeStr);

				switch (resultCodeInt)
				{
				case 200: rackspaceEventType=RET_Success_200; break;
				case 201: rackspaceEventType=RET_Success_201; break;
				case 202: rackspaceEventType=RET_Success_202; break;
				case 203: rackspaceEventType=RET_Success_203; break;
				case 204: rackspaceEventType=RET_Success_204; break;
				case 500: rackspaceEventType=RET_Cloud_Servers_Fault_500; break;
				case 503: rackspaceEventType=RET_Service_Unavailable_503; break;
				case 401: rackspaceEventType=RET_Unauthorized_401; break;
				case 400: rackspaceEventType=RET_Bad_Request_400; break;
				case 413: rackspaceEventType=RET_Over_Limit_413; break;
				case 415: rackspaceEventType=RET_Bad_Media_Type_415; break;
				case 404: rackspaceEventType=RET_Item_Not_Found_404; break;
				case 409: rackspaceEventType=RET_Build_In_Progress_409; break;
				case 403: rackspaceEventType=RET_Resize_Not_Allowed_403; break;
				default: rackspaceEventType=RET_Unknown_Failure; break;
				}
			}
			else
			{
				rackspaceEventType=RET_Connection_Closed_Without_Reponse;
			}

			switch (ro.type)
			{
			case RO_CONNECT_AND_AUTHENTICATE:
				{
					if (rackspaceEventType==RET_Success_204)
					{
						SLNet::RakString header;
						ReadLine(packetData, "X-Server-Management-Url: ", serverManagementURL);
						serverManagementURL.SplitURI(header, serverManagementDomain, serverManagementPath);
						ReadLine(packetData, "X-Storage-Url: ", storageURL);
						storageURL.SplitURI(header, storageDomain, storagePath);
						ReadLine(packetData, "X-CDN-Management-Url: ", cdnManagementURL);
						cdnManagementURL.SplitURI(header, cdnManagementDomain, cdnManagementPath);
						ReadLine(packetData, "X-Auth-Token: ", authToken);
						ReadLine(packetData, "X-Storage-Token: ", storageToken);

						operationsIndex=0;
						while (operationsIndex < operations.Size())
						{
							if (operations[operationsIndex].isPendingAuthentication==true)
							{
								operations[operationsIndex].isPendingAuthentication=false;
								if (ExecuteOperation(operations[operationsIndex])==false)
								{
									operations.RemoveAtIndex(operationsIndex);
								}
								else
									operationsIndex++;
							}
							else
								operationsIndex++;
						}

						// Restart in list
						operationsIndex=0;
					}

					for (i=0; i < eventCallbacks.Size(); i++)
						eventCallbacks[i]->OnAuthenticationResult(rackspaceEventType, (const char*) packetData);

					break;
				}
			case RO_LIST_SERVERS:
				{
					for (i=0; i < eventCallbacks.Size(); i++)
						eventCallbacks[i]->OnListServersResult(rackspaceEventType, (const char*) packetData);
					break;
				}
			case RO_LIST_SERVERS_WITH_DETAILS:
				{
					for (i=0; i < eventCallbacks.Size(); i++)
						eventCallbacks[i]->OnListServersWithDetailsResult(rackspaceEventType, (const char*) packetData);
					break;
				}
			case RO_CREATE_SERVER:
				{
					for (i=0; i < eventCallbacks.Size(); i++)
						eventCallbacks[i]->OnCreateServerResult(rackspaceEventType, (const char*) packetData);
					break;
				}

			case RO_GET_SERVER_DETAILS:
				{
					for (i=0; i < eventCallbacks.Size(); i++)
						eventCallbacks[i]->OnGetServerDetails(rackspaceEventType, (const char*) packetData);
					break;
				}
			case RO_UPDATE_SERVER_NAME_OR_PASSWORD:
				{
					for (i=0; i < eventCallbacks.Size(); i++)
						eventCallbacks[i]->OnUpdateServerNameOrPassword(rackspaceEventType, (const char*) packetData);
					break;
				}
			case RO_DELETE_SERVER:
				{
					for (i=0; i < eventCallbacks.Size(); i++)
						eventCallbacks[i]->OnDeleteServer(rackspaceEventType, (const char*) packetData);
					break;
				}
			case RO_LIST_SERVER_ADDRESSES:
				{
					for (i=0; i < eventCallbacks.Size(); i++)
						eventCallbacks[i]->OnListServerAddresses(rackspaceEventType, (const char*) packetData);
					break;
				}
			case RO_SHARE_SERVER_ADDRESS:
				{
					for (i=0; i < eventCallbacks.Size(); i++)
						eventCallbacks[i]->OnShareServerAddress(rackspaceEventType, (const char*) packetData);
					break;
				}
			case RO_DELETE_SERVER_ADDRESS:
				{
					for (i=0; i < eventCallbacks.Size(); i++)
						eventCallbacks[i]->OnDeleteServerAddress(rackspaceEventType, (const char*) packetData);
					break;
				}
			case RO_REBOOT_SERVER:
				{
					for (i=0; i < eventCallbacks.Size(); i++)
						eventCallbacks[i]->OnRebootServer(rackspaceEventType, (const char*) packetData);
					break;
				}
			case RO_REBUILD_SERVER:
				{
					for (i=0; i < eventCallbacks.Size(); i++)
						eventCallbacks[i]->OnRebuildServer(rackspaceEventType, (const char*) packetData);
					break;
				}
			case RO_RESIZE_SERVER:
				{
					for (i=0; i < eventCallbacks.Size(); i++)
						eventCallbacks[i]->OnResizeServer(rackspaceEventType, (const char*) packetData);
					break;
				}
			case RO_CONFIRM_RESIZED_SERVER:
				{
					for (i=0; i < eventCallbacks.Size(); i++)
						eventCallbacks[i]->OnConfirmResizedServer(rackspaceEventType, (const char*) packetData);
					break;
				}
			case RO_REVERT_RESIZED_SERVER:
				{
					for (i=0; i < eventCallbacks.Size(); i++)
						eventCallbacks[i]->OnRevertResizedServer(rackspaceEventType, (const char*) packetData);
					break;
				}


			case RO_LIST_FLAVORS:
				{
					for (i=0; i < eventCallbacks.Size(); i++)
						eventCallbacks[i]->OnListFlavorsResult(rackspaceEventType, (const char*) packetData);
					break;
				}
			case RO_GET_FLAVOR_DETAILS:
				{
					for (i=0; i < eventCallbacks.Size(); i++)
						eventCallbacks[i]->OnGetFlavorDetailsResult(rackspaceEventType, (const char*) packetData);
					break;
				}
			case RO_LIST_IMAGES:
				{
					for (i=0; i < eventCallbacks.Size(); i++)
						eventCallbacks[i]->OnListImagesResult(rackspaceEventType, (const char*) packetData);
					break;
				}
			case RO_CREATE_IMAGE:
				{
					for (i=0; i < eventCallbacks.Size(); i++)
						eventCallbacks[i]->OnCreateImageResult(rackspaceEventType, (const char*) packetData);
					break;
				}
			case RO_GET_IMAGE_DETAILS:
				{
					for (i=0; i < eventCallbacks.Size(); i++)
						eventCallbacks[i]->OnGetImageDetailsResult(rackspaceEventType, (const char*) packetData);
					break;
				}
			case RO_DELETE_IMAGE:
				{
					for (i=0; i < eventCallbacks.Size(); i++)
						eventCallbacks[i]->OnDeleteImageResult(rackspaceEventType, (const char*) packetData);
					break;
				}
			case RO_LIST_SHARED_IP_GROUPS:
				{
					for (i=0; i < eventCallbacks.Size(); i++)
						eventCallbacks[i]->OnListSharedIPGroups(rackspaceEventType, (const char*) packetData);
					break;
				}
			case RO_LIST_SHARED_IP_GROUPS_WITH_DETAILS:
				{
					for (i=0; i < eventCallbacks.Size(); i++)
						eventCallbacks[i]->OnListSharedIPGroupsWithDetails(rackspaceEventType, (const char*) packetData);
					break;
				}
			case RO_CREATE_SHARED_IP_GROUP:
				{
					for (i=0; i < eventCallbacks.Size(); i++)
						eventCallbacks[i]->OnCreateSharedIPGroup(rackspaceEventType, (const char*) packetData);
					break;
				}
			case RO_GET_SHARED_IP_GROUP_DETAILS:
				{
					for (i=0; i < eventCallbacks.Size(); i++)
						eventCallbacks[i]->OnGetSharedIPGroupDetails(rackspaceEventType, (const char*) packetData);
					break;
				}
			case RO_DELETE_SHARED_IP_GROUP:
				{
					for (i=0; i < eventCallbacks.Size(); i++)
						eventCallbacks[i]->OnDeleteSharedIPGroup(rackspaceEventType, (const char*) packetData);
					break;
				}
			default:
				break;

			}
		}
		else
		{
			operationsIndex++;
		}
	}
}
void Rackspace::OnReceive(Packet *packet)
{
	unsigned int operationsIndex;
	for (operationsIndex=0; operationsIndex < operations.Size(); operationsIndex++)
	{
		if (operations[operationsIndex].isPendingAuthentication==false && operations[operationsIndex].connectionAddress==packet->systemAddress)
		{
			operations[operationsIndex].incomingStream+=packet->data;
		}
	}
}
bool Rackspace::ExecuteOperation(RackspaceOperation &ro)
{
	if (ConnectToServerManagementDomain(ro)==false)
		return false;

	SLNet::RakString command(
		"%s %s/%s HTTP/1.1\n"
		"Host: %s\n"
		"Content-Type: application/xml\n"
		"Content-Length: %i\n"
		"Accept: application/xml\n"
		"X-Auth-Token: %s\n",
		ro.httpCommand.C_String(), serverManagementPath.C_String(), ro.operation.C_String(), serverManagementDomain.C_String(),
		ro.xml.GetLength(),
		authToken.C_String());

	if (ro.xml.IsEmpty()==false)
	{
		command+="\n";
		command+=ro.xml;
		command+="\n";
	}

	command+="\n";

	//printf(command.C_String());

	tcpInterface->Send(command.C_String(), (unsigned int) command.GetLength(), ro.connectionAddress, false);
	return true;
}
void Rackspace::ReadLine(const char *data, const char *stringStart, SLNet::RakString &output)
{
	output.Clear();

	char *result, *resultEnd;

	result=strstr((char*) data, stringStart);
	if (result==0)
	{
		RakAssert(0);
		return;
	}

	result+=strlen(stringStart);
	if (result==0)
	{
		RakAssert(0);
		return;
	}

	output=result;
	resultEnd=result;
	while (*resultEnd && (*resultEnd!='\r') && (*resultEnd!='\n') )
		resultEnd++;
	output.Truncate((unsigned int) (resultEnd-result));
}


bool Rackspace::ConnectToServerManagementDomain(RackspaceOperation &ro)
{
	unsigned int i;

	ro.connectionAddress=tcpInterface->Connect(serverManagementDomain.C_String(),443,true);
	if (ro.connectionAddress==UNASSIGNED_SYSTEM_ADDRESS)
	{
		for (i=0; i < eventCallbacks.Size(); i++)
			eventCallbacks[i]->OnConnectionAttemptFailure(ro.type, serverManagementURL);
		return false;
	}

#if OPEN_SSL_CLIENT_SUPPORT==1
	tcpInterface->StartSSLClient(ro.connectionAddress);
#endif

	return true;
}
bool Rackspace::HasOperationOfType(RackspaceOperationType t)
{
	unsigned int i;
	for (i=0; i < operations.Size(); i++)
	{
		if (operations[i].type==t)
			return true;
	}
	return false;
}
unsigned int Rackspace::GetOperationOfTypeIndex(RackspaceOperationType t)
{
	unsigned int i;
	for (i=0; i < operations.Size(); i++)
	{
		if (operations[i].type==t)
			return i;
	}
	return (unsigned int) -1;
}

#endif
