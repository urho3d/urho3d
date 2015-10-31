// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_widget_value.h"
#include "tb_widgets.h"

namespace tb {

// == TBWidgetValueConnection ===========================================================

void TBWidgetValueConnection::Connect(TBWidgetValue *value, TBWidget *widget)
{
	Unconnect();
	m_widget = widget;
	m_value = value;
	m_value->m_connections.AddLast(this);
	m_value->SyncToWidget(m_widget);
}

void TBWidgetValueConnection::Unconnect()
{
	if (m_value)
		m_value->m_connections.Remove(this);
	m_value = nullptr;
	m_widget = nullptr;
}

void TBWidgetValueConnection::SyncFromWidget(TBWidget *source_widget)
{
	if (m_value)
		m_value->SetFromWidget(source_widget);
}

// == TBWidgetValue =====================================================================

TBWidgetValue::TBWidgetValue(const TBID &name, TBValue::TYPE type)
	: m_name(name)
	, m_value(type)
	, m_syncing(false)
{
}

TBWidgetValue::~TBWidgetValue()
{
	while (m_connections.GetFirst())
		m_connections.GetFirst()->Unconnect();
}

void TBWidgetValue::SetFromWidget(TBWidget *source_widget)
{
	if (m_syncing)
		return; // We ended up here because syncing is in progress.

	// Get the value in the format
	TBStr text;
	switch (m_value.GetType())
	{
		case TBValue::TYPE_STRING:
			if (!source_widget->GetText(text))
				return;
			m_value.SetString(text, TBValue::SET_NEW_COPY);
			break;
		case TBValue::TYPE_NULL:
		case TBValue::TYPE_INT:
			m_value.SetInt(source_widget->GetValue());
			break;
		case TBValue::TYPE_FLOAT:
			// FIX: TBValue should use double instead of float?
			m_value.SetFloat((float)source_widget->GetValueDouble());
			break;
		default:
			assert(!"Unsupported value type!");
	}

	SyncToWidgets(source_widget);
}

bool TBWidgetValue::SyncToWidgets(TBWidget *exclude_widget)
{
	// FIX: Assign group to each value. Currently we only have one global group.
	g_value_group.InvokeOnValueChanged(this);

	bool fail = false;
	TBLinkListOf<TBWidgetValueConnection>::Iterator iter = m_connections.IterateForward();
	while (TBWidgetValueConnection *connection = iter.GetAndStep())
	{
		if (connection->m_widget != exclude_widget)
			fail |= !SyncToWidget(connection->m_widget);
	}
	return !fail;
}

bool TBWidgetValue::SyncToWidget(TBWidget *dst_widget)
{
	if (m_syncing)
		return true; // We ended up here because syncing is in progress.

	m_syncing = true;
	bool ret = true;
	switch (m_value.GetType())
	{
		case TBValue::TYPE_STRING:
			ret = dst_widget->SetText(m_value.GetString());
			break;
		case TBValue::TYPE_NULL:
		case TBValue::TYPE_INT:
			dst_widget->SetValue(m_value.GetInt());
			break;
		case TBValue::TYPE_FLOAT:
			// FIX: TBValue should use double instead of float?
			dst_widget->SetValueDouble(m_value.GetFloat());
			break;
		default:
			assert(!"Unsupported value type!");
	}
	m_syncing = false;
	return ret;
}

void TBWidgetValue::SetInt(int value)
{
	m_value.SetInt(value);
	SyncToWidgets(nullptr);
}

bool TBWidgetValue::SetText(const char *text)
{
	m_value.SetString(text, TBValue::SET_NEW_COPY);
	return SyncToWidgets(nullptr);
}

void TBWidgetValue::SetDouble(double value)
{
	// FIX: TBValue should use double instead of float?
	m_value.SetFloat((float)value);
	SyncToWidgets(nullptr);
}

// == TBValueGroup ================================================================================

/*extern*/ TBValueGroup g_value_group;

TBWidgetValue *TBValueGroup::CreateValueIfNeeded(const TBID &name, TBValue::TYPE type)
{
	if (TBWidgetValue *val = GetValue(name))
		return val;
	if (TBWidgetValue *val = new TBWidgetValue(name, type))
	{
		if (m_values.Add(name, val))
			return val;
		else
			delete val;
	}
	return nullptr;
}

void TBValueGroup::InvokeOnValueChanged(const TBWidgetValue *value)
{
	TBLinkListOf<TBValueGroupListener>::Iterator iter = m_listeners.IterateForward();
	while (TBValueGroupListener *listener = iter.GetAndStep())
		listener->OnValueChanged(this, value);
}

}; // namespace tb
