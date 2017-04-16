
#include <iostream>
#include <cmath>
#include <complex>

#include <curl/curl.h>
#include "ClientStub.cpp"

using namespace std;

ClientStub *client;

bool testSUM(int a, int b){

	int reslt= client->sum(a, b);

	if(client->isError()){
		cout << "Error" << endl;
		return false;
	}

	if(reslt != (a + b))
		cout << reslt << " " << a + b << " ";
		
	return reslt == (a + b);

}

bool testSUM(double a, double b){

	double reslt= client->sum(a, b);

	if(client->isError()){
		cout << "Error" << endl;
		return false;
	}
	
	if(reslt != (a + b))
		cout << reslt << " " << a + b << " ";

	return reslt == (a + b);

}

/*
bool testSUBTRACT(int a, int b){

	int reslt= client->subtract(a, b);

	if(client->isError()){
		cout << "Error" << endl;
		return false;
	}

	if(reslt != (a - b))
		cout << reslt << " " << a - b << " ";
		
	return reslt == (a - b);

}

bool testSUBTRACT(double a, double b){

	double reslt= client->subtract(a, b);

	if(client->isError()){
		cout << "Error" << endl;
		return false;
	}

	if(reslt != (a - b))
		cout << reslt << " " << a - b << " ";
		
	return reslt == (a - b);

}

bool testMULTIPLY(int a, int b){

	int reslt= client->multiply(a, b);

	if(client->isError()){
		cout << "Error" << endl;
		return false;
	}

	if(reslt != (a * b))
		cout << reslt << " " << a * b << " ";
		
	return reslt == (a * b);

}

bool testMULTIPLY(double a, double b){

	double reslt= client->multiply(a, b);

	if(client->isError()){
		cout << "Error" << endl;
		return false;
	}

	if(reslt != (a * b))
		cout << reslt << " " << a * b << " ";
		
	return reslt == (a * b);

}

bool testDIVISION(int a, int b){

	int reslt= client->division(a, b);

	if(client->isError()){
		cout << "Error" << endl;
		return false;
	}

	if(reslt != (a / b))
		cout << reslt << " " << a / b << " ";
		
	return reslt == (a / b);

}

bool testDIVISION(double a, double b){

	double reslt= client->division(a, b);

	if(client->isError()){
		cout << "Error" << endl;
		return false;
	}

	if(reslt != (a / b))
		cout << reslt << " " << a / b << " ";
		
	return reslt == (a / b);

}

bool testPOW(double a, double b){

	double reslt= client->pow(a, b);

	if(client->isError()){
		cout << "Error" << endl;
		return false;
	}

	if(reslt != std::pow(a, b))
		cout << reslt << " " << std::pow(a, b) << " ";
		
	return reslt == std::pow(a, b);

}

bool testSQRT(double a){

	double reslt= client->sqrt(a);

	if(client->isError()){
		cout << "Error" << endl;
		return false;
	}

	if(reslt != std::sqrt(a))
		cout << reslt << " " << std::sqrt(a) << " ";
		
	return reslt == std::sqrt(a);

}

bool testCOS(double a){

	double reslt= client->cos(a);

	if(client->isError()){
		cout << "Error" << endl;
		return false;
	}
		
	if(reslt != std::cos(a))
		cout << reslt << " " << std::cos(a) << " ";

	return reslt == std::cos(a);

}

bool testSIN(double a){

	double reslt= client->sin(a);

	if(client->isError()){
		cout << "Error" << endl;
		return false;
	}
	
	if(reslt != std::sin(a))
		cout << reslt << " " << std::sin(a) << " ";

	return reslt == std::sin(a);

}

bool testTAN(double a){

	double reslt= client->tan(a);

	if(client->isError()){
		cout << "Error" << endl;
		return false;
	}

	if(reslt != std::tan(a))
		cout << reslt << " " << std::tan(a) << " ";
		
	return reslt == std::tan(a);

}

bool testATAN2(double b, double a){

	double reslt= client->atan2(b, a);

	if(client->isError()){
		cout << "Error" << endl;
		return false;
	}
		
	if(reslt != std::atan2(b, a))
		cout << reslt << " " << std::atan2(b, a) << " ";
		
	return reslt == std::atan2(b, a);

}

bool testACOS(double a){

	double reslt= client->acos(a);

	if(client->isError()){
		cout << "Error" << endl;
		return false;
	}
		
	if(reslt != std::acos(a))
		cout << reslt << " " << std::acos(a) << " ";

	return reslt == std::acos(a);

}

bool testASIN(double a){

	double reslt= client->asin(a);

	if(client->isError()){
		cout << "Error" << endl;
		return false;
	}

	if(reslt != std::asin(a))
		cout << reslt << " " << std::asin(a) << " ";
		
	return reslt == std::asin(a);

}

bool testATAN(double a){

	double reslt= client->atan(a);

	if(client->isError()){
		cout << "Error" << endl;
		return false;
	}

	if(reslt != std::atan(a))
		cout << reslt << " " << std::atan(a) << " ";
		
	return reslt == std::atan(a);

}

bool testCOSH(double a){

	double reslt= client->cosh(a);

	if(client->isError()){
		cout << "Error" << endl;
		return false;
	}

	if(reslt != std::cosh(a))
		cout << reslt << " " << std::cosh(a) << " ";
		
	return reslt == std::cosh(a);

}

bool testSINH(double a){

	double reslt= client->sinh(a);

	if(client->isError()){
		cout << "Error" << endl;
		return false;
	}

	if(reslt != std::sinh(a))
		cout << reslt << " " << std::sinh(a) << " ";
		
	return reslt == std::sinh(a);

}

bool testTANH(double a){

	double reslt= client->tanh(a);

	if(client->isError()){
		cout << "Error" << endl;
		return false;
	}

	if(reslt != std::tanh(a))
		cout << reslt << " " << std::tanh(a) << " ";
		
	return reslt == std::tanh(a);

}

bool testCCOS(double a, double b){

	complex<double> cplx= complex<double>(a, b);
	complex<double> mcplx= client->ccos(cplx);

	if(client->isError()){
		cout << "Error" << endl;
		return false;
	}

	if(mcplx != std::cos(cplx))
		cout << mcplx << " " << std::cos(cplx) << " ";
		
	return mcplx == std::cos(cplx);

}

bool testCSIN(double a, double b){

	complex<double> cplx= complex<double>(a, b);
	complex<double> mcplx= client->csin(cplx);

	if(client->isError()){
		cout << "Error" << endl;
		return false;
	}
	if(mcplx != std::sin(cplx))
		cout << mcplx << " " << std::sin(cplx) << " ";
		
	return mcplx == std::sin(cplx);

}

bool testCTAN(double a, double b){

	complex<double> cplx= complex<double>(a, b);
	complex<double> mcplx= client->ctan(cplx);

	if(client->isError()){
		cout << "Error" << endl;
		return false;
	}
		
	if(mcplx != std::tan(cplx))
		cout << mcplx << " " << std::tan(cplx) << " ";
		
	return mcplx == std::tan(cplx);

}
*/

int main(){

	double result;
	client= new ClientStub("localhost", 8888);
	
	std::cout << std::boolalpha;

	try{
	
		client->beginBatch();
		cout << "*************************************************************************" << endl;
		cout << "testSUM: " << testSUM(1.1, 5.0) << endl;
		cout << "*************************************************************************" << endl;
		cout << "*************************************************************************" << endl;
		cout << "testSUM: " << testSUM(1.1, 3.0) << endl;
		cout << "*************************************************************************" << endl;
		client->endBatch();
		cout << client->getBatch(0, &result) << endl;
		cout << "result: "  << result << endl;
		cout << client->getBatch(1, &result) << endl;
		cout << "result: "  << result << endl;
		cout << "testSUM: " << testSUM(1, 3) << endl;
		//cout << "*************************************************************************" << endl;
		//cout << "testDIVISION: " << testDIVISION(2, 0) << endl;
		//cout << "*************************************************************************" << endl;
	}catch(const char* msg){
		cout << msg << endl;
	}

	return 0;

}
