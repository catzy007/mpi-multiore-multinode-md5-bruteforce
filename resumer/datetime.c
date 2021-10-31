#include "datetime.h"

void datetime(void){
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	printf("Date : %.2d/%.2d/%d - %.2d:%.2d:%.2d\n", 
            tm.tm_year + 1900, tm.tm_mon + 1, 
            tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}