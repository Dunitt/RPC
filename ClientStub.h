
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

		int subtract(int a, int b, bool notification);
		double subtract(double a, double b, bool notification);

		int multiply(int a, int b, bool notification);
		double multiply(double a, double b, bool notification);

		int division(int a, int b, bool notification);
		double division(double a, double b, bool notification);

		double pow(double a, double b, bool notification);

		double sqrt(double a, bool notification);

		
		double cos(double alpha, bool notification);
		double sin(double alpha, bool notification);
		double tan(double alpha, bool notification);
		double atan2(double beta, double alpha, bool notification);
		double acos(double alpha, bool notification);
		double asin(double alpha, bool notification);
		double atan(double alpha, bool notification);

		double cosh(double alpha, bool notification);
		double sinh(double alpha, bool notification);
		double tanh(double alpha, bool notification);

		complex<double> ccos(complex<double> cplx, bool notification);
		complex<double> csin(complex<double> cplx, bool notification);
		complex<double> ctan(complex<double> cplx, bool notification);

};
