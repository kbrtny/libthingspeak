#ifndef _TS_TIME_H_
#define _TS_TIME_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <thingspeak.h>
#include <time.h>


typedef struct tm  ts_tm_t;


typedef enum
{
    TS_TIME_LOCAL = 0 ,
    TS_TIME_GMT
} ts_time_type_t;

/* set local time to datapoint */
ts_tm_t *ts_settime(ts_datapoint_t *, ts_time_type_t);             
/* create time to datapoint */ 
void     ts_mktime(ts_datapoint_t *, int, int, int, int, int, int);

#ifdef __cplusplus
}
#endif

#endif
