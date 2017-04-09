

#include <cstdio>
#include <string>
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <microhttpd.h>
#include "json.hpp"

#pragma STDC FENV_ACCESS on


using namespace std;
using json = nlohmann::json;

#define PORT 8888
#define POSTBUFFERSIZE 65536
#define REQUEST_OK 2
#define NOTIFICATION_OK 1
#define PARSE_ERROR 0
#define INVALID_REQUEST -1
#define METHOD_NOT_FOUND -2
#define INVALID_PARAMS -3

typedef enum CONNECTION_TYPE{
	GET= 0,
	POST
}CONNECTION_TYPE;

typedef struct MHD_DATA{
	char *data;
	size_t len;
	CONNECTION_TYPE type;
}MHD_DATA;