// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#ifndef TB_WIDGET_SKIN_CONDITION_CONTEXT_H
#define TB_WIDGET_SKIN_CONDITION_CONTEXT_H

#include "tb_widgets.h"
#include "tb_skin.h"

namespace tb {

/** Check if a condition is true for a widget when painting a skin. */

class TBWidgetSkinConditionContext : public TBSkinConditionContext
{
public:
	TBWidgetSkinConditionContext(TBWidget *widget) : m_widget(widget) {}
	virtual bool GetCondition(TBSkinCondition::TARGET target, const TBSkinCondition::CONDITION_INFO &info);
private:
	bool GetCondition(TBWidget *widget, const TBSkinCondition::CONDITION_INFO &info);
	TBWidget *m_widget;
};

}; // namespace tb

#endif // TB_WIDGET_SKIN_CONDITION_CONTEXT_H
