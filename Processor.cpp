
#include "Processor.h"


json Processor::Errors;
json Processor::Methods;

Processor::Processor(){

	

}

int Processor::init(const char *pathMethods, const char *pathErrors){

	ifstream ifs;
	ifs.open(pathMethods, ifstream::in);

	if(!ifs.is_open()){

		cout << "Error opening file." << endl;
		return 1;

	}

	ifs >> Methods;
	ifs.close();

	ifs.open(pathErrors, ifstream::in);

	if(!ifs.is_open()){

		cout << "Error opening file." << endl;
		return 1;

	}

	ifs >> Errors;
	ifs.close();

	return 0;

}