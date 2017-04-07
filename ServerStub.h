
#include <string>
#include <cstring>
#include <iostream>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <microhttpd.h>

#include "Processor.cpp"

using namespace std;

#define PORT 8888
#define POSTBUFFERSIZE 65536

typedef enum CONNECTION_TYPE{
	GET= 0,
	POST
}CONNECTION_TYPE;

typedef struct MHD_DATA{
	char *data;
	size_t len;
	CONNECTION_TYPE type;
}MHD_DATA;


static void request_completed(void *cls, struct MHD_Connection *connection, void **con_cls, enum MHD_RequestTerminationCode toe);
static int answer_to_connection (void *cls, struct MHD_Connection *connection, const char *url, const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls);
int main();