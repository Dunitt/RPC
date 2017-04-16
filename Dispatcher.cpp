
#include "Dispatcher.h"


Dispatcher::Dispatcher(){

	//data.method= "";
	//data.nparams= 0;
	//data.types.clear();
	//data.params= json::array();

	mapInt["sum"]= &Dispatcher::sum;
	mapInt["subtract"]= &Dispatcher::subtract;
	mapInt["multiply"]= &Dispatcher::multiply;
	mapInt["division"]= &Dispatcher::division;

	mapDbl["sum"]= &Dispatcher::sum;
	mapDbl["subtract"]= &Dispatcher::subtract;
	mapDbl["multiply"]= &Dispatcher::multiply;
	mapDbl["division"]= &Dispatcher::division;

	mapDbl["pow"]= &Dispatcher::pow;
	mapDbl["sqrt"]= &Dispatcher::sqrt;

	mapDbl["cos"]= &Dispatcher::cos;
	mapDbl["sin"]= &Dispatcher::sin;
	mapDbl["tan"]= &Dispatcher::tan;
	mapDbl["atan2"]= &Dispatcher::atan2;

	mapDbl["acos"]= &Dispatcher::acos;
	mapDbl["asin"]= &Dispatcher::asin;
	mapDbl["atan"]= &Dispatcher::atan;
	
	mapDbl["cosh"]= &Dispatcher::cosh;
	mapDbl["sinh"]= &Dispatcher::sinh;
	mapDbl["tanh"]= &Dispatcher::tanh;

	mapCplx["ccos"]= &Dispatcher::ccos;
	mapCplx["csin"]= &Dispatcher::csin;
	mapCplx["ctan"]= &Dispatcher::ctan;


}

Dispatcher::~Dispatcher(){
	
}


json Dispatcher::Dispatch(REQUEST_DATA req){

	

	//try{
/*
	errno = 0;
    if(math_errhandling & MATH_ERREXCEPT)
        feclearexcept(FE_ALL_EXCEPT);
*/
	if(req.method == "ccos" || req.method == "csin" || req.method == "ctan"){

		complex<double> cplx(req.params[0], req.params[1]);
		cplx= _Dispatch(req.method, cplx);
		req.result= json::array({real(cplx), imag(cplx)});
		cout << "RESULTADO: " << cplx << endl;

	}else if(all_of(req.types.begin(), req.types.end(), [](TYPE_DATA t){return t == INTEGER;})){

		int r= _Dispatch(req.method, req.params[0].get<int>(), req.params[1].get<int>());
		req.result= r;
		cout << "RESULTADO: " << r << endl;

	}else if(all_of(req.types.begin(), req.types.end(), [](TYPE_DATA t){return t == DOUBLE;})){

		double r= _Dispatch(req.method, req.params[0].get<double>(), req.params[1].get<double>());
		req.result= r;
		cout << "RESULTADO: " << r << endl;

	}

	//}catch(...){

	//cout << "NADA" << endl;
/*
	if((math_errhandling & MATH_ERRNO) && (math_errhandling & MATH_ERREXCEPT)){

		cout << "ALGUNA EXCEPCIÓN" << endl;
		//data.

    	if(errno == EDOM && fetestexcept(FE_INVALID)){
    		printf("errno set to EDOM\n");
    		req.status= DOMAIN_ERROR;
    		//outJson["error"]= errors[6]["error"];
    	}

    	if(errno == ERANGE && fetestexcept(FE_DIVBYZERO)){
    		printf("errno set to ERANGE\n");
    		req.status= RANGE_ERROR;
    		//outJson["error"]= errors[7]["error"];
    	}

    	if(fetestexcept(FE_DIVBYZERO)){
			printf("FE_DIVBYZERO raised\n");
			req.status= DIVISION_BY_ZERO;
			//outJson["error"]= errors[5]["error"];
		}

    	if(errno == ERANGE){

    		if(fetestexcept(FE_UNDERFLOW)){
	    		printf("FE_UNDERFLOW raised\n");
	    		req.status= UNDERFLOW_ERROR;
	    		//outJson["error"]= errors[7]["error"];
	    	}

	    	if(fetestexcept(FE_OVERFLOW)){
	    		printf("FE_OVERFLOW raised\n");
	    		req.status= OVERFLOW_ERROR;
	    		//outJson["error"]= errors[7]["error"];
	    	}

    	}
*/
	
/*
	}else if(math_errhandling & MATH_ERREXCEPT){

		if(fetestexcept(FE_INVALID)){
			printf("FE_INVALID raised\n");
			req.status= DOMAIN_ERROR;
			//outJson["error"]= errors[6]["error"];
		}

		if(fetestexcept(FE_DIVBYZERO)){
			printf("FE_DIVBYZERO raised\n");
			req.status= DIVISION_BY_ZERO;
			//outJson["error"]= errors[5]["error"];
		}

		if(fetestexcept(FE_UNDERFLOW)){
    		printf("FE_UNDERFLOW raised\n");
    		req.status= UNDERFLOW_ERROR;
    		//outJson["error"]= errors[7]["error"];
    	}

    	if(fetestexcept(FE_OVERFLOW)){
    		printf("FE_OVERFLOW raised\n");
    		req.status= OVERFLOW_ERROR;
    		//outJson["error"]= errors[7]["error"];
    	}

  	}
*/
	//}

	//json outJson= req;

	//return outJson;
	return json(req);

}

int Dispatcher::_Dispatch(string mt, int a, int b){
	return (this->*(mapInt[mt]))(a, b);
}

double Dispatcher::_Dispatch(string mt, double a, double b){
	return (this->*(mapDbl[mt]))(a, b);
}

complex<double> Dispatcher::_Dispatch(string mt, complex<double> cplx){
	return (this->*(mapCplx[mt]))(cplx);
}

int Dispatcher::sum(int a, int b){
	return a + b;
}

double Dispatcher::sum(double a, double b){
	return a + b;
}


int Dispatcher::subtract(int a, int b){
	return a - b;
}

double Dispatcher::subtract(double a, double b){
	return a - b;
}

int Dispatcher::multiply(int a, int b){
	return a * b;
}

double Dispatcher::multiply(double a, double b){
	return a * b;
}


int Dispatcher::division(int a, int b){
	if(b == 0)
		throw std::overflow_error("Divide by zero exception");
	return a / b;
}

double Dispatcher::division(double a, double b){
	//if(b == 0.0)
	//	throw std::overflow_error("Divide by zero exception");
	return a / b;
}

double Dispatcher::pow(double a, double b){

	/*

	if(a < 0 && isfinite(a) && isfinite(b))
		throw std::domain_error("Domain error exception");

	if(a == 0.0 && b < 0)
		throw std::domain_error("Domain error exception");		
	*/

	

    double r= std::pow(a, b);
    //double r= std::sqrt(-1);

    

	return r;
}

double Dispatcher::sqrt(double a, double useless){
	return std::sqrt(a);
}



double Dispatcher::cos(double alpha, double useless){
	return std::cos(alpha);
}

double Dispatcher::sin(double alpha, double useless){
	return std::sin(alpha);
}

double Dispatcher::tan(double alpha, double useless){
	return std::tan(alpha);
}

double Dispatcher::atan2(double beta, double alpha){
	return std::atan2(beta, alpha);
}

double Dispatcher::acos(double alpha, double useless){
	return std::acos(alpha);
}

double Dispatcher::asin(double alpha, double useless){
	return std::asin(alpha);
}

double Dispatcher::atan(double alpha, double useless){
	return std::atan(alpha);
}


double Dispatcher::cosh(double alpha, double useless){
	return std::cosh(alpha);
}

double Dispatcher::sinh(double alpha, double useless){
	return std::sinh(alpha);
}

double Dispatcher::tanh(double alpha, double useless){
	return std::tanh(alpha);
}

complex<double> Dispatcher::ccos(complex<double> cplx){
	return std::cos(cplx);
}

complex<double> Dispatcher::csin(complex<double> cplx){
	return std::sin(cplx);
}

complex<double> Dispatcher::ctan(complex<double> cplx){
	return std::tan(cplx);
}
