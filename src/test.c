#include <thingspeak.h>
#include <ts_http.h>

#define CHANNEL_CNT 3

int main(int argc, char **argv)
{
	ts_context_t *ctx   = NULL;
	ts_datapoint_t data[CHANNEL_CNT];

	const char* ids[CHANNEL_CNT] = {"field1", "field2", "field3"};
	char *result        = NULL;

	if(argc < 3) {
		printf("Usage: %s <API key> <feed ID>\n", argv[0]);
		return -1;
	}

	ctx = ts_create_context(argv[1], atoi(argv[2]));
	result = (char*)malloc(sizeof(char)*MAXLINE);
	bzero(result, MAXLINE);

	ts_set_value_i32(&data[0], 11);
	ts_set_value_i32(&data[1], 22);
	ts_set_value_i32(&data[2], 33);
	/*ts_http_post(ctx, HOST_API, "/update", "field1=0&field2=36&field3=21324");
	printf("%s\n", ts_http_get(HOST_API, "/channels/16258/feed.json"));*/

	ts_datastream_update_many(ctx, 0, ids, data, CHANNEL_CNT);

	printf("\n\nJSON:\n%s\n", ts_feed_get_all(ctx, 0, TS_DATA_JSON, result));
	printf("\n\nCSV:\n%s\n", ts_datastream_get(ctx, 0, TS_DATA_CSV, "field2", result));

	ts_delete_context(ctx);

	return 0;
}
