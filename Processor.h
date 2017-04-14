
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>

#include "json.hpp"

using namespace std;
using json = nlohmann::json;

typedef enum STATUS{
	REQUEST_OK= -2,
	NOTIFICATION_OK= -1,
	PARSE_ERROR= 0,
	INVALID_REQUEST,
	METHOD_NOT_FOUND,
	INVALID_PARAMS,
	INTERNAL_ERROR,
	DIVISION_BY_ZERO,
	DOMAIN_ERROR,
	RANGE_ERROR,
	UNEXPECTED_ERROR
}STATUS;

typedef enum TYPE_DATA{
	INTEGER,
	DOUBLE,
	COMPLEX
}TYPE_DATA;

/*
typedef enum TYPE_ERRORS{
	PARSE_ERROR= 0,
	INVALID_REQUEST,
	METHOD_NOT_FOUND,
	INVALID_PARAMS,
	INTERNAL_ERROR,
	DIVISION_BY_ZERO,
	DOMAIN_ERROR,
	RANGE_ERROR,
	UNEXPECTED_ERROR
}TYPE_ERRORS;
*/

typedef struct REQUEST_DATA{

	int nparams;
	json params;
	string method;
	vector<TYPE_DATA> types;

}REQUEST_DATA;

class Processor{

	private:
		json inJson;
		json outJson;
		bool isBatch;
		static json Errors;
		static json Methods;
		vector<json> requests;
		vector<json> response;
		vector<REQUEST_DATA> data;
		//vector<STATUS> status_request;

		STATUS validate(string str);

	public:
		Processor(const char* inRequest);
		static int init(const char *pathMethods, const char *pathErrors);
		void Process();
		string getResponse();

};