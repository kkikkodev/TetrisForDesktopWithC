#include <stdio.h>
#include <time.h>
#include "Time.h"

// 현재 시간을 가져옴
time_t Time_GetTime() {

	time_t current;
	time(&current);

	return current;
}