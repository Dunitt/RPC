
#include <cmath>
#include <complex>

#include "json.hpp"

using namespace std;
using json = nlohmann::json;


typedef enum TYPE_DATA{
	INTEGER,
	DOUBLE,
	COMPLEX
}TYPE_DATA;

typedef struct REQUEST_DATA{

	int nparams;
	json params;
	string method;
	vector<TYPE_DATA> types;

}REQUEST_DATA;

class Dispatcher{

	private:
		REQUEST_DATA data;


	public:
		Dispatcher();
		json Dispatch(json inJson);

};
