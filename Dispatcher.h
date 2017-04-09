
#include <map>
#include <cmath>
#include <string>
#include <complex>
#include <fstream>
#include <iostream>
#include <exception>
#include <cerrno>
#include <cfenv>  

#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class Dispatcher;

typedef int (Dispatcher::*method_int)(int, int);
typedef double (Dispatcher::*method_double)(double, double);
typedef complex<double> (Dispatcher::*method_complex)(complex<double>);

typedef map<string, method_int> map_func_int;
typedef map<string, method_double> map_func_double;
typedef map<string, method_complex> map_func_complex;

class Dispatcher{

	private:
		json method;
		json errors;
		map_func_int mapInt;
		map_func_double mapDbl;
		map_func_complex mapCplx;


		int validate(string str);
		string _dispatch(int cs, const char *str);

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
		int dispatch(string mt, int a, int b);
		double dispatch(string mt, double a, double b);
		complex<double> dispatch(string mt, complex<double> cplx);

};

//Peticiones:
//Validar que los métodos no empiecen con "rpc."
//El "id" puede ser un cadena de carácteres, un número o NULL. Además puede ser omitido.
//"params" puede ser omitido.
//El parámetro "method" es obligatorio.
//El parámetro "jsonrpc" siempe debe ser "2.0". (NO NÚMERICO)
//El resto de los valores no puede ser omitido.
//Una notificación es una solicitud sin "id".
//Las notificaciones no son respondidas.

//Respuestas:
//El parámetro "jsonrpc" siempe debe ser "2.0". (NO NÚMERICO)
//El campo "result" es requerido cuando la ejecución fue exitosa y no debe ser incluido si ocurre un error.
//El campo "error" es requerido si ocurre un error, y debe ser omitido cuando se obtiene una ejecución exitosa.
//El "id" es un miembro requerido y debe ser el mismo que la petición sin embargo en caso de error debe ser NULL.
//Es recomendable incluir al menos uno de los dos campos ("result" o "error"), mas no ambos en una misma respuesta.

//Errores:
//code
//   A Number that indicates the error type that occurred.
//    This MUST be an integer.
//message
//    A String providing a short description of the error.
//    The message SHOULD be limited to a concise single sentence.
//data
//    A Primitive or Structured value that contains additional information about the error.
//    This may be omitted.
//    The value of this member is defined by the Server (e.g. detailed error information, nested errors etc.). 