// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#ifndef TB_MSG_H
#define TB_MSG_H

#include "tb_core.h"
#include "tb_linklist.h"
#include "tb_value.h"
#include "tb_object.h"
#include "tb_id.h"

namespace tb {

class TBMessageHandler;

/** TB_NOT_SOON is returned from TBMessageHandler::GetNextMessageFireTime
	and means that there is currently no more messages to process. */
#define TB_NOT_SOON 0xffffffff

/** TBMessageData holds custom data to send with a posted message. */

class TBMessageData : public TBTypedObject
{
public:
	TBMessageData() {}
	TBMessageData(int v1, int v2) : v1(v1), v2(v2) {}
	virtual ~TBMessageData() {}
public:
	TBValue v1; ///< Use for anything
	TBValue v2; ///< Use for anything
	TBID id1;	///< Use for anything
	TBID id2;	///< Use for anything
};

/** TBMessageLink should never be created or subclassed anywhere except in TBMessage.
	It's only purpose is to add a extra typed link for TBMessage, since it needs to be
	added in multiple lists. */
class TBMessageLink : public TBLinkOf<TBMessageLink> { };

/** TBMessage is a message created and owned by TBMessageHandler.
	It carries a message id, and may also carry a TBMessageData with
	additional parameters. */

class TBMessage : public TBLinkOf<TBMessage>, public TBMessageLink
{
private:
	TBMessage(TBID message, TBMessageData *data, double fire_time_ms, TBMessageHandler *mh);
	~TBMessage();

public:
	TBID message;			///< The message id
	TBMessageData *data;	///< The message data, or nullptr if no data is set

	/** The time which a delayed message should have fired (0 for non delayed messages) */
	double GetFireTime() { return fire_time_ms; }

private:
	friend class TBMessageHandler;
	double fire_time_ms;
	TBMessageHandler *mh;
};

/** TBMessageHandler handles a list of pending messages posted to itself.
	Messages can be delivered immediately or after a delay.
	Delayed message are delivered as close as possible to the time they should fire.
	Immediate messages are put on a queue and delivered as soon as possible, after any delayed
	messages that has passed their delivery time. This queue is global (among all TBMessageHandlers) */

class TBMessageHandler
{
public:
	TBMessageHandler();
	virtual ~TBMessageHandler();

	/** Posts a message to the target after a delay.
		data may be nullptr if no extra data need to be sent. It will be deleted
		automatically when the message is deleted. */
	bool PostMessageDelayed(TBID message, TBMessageData *data, uint32 delay_in_ms);

	/** Posts a message to the target at the given time (relative to TBSystem::GetTimeMS()).
		data may be nullptr if no extra data need to be sent. It will be deleted
		automatically when the message is deleted. */
	bool PostMessageOnTime(TBID message, TBMessageData *data, double fire_time);

	/** Posts a message to the target.
		data may be nullptr if no extra data need to be sent. It will be deleted
		automatically when the message is deleted. */
	bool PostMessage(TBID message, TBMessageData *data);

	/** Check if this messagehandler has a pending message with the given id.
		Returns the message if found, or nullptr.
		If you want to delete the message, call DeleteMessage. */
	TBMessage *GetMessageByID(TBID message);

	/** Delete the message from this message handler. */
	void DeleteMessage(TBMessage *msg);

	/** Delete all messages from this message handler. */
	void DeleteAllMessages();

	/** Called when a message is delivered.

		This message won't be found using GetMessageByID. It is already removed from the list.
		You should not call DeleteMessage on this message. That is done automatically after this method exit. */
	virtual void OnMessageReceived(TBMessage *msg) {}

	// == static methods to handle the queue of messages ====================================================

	/** Process any messages in queue. */
	static void ProcessMessages();

	/** Get when the time when ProcessMessages needs to be called again.
		Always returns 0 if there is nondelayed messages to process, which means it needs to be called asap.
		If there's only delayed messages to process, it returns the time that the earliest delayed message should be fired.
		If there's no more messages to process at the moment, it returns TB_NOT_SOON (No call to ProcessMessages is needed). */
	static double GetNextMessageFireTime();
private:
	TBLinkListOf<TBMessage> m_messages;
};

}; // namespace tb

#endif // TB_MSG_H
