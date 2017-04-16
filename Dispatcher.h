
#include <cmath>       /* math_errhandling */
#include <cfenv>       /* feclearexcept, fetestexcept, FE_ALL_EXCEPT, FE_INVALID */
#include <cerrno>      /* errno, EDOM */
#include <string>
#include <complex>
#include <algorithm>

#include "json.hpp"


using namespace std;
using json = nlohmann::json;

#pragma STDC FENV_ACCESS on

namespace ns{

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
		UNDERFLOW_ERROR,
		OVERFLOW_ERROR,
		UNEXPECTED_ERROR
	}STATUS;

	typedef enum TYPE_DATA{
		INTEGER,
		DOUBLE
		//COMPLEX
	}TYPE_DATA;

	typedef struct REQUEST_DATA{

		json id;
		int nparams;
		json params;
		json result;
		STATUS status;	
		string method;
		//bool notification;
		vector<TYPE_DATA> types;

	}REQUEST_DATA;

}

using namespace ns;

class Dispatcher{

	private:

		typedef int (Dispatcher::*method_int)(int, int);
		typedef double (Dispatcher::*method_double)(double, double);
		typedef complex<double> (Dispatcher::*method_complex)(complex<double>);

		typedef map<string, method_int> map_func_int;
		typedef map<string, method_double> map_func_double;
		typedef map<string, method_complex> map_func_complex;

		//Quizás sea un atributo innecesario.
		//REQUEST_DATA data;
		map_func_int mapInt;
		map_func_double mapDbl;
		map_func_complex mapCplx;

		int _Dispatch(string mt, int a, int b);
		double _Dispatch(string mt, double a, double b);
		complex<double> _Dispatch(string mt, complex<double> cplx);

		int sum(int a, int b);
		double sum(double a, double b);
		
		int subtract(int a, int b);
		double subtract(double a, double b);

		int multiply(int a, int b);
		double multiply(double a, double b);

		int division(int a, int b);
		double division(double a, double b);

		double pow(double a, double b);

		double sqrt(double a, double useless);

		
		double cos(double alpha, double useless);
		double sin(double alpha, double useless);
		double tan(double alpha, double useless);
		double atan2(double beta, double alpha);
		double acos(double alpha, double useless);
		double asin(double alpha, double useless);
		double atan(double alpha, double useless);

		double cosh(double alpha, double useless);
		double sinh(double alpha, double useless);
		double tanh(double alpha, double useless);

		complex<double> ccos(complex<double> cplx);
		complex<double> csin(complex<double> cplx);
		complex<double> ctan(complex<double> cplx);


	public:
		Dispatcher();
		json Dispatch(REQUEST_DATA req);

};
