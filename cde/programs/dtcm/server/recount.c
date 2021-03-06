/*
 * CDE - Common Desktop Environment
 *
 * Copyright (c) 1993-2012, The Open Group. All rights reserved.
 *
 * These libraries and programs are free software; you can
 * redistribute them and/or modify them under the terms of the GNU
 * Lesser General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * These libraries and programs are distributed in the hope that
 * they will be useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with these libraries and programs; if not, write
 * to the Free Software Foundation, Inc., 51 Franklin Street, Fifth
 * Floor, Boston, MA 02110-1301 USA
 */
/* $XConsortium: recount.c /main/6 1996/11/21 19:45:46 drk $ */
/*
 *  (c) Copyright 1993, 1994 Hewlett-Packard Company
 *  (c) Copyright 1993, 1994 International Business Machines Corp.
 *  (c) Copyright 1993, 1994 Novell, Inc.
 *  (c) Copyright 1993, 1994 Sun Microsystems, Inc.
 */

#define XOS_USE_NO_LOCKING
#define X_INCLUDE_TIME_H
#if defined(__linux__)
#undef SVR4
#endif
#include <X11/Xos_r.h>

#include <EUSCompat.h>
#include "csa.h"
#include "rerule.h"
#include "repeat.h"
#include "reutil.h"
#include "iso8601.h"

static int InitialEventsToExclude(time_t, RepeatEvent *);
static int EventsPerMonth(RepeatEvent *);
static int DoBruteForce(const time_t, RepeatEvent	*);

/*
 * Give a start time, a parsed rule and a list of exception dates, determine
 * the number of events that will be generated.
 */
int
CountEvents(
	Tick		 	 start_time,
	RepeatEvent		*re,
	CSA_date_time_entry	*dte)
{
	time_t			 exclude_time,
				 close_time;
	int			 excluded_days = 0;
	unsigned int		 nevents1 = (unsigned int)-1,
				 nevents2 = (unsigned int)-1;

	if (!re || !start_time) return RE_ERROR;

	if (!re->re_end_date && re->re_duration == RE_INFINITY)
		return RE_INFINITY;

	/*
	 * Count the number of times an excluded time hits an event time
	 * generated by the rule.
	 */
	for (; dte; dte = dte->next) {
		RepeatEventState	*res;

		if (_csa_iso8601_to_tick(dte->date_time, &exclude_time) == -1)
			continue;

		if (!(close_time = ClosestTick(exclude_time, start_time, re,
								       &res))) {
			time_t		last_time;

			last_time = LastTick(start_time, re);
			if (last_time == exclude_time)
				excluded_days++;
		} else {
			if (close_time == exclude_time)
				excluded_days++;
		}
		
		_DtCm_free_re_state(res);
	}

	/*
	 * If there is an end date, then we must calculate the total number
	 * of events via the brute force method.
	 */
	if (re->re_end_date) {
		nevents1 = DoBruteForce(start_time, re) - excluded_days;
	}

	if (re->re_duration == RE_NOTSET)
		return nevents1;

	switch (re->re_type) {
	case RT_MINUTE:
		break;
	case RT_DAILY:
		nevents2 = re->re_duration;		
		break;
	case RT_WEEKLY:
		if (!RE_WEEKLY(re)->wd_ndaytime)
			nevents2 = re->re_duration;
		else
			nevents2 = re->re_duration *
						RE_WEEKLY(re)->wd_ndaytime;

		nevents2 -= InitialEventsToExclude(start_time, re);
		break;
	case RT_MONTHLY_POSITION: {
		int	events_per_month = EventsPerMonth(re);

		if (!events_per_month) {
			nevents2 = DoBruteForce(start_time, re);
		} else {
			nevents2 = re->re_duration * events_per_month -
				InitialEventsToExclude(start_time, re);
		}
		break;
	}
	case RT_MONTHLY_DAY: {
		int		 ndays = RE_MONTHLY(re)->md_nitems;
		struct tm	*start_tm;
		_Xltimeparams	 localtime_buf;

		start_tm = _XLocaltime((const time_t *)&start_time, localtime_buf);
		/* 
		 * Need to do this by brute force if they want days that may
		 * not exist in a given month.
		 */
		if (((!ndays) && start_tm->tm_mday > 28) ||
		    (ndays && RE_MONTHLY(re)->md_days[ndays - 1] > 28)) {
			nevents2 = DoBruteForce(start_time, re);
		} else {
			if (!ndays)
				nevents2 = re->re_duration;
			else
				nevents2 = re->re_duration * ndays;

			nevents2 -= InitialEventsToExclude(start_time, re);
		}
		break;
	}
	case RT_YEARLY_MONTH:
		if (!RE_YEARLY(re)->yd_nitems)
			nevents2 = re->re_duration;
		else
			nevents2 = re->re_duration * 
						RE_YEARLY(re)->yd_nitems;
		nevents2 -= InitialEventsToExclude(start_time, re);
		break;
	case RT_YEARLY_DAY:
		if (!RE_YEARLY(re)->yd_nitems)
			nevents2 = re->re_duration;
		else
			nevents2 = re->re_duration * 
						RE_YEARLY(re)->yd_nitems;
		nevents2 -= InitialEventsToExclude(start_time, re);
		break;
	}

	nevents2 -= excluded_days;

	/*
	 * If both a duration and and enddate are set the policy is to use
	 * the lesser of the two.
	 */
	if (nevents1 < nevents2)
		return nevents1;

	return nevents2;
}

/* 
 * If the rule is a weekly or monthly style with specific weekdays listed,
 * such as W1 MO WE FR and the start_time indicates the rule starts on say a
 * WE, then the first MO would not count as an event day so it must be
 * excluded from the total count.
 */
static int
InitialEventsToExclude(
	time_t		 start_time,
	RepeatEvent	*re)
{
	struct tm	*start_tm;
	_Xltimeparams	 localtime_buf;

	start_tm = _XLocaltime((const time_t *)&start_time, localtime_buf);

	if (re->re_type == RT_WEEKLY) {
		DayTime	*daytime = (DayTime *)RE_WEEKLY(re)->wd_daytime;
		int	 nevent_days = RE_WEEKLY(re)->wd_ndaytime,
			 i;

		if (!nevent_days) return 0;

		for (i = 0; i < nevent_days; i++) {
			if (daytime[i].dt_day >= start_tm->tm_wday)
				return i;
		}
		return (nevent_days);
	} else if (re->re_type == RT_MONTHLY_POSITION) {
		WeekDayTime *wdt = (WeekDayTime *)RE_MONTHLY(re)->md_weektime;
		int	     i,
			     ndays = 0;

		for (i = 0; i < RE_MONTHLY(re)->md_nitems; i++) {
			int 	j, k;
			time_t	date;

			for (j = 0; 
			    j < RE_MONTHLY(re)->md_weektime[i].wdt_nweek; 
			    j++) {

				for (k = 0; 
				    k < RE_MONTHLY(re)->md_weektime[i].wdt_nday;
				    k++) { 

					date = WeekNumberToDay(start_time,
						RE_MONTHLY(re)->md_weektime[i].
								   wdt_week[j],
						RE_MONTHLY(re)->md_weektime[i].
								   wdt_day[k]);
					if (!date || date < start_time)
						ndays++;
				}
			}
		}
		return (ndays);
	} else if (re->re_type == RT_MONTHLY_DAY) {
		int i;

		if (!RE_MONTHLY(re)->md_nitems) return 0;

		for (i = 0; i < RE_MONTHLY(re)->md_nitems; i++) {
			if (RE_MONTHLY(re)->md_days[i] >= start_tm->tm_mday)
				return i;
		}
		return (RE_MONTHLY(re)->md_nitems);
	} else if (re->re_type == RT_YEARLY_MONTH) {
		int i;

		if (!RE_YEARLY(re)->yd_nitems) return 0;

		for (i = 0; i < RE_YEARLY(re)->yd_nitems; i++) {
			if (RE_YEARLY(re)->yd_items[i] >= (start_tm->tm_mon +1))
				return i;
		}
		return (RE_YEARLY(re)->yd_nitems);
	} else if (re->re_type == RT_YEARLY_DAY) {
		int i;

		if (!RE_YEARLY(re)->yd_nitems) return 0;

		for (i = 0; i < RE_YEARLY(re)->yd_nitems; i++) {
			if (RE_YEARLY(re)->yd_items[i] >= 
							(start_tm->tm_yday + 1))
				return i;
		}
		return (RE_YEARLY(re)->yd_nitems);
	}

	return 0;
}
	
/*
 * Given a parsed MP rule determine the number of events it would generate
 * in a month.  If the rule suggests events should occure on the 5th week
 * which means the number of events generated in a given month is not
 * constant, we return 0.
 */
static int
EventsPerMonth(
	RepeatEvent	*re)
{
	int		 nevents = 1,
			 i;

	for (i = 0, nevents = 0; i < RE_MONTHLY(re)->md_nitems; i++) {
		int j;

		/* If 5+ or 5- is used, we must compute count by brute force */
		for (j = 0; j < RE_MONTHLY(re)->md_weektime[i].wdt_nweek; j++) {
			if ((RE_MONTHLY(re)->md_weektime[i].wdt_week[j] == 
								       WK_F5) ||
			    (RE_MONTHLY(re)->md_weektime[i].wdt_week[j] == 
								       WK_L5))
				return 0;
		}

		nevents += RE_MONTHLY(re)->md_weektime[i].wdt_nday *
			   RE_MONTHLY(re)->md_weektime[i].wdt_nweek;
	}

	return nevents;
}

/*
 * Given a start time and a parsed rule determine the number events generated
 * by walking the event stream until we reach the end.
 */
static int
DoBruteForce(
	const time_t	 	 start_time, 
	RepeatEvent		*re)
{
	RepeatEventState	*res;
	time_t			 cur_time;
	int			 nevents = 0;
	

	if (!(cur_time = ClosestTick(start_time, start_time, re, &res)))
		return nevents;

	nevents = 1;

	while ((cur_time = NextTick(cur_time, start_time, re, res))) {
		nevents++;
	}

	_DtCm_free_re_state(res);

	return nevents;
}
