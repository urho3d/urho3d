// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "animation/tb_widget_animation.h"
#include "tb_window.h"
#include "tb_widgets.h"
#include "tb_widgets_common.h"
#include "tb_message_window.h"
#include "tb_list.h"

namespace tb {

TBLinkListOf<TBWidgetAnimationObject> widget_animations;

#define LERP(src, dst, progress) (src + (dst - src) * progress)

// == TBWidgetAnimationObject =============================================================

TBWidgetAnimationObject::TBWidgetAnimationObject(TBWidget *widget)
	: m_widget(widget)
{
	widget_animations.AddLast(this);
}

TBWidgetAnimationObject::~TBWidgetAnimationObject()
{
	widget_animations.Remove(this);
}

// == TBWidgetAnimationOpacity ============================================================

TBWidgetAnimationOpacity::TBWidgetAnimationOpacity(TBWidget *widget, float src_opacity, float dst_opacity, bool die)
	: TBWidgetAnimationObject(widget)
	, m_src_opacity(src_opacity)
	, m_dst_opacity(dst_opacity)
	, m_die(die)
{
}

void TBWidgetAnimationOpacity::OnAnimationStart()
{
	// Make sure we don't stay idle if nothing is scheduled (hack).
	// FIX: fix this properly
	m_widget->Invalidate();

	m_widget->SetOpacity(m_src_opacity);
}

void TBWidgetAnimationOpacity::OnAnimationUpdate(float progress)
{
	m_widget->SetOpacity(LERP(m_src_opacity, m_dst_opacity, progress));
}

void TBWidgetAnimationOpacity::OnAnimationStop(bool aborted)
{
	// If we're aborted, it may be because the widget is being deleted
	if (m_die && !aborted)
	{
		TBWidgetSafePointer the_widget(m_widget);
		if (m_widget->GetParent())
			m_widget->GetParent()->RemoveChild(m_widget);
		if (the_widget.Get())
			delete the_widget.Get();
	}
	else
		m_widget->SetOpacity(m_dst_opacity);
}

// == TBWidgetAnimationRect ===============================================================

TBWidgetAnimationRect::TBWidgetAnimationRect(TBWidget *widget, const TBRect &src_rect, const TBRect &dst_rect)
	: TBWidgetAnimationObject(widget)
	, m_src_rect(src_rect)
	, m_dst_rect(dst_rect)
	, m_mode(MODE_SRC_TO_DST)
{
}

TBWidgetAnimationRect::TBWidgetAnimationRect(TBWidget *widget, const TBRect &delta_rect, MODE mode)
	: TBWidgetAnimationObject(widget)
	, m_delta_rect(delta_rect)
	, m_mode(mode)
{
	assert(mode == MODE_DELTA_IN || mode == MODE_DELTA_OUT);
}

void TBWidgetAnimationRect::OnAnimationStart()
{
	// Make sure we don't stay idle if nothing is scheduled (hack).
	// FIX: fix this properly
	m_widget->Invalidate();

	if (m_mode == MODE_SRC_TO_DST)
		m_widget->SetRect(m_src_rect);
}

void TBWidgetAnimationRect::OnAnimationUpdate(float progress)
{
	if (m_mode == MODE_DELTA_IN || m_mode == MODE_DELTA_OUT)
	{
		m_dst_rect = m_src_rect = m_widget->GetRect();
		if (m_dst_rect.Equals(TBRect()))
		{
			// Widget hasn't been laid out yet,
			// the animation was started too soon.
			TBAnimationManager::AbortAnimation(this, true);
			return;
		}
		if (m_mode == MODE_DELTA_IN)
		{
			m_dst_rect.x += m_delta_rect.x;
			m_dst_rect.y += m_delta_rect.y;
			m_dst_rect.w += m_delta_rect.w;
			m_dst_rect.h += m_delta_rect.h;
		}
		else
		{
			m_src_rect.x += m_delta_rect.x;
			m_src_rect.y += m_delta_rect.y;
			m_src_rect.w += m_delta_rect.w;
			m_src_rect.h += m_delta_rect.h;
		}
		m_mode = MODE_SRC_TO_DST;
	}
	TBRect rect;
	rect.x = (int) LERP(m_src_rect.x, m_dst_rect.x, progress);
	rect.y = (int) LERP(m_src_rect.y, m_dst_rect.y, progress);
	rect.w = (int) LERP(m_src_rect.w, m_dst_rect.w, progress);
	rect.h = (int) LERP(m_src_rect.h, m_dst_rect.h, progress);
	m_widget->SetRect(rect);
}

void TBWidgetAnimationRect::OnAnimationStop(bool aborted)
{
	if (m_mode == MODE_SRC_TO_DST) // m_dst_rect may still be unset if aborted.
		m_widget->SetRect(m_dst_rect);
}

// == TBWidgetsAnimationManager =====================================================

TBWidgetsAnimationManager widgets_animation_manager;

void TBWidgetsAnimationManager::Init()
{
	TBWidgetListener::AddGlobalListener(&widgets_animation_manager);
}

void TBWidgetsAnimationManager::Shutdown()
{
	TBWidgetListener::RemoveGlobalListener(&widgets_animation_manager);
}

void TBWidgetsAnimationManager::AbortAnimations(TBWidget *widget)
{
	AbortAnimations(widget, nullptr);
}

void TBWidgetsAnimationManager::AbortAnimations(TBWidget *widget, TB_TYPE_ID type_id)
{
	TBLinkListOf<TBWidgetAnimationObject>::Iterator iter = widget_animations.IterateForward();
	while (TBWidgetAnimationObject *wao = iter.GetAndStep())
	{
		if (wao->m_widget == widget)
		{
			// Skip this animation if we asked for a specific (and
			// different) animation type.
			if (type_id != nullptr && !wao->IsOfTypeId(type_id))
				continue;

			// Abort the animation. This will both autoremove itself
			// and delete it, so no need to do it here.
			TBAnimationManager::AbortAnimation(wao, true);
		}
	}
}

void TBWidgetsAnimationManager::OnWidgetDelete(TBWidget *widget)
{
	// Kill and delete all animations running for the widget being deleted.
	AbortAnimations(widget);
}

bool TBWidgetsAnimationManager::OnWidgetDying(TBWidget *widget)
{
	bool handled = false;
	if (TBWindow *window = TBSafeCast<TBWindow>(widget))
	{
		// Fade out dying windows
		if (TBAnimationObject *anim = new TBWidgetAnimationOpacity(window, 1.f, TB_ALMOST_ZERO_OPACITY, true))
			TBAnimationManager::StartAnimation(anim, ANIMATION_CURVE_BEZIER);
		handled = true;
	}
	if (TBMessageWindow *window = TBSafeCast<TBMessageWindow>(widget))
	{
		// Move out dying message windows
		if (TBAnimationObject *anim = new TBWidgetAnimationRect(window, TBRect(0, 50, 0, 0), TBWidgetAnimationRect::MODE_DELTA_IN))
			TBAnimationManager::StartAnimation(anim, ANIMATION_CURVE_SPEED_UP);
		handled = true;
	}
	if (TBDimmer *dimmer = TBSafeCast<TBDimmer>(widget))
	{
		// Fade out dying dim layers
		if (TBAnimationObject *anim = new TBWidgetAnimationOpacity(dimmer, 1.f, TB_ALMOST_ZERO_OPACITY, true))
			TBAnimationManager::StartAnimation(anim, ANIMATION_CURVE_BEZIER);
		handled = true;
	}
	return handled;
}

void TBWidgetsAnimationManager::OnWidgetAdded(TBWidget *parent, TBWidget *widget)
{
	if (TBWindow *window = TBSafeCast<TBWindow>(widget))
	{
		// Fade in new windows
		if (TBAnimationObject *anim = new TBWidgetAnimationOpacity(window, TB_ALMOST_ZERO_OPACITY, 1.f, false))
			TBAnimationManager::StartAnimation(anim, ANIMATION_CURVE_BEZIER);
	}
	if (TBMessageWindow *window = TBSafeCast<TBMessageWindow>(widget))
	{
		// Move in new message windows
		if (TBAnimationObject *anim = new TBWidgetAnimationRect(window, TBRect(0, -50, 0, 0), TBWidgetAnimationRect::MODE_DELTA_OUT))
			TBAnimationManager::StartAnimation(anim);
	}
	if (TBDimmer *dimmer = TBSafeCast<TBDimmer>(widget))
	{
		// Fade in dim layer
		if (TBAnimationObject *anim = new TBWidgetAnimationOpacity(dimmer, TB_ALMOST_ZERO_OPACITY, 1.f, false))
			TBAnimationManager::StartAnimation(anim, ANIMATION_CURVE_BEZIER);
	}
}

void TBWidgetsAnimationManager::OnWidgetRemove(TBWidget *parent, TBWidget *widget)
{
}

}; // namespace tb
