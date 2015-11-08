// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "animation/tb_animation.h"
#include "tb_system.h"

namespace tb {

// == Helpers =======================================================

#define SMOOTHSTEP(x) ((x) * (x) * (3.0f - 2.0f * (x)))

static float sc(float x)
{
	float s = x < 0 ? -1.f : 1.f;
	x = ABS(x);
	if (x >= 1)
		return s;
	return s * (x < 0 ? x / 0.5f : (x / (1 + x * x)) / 0.5f);
}

static float SmoothCurve(float x, float a)
{
	float r = a * x / (2 * a * x - a - x + 1);
	r = (r - 0.5f) * 2;
	return sc(r) * 0.5f + 0.5f;
}

// == TBAnimationObject ===============================================

void TBAnimationObject::InvokeOnAnimationStart()
{
	TBLinkListOf<TBAnimationListener>::Iterator li = m_listeners.IterateForward();
	OnAnimationStart();
	while (TBAnimationListener *listener = li.GetAndStep())
		listener->OnAnimationStart(this);
}

void TBAnimationObject::InvokeOnAnimationUpdate(float progress)
{
	TBLinkListOf<TBAnimationListener>::Iterator li = m_listeners.IterateForward();
	OnAnimationUpdate(progress);
	while (TBAnimationListener *listener = li.GetAndStep())
		listener->OnAnimationUpdate(this, progress);
}

void TBAnimationObject::InvokeOnAnimationStop(bool aborted)
{
	TBLinkListOf<TBAnimationListener>::Iterator li = m_listeners.IterateForward();
	OnAnimationStop(aborted);
	while (TBAnimationListener *listener = li.GetAndStep())
		listener->OnAnimationStop(this, aborted);
}

// == TBAnimationManager ==============================================

TBLinkListOf<TBAnimationObject> TBAnimationManager::animating_objects;
static int block_animations_counter = 0;

//static
void TBAnimationManager::AbortAllAnimations()
{
	while (TBAnimationObject *obj = animating_objects.GetFirst())
		AbortAnimation(obj, true);
}

//static
void TBAnimationManager::Update()
{
	double time_now = TBSystem::GetTimeMS();

	TBLinkListOf<TBAnimationObject>::Iterator iter = animating_objects.IterateForward();
	while (TBAnimationObject *obj = iter.GetAndStep())
	{
		// Adjust the start time if it's the first update time for this object.
		if (obj->adjust_start_time)
		{
			obj->animation_start_time = time_now;
			obj->adjust_start_time = false;
		}

		// Calculate current progress
		// If animation_duration is 0, it should just complete immediately.
		float progress = 1.0f;
		if (obj->animation_duration != 0)
		{
			progress = (float)(time_now - obj->animation_start_time) / (float)obj->animation_duration;
			progress = MIN(progress, 1.0f);
		}

		// Apply animation curve
		float tmp;
		switch (obj->animation_curve)
		{
		case ANIMATION_CURVE_SLOW_DOWN:
			tmp = 1 - progress;
			progress = 1 - tmp * tmp * tmp;
			break;
		case ANIMATION_CURVE_SPEED_UP:
			progress = progress * progress * progress;
			break;
		case ANIMATION_CURVE_BEZIER:
			progress = SMOOTHSTEP(progress);
			break;
		case ANIMATION_CURVE_SMOOTH:
			progress = SmoothCurve(progress, 0.6f);
			break;
		default: // linear (progress is already linear)
			break;
		};

		// Update animation
		obj->InvokeOnAnimationUpdate(progress);

		// Remove completed animations
		if (progress == 1.0f)
		{
			animating_objects.Remove(obj);
			obj->InvokeOnAnimationStop(false);
			delete obj;
		}
	}
}

//static
bool TBAnimationManager::HasAnimationsRunning()
{
	return animating_objects.HasLinks();
}

//static
void TBAnimationManager::StartAnimation(TBAnimationObject *obj, ANIMATION_CURVE animation_curve, double animation_duration, ANIMATION_TIME animation_time)
{
	if (obj->IsAnimating())
		AbortAnimation(obj, false);
	if (IsAnimationsBlocked())
		animation_duration = 0;
	obj->adjust_start_time = (animation_time == ANIMATION_TIME_FIRST_UPDATE ? true : false);
	obj->animation_start_time = TBSystem::GetTimeMS();
	obj->animation_duration = MAX(animation_duration, 0.0);
	obj->animation_curve = animation_curve;
	animating_objects.AddLast(obj);
	obj->InvokeOnAnimationStart();
}

//static
void TBAnimationManager::AbortAnimation(TBAnimationObject *obj, bool delete_animation)
{
	if (obj->IsAnimating())
	{
		animating_objects.Remove(obj);
		obj->InvokeOnAnimationStop(true);
		if (delete_animation)
			delete obj;
	}
}

//static
bool TBAnimationManager::IsAnimationsBlocked()
{
	return block_animations_counter > 0;
}

//static
void TBAnimationManager::BeginBlockAnimations()
{
	block_animations_counter++;
}

//static
void TBAnimationManager::EndBlockAnimations()
{
	assert(block_animations_counter > 0);
	block_animations_counter--;
}

}; // namespace tb
