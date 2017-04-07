
#include <string>
#include <vector>
#include <fstream>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class Processor{

	private:
		static json Errors;
		static json Methods;

	public:
		Processor();
		static int init(const char *pathMethods, const char *pathErrors);

};