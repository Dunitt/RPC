
#include "Processor.h"


json Processor::Errors;
json Processor::Methods;

Processor::Processor(const char *inRequest){

	if(Methods.empty() || Errors.empty())
		throw "Processor not initialized exception";

	try{
		inJson= json::parse(inRequest);
	}catch(exception& e){
		outJson= Errors[STATUS::PARSE_ERROR];
	}


	if(inJson.is_object()){

		isBatch= false;
		requests.push_back(inJson);

	}else
		for(json::iterator it= inJson.begin(); it != inJson.end(); ++it)
			requests.push_back(*it);

	for(int i= 0; i<requests.size(); ++i)
		cout << requests[i] << endl;

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
			if((*it).find("list") == it->end() && in.find("params") == in.end()){
				p= true;
				break;

			}else if((*it).find("list") != it->end() && in.find("params") != in.end() &&
				in["params"].is_array() && in["params"].size() == (*it)["list"].size()){

				bool pl= true;
				json::iterator pmList= (*it)["list"].begin();
				for(json::iterator pm= in["params"].begin(); pm != in["params"].end(); ++pm, ++pmList){

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
				if(pl)
					break;

			}else if((*it).find("names") != it->end() && in.find("params") != in.end() &&
				in["params"].is_object() && in["params"].size() == (*it)["names"].size()){

				bool pl= true;
				json::iterator pmNames;
				for(json::iterator pm= (*it)["names"].begin(); pm != (*it)["names"].end(); ++pm){

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
				if(pl)
					break;
				
			}

		}

	}

	if(!e)
		return METHOD_NOT_FOUND;

	if(!p)
		return INVALID_PARAMS;

	if(in.find("id") == in.end())
		return NOTIFICATION_OK;
	else if(!in["id"].is_string() && !in["id"].is_number() && !in["id"].is_null())
		return INVALID_REQUEST;

	return REQUEST_OK;

}

void Processor::Process(){

	vector<json>::iterator it;
	for(it= requests.begin(); it != requests.end(); ++it)
		status_request.push_back(validate(it->dump()));

}