
#include "Dispatcher.h"

Dispatcher::Dispatcher(){

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

	/*
	ifstream ifs;

	ifs.open(pathMethods, ifstream::in);

	if(!ifs.is_open()){

		cout << "Error opening file." << endl;
		return;

	}

	ifs >> method;
	//std::cout << method.dump(4) << std::endl;
	ifs.close();

	ifs.open(pathErrors, ifstream::in);

	if(!ifs.is_open()){

		cout << "Error opening file." << endl;
		return;

	}

	ifs >> errors;
//	std::cout << errors.dump(4) << std::endl;
	ifs.close();

	std::cout << std::boolalpha;
	*/
/*
	std::cout << std::boolalpha;
	cout << "size(list): " << method[0]["list"].size() << endl;
	cout << "size(names) " << method[0]["names"].size() << endl;
	cout << "¿Existe (params)? " << (method[0].find("params") != method[0].end()) << endl;
	cout << "size(params): " << method[0]["params"].size() << endl;
	cout << "¿Ahora existe (params)? " << (method[0].find("params") != method[0].end()) << endl;
	cout << "substr: " << errors[0]["message"].get<std::string>() << endl;
	cout << "¿Es number? " << method[0]["prueba"].is_number() << endl;
	cout << "¿Es float? " << method[0]["prueba"].is_number_float() << endl;
	cout << "¿Es integer? " << method[0]["prueba"].is_number_integer() << endl;
	cout << "¿Es unsigned integer? " << method[0]["prueba"].is_number_unsigned() << endl;

	std::cout << errors[1].dump(4) << std::endl;

	for (json::iterator it = method.begin(); it != method.end(); ++it) {
		string m= method[0]["method"].get<std::string>();
		cout << method[0]["method"].get<std::string>() << endl;
  		std::cout << (it->find(m) != it->end()) << "\n";
	}

	for (json::iterator it = method[0]["names"].begin(); it != method[0]["names"].end(); ++it) {
  		std::cout << it.key() << " " << it.value() << (it.value() == "int" ? "Es un entero":"No es un entero.") << "\n";
	}

	//std::cout << (method.find("sum") == method.end()) << std::endl;	

	cout << "size(method): " << method.size() << endl;     // nº entries
	cout << "empty(): " << method.empty() << endl;    // false
	cout << "type(method): " << (method.type() == json::value_t::array) << endl;     // json::value_t::array
	//cout << "clear(): " << method.clear() << endl;    // the array is empty again

	// convenience type checkers
	cout << "is_null(): " << method.is_null() << endl;
	cout << "is_boolean(): " << method.is_boolean() << endl;
	cout << "is_number(): " << method.is_number() << endl;
	cout << "is_object(): " << method.is_object() << endl;
	cout << "is_array(): " << method.is_array() << endl;
	cout << "is_string(): " << method.is_string() << endl;

*/

	//cout << "VALIDANDO" << endl;
	int reslt;
/*	
	reslt= validate("\"id\":0,\"jsonrpc\":\"2.0\",\"method\":\"sum\",\"params\":[1.0,2.0]}");
	cout << "Debería: PARSE ERROR " << reslt << endl;

	reslt= validate("{\"id\":0,\"jsonrpc\":\"2.0\",\"method\":\"sum\",\"params\":[1.0,2.0]}");
	cout << "Debería: OK " << reslt << endl;

	reslt= validate("{\"jsonrpc\":\"2.0\",\"method\":\"sum\",\"params\":[1.0,2.0]}");
	cout << "Debería: OK (NOTIFICACIÓN) " << reslt << endl;

	reslt= validate("{\"id\":0,\"jsonrpc\":\"2.0\",\"method\":\"sums\",\"params\":[1.0,2.0]}");
	cout << "Debería: METHOD NOT FOUND " << reslt << endl;

	reslt= validate("{\"id\":0,\"jsonrpc\":\"2.0\",\"method\":\"sum\",\"params\":[1,2.0]}");
	cout << "Debería: INVALID PARAMS " << reslt << endl;

	reslt= validate("{\"id\": null,\"jsonrpc\":\"2.0\",\"method\":\"sum\",\"params\":[1.0,2.0]}");
	cout << "Debería: OK (ID= NULL) " << reslt << endl;

	reslt= validate("{\"id\":0,\"jsonrpc\": 2.0,\"method\":\"sum\",\"params\":[1.0,2.0]}");
	cout << "Debería: INVALID JSON " << reslt << endl;

	reslt= validate("{\"id\":0,\"jsonrpc\":\"2.0\",\"method\":\"sum\"}");
	cout << "Debería: INVALID PARAMS " << reslt << endl;

	reslt= validate("{\"id\": \"A\",\"jsonrpc\":\"2.0\",\"method\":\"sum\",\"params\":[1.0,2.0]}");
	cout << "Debería: OK (ID=\"A\") " << reslt << endl;

	reslt= validate("{\"id\":0,\"jsonrpc\":\"2.0\",\"method\":\"RPC.sum\",\"params\":[1.0,2.0]}");
	cout << "Debería: METHOD NOT FOUND " << reslt << endl;


	reslt= validate("{\"id\": 0,\"jsonrpc\": \"2.0\",\"method\":\"sum\",\"params\": { \"a\": 1.0, \"b\": 2.0} }");
	cout << "Debería: OK " << reslt << endl;

	reslt= validate("{\"id\": 0,\"jsonrpc\": \"2.0\",\"method\":\"sum\",\"params\": { \"b\": 1.0, \"a\": 2.0} }");
	cout << "Debería: OK " << reslt << endl;

	*/
/*
	string aux= string(dispatch("{\"id\": 0,\"jsonrpc\":\"2.0\",\"method\":\"RPC.sum\",\"params\":[1,2]}"));
	cout << "RETORNO: " << aux << endl;

	cout << dispatch("{\"id\": 0,\"jsonrpc\": \"2.0\",\"method\":\"sum\",\"params\":[1.0,2.0]}") << endl;

	cout << dispatch("{\"id\": null,\"jsonrpc\": \"2.0\",\"method\":\"sum\",\"params\":[1.0,2.0]}") << endl;

	cout << dispatch("{\"id\": \"A\",\"jsonrpc\": \"2.0\",\"method\":\"sum\",\"params\":[1.0,2.0]}") << endl;

	cout << dispatch("{\"id\": 0,\"jsonrpc\": \"2.0\",\"method\":\"sum\",\"params\": { \"a\": 1, \"b\": 2} }") << endl;

	cout << dispatch("{\"id\": 0,\"jsonrpc\": \"2.0\",\"method\":\"sum\",\"params\": { \"b\": 1.0, \"a\": 2.0} }") << endl;

	cout << dispatch("{\"id\": null,\"jsonrpc\": \"2.0\",\"method\":\"subtract\",\"params\":[2,1]}") << endl;

	cout << dispatch("{\"id\": \"A\",\"jsonrpc\": \"2.0\",\"method\":\"subtract\",\"params\":[1.0,2.0]}") << endl;

	cout << dispatch("{\"id\": 0,\"jsonrpc\": \"2.0\",\"method\":\"subtract\",\"params\": { \"a\": 1, \"b\": 2} }") << endl;

	cout << dispatch("{\"id\": 0,\"jsonrpc\": \"2.0\",\"method\":\"subtract\",\"params\": { \"b\": 2.0, \"a\": 1.0} }") << endl;
*/
	//cout << dispatch("[{\"jsonrpc\": \"2.0\",\"method\":\"subtract\",\"params\": { \"b\": 2.0, \"a\": 1.0} }]") << endl;

	string prueba;
	//string prueba= "[{\"jsonrpc\": \"2.0\", \"method\": \"sum\", \"params\": [1,2], \"id\": \"1\"}, {\"jsonrpc\": \"2.0\", \"method\": \"sum\", \"params\": [7, 5]}, {\"jsonrpc\": \"2.0\", \"method\": \"subtract\", \"params\": [42,23], \"id\": \"2\"}, {\"foo\": \"boo\"}, {\"jsonrpc\": \"2.0\", \"method\": \"foo.get\", \"params\": {\"name\": \"myself\"}, \"id\": \"5\"}, {\"jsonrpc\": \"2.0\", \"method\": \"subtract\", \"params\": [42,23], \"id\": \"9\"}]";
	//cout << dispatch(prueba.data()) << endl;

	//cout << dispatch("[{\"id\": 0,\"jsonrpc\": \"2.0\",\"method\":\"subtract\",\"params\": { \"b\": 99999999999999999999999999900000000.1, \"a\": 89999999999999999999999999900000000.01} }]") << endl;
	//json j_object = {{"one", 1}, {"two", 2}};
	//cout << "size(): " << j_object.size() << endl;     // nº entries
	//cout << "is_array(): " << j_object.is_array() << endl;


	/*
	// create JSON values
    json j_null;
    json j_boolean = true;
    json j_number_integer = 17;
    json j_number_unsigned_integer = 12345678987654321u;
    json j_number_float = 23.42;
    json j_object = {{"one", 1}, {"two", 2}};
    json j_array = {1, 2, 4, 8, 16};
    json j_string = "Hello, world";

    // call is_null()
    std::cout << std::boolalpha;
    std::cout << j_null.is_null() << '\n';
    std::cout << j_boolean.is_null() << '\n';
    std::cout << j_number_integer.is_null() << '\n';
    std::cout << j_number_unsigned_integer.is_null() << '\n';
    std::cout << j_number_float.is_null() << '\n';
    std::cout << j_object.is_null() << '\n';
    std::cout << j_array.is_null() << '\n';
	std::cout << j_string.is_null() << '\n';
	*/

}

int Dispatcher::dispatch(string mt, int a, int b){
	return (this->*(mapInt[mt]))(a, b);
}

double Dispatcher::dispatch(string mt, double a, double b){
	return (this->*(mapDbl[mt]))(a, b);
}

complex<double> Dispatcher::dispatch(string mt, complex<double> cplx){
	return (this->*(mapCplx[mt]))(cplx);
}

int Dispatcher::validate(string str){

	json in;

	try{
		in= json::parse(str);
	}catch(...){
		return 0;
	}

	if(!in.is_object())
		return 0;
	
	if(in.find("jsonrpc") == in.end() || in.find("method") == in.end())
		return 1;

	if(!in["jsonrpc"].is_string() || (in["jsonrpc"].is_string() && in["jsonrpc"] != "2.0"))
		return 1;

	if(!in["method"].is_string())
		return 1;

	string aux= in["method"];

	for(int i= 0; i<aux.size(); ++i)
		aux[i]= tolower(aux[i]);

	//cout << aux << endl;
	//cout << aux.substr(0, 4) << endl;
	if(aux.size() >= 4 && aux.substr(0, 4) == "rpc.")
		return 2;

	bool e= false, p= false;
	for(json::iterator it= method.begin(); it != method.end(); ++it){

		//cout << *it << endl;

		if((*it)["method"] == in["method"]){

			//cout << "Encontro el metodo " << in["method"] << endl;
			e= true;

			if((*it).find("list") == it->end() && in.find("params") == in.end()){

				//cout << "Es un metodo sin parametros" << endl;

				p= true;
				break;

			}else if((*it).find("list") != it->end() && in.find("params") != in.end() &&
				in["params"].is_array() && in["params"].size() == (*it)["list"].size()){

				
				bool pl= true;
				json::iterator pmList= (*it)["list"].begin();

				for(json::iterator pm= in["params"].begin(); pl && pm != in["params"].end(); ++pm, ++pmList){

					//cout << *pmList << " " << *pm << endl;
					if(*pmList == "int" && !(*pm).is_number_integer()){

						pl= false;
						break;

					}

					if(*pmList == "double" && !(*pm).is_number_float()){

						pl= false;
						break;

					}

				}

				p= pl;

				if(pl){
				//	cout << "Los parametros coinciden [ORDEN]." << endl;
					break;
				}//else
				//	cout << "Los parametros no coinciden [ORDEN]" << endl;
	

			}else if((*it).find("names") != it->end() && in.find("params") != in.end() &&
				in["params"].is_object() && in["params"].size() == (*it)["names"].size()){

				//cout << "Hay otra posibilidad en \"names\"." << endl;

				bool pl= true;
				json::iterator pmNames;

				for(json::iterator pm= (*it)["names"].begin(); pl && pm != (*it)["names"].end(); ++pm){

					pmNames= in["params"].find(pm.key());

					if(pmNames == in["params"].end()){
						pl= false;
						break;
					}

					if(pm.value() == "int" && !pmNames.value().is_number_integer()){
						pl= false;
						break;
					}

					if(pm.value() == "double" && !pmNames.value().is_number_float()){
						pl= false;
						break;
					}

				}

				p= pl;

				if(pl){
				//	cout << "Los parametros coinciden [NOMBRE]." << endl;
					break;
				}//else
					//cout << "Los parametros no coinciden [NOMBRE]" << endl;

			}

		}


	}

	//cout << "Encontrado: " << e << " Parametos: " << p << endl;

	if(!e)
		return 2;

	if(!p)
		return 3;


	if(in.find("id") == in.end()){

		return -1;

	}else if(!in["id"].is_string() && !in["id"].is_number() && !in["id"].is_null()){

		return 1;

	}

	return -2;
	
}

string Dispatcher::_dispatch(int cs, const char *str){

	string nid= "null";
	json in= json::parse(str);

	//cout << "CASO: " << in << endl;

	if(cs == 0)
		return "{\"jsonrpc\": \"2.0\", \"error\": {\"code\": -32700, \"message\": \"Parse error\"}, \"id\": null}";

	if(cs == 1)
		return "{\"jsonrpc\": \"2.0\", \"error\": {\"code\": -32600, \"message\": \"Invalid Request\"}, \"id\": null}";

	//cout << "Aqui: " << in["id"] << endl;

	if(in.find("id") != in.end()){
		if(in["id"].is_string()){
			nid= "\"" + in["id"].get<std::string>() + "\"";
		//	cout << "Entro string" << endl;
		}
		else if(in["id"].is_number() && in["id"].is_number_integer()){
			nid= to_string(in["id"].get<int>());
		//	cout << "Entro int" << endl;
		}
		else if(in["id"].is_number() && in["id"].is_number_float()){
			nid= to_string(in["id"].get<float>());
		//	cout << "Entro float" << endl;
		}

	}

	if(cs == 2){

		//	cout << "Entro: " << in["id"] << endl;
		//	nid= to_string(in["id"]);

		nid= "{\"jsonrpc\": \"2.0\", \"error\": {\"code\": -32601, \"message\": \"Method not found\"}, \"id\": " + nid +  "}";

		return nid;
	}
	
	if(cs == 3){

		nid= "{\"jsonrpc\": \"2.0\", \"error\": {\"code\": -32602, \"message\": \"Invalid params\"}, \"id\": " + nid +  "}";
		return nid;
	}

	if(cs == 4){
		nid= "{\"jsonrpc\": \"2.0\", \"error\": {\"code\": -32603, \"message\": \"Internal error\"}, \"id\": " + nid +  "}";
		return nid;
	}

	int i= 0;
	string tp;
	int pmInt[3];
	double pmDouble[3];
	string mt= in["method"];
	int sz= in["params"].size(); //INNECESARIO

	//CORREGIR, ¿QUÉ PASA SI EL MÉTODO NO TIENE PARÁMETROS?
	if(in["params"].is_array()){

		//cout << "Parametros [ORDEN]" << endl;

		for(json::iterator it= in["params"].begin(); it != in["params"].end(); ++it, ++i){

			if((*it).is_number_integer()){
			//	cout << "int" << endl;
				tp= "int";
				pmInt[i]= it.value();
			//	cout << "Real: " << it.value() << endl;
			//	cout << "Recibido: " << pmInt[i] << endl;
			}else{
			//	cout << "double" << endl;
				tp= "double";
				pmDouble[i]= it.value();
			//	cout << "Real: " << it.value() << endl;
			//	cout << "Recibido: " << pmDouble[i] << endl;
			}

		}

		//cout << "SALIO" << endl;

	}else{

		//cout << "Parametros [NOMBRE]" << endl;

		json::iterator it= in["params"].find("a");
		if(it != in["params"].end() && (*it).is_number_integer()){
			tp= "int";
			pmInt[0]= it.value();
		//	cout << "Real: " << it.value() << endl;
		//	cout << "Recibido: " << pmInt[0] << endl;
		}else if(it != in["params"].end() && (*it).is_number_float()){
			tp= "double";
			pmDouble[0]= it.value();
		//	cout << "Real: " << it.value() << endl;
		//	cout << "Recibido: " << pmDouble[0] << endl;
		}

		it= in["params"].find("b");
		if(it != in["params"].end() && (*it).is_number_integer()){
			tp= "int";
			pmInt[1]= it.value();
		//	cout << "Real: " << it.value() << endl;
		//	cout << "Recibido: " << pmInt[1] << endl;
		}else if(it != in["params"].end() && (*it).is_number_float()){
			tp= "double";
			pmDouble[1]= it.value();
		//	cout << "Real: " << it.value() << endl;
		//	cout << "Recibido: " << pmDouble[1] << endl;
		}

	}


	//cout << "PASO" << endl;
	//cout << mt << endl;
	/*
	if(mt == "sum"){

		if(tp == "int"){
			pmInt[2]= sum(pmInt[0], pmInt[1]);
			nid= "{\"jsonrpc\": \"2.0\", \"result\": " + to_string(pmInt[2]) + ", \"id\": " + nid +  "}";
		}else{
		//	cout << "PASO2" << endl;
			pmDouble[2]= sum(pmDouble[0], pmDouble[1]);
		//	cout << "PASO3 " << pmDouble[2] << endl;
			nid= "{\"jsonrpc\": \"2.0\", \"result\": " + to_string(pmDouble[2]) + ", \"id\": " + nid +  "}";
		//	cout << "PASO4" << endl;
		}

	}else if(mt == "subtract"){

		if(tp == "int"){
			pmInt[2]= subtract(pmInt[0], pmInt[1]);
			nid= "{\"jsonrpc\": \"2.0\", \"result\": " + to_string(pmInt[2]) + ", \"id\": " + nid +  "}";
		}else{
			pmDouble[2]= subtract(pmDouble[0], pmDouble[1]);
			nid= "{\"jsonrpc\": \"2.0\", \"result\": " + to_string(pmDouble[2]) + ", \"id\": " + nid +  "}";
		}

	}else if(mt == "multiply"){
		
		if(tp == "int"){
			pmInt[2]= multiply(pmInt[0], pmInt[1]);
			nid= "{\"jsonrpc\": \"2.0\", \"result\": " + to_string(pmInt[2]) + ", \"id\": " + nid +  "}";
		}else{
			pmDouble[2]= multiply(pmDouble[0], pmDouble[1]);
			nid= "{\"jsonrpc\": \"2.0\", \"result\": " + to_string(pmDouble[2]) + ", \"id\": " + nid +  "}";
		}

	}else if(mt == "division"){

		if(tp == "int"){
			pmInt[2]= division(pmInt[0], pmInt[1]);
			nid= "{\"jsonrpc\": \"2.0\", \"result\": " + to_string(pmInt[2]) + ", \"id\": " + nid +  "}";
		}else{
			pmDouble[2]= division(pmDouble[0], pmDouble[1]);
			//cout << "LLEGO" << endl;
			nid= "{\"jsonrpc\": \"2.0\", \"result\": " + to_string(pmDouble[2]) + ", \"id\": " + nid +  "}";
		}

	}else if(mt == "pow"){

		pmDouble[2]= Dispatcher::pow(pmDouble[0], pmDouble[1]);
		nid= "{\"jsonrpc\": \"2.0\", \"result\": " + to_string(pmDouble[2]) + ", \"id\": " + nid +  "}";

	}else if(mt == "sqrt"){

		//cout << "LLEGO" << endl;
		pmDouble[2]= Dispatcher::sqrt(pmDouble[0]);
		//cout << "LISTO" << endl;
		nid= "{\"jsonrpc\": \"2.0\", \"result\": " + to_string(pmDouble[2]) + ", \"id\": " + nid +  "}";

	}else if(mt == "cos"){

		pmDouble[2]= Dispatcher::cos(pmDouble[0]);
		nid= "{\"jsonrpc\": \"2.0\", \"result\": " + to_string(pmDouble[2]) + ", \"id\": " + nid +  "}";

	}else if(mt == "sin"){

		pmDouble[2]= Dispatcher::sin(pmDouble[0]);
		nid= "{\"jsonrpc\": \"2.0\", \"result\": " + to_string(pmDouble[2]) + ", \"id\": " + nid +  "}";

	}else if(mt == "tan"){

		pmDouble[2]= Dispatcher::tan(pmDouble[0]);
		nid= "{\"jsonrpc\": \"2.0\", \"result\": " + to_string(pmDouble[2]) + ", \"id\": " + nid +  "}";

	}else if(mt == "atan2"){

		pmDouble[2]= Dispatcher::atan2(pmDouble[0], pmDouble[1]);
		nid= "{\"jsonrpc\": \"2.0\", \"result\": " + to_string(pmDouble[2]) + ", \"id\": " + nid +  "}";

	}else if(mt == "acos"){

		pmDouble[2]= Dispatcher::acos(pmDouble[0]);
		nid= "{\"jsonrpc\": \"2.0\", \"result\": " + to_string(pmDouble[2]) + ", \"id\": " + nid +  "}";

	}else if(mt == "asin"){

		pmDouble[2]= Dispatcher::asin(pmDouble[0]);
		nid= "{\"jsonrpc\": \"2.0\", \"result\": " + to_string(pmDouble[2]) + ", \"id\": " + nid +  "}";

	}else if(mt == "atan"){

		pmDouble[2]= Dispatcher::atan(pmDouble[0]);
		nid= "{\"jsonrpc\": \"2.0\", \"result\": " + to_string(pmDouble[2]) + ", \"id\": " + nid +  "}";

	}else if(mt == "cosh"){

		pmDouble[2]= Dispatcher::cosh(pmDouble[0]);
		nid= "{\"jsonrpc\": \"2.0\", \"result\": " + to_string(pmDouble[2]) + ", \"id\": " + nid +  "}";

	}else if(mt == "sinh"){

		pmDouble[2]= Dispatcher::sinh(pmDouble[0]);
		nid= "{\"jsonrpc\": \"2.0\", \"result\": " + to_string(pmDouble[2]) + ", \"id\": " + nid +  "}";

	}else if(mt == "tanh"){

		pmDouble[2]= Dispatcher::tanh(pmDouble[0]);
		nid= "{\"jsonrpc\": \"2.0\", \"result\": " + to_string(pmDouble[2]) + ", \"id\": " + nid +  "}";

	}else if(mt == "ccos"){

		complex<double> cplx= Dispatcher::ccos(pmDouble[0], pmDouble[1]);
		nid= "{\"jsonrpc\": \"2.0\", \"result\": [" + to_string(real(cplx)) + "," + to_string(imag(cplx)) + "], \"id\": " + nid +  "}";

	}else if(mt == "csin"){

		complex<double> cplx= Dispatcher::csin(pmDouble[0], pmDouble[1]);
		nid= "{\"jsonrpc\": \"2.0\", \"result\": [" + to_string(real(cplx)) + "," + to_string(imag(cplx)) + "], \"id\": " + nid +  "}";

	}else if(mt == "ctan"){

		complex<double> cplx= Dispatcher::ctan(pmDouble[0], pmDouble[1]);
		nid= "{\"jsonrpc\": \"2.0\", \"result\": [" + to_string(real(cplx)) + "," + to_string(imag(cplx)) + "], \"id\": " + nid +  "}";

	}
	*/

	//cout << "CASOS" << endl;

	//cout << nid << endl;
	
	if(cs == -1){
		return "";
	}
	
	if(cs == -2){
		//cout << "FINAL: " << nid << endl;
		return nid;
	}
	//cout << "NO" << endl;
	nid= "{\"jsonrpc\": \"2.0\", \"error\": {\"code\": -32603, \"message\": \"Internal error\"}, \"id\": " + nid + "}";

	return nid;

}

/*
string Dispatcher::dispatch(const char *str){

	int t;
	json bt;

	vector<string> reslt;



	try{
		bt= json::parse(str);
	}catch(...){
		return "{\"jsonrpc\": \"2.0\", \"error\": {\"code\": -32700, \"message\": \"Parse error\"}, \"id\": null}";
	}



	if(bt.is_object()){

		t= validate(str);

		string aux= _dispatch(t, str);

		return aux;
		
	}else{

		string aux;
		for(int i= 0; i<bt.size(); ++i){

			
			aux= bt[i].dump();
			
			t= validate(aux);
			aux= _dispatch(t, aux.data());

			if(aux.size())
				reslt.push_back(aux);

		}

		bt= json(reslt);

		return (bt.size() ? bt.dump():"");

	}

	return "{\"jsonrpc\": \"2.0\", \"error\": {\"code\": -32603, \"message\": \"Internal error\"}, \"id\": null}";

}
*/

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
	if(b == 0.0)
		throw std::overflow_error("Divide by zero exception");
	return a / b;
}

double Dispatcher::pow(double a, double b){

	/*

	if(a < 0 && isfinite(a) && isfinite(b))
		throw std::domain_error("Domain error exception");

	if(a == 0.0 && b < 0)
		throw std::domain_error("Domain error exception");		
	*/
	return std::pow(a, b);
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


