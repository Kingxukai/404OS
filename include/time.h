/*ref linux011*/
#ifndef _TIME_H
#define _TIME_H

#ifndef _TIME_T
#define _TIME_T

#endif

#ifndef _SIZE_T
#define _SIZE_T

#endif

typedef long clock_t;

struct tm {
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
};

time_t mktime(struct tm * tp);

#endif
