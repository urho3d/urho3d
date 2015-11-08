// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_msg.h"
#include "tb_system.h"
#include <stddef.h>

namespace tb {

/** List of all delayed messages */
TBLinkListOf<TBMessageLink> g_all_delayed_messages;

/** List of all nondelayed messages. */
TBLinkListOf<TBMessageLink> g_all_normal_messages;

// == TBMessage =========================================================================

TBMessage::TBMessage(TBID message, TBMessageData *data, double fire_time_ms, TBMessageHandler *mh)
	: message(message), data(data), fire_time_ms(fire_time_ms), mh(mh)
{
}

TBMessage::~TBMessage()
{
	delete data;
}

// == TBMessageHandler ==================================================================

TBMessageHandler::TBMessageHandler()
{
}

TBMessageHandler::~TBMessageHandler()
{
	DeleteAllMessages();
}

bool TBMessageHandler::PostMessageDelayed(TBID message, TBMessageData *data, uint32 delay_in_ms)
{
	return PostMessageOnTime(message, data, TBSystem::GetTimeMS() + (double)delay_in_ms);
}

bool TBMessageHandler::PostMessageOnTime(TBID message, TBMessageData *data, double fire_time)
{
	if (TBMessage *msg = new TBMessage(message, data, fire_time, this))
	{
		// Find the message that is already in the list that should fire later, so we can
		// insert msg just before that. (Always keep the list ordered after fire time)

		// NOTE: If another message is added during OnMessageReceived, it might or might not be fired
		// in the right order compared to other delayed messages, depending on if it's inserted before or
		// after the message being processed!

		TBMessage *later_msg = nullptr;
		TBMessageLink *link = g_all_delayed_messages.GetFirst();
		while (link)
		{
			TBMessage *msg_in_list = static_cast<TBMessage*>(link);
			if (msg_in_list->fire_time_ms > msg->fire_time_ms)
			{
				later_msg = msg_in_list;
				break;
			}
			link = link->GetNext();
		}

		// Add it to the global list in the right order.
		if (later_msg)
			g_all_delayed_messages.AddBefore(msg, later_msg);
		else
			g_all_delayed_messages.AddLast(msg);

		// Add it to the list in messagehandler.
		m_messages.AddLast(msg);

		// If we added it first and there's no normal messages, the next fire time has
		// changed and we have to reschedule the timer.
		if (!g_all_normal_messages.GetFirst() && g_all_delayed_messages.GetFirst() == msg)
			TBSystem::RescheduleTimer(msg->fire_time_ms);
		return true;
	}
	return false;
}

bool TBMessageHandler::PostMessage(TBID message, TBMessageData *data)
{
	if (TBMessage *msg = new TBMessage(message, data, 0, this))
	{
		g_all_normal_messages.AddLast(msg);
		m_messages.AddLast(msg);

		// If we added it and there was no messages, the next fire time has
		// changed and we have to rescedule the timer.
		if (g_all_normal_messages.GetFirst() == msg)
			TBSystem::RescheduleTimer(0);
		return true;
	}
	return false;
}

TBMessage *TBMessageHandler::GetMessageByID(TBID message)
{
	TBLinkListOf<TBMessage>::Iterator iter = m_messages.IterateForward();
	while (TBMessage *msg = iter.GetAndStep())
		if (msg->message == message)
			return msg;
	return nullptr;
}

void TBMessageHandler::DeleteMessage(TBMessage *msg)
{
	assert(msg->mh == this); // This is not the message handler owning the message!

	// Remove from global list (g_all_delayed_messages or g_all_normal_messages)
	if (g_all_delayed_messages.ContainsLink(msg))
		g_all_delayed_messages.Remove(msg);
	else if (g_all_normal_messages.ContainsLink(msg))
		g_all_normal_messages.Remove(msg);

	// Remove from local list
	m_messages.Remove(msg);

	delete msg;

	// Note: We could call TBSystem::RescheduleTimer if we think that deleting
	// this message changed the time for the next message.
}

void TBMessageHandler::DeleteAllMessages()
{
	while (TBMessage *msg = m_messages.GetFirst())
		DeleteMessage(msg);
}

//static
void TBMessageHandler::ProcessMessages()
{
	// Handle delayed messages
	TBLinkListOf<TBMessageLink>::Iterator iter = g_all_delayed_messages.IterateForward();
	while (TBMessage *msg = static_cast<TBMessage*>(iter.GetAndStep()))
	{
		if (TBSystem::GetTimeMS() >= msg->fire_time_ms)
		{
			// Remove from global list
			g_all_delayed_messages.Remove(msg);
			// Remove from local list
			msg->mh->m_messages.Remove(msg);

			msg->mh->OnMessageReceived(msg);

			delete msg;
		}
		else
			break; // Since the list is sorted, all remaining messages should fire later
	}

	// Handle normal messages
	iter = g_all_normal_messages.IterateForward();
	while (TBMessage *msg = static_cast<TBMessage*>(iter.GetAndStep()))
	{
		// Remove from global list
		g_all_normal_messages.Remove(msg);
		// Remove from local list
		msg->mh->m_messages.Remove(msg);

		msg->mh->OnMessageReceived(msg);

		delete msg;
	}
}

//static
double TBMessageHandler::GetNextMessageFireTime()
{
	if (g_all_normal_messages.GetFirst())
		return 0;

	if (g_all_delayed_messages.GetFirst())
	{
		TBMessage *first_delayed_msg = static_cast<TBMessage*>(g_all_delayed_messages.GetFirst());
		return first_delayed_msg->fire_time_ms;
	}

	return TB_NOT_SOON;
}

}; // namespace tb
