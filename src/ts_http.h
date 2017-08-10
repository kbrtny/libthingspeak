#ifndef  _TS_HTTP_H_
# define _TS_HTTP_

#ifdef __cplusplus
extern "C" {
#endif
	
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>


#define SA      struct sockaddr
#define MAXLINE 8192
#define MAXSUB  1024


#define LISTENQ         1024
#define HOST_API        "api.thingspeak.com"

extern int h_errno;


ssize_t ts_http_post(const ts_context_t *, const char *, const char *, const char *);
char   *ts_http_get(const char *, char *, char *);

#ifdef __cplusplus
}
#endif

#endif /*_TS_HTTP_*/
