// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_linklist.h"

namespace tb {

// == TBLinkListIterator ====================================================================================

TBLinkListIterator::TBLinkListIterator(TBLinkList *linklist, TBLink *current_link, bool forward)
	: m_linklist(linklist)
	, m_current_link(current_link)
	, m_forward(forward)
{
	Register();
}

TBLinkListIterator::TBLinkListIterator(const TBLinkListIterator &iter)
	: m_linklist(iter.m_linklist)
	, m_current_link(iter.m_current_link)
	, m_forward(iter.m_forward)
{
	Register();
}

TBLinkListIterator::~TBLinkListIterator()
{
	Unregister();
}

void TBLinkListIterator::Register()
{
	m_prev = nullptr;
	m_next = m_linklist->first_iterator;
	if (m_linklist->first_iterator)
		m_linklist->first_iterator->m_prev = this;
	m_linklist->first_iterator = this;
}

void TBLinkListIterator::Unregister()
{
	if (!m_linklist) // Already unregistered
		return;
	if (m_prev)
		m_prev->m_next = m_next;
	if (m_next)
		m_next->m_prev = m_prev;
	if (m_linklist->first_iterator == this)
		m_linklist->first_iterator = m_next;
}

void TBLinkListIterator::UnregisterAndClear()
{
	Unregister();
	m_linklist = nullptr;
	m_current_link = nullptr;
	m_prev = nullptr;
	m_next = nullptr;
}

const TBLinkListIterator& TBLinkListIterator::operator = (const TBLinkListIterator &iter)
{
	if (m_linklist != iter.m_linklist)
	{
		// Change where we are registered if we change linklist.
		Unregister();
		m_linklist = iter.m_linklist;
		Register();
	}
	m_linklist = iter.m_linklist;
	m_current_link = iter.m_current_link;
	m_forward = iter.m_forward;
	return *this;
}

void TBLinkListIterator::Reset()
{
	if (m_linklist)
		m_current_link = m_forward ? m_linklist->first : m_linklist->last;
	else
		m_current_link  = nullptr;
}

TBLink *TBLinkListIterator::GetAndStep()
{
	if (!m_current_link)
		return nullptr;
	TBLink *current = m_current_link;
	m_current_link = m_forward ? m_current_link->next : m_current_link->prev;
	return current;
}

void TBLinkListIterator::RemoveLink(TBLink *link)
{
	// If the current link is being removed, step away from it
	if (m_current_link == link)
		GetAndStep();
}

// == TBLinkList ============================================================================================

TBLinkList::~TBLinkList()
{
	RemoveAll();

	// Make sure any live iterators for this linklist are cleared!
	while (first_iterator)
		first_iterator->UnregisterAndClear();
}

void TBLinkList::AddFirst(TBLink *link)
{
	assert(!link->linklist); // Link is already in some list!
	link->linklist = this;
	link->next = first;
	if (first)
		first->prev = link;
	first = link;
	if (!last)
		last = link;
}

void TBLinkList::AddLast(TBLink *link)
{
	assert(!link->linklist); // Link is already in some list!
	link->linklist = this;
	link->prev = last;
	if (last)
		last->next = link;
	last = link;
	if (!first)
		first = link;
}

void TBLinkList::AddBefore(TBLink *link, TBLink *reference)
{
	assert(reference->linklist == this); // Reference is not added to this list!
	link->linklist = this;
	link->prev = reference->prev;
	link->next = reference;
	if (reference->prev)
		reference->prev->next = link;
	else
		first = link;
	reference->prev = link;
}

void TBLinkList::AddAfter(TBLink *link, TBLink *reference)
{
	assert(reference->linklist == this); // Reference is not added to this list!
	link->linklist = this;
	link->prev = reference;
	link->next = reference->next;
	if (reference->next)
		reference->next->prev = link;
	else
		last = link;
	reference->next = link;
}

void TBLinkList::Remove(TBLink *link)
{
	assert(link->linklist == this); // Link is not added to this list!

	// Go through iterators and make sure there are no pointers
	// to the link we remove.
	TBLinkListIterator *iter = first_iterator;
	while (iter)
	{
		iter->RemoveLink(link);
		iter = iter->m_next;
	}
	// Remove the link
	if (link->next)
		link->next->prev = link->prev;
	if (link->prev)
		link->prev->next = link->next;
	if (first == link)
		first = link->next;
	if (last == link)
		last = link->prev;
	link->linklist = nullptr;
	link->prev = nullptr;
	link->next = nullptr;
}

void TBLinkList::RemoveAll()
{
	// Reset all iterators.
	TBLinkListIterator *iter = first_iterator;
	while (iter)
	{
		iter->m_current_link = nullptr;
		iter = iter->m_next;
	}
	// Remove all links
	TBLink *link = first;
	while (link)
	{
		TBLink *next = link->next;
		link->linklist = nullptr;
		link->prev = nullptr;
		link->next = nullptr;
		link = next;
	}
	first = nullptr;
	last = nullptr;
}

int TBLinkList::CountLinks() const
{
	int count = 0;
	for (TBLink *link = first; link; link = link->next)
		count++;
	return count;
}

}; // namespace tb
