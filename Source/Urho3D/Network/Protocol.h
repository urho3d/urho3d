// Copyright (c) 2008-2022 the Urho3D project
// License: MIT

#pragma once

namespace Urho3D
{

/// Client->server: send VariantMap of identity and authentication data.
static const int MSG_IDENTITY = 0x87;
/// Client->server: send controls (buttons and mouse movement).
static const int MSG_CONTROLS = 0x88;
/// Client->server: scene has been loaded and client is ready to proceed.
static const int MSG_SCENELOADED = 0x89;
/// Client->server: request a package file.
static const int MSG_REQUESTPACKAGE = 0x8A;

/// Server->client: package file data fragment.
static const int MSG_PACKAGEDATA = 0x8B;
/// Server->client: load new scene. In case of empty filename the client should just empty the scene.
static const int MSG_LOADSCENE = 0x8C;
/// Server->client: wrong scene checksum, can not participate.
static const int MSG_SCENECHECKSUMERROR = 0x8D;
/// Server->client: create new node.
static const int MSG_CREATENODE = 0x8E;
/// Server->client: node delta update.
static const int MSG_NODEDELTAUPDATE = 0x8F;
/// Server->client: node latest data update.
static const int MSG_NODELATESTDATA = 0x90;
/// Server->client: remove node.
static const int MSG_REMOVENODE = 0x91;
/// Server->client: create new component.
static const int MSG_CREATECOMPONENT = 0x92;
/// Server->client: component delta update.
static const int MSG_COMPONENTDELTAUPDATE = 0x93;
/// Server->client: component latest data update.
static const int MSG_COMPONENTLATESTDATA = 0x94;
/// Server->client: remove component.
static const int MSG_REMOVECOMPONENT = 0x95;

/// Client->server and server->client: remote event.
static const int MSG_REMOTEEVENT = 0x96;
/// Client->server and server->client: remote node event.
static const int MSG_REMOTENODEEVENT = 0x97;
/// Server->client: info about package.
static const int MSG_PACKAGEINFO = 0x98;

/// Packet that includes all the above messages
static const int MSG_PACKED_MESSAGE = 0x99;

/// Used to define custom messages, usually of the form MSG_USER + x, where x is an integer value.
static const int MSG_USER = 0x200;

/// Fixed content ID for client controls update.
static const unsigned CONTROLS_CONTENT_ID = 1;
/// Package file fragment size.
static const unsigned PACKAGE_FRAGMENT_SIZE = 1024;

}
