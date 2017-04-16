
#include <string>
#include <iostream>

#include <curl/curl.h>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

typedef struct MemoryStruct{

	char *memory;
	size_t size;

}MemoryStruct;

typedef enum{
	INACTIVE= 0,
	ACTIVE,
	READY,
	RECEIVED
}BacthStage;

class ClientStub{

	public:

		char* url;
		CURL *curl;
		bool error;
		CURLcode res;
		json request;
		json response;
		BacthStage batch;
		unsigned int port;
		MemoryStruct chunk;
		static unsigned int id;

		bool send(const char* str, long size);

	public:
		
		ClientStub(const char* url, unsigned int port);
		~ClientStub();
		bool isReady();
		bool isError();

		void beginBatch();
		void endBatch();
		int getBatch(unsigned int idx, int *result);
		int getBatch(unsigned int idx, double *result);
		int getBatch(unsigned int idx, complex<double> *result);
		
		int sum(int a, int b, bool notification);
		double sum(double a, double b, bool notification);


};
