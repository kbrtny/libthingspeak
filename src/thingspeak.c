#include <thingspeak.h>
#include <ts_http.h>
#include <ts_time.h>


ts_context_t *ts_create_context(const char *api_key, ts_feed_id_t feed_id)
{
    ts_context_t *ctx = NULL;

    if(api_key != NULL)
    {
        ctx = (ts_context_t*)malloc(sizeof(ts_context_t));
        bzero(ctx->api_key, 16);
        strcpy(ctx->api_key, api_key);
        ctx->api_key[16] = '\0';
        ctx->feed_id = feed_id;
    }
    return ctx;
}


void ts_delete_context(ts_context_t *ctx)
{
    if(ctx)
        free(ctx);
}



ts_datapoint_t *ts_set_value_i32(ts_datapoint_t *datapoint, int32_t val)
{
    datapoint->value_type = TS_VALUE_TYPE_I32;
    datapoint->value.i32_value = val;
    datapoint->timestamp = 0;
    return datapoint;
}


int32_t ts_get_value_i32(const ts_datapoint_t *datapoint)
{
    return datapoint->value.i32_value;
}

ts_datapoint_t *ts_set_value_f32(ts_datapoint_t *datapoint, float val)
{
    datapoint->value_type = TS_VALUE_TYPE_F32;
    datapoint->value.f32_value = val;
    datapoint->timestamp = 0;
    return datapoint;
}

float ts_get_value_f32(const ts_datapoint_t *datapoint)
{
    return datapoint->value.f32_value;
}


int32_t ts_datastream_update(const ts_context_t* ctx, ts_feed_id_t feed_id, const char * datastream_id,
                                                                      ts_datapoint_t *datapoint)
{
    char  num[200]    = {0};
    ssize_t n         = 0;
    ts_context_t *tsx = NULL;
    ts_tm_t *timeinfo;

    if(datapoint->timestamp <= 0)
        timeinfo = ts_settime(datapoint, TS_TIME_LOCAL);
        
    switch(datapoint->value_type)
    {
        case TS_VALUE_TYPE_I32:
            sprintf(num, "%s=%d", datastream_id, datapoint->value.i32_value);
            break;
        case TS_VALUE_TYPE_F32:
            sprintf(num, "%s=%f", datastream_id, datapoint->value.f32_value);
            break;
        case TS_VALUE_TYPE_STR:
            sprintf(num, "%s=%s", datastream_id, datapoint->value.str_value);
            break;
        default:
            break;
    }
    
    sprintf(num, "%s&created_at=%d-%d-%d %d:%d:%d", num, (1900/*unix time start*/+timeinfo->tm_year),
                                                                                (timeinfo->tm_mon+1),
                                                                                   timeinfo->tm_mday,
                                                                                   timeinfo->tm_hour,
                                                                                    timeinfo->tm_min, 
                                                                                   timeinfo->tm_sec);
#if TS_DEBUG                                                                                    
    printf("%s\n", num);
#endif


    if(feed_id == 0)
        n = ts_http_post(ctx, HOST_API, "/update", num);
    else
    {
        tsx = ts_create_context(ctx->api_key, feed_id);
        if(tsx)
        {
            n = ts_http_post(ctx, HOST_API, "/update", num);
            ts_delete_context(tsx);
        }
        else
            return -1;
    }
    return (n > 0) ? 0 : 1;
}

int32_t ts_datastream_update_four(const ts_context_t* ctx, ts_feed_id_t feed_id, 
                                    const char * datastream_id1, /*"field1" */ ts_datapoint_t *datapoint1,
                                    const char * datastream_id2, /*"field2" */ ts_datapoint_t *datapoint2,
                                    const char * datastream_id3, /*"field3" */ ts_datapoint_t *datapoint3,
                                    const char * datastream_id4, /*"field4" */ ts_datapoint_t *datapoint4
                                    )
{
    char  num[200]    = {0};
    char  num1[200]    = {0};
    char  num2[200]    = {0};
    char  num3[200]    = {0};
    char  num4[200]    = {0};
    ssize_t n         = 0;
    ts_context_t *tsx = NULL;
    ts_tm_t *timeinfo;

    if(datapoint1->timestamp <= 0)
        timeinfo = ts_settime(datapoint1, TS_TIME_LOCAL);
        
    switch(datapoint1->value_type)
    {
        case TS_VALUE_TYPE_I32:
            sprintf(num1, "%s=%d", datastream_id1, datapoint1->value.i32_value);
            break;
        case TS_VALUE_TYPE_F32:
            sprintf(num1, "%s=%f", datastream_id1, datapoint1->value.f32_value);
            break;
        case TS_VALUE_TYPE_STR:
            sprintf(num1, "%s=%s", datastream_id1, datapoint1->value.str_value);
            break;
        default:
            break;
    }

    switch(datapoint2->value_type)
    {
        case TS_VALUE_TYPE_I32:
            sprintf(num2, "&%s=%d", datastream_id2, datapoint2->value.i32_value);
            break;
        case TS_VALUE_TYPE_F32:
            sprintf(num2, "&%s=%f", datastream_id2, datapoint2->value.f32_value);
            break;
        case TS_VALUE_TYPE_STR:
            sprintf(num2, "&%s=%s", datastream_id2, datapoint2->value.str_value);
            break;
        default:
            break;
    }

    switch(datapoint3->value_type)
    {
        case TS_VALUE_TYPE_I32:
            sprintf(num3, "&%s=%d", datastream_id3, datapoint3->value.i32_value);
            break;
        case TS_VALUE_TYPE_F32:
            sprintf(num3, "&%s=%f", datastream_id3, datapoint3->value.f32_value);
            break;
        case TS_VALUE_TYPE_STR:
            sprintf(num3, "&%s=%s", datastream_id3, datapoint3->value.str_value);
            break;
        default:
            break;
    }  

    switch(datapoint4->value_type)
    {
        case TS_VALUE_TYPE_I32:
            sprintf(num4, "&%s=%d", datastream_id4, datapoint4->value.i32_value);
            break;
        case TS_VALUE_TYPE_F32:
            sprintf(num4, "&%s=%f", datastream_id4, datapoint4->value.f32_value);
            break;
        case TS_VALUE_TYPE_STR:
            sprintf(num4, "&%s=%s", datastream_id4, datapoint4->value.str_value);
            break;
        default:
            break;
    }        

    sprintf(num, "%s%s%s%s&created_at=%d-%d-%d %d:%d:%d", num1, num2, num3, num4, (1900/*unix time start*/+timeinfo->tm_year),
                                                                                (timeinfo->tm_mon+1),
                                                                                   timeinfo->tm_mday,
                                                                                   timeinfo->tm_hour,
                                                                                    timeinfo->tm_min, 
                                                                                   timeinfo->tm_sec);

#if TS_DEBUG                                                                                    
    printf("%s\n", num);
#endif

    if(feed_id == 0)
        n = ts_http_post(ctx, HOST_API, "/update", num);
    else
    {
        tsx = ts_create_context(ctx->api_key, feed_id);
        if(tsx)
        {
            n = ts_http_post(ctx, HOST_API, "/update", num);
            ts_delete_context(tsx);
        }
        else
            return -1;
    }
    return (n > 0) ? 0 : 1;
}

/** Update multiple data points.
 * \param ctx Context
 * \param feed_id Feed ID
 * \param datastream_ids Array of data stream IDs
 * \param datapoints Array of data points
 * \param many No of items in datastream_ids[] and datapoints[]
 * \retval 0 on success
 * \retval 1 on failure
 */
int32_t ts_datastream_update_many(const ts_context_t* ctx, ts_feed_id_t feed_id,
                                    const char * datastream_ids[], ts_datapoint_t *datapoints,
                                    int many)
{
    char  num[200]    = {0};
    ssize_t n         = 0;
    ts_context_t *tsx = NULL;
    ts_tm_t *timeinfo;
    int i;
    int char_ctr = 0;

    if(datapoints[0].timestamp <= 0)
        timeinfo = ts_settime(&datapoints[0], TS_TIME_LOCAL);

    for (i=0; i<many; i++) {
        /* Choose the right format string */
        const char * format[TS_VALUE_TYPE_CNT][2] = {
            /*   1st,     N-th data point */
            {"%s=%d", "&%s=%d"},  /* TS_VALUE_TYPE_I32 */
            {"%s=%f", "&%s=%f"},  /* TS_VALUE_TYPE_F32 */
            {"%s=%s", "&%s=%s"}   /* TS_VALUE_TYPE_STR */
        };
        const char * fmt = format[datapoints[i].value_type][i > 0];

        /* Append data to URL */
        switch(datapoints[i].value_type)
        {
            case TS_VALUE_TYPE_I32:
                char_ctr += sprintf(num + char_ctr, fmt, datastream_ids[i], datapoints[i].value.i32_value);
                break;
            case TS_VALUE_TYPE_F32:
                char_ctr += sprintf(num + char_ctr, fmt, datastream_ids[i], datapoints[i].value.f32_value);
                break;
            case TS_VALUE_TYPE_STR:
                char_ctr += sprintf(num + char_ctr, fmt, datastream_ids[i], datapoints[i].value.str_value);
                break;
            default:
                break;
        }
    }

    char_ctr += strftime(num + char_ctr, sizeof(num) - char_ctr, "&created_at=%F %T", timeinfo);

#if TS_DEBUG
    printf("%s\n", num);
#endif

    if(feed_id == 0)
        n = ts_http_post(ctx, HOST_API, "/update", num);
    else
    {
        tsx = ts_create_context(ctx->api_key, feed_id);
        if(tsx)
        {
            n = ts_http_post(ctx, HOST_API, "/update", num);
            ts_delete_context(tsx);
        }
        else
            return -1;
    }
    return (n > 0) ? 0 : 1;
}

char *ts_datastream_get(const ts_context_t *ctx, ts_feed_id_t feed_id,
                                           ts_data_type_t type,
                                           const char *datastream_id,
                                           char *result)
{
    char *ans       = NULL;
    uint32_t id     = 0;
    char  page[128] = {0};
    char  d_id[2]   = {0}; 

    id = (feed_id == 0) ? ctx->feed_id : feed_id;
    sscanf(datastream_id, "field%s", d_id);

    switch(type)
    {
        case TS_DATA_CSV:
            sprintf(page, "/channels/%d/feeds/%s.csv", id, d_id);
            break;
        case TS_DATA_XML:
            sprintf(page, "/channels/%d/feeds/%s.xml", id, d_id);
            break;
        case TS_DATA_JSON:
            sprintf(page, "/channels/%d/feeds/%s.json", id, d_id);
            break;
    }

#if TS_DEBUG
    printf("%s\n", page);
#endif

    ans = ts_http_get(HOST_API, page, result);

    return ans;
}


char *ts_feed_get_all(const ts_context_t* ctx, ts_feed_id_t feed_id,
                                         ts_data_type_t type,
                                         char *result)
{
    char *ans       = NULL;
    uint32_t id     = 0;
    char  page[128] = {0};


    id = (feed_id == 0) ? ctx->feed_id : feed_id;

    switch(type)
    {
        case TS_DATA_CSV:
            sprintf(page, "/channels/%d/feeds.csv", id);
            break;
        case TS_DATA_XML:
            sprintf(page, "/channels/%d/feeds.xml", id);
            break;
        case TS_DATA_JSON:
            sprintf(page, "/channels/%d/feeds.json", id);
            break;
    }

#if TS_DEBUG
    printf("%s\n", page);
#endif    

    ans = ts_http_get(HOST_API, page, result);


    return ans;
}
