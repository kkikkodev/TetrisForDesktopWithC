#ifndef _TIME_H
#define _TIME_H

typedef struct _time{
	
	int second;
	int minute;
	int hour;

}Time;

Time Time_GetCurrentTime();
Time Time_Init();
int Time_GetTimeDifference(Time currentTime, Time lastTime);

#endif