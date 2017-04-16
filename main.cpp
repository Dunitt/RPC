
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
