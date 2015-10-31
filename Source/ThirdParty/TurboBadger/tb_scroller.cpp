// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_scroller.h"
#include "tb_widgets.h"
#include "tb_system.h"
#include <math.h>

namespace tb {

// == Misc constants ====================================================================

#define PAN_TARGET_FPS 60
#define PAN_MSG_DELAY_MS ((double)(1000.0 / PAN_TARGET_FPS))

#define PAN_START_THRESHOLD_MS 50
#define PAN_POWER_ACC_THRESHOLD_MS 600

#define PAN_POWER_MULTIPLIER 1.3f

#define SCROLL_DECAY 200.0f

#define SF_GATE_THRESHOLD 0.01f

// == TBScrollerFunction ================================================================

// Lab: http://www.madtealab.com/?V=1&C=6&F=5&G=1&O=1&W=774&GW=720&GH=252&GX=13.389616776278201&GY=4.790704772336853&GS=0.13102127484993598&EH=189&a=3.6666666666666665&aMa=20&aN=OrgSpeed&bMa=3&bN=CurPos&c=8&cMa=60&cI=1&cN=FrameRate&d=16&dMa=16&dI=1&dN=numSimulatedSeconds&l=2.388888888888889&lMa=5&lN=Decay&m=0.1&mMa=0.1&mN=GateThreshold&f1=OrgSpeed+%2A+exp%28-x+%2F+Decay%29&f1N=Speed&f2=CurPos+%2B+OrgSpeed+%2A+%281-exp%28-x+%2F+Decay%29%29%2A+Decay&f2N=Pos&f3=marker%28x%2C+predictGatedPoint%29&f3N=GatePoint&f4=aToF%28simulatedPoints%2Cnearest%2C0%2CnumSimulatedSeconds%29%28x%29&f4N=Iterated&f5=OrgSpeed+%2A+x&f5N=Linear1&Expr=%0ApredictGatedPoint+%3D+-log%28GateThreshold+%2F+%28OrgSpeed%29%29+%2A+Decay%0A%0Avar+cur+%3D+OrgSpeed%0AsimulatedPoints+%3D+sample%28function%28%29+%7B%0A+++cur+%3D+cur+%2A+%281+-+0.05%29%3B%0A+++return+cur%0A+%7D%2C+%5BnumSimulatedSeconds+%2A+FrameRate%5D%29%3B%0A%0ApredictGatedPoint

float TBScrollerFunction::GetDurationFromSpeed(float start_speed)
{
	float abs_start_speed = ABS(start_speed);
	if (abs_start_speed <= SF_GATE_THRESHOLD)
		return 0;
	return -log(SF_GATE_THRESHOLD / abs_start_speed) * m_decay;
}

float TBScrollerFunction::GetSpeedFromDistance(float distance)
{
	float speed = distance / m_decay;
	if (distance > SF_GATE_THRESHOLD)
		return speed + SF_GATE_THRESHOLD;
	else if (distance < -SF_GATE_THRESHOLD)
		return speed - SF_GATE_THRESHOLD;
	return speed;
}

float TBScrollerFunction::GetDistanceAtTime(float start_speed, float elapsed_time_ms)
{
	assert(elapsed_time_ms >= 0);
	return start_speed * (1 - exp(-elapsed_time_ms / m_decay)) * m_decay;
}

int TBScrollerFunction::GetDistanceAtTimeInt(float start_speed, float elapsed_time_ms)
{
	float distance = GetDistanceAtTime(start_speed, elapsed_time_ms);
	return (int)(distance < 0 ? distance - 0.5f : distance + 0.5f);
}

// == TBScroller ========================================================================

TBScroller::TBScroller(TBWidget *target)
	: m_target(target)
	, m_snap_listener(nullptr)
	, m_func(SCROLL_DECAY)
	, m_previous_pan_dx(0)
	, m_previous_pan_dy(0)
	, m_scroll_start_ms(0)
	, m_scroll_duration_x_ms(0)
	, m_scroll_duration_y_ms(0)
	, m_pan_power_multiplier_x(1)
	, m_pan_power_multiplier_y(1)
{
	Reset();
}

TBScroller::~TBScroller()
{
}

void TBScroller::Reset()
{
	m_is_started = false;
	m_pan_dx = m_pan_dy = 0;
	m_pan_time_ms = 0;
	m_pan_delta_time_ms = 0;
	m_scroll_start_speed_ppms_x = m_scroll_start_speed_ppms_y = 0;
	m_scroll_start_scroll_x = m_scroll_start_scroll_y = 0;
	// don't reset m_previous_pan_dx and m_previous_pan_dy here.
	// don't reset m_pan_power here. It's done on start since it's needed for next pan!
	m_expected_scroll_x = m_expected_scroll_y = 0;
}

void TBScroller::OnScrollBy(int dx, int dy, bool accumulative)
{
	if (!IsStarted())
		Start();

	float ppms_x = m_func.GetSpeedFromDistance((float)dx);
	float ppms_y = m_func.GetSpeedFromDistance((float)dy);

	if (accumulative && IsScrolling())
	{
		TBWidget::ScrollInfo info = m_target->GetScrollInfo();
		// If new direction is the same as the current direction,
		// calculate the speed needed for the remaining part and
		// add that to the new scroll speed.
		if ((ppms_x < 0) == (m_scroll_start_speed_ppms_x < 0))
		{
			int distance_x = m_func.GetDistanceAtTimeInt(m_scroll_start_speed_ppms_x,
				m_func.GetDurationFromSpeed(m_scroll_start_speed_ppms_x));
			int distance_remaining_x = m_scroll_start_scroll_x + distance_x - info.x;
			distance_remaining_x += m_func.GetDistanceAtTimeInt(ppms_x, m_func.GetDurationFromSpeed(ppms_x));
			ppms_x = m_func.GetSpeedFromDistance((float)distance_remaining_x);
		}
		if ((ppms_y < 0) == (m_scroll_start_speed_ppms_y < 0))
		{
			int distance_y = m_func.GetDistanceAtTimeInt(m_scroll_start_speed_ppms_y,
				m_func.GetDurationFromSpeed(m_scroll_start_speed_ppms_y));
			int distance_remaining_y = m_scroll_start_scroll_y + distance_y - info.y;
			distance_remaining_y += m_func.GetDistanceAtTimeInt(ppms_y, m_func.GetDurationFromSpeed(ppms_y));
			ppms_y = m_func.GetSpeedFromDistance((float)distance_remaining_y);
		}
	}

	AdjustToSnappingAndScroll(ppms_x, ppms_y);
}

bool TBScroller::OnPan(int dx, int dy)
{
	if (!IsStarted())
		Start();

	// Pan the target
	const int in_dx = dx, in_dy = dy;
	m_target->ScrollByRecursive(dx, dy);

	// Calculate the pan speed. Smooth it out with the
	// previous pan speed to reduce fluctuation a little.
	double now_ms = TBSystem::GetTimeMS();
	if (m_pan_time_ms)
	{
		if (m_pan_delta_time_ms)
			m_pan_delta_time_ms = (now_ms - m_pan_time_ms + m_pan_delta_time_ms) / 2.0f;
		else
			m_pan_delta_time_ms = now_ms - m_pan_time_ms;
	}

	m_pan_time_ms = now_ms;
	m_pan_dx = (m_pan_dx + in_dx) / 2.0f;
	m_pan_dy = (m_pan_dy + in_dy) / 2.0f;

	// If we change direction, reset the pan power multiplier in that axis.
	if (m_pan_dx != 0 && (m_previous_pan_dx < 0) != (m_pan_dx < 0))
		m_pan_power_multiplier_x = 1;
	if (m_pan_dy != 0 && (m_previous_pan_dy < 0) != (m_pan_dy < 0))
		m_pan_power_multiplier_y = 1;
	m_previous_pan_dx = m_pan_dx;
	m_previous_pan_dy = m_pan_dy;

	return in_dx != dx || in_dy != dy;
}

void TBScroller::OnPanReleased()
{
	if (TBSystem::GetTimeMS() < m_pan_time_ms + PAN_START_THRESHOLD_MS)
	{
		// Don't start scroll if we have too little speed.
		// This will prevent us from scrolling accidently.
		float pan_start_distance_threshold_px = 2 * TBSystem::GetDPI() / 100.0f;
		if (ABS(m_pan_dx) < pan_start_distance_threshold_px && ABS(m_pan_dy) < pan_start_distance_threshold_px)
		{
			StopOrSnapScroll();
			return;
		}

		if (m_pan_delta_time_ms == 0)
		{
			StopOrSnapScroll();
			return;
		}

		float ppms_x = (float)m_pan_dx / (float)m_pan_delta_time_ms;
		float ppms_y = (float)m_pan_dy / (float)m_pan_delta_time_ms;
		ppms_x *= m_pan_power_multiplier_x;
		ppms_y *= m_pan_power_multiplier_y;

		AdjustToSnappingAndScroll(ppms_x, ppms_y);
	}
	else
		StopOrSnapScroll();
}

void TBScroller::Start()
{
	if (IsStarted())
		return;
	m_is_started = true;
	double now_ms = TBSystem::GetTimeMS();
	if (now_ms < m_scroll_start_ms + PAN_POWER_ACC_THRESHOLD_MS)
	{
		m_pan_power_multiplier_x *= PAN_POWER_MULTIPLIER;
		m_pan_power_multiplier_y *= PAN_POWER_MULTIPLIER;
	}
	else
	{
		m_pan_power_multiplier_x = m_pan_power_multiplier_y = 1;
	}
}

void TBScroller::Stop()
{
	DeleteAllMessages();
	Reset();
}

bool TBScroller::StopIfAlmostStill()
{
	double now_ms = TBSystem::GetTimeMS();
	if (now_ms > m_scroll_start_ms + (double)m_scroll_duration_x_ms &&
		now_ms > m_scroll_start_ms + (double)m_scroll_duration_y_ms)
	{
		Stop();
		return true;
	}
	return false;
}

void TBScroller::StopOrSnapScroll()
{
	AdjustToSnappingAndScroll(0, 0);
	if (!IsScrolling())
		Stop();
}

void TBScroller::AdjustToSnappingAndScroll(float ppms_x, float ppms_y)
{
	if (m_snap_listener)
	{
		// Calculate the distance
		int distance_x = m_func.GetDistanceAtTimeInt(ppms_x, m_func.GetDurationFromSpeed(ppms_x));
		int distance_y = m_func.GetDistanceAtTimeInt(ppms_y, m_func.GetDurationFromSpeed(ppms_y));

		// Let the snap listener modify the distance
		TBWidget::ScrollInfo info = m_target->GetScrollInfo();
		int target_x = distance_x + info.x;
		int target_y = distance_y + info.y;
		m_snap_listener->OnScrollSnap(m_target, target_x, target_y);
		distance_x = target_x - info.x;
		distance_y = target_y - info.y;

		// Get the start speed from the new distance
		ppms_x = m_func.GetSpeedFromDistance((float)distance_x);
		ppms_y = m_func.GetSpeedFromDistance((float)distance_y);
	}

	Scroll(ppms_x, ppms_y);
}

void TBScroller::Scroll(float start_speed_ppms_x, float start_speed_ppms_y)
{
	// Set start values
	m_scroll_start_ms = TBSystem::GetTimeMS();
	GetTargetScrollXY(m_scroll_start_scroll_x, m_scroll_start_scroll_y);
	m_scroll_start_speed_ppms_x = start_speed_ppms_x;
	m_scroll_start_speed_ppms_y = start_speed_ppms_y;

	// Calculate duration for the scroll (each axis independently)
	m_scroll_duration_x_ms = m_func.GetDurationFromSpeed(m_scroll_start_speed_ppms_x);
	m_scroll_duration_y_ms = m_func.GetDurationFromSpeed(m_scroll_start_speed_ppms_y);

	if (StopIfAlmostStill())
		return;

	// Post the pan message if we don't already have one
	if (!GetMessageByID(TBIDC("scroll")))
	{
		// Update expected translation
		GetTargetChildTranslation(m_expected_scroll_x, m_expected_scroll_y);

		PostMessageDelayed(TBIDC("scroll"), nullptr, (uint32)PAN_MSG_DELAY_MS);
	}
}

bool TBScroller::IsScrolling()
{
	return GetMessageByID(TBIDC("scroll")) ? true : false;
}

void TBScroller::GetTargetChildTranslation(int &x, int &y) const
{
	int root_x = 0, root_y = 0;
	int child_translation_x = 0, child_translation_y = 0;
	TBWidget *scroll_root = m_target->GetScrollRoot();
	scroll_root->ConvertToRoot(root_x, root_y);
	scroll_root->GetChildTranslation(child_translation_x, child_translation_y);
	x = root_x + child_translation_x;
	y = root_y + child_translation_y;
}

void TBScroller::GetTargetScrollXY(int &x, int &y) const
{
	x = 0;
	y = 0;
	TBWidget *tmp = m_target->GetScrollRoot();
	while (tmp)
	{
		TBWidget::ScrollInfo info = tmp->GetScrollInfo();
		x += info.x;
		y += info.y;
		tmp = tmp->GetParent();
	}
}

void TBScroller::OnMessageReceived(TBMessage *msg)
{
	if (msg->message == TBIDC("scroll"))
	{
		int actual_scroll_x = 0, actual_scroll_y = 0;
		GetTargetChildTranslation(actual_scroll_x, actual_scroll_y);
		if (actual_scroll_x != m_expected_scroll_x ||
			actual_scroll_y != m_expected_scroll_y)
		{
			// Something else has affected the target child translation.
			// This should abort the scroll.
			// This could happen f.ex if something shrunk the scroll limits,
			// some other action changed scroll position, or if another
			// scroller started operating on a sub child that when reacing
			// its scroll limit, started scrolling its chain of parents.
			Stop();
			return;
		}

		// Calculate the time elapsed from scroll start. Clip within the
		// duration for each axis.
		double now_ms = TBSystem::GetTimeMS();
		float elapsed_time_x = (float)(now_ms - m_scroll_start_ms);
		float elapsed_time_y = elapsed_time_x;
		elapsed_time_x = MIN(elapsed_time_x, m_scroll_duration_x_ms);
		elapsed_time_y = MIN(elapsed_time_y, m_scroll_duration_y_ms);

		// Get the new scroll position from the current distance in each axis.
		int scroll_x = m_func.GetDistanceAtTimeInt(m_scroll_start_speed_ppms_x, elapsed_time_x);
		int scroll_y = m_func.GetDistanceAtTimeInt(m_scroll_start_speed_ppms_y, elapsed_time_y);
		scroll_x += m_scroll_start_scroll_x;
		scroll_y += m_scroll_start_scroll_y;

		// Get the scroll delta and invoke ScrollByRecursive.
		int curr_scroll_x, curr_scroll_y;
		GetTargetScrollXY(curr_scroll_x, curr_scroll_y);
		const int dx = scroll_x - curr_scroll_x;
		const int dy = scroll_y - curr_scroll_y;

		int idx = dx, idy = dy;
		m_target->ScrollByRecursive(idx, idy);

		// Update expected translation
		GetTargetChildTranslation(m_expected_scroll_x, m_expected_scroll_y);

		if ((dx && actual_scroll_x == m_expected_scroll_x) &&
			(dy && actual_scroll_y == m_expected_scroll_y))
		{
			// We didn't get anywhere despite we tried,
			// so we're done (reached the end).
			Stop();
			return;
		}

		if (!StopIfAlmostStill())
		{
			double next_fire_time = msg->GetFireTime() + PAN_MSG_DELAY_MS;
			// avoid timer catch-up if program went sleeping for a while.
			next_fire_time = MAX(next_fire_time, now_ms);
			PostMessageOnTime(TBIDC("scroll"), nullptr, next_fire_time);
		}
	}
}

}; // namespace tb
