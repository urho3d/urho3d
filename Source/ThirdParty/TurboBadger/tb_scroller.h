// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#ifndef TB_SCROLLER_H
#define TB_SCROLLER_H

#include "tb_core.h"
#include "tb_msg.h"

namespace tb {

class TBWidget;

/** TBScrollerFunction does the calculations of time, speed and distance
	that decides how the slow down of a scroll will happen.

	Note: Speed is in pixels per millisecond. Duration is in milliseconds
		  and distance is in pixels. Distance and speed may be negative! */

class TBScrollerFunction
{
public:
	TBScrollerFunction(float decay) : m_decay(decay) {}

	/** Calculate the duration needed until the end distance is reached
		from the given start speed. */
	float GetDurationFromSpeed(float start_speed);

	/** Calculate the start speed needed to reach the given distance. */
	float GetSpeedFromDistance(float distance);

	/** Calculate the distance reached at the given elapsed_time_ms with the given start_speed. */
	float GetDistanceAtTime(float start_speed, float elapsed_time_ms);

	/** Same as GetDistanceAtTime but rounded to integer. */
	int GetDistanceAtTimeInt(float start_speed, float elapsed_time_ms);
private:
	float m_decay;
};

/** TBScrollerSnapListener may override the target scroll position of a TBScroller. */

class TBScrollerSnapListener
{
public:
	virtual ~TBScrollerSnapListener() {};

	/** Called when the target scroll position is calculated.

		target_widget is the widget being scroller.
		target_x, target_y is the suggested target scroll position which may be changed
		to something else in this call.

		Note: The scroll positions are relative to the target widget (inner scrolled TBWidget).
			  If there's nested scrollable widgets, only the inner scrolled widget applies snapping. */
	virtual void OnScrollSnap(TBWidget *target_widget, int &target_x, int &target_y) = 0;
};

/** TBScroller handles panning while the pointer is down and measure the pan
	speed over time. It also handles continued scrolling when the pointer has
	been released with a flick. */
class TBScroller : private TBMessageHandler
{
public:
	TBScroller(TBWidget *target);
	~TBScroller();

	/** Set the listener that may override the target scroll position. */
	void SetSnapListener(TBScrollerSnapListener *listener) { m_snap_listener = listener; }

	/** Start tracking pan movement from calls to OnPan. */
	void Start();

	/** Stop tracking pan movement from calls to OnPan,
		or stop any ongoing scrolling. */
	void Stop();

	/** Return true if the pan tracking is started or. */
	bool IsStarted() const { return m_is_started; }

	/** Get the widget that will be panned/scrolled. Any parent of this
		widget may also be panned/scrolled. */
	TBWidget *GetTarget() const { return m_target; }

	/** Pan the target widget (or any parent) with the given deltas.
		Should be called while the pointer is down.
		This will track the pan speed over time. */
	bool OnPan(int dx, int dy);

	/** The panning ends and the scroller should start scrolling.
		Should be called when the pointer is released. */
	void OnPanReleased();

	/** Start the scroller based on the given delta. Doesn't
		require previous calls to OnPan or OnPanReleased.

		If accumulative is true, the given delta will be
		added to any on going scroll. If it's false, any
		ongoing scroll will be canceled. */
	void OnScrollBy(int dx, int dy, bool accumulative);
private:
	virtual void OnMessageReceived(TBMessage *msg);
	bool IsScrolling();
	bool StopIfAlmostStill();
	void StopOrSnapScroll();
	void Reset();
	void AdjustToSnappingAndScroll(float ppms_x, float ppms_y);
	void Scroll(float start_speed_ppms_x, float start_speed_ppms_y);
	void GetTargetChildTranslation(int &x, int &y) const;
	void GetTargetScrollXY(int &x, int &y) const;
	TBWidget *m_target;
	TBScrollerSnapListener *m_snap_listener;
	TBScrollerFunction m_func;
	bool m_is_started;
	float m_pan_dx, m_pan_dy;
	float m_previous_pan_dx, m_previous_pan_dy;
	double m_pan_time_ms;
	double m_pan_delta_time_ms;
	float m_scroll_start_speed_ppms_x, m_scroll_start_speed_ppms_y;
	double m_scroll_start_ms;
	float m_scroll_duration_x_ms, m_scroll_duration_y_ms;
	int m_scroll_start_scroll_x, m_scroll_start_scroll_y;
	float m_pan_power_multiplier_x;
	float m_pan_power_multiplier_y;
	int m_expected_scroll_x;
	int m_expected_scroll_y;
};

}; // namespace tb

#endif // TB_SCROLLER_H
