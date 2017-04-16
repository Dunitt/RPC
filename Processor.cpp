
#include "Processor.h"


json Processor::Errors;
json Processor::Methods;


namespace ns{

    void to_json(json& j, const REQUEST_DATA& r){
       
    	//Definir esto como una conversión de REQUEST_DATA a json y viceversa.
    	cout << "**********************************************" << endl;
    	cout << "REQUEST_DATA: " << endl;
    	cout << "NOTIFICATION: " << r.notification << endl;
    	cout << "ID: " << r.id << endl;
    	cout << "#PARAMS: " << r.nparams << endl;
    	cout << "PARAMS: " << r.params << endl;
    	cout << "RESULT: " << r.result << endl;
    	cout << "STATUS: " << r.status << endl;
    	cout << "METHOD: " << r.method << endl;
    	cout << "TYPES: ";
    	for(int i= 0; i<r.types.size(); ++i)
    		cout << " " << r.types[i];
    	cout << endl;
    	cout << "**********************************************" << endl;

    	if(r.notification){
    		j= nullptr;
    		return;
    	}

    	if(r.status < PARSE_ERROR){
    		j= {{"jsonrpc", "2.0"},{"result", r.result}};
    	}else{
    		j= Processor::Errors[r.status];
    	}

		j["id"]= r.id;

		cout << "**********************************************" << endl;
		cout << "JSON: " << endl << j.dump(4) << endl;
		cout << "**********************************************" << endl;

    }

    void from_json(const json& j, REQUEST_DATA& r){

    	r.nparams= 0;
		r.status= REQUEST_OK;
		r.method= j["method"];
    	r.notification= false;

		if(j.find("id") != j.end())
			r.id= j["id"];
		else
			r.notification= true;
		

		if(j.find("params") != j.end()){

			json::const_iterator it;
			for(it= j["params"].begin(); it != j["params"].end(); ++it){
				
				r.params.push_back(it.value());

				if(it->is_number_integer())
					r.types.push_back(INTEGER);

				else if(it->is_number_float())
					r.types.push_back(DOUBLE);
			
			}

			r.nparams= j["params"].size();

		}
    }

} // namespace ns


Processor::Processor(const char *inRequest){

	if(Methods.empty() || Errors.empty())
		throw "Processor not initialized exception";

	isBatch= false;
	inJson= nullptr;
	outJson= nullptr;
	requests.clear();
	response.clear();

	try{
		inJson= json::parse(inRequest);
		cout << "CONTINUA" << endl;
	}catch(exception& e){
		cout << "EXCEPTION" << endl;
		outJson= Errors[STATUS::PARSE_ERROR];
		return;
		//throw;
	}

	if(inJson.empty()){
		outJson= Errors[STATUS::INVALID_REQUEST];
		return;
	}

	cout << "PASO" << endl;
	if(inJson.is_object()){

		isBatch= false;
		requests.push_back(inJson);

	}else{

		isBatch= true;
		for(json::iterator it= inJson.begin(); it != inJson.end(); ++it)
			requests.push_back(*it);

	}

	//for(int i= 0; i<requests.size(); ++i)
	//	cout << requests[i] << endl;

}

Processor::~Processor(){
	
}

int Processor::init(const char *pathMethods, const char *pathErrors){

	ifstream ifs;

	try{
		ifs.open(pathMethods, ifstream::in);
	}catch(exception& e){
		ifs.close();
		throw "Error opening file.";
		//throw e.what();
	}
	/*
	if(!ifs.is_open()){
		throw "Error opening file: " << pathMethods;
	}*/

	ifs >> Methods;
	ifs.close();

	try{
		ifs.open(pathErrors, ifstream::in);
	}catch(exception& e){
		ifs.close();
		throw "Error opening file.";
		//throw e.what();
	}

	/*if(!ifs.is_open()){
		throw "Error opening file: " << pathErrors;
	}*/

	ifs >> Errors;
	ifs.close();

	return 0;

}

STATUS Processor::validate(string str){

	json in= json::parse(str);

	if(!in.is_object())
		return INVALID_REQUEST;
	
	if(in.find("jsonrpc") == in.end() || in.find("method") == in.end())
		return INVALID_REQUEST;

	if(!in["jsonrpc"].is_string() || (in["jsonrpc"].is_string() && in["jsonrpc"] != "2.0"))
		return INVALID_REQUEST;

	if(!in["method"].is_string())
		return INVALID_REQUEST;

	string name= in["method"];
	for(int i= 0; i<name.size(); ++i)
		name[i]= tolower(name[i]);

	if(name.size() >= 4 && name.substr(0, 4) == "rpc.")
		return INVALID_REQUEST;

	if(in.find("params") != in.end() && !(in["params"].is_array() || in["params"].is_object()))
		return INVALID_REQUEST;

	bool e= false, p= false;
	for(json::iterator it= Methods.begin(); it != Methods.end(); ++it){

		if((*it)["method"] == in["method"]){

			e= true;
			if(it->find("list") == it->end() && in.find("params") == in.end()){
				p= true;
				break;

			}else if(it->find("list") != it->end() && in.find("params") != in.end() &&
				in["params"].is_array() && in["params"].size() == (*it)["list"].size()){

				bool pl= true;
				json::iterator pmList= (*it)["list"].begin();
				for(json::iterator pm= in["params"].begin(); pm != in["params"].end(); ++pm, ++pmList){

					if(*pmList == "int" && !(pm->is_number_integer())){
						pl= false;
						break;
					}

					//Se puede cambiar "!(*pm).is_number_float()" por
					//"!(pm->is_number_float())"
					if(*pmList == "double" && !(pm->is_number_float())){
						pl= false;
						break;
					}

				}

				p= pl;
				if(pl)
					break;

			}else if(it->find("names") != it->end() && in.find("params") != in.end() &&
				in["params"].is_object() && in["params"].size() == (*it)["names"].size()){

				bool pl= true;
				json::iterator pmNames;
				for(json::iterator pm= (*it)["names"].begin(); pm != (*it)["names"].end(); ++pm){

					pmNames= in["params"].find(pm.key());

					if(pmNames == in["params"].end()){
						pl= false;
						break;
					}

					//Se puede cambiar "!pmNames.value().is_number_integer()" 
					//por "!(pmNames->is_number_integer())"
					if(pm.value() == "int" && !(pmNames->is_number_integer())){
						pl= false;
						break;
					}

					if(pm.value() == "double" && !(pmNames->is_number_float())){
						pl= false;
						break;
					}

				}

				p= pl;
				if(pl)
					break;
				
			}

		}

	}

	if(!e)
		return METHOD_NOT_FOUND;

	if(!p)
		return INVALID_PARAMS;

	if(in.find("id") != in.end() && !(in["id"].is_string() || in["id"].is_number() || in["id"].is_null()))
		return INVALID_REQUEST;

	return REQUEST_OK;

}

void Processor::Process(){

	json out;
	STATUS status;
	bool notification;
	vector<json>::iterator it;
	//cout << "Entro" << endl;

	for(it= requests.begin(); it != requests.end(); ++it){
		//status_request.push_back(validate(it->dump()));

		//cout << *it << endl;
		out= nullptr;
		notification= false;
		status= validate(it->dump());
		cout << "STATUS: " << status << endl;
		if(status != PARSE_ERROR && status != INVALID_REQUEST && it->find("id") == it->end())
			notification= true;

		if(status >= PARSE_ERROR){

			out= Errors[status];
			if(status != PARSE_ERROR && status != INVALID_REQUEST && !notification)
				out["id"]= (*it)["id"];

			cout << out << endl;

		}else{

			//REQUEST_DATA req= *it;
			//out= dispatcher.Dispatch(req);
			out= dispatcher.Dispatch(*it);
			cout << out << endl;

		}

		if(!notification)
			response.push_back(out);

	}

	//if(response.empty()){
		//cout << "EMPTY" << endl;
	//	outJson= nullptr;
	//}else 
/*	if(response.empty())
		outJson= nullptr;
	else if(isBatch)
		outJson= response;
	else
		outJson= response[0];

*/

	if(isBatch){
		cout << "BATCH" << endl;
		if(!response.empty())
			outJson= response;
		else
			outJson= nullptr;
	}else if(!response.empty()){
		cout << "NO BATCH" << endl;
		outJson= response[0];
	}

}

string Processor::getResponse(){
	cout << "outJson: " << endl;
	cout << outJson.dump(4) << endl;
	return (outJson == nullptr) ? "":outJson.dump();
}