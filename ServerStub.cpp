
#include "ServerStub.h"
#include "Dispatcher.cpp"


json method;
json errors;

int init(const char *pathMethods, const char *pathErrors){

	ifstream ifs;
	ifs.open(pathMethods, ifstream::in);

	if(!ifs.is_open()){

		cout << "Error opening file." << endl;
		return -1;

	}

	ifs >> method;
	ifs.close();

	ifs.open(pathErrors, ifstream::in);

	if(!ifs.is_open()){

		cout << "Error opening file." << endl;
		return -1;

	}

	ifs >> errors;
	ifs.close();

	return 0;
}

int validate(string str){

	json in= json::parse(str);

	if(!in.is_object()){
		cout << "AQUI" << endl;
		return INVALID_REQUEST;
	}
	
	if(in.find("jsonrpc") == in.end() || in.find("method") == in.end())
		return INVALID_REQUEST;

	if(!in["jsonrpc"].is_string() || (in["jsonrpc"].is_string() && in["jsonrpc"] != "2.0"))
		return INVALID_REQUEST;

	if(!in["method"].is_string())
		return INVALID_REQUEST;

	string aux= in["method"];
	for(int i= 0; i<aux.size(); ++i)
		aux[i]= tolower(aux[i]);

	if(aux.size() >= 4 && aux.substr(0, 4) == "rpc.")
		return METHOD_NOT_FOUND;

	if(in.find("params") != in.end() && !(in["params"].is_array() || in["params"].is_object()))
		return INVALID_REQUEST;

	bool e= false, p= false;
	for(json::iterator it= method.begin(); it != method.end(); ++it){

		if((*it)["method"] == in["method"]){

			e= true;
			if((*it).find("list") == it->end() && in.find("params") == in.end()){
				p= true;
				break;

			}else if((*it).find("list") != it->end() && in.find("params") != in.end() &&
				in["params"].is_array() && in["params"].size() == (*it)["list"].size()){

				bool pl= true;
				json::iterator pmList= (*it)["list"].begin();
				for(json::iterator pm= in["params"].begin(); pl && pm != in["params"].end(); ++pm, ++pmList){

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

json dispatch(json inJson){

	int len= 0;
	Dispatcher dispatcher;
	string mt= inJson["method"];
	json outJson= {{"jsonrpc", "2.0"}, {"id", nullptr}};

	if(inJson.find("id") != inJson.end())
		outJson["id"]= inJson["id"];

	if(inJson.find("params") != inJson.end())
		len= inJson["params"].size();

	if(mt == "ccos" || mt == "csin" || mt == "ctan"){

		complex<double> cplx;
		if(inJson["params"].is_array())
			cplx= complex<double>(inJson["params"][0], inJson["params"][1]);
		else
			cplx= complex<double>(inJson["params"]["a"], inJson["params"]["b"]);

		cplx= dispatcher.dispatch(mt, cplx);
		outJson["result"]= json::array({real(cplx), imag(cplx)});

	}else if(inJson["params"].is_array()){
		if(len == 2 && inJson["params"][0].is_number_integer() && inJson["params"][1].is_number_integer()){

			//cout << "AQUI" << endl;
			int a= inJson["params"][0];
			int b= inJson["params"][1];
			int r;
			try{

				errno= 0;
				//if (math_errhandling & MATH_ERREXCEPT)
					feclearexcept(FE_ALL_EXCEPT);

				r= dispatcher.dispatch(mt, a, b);
				//r= a / b;
				outJson["result"]= r;

			}catch(exception& e){ //Divide by zero exception

				if (math_errhandling & MATH_ERRNO) {
			    	if (errno == EDOM)
			    		//printf("errno set to EDOM\n");
			    		outJson["error"]= errors[6]["error"];

			    	if (errno == ERANGE)
			    		//printf("errno set to EDOM\n");
			    		outJson["error"]= errors[7]["error"];
				}
				
				if (math_errhandling & MATH_ERREXCEPT) {
					if (fetestexcept(FE_INVALID))
						//printf("FE_INVALID raised\n");
						outJson["error"]= errors[6]["error"];

					if (fetestexcept(FE_DIVBYZERO))
						//printf("FE_INVALID raised\n");
						outJson["error"]= errors[5]["error"];

					if (fetestexcept(FE_UNDERFLOW))
			    		//printf("errno set to EDOM\n");
			    		outJson["error"]= errors[7]["error"];

			    	if (fetestexcept(FE_OVERFLOW))
			    		//printf("errno set to EDOM\n");
			    		outJson["error"]= errors[7]["error"];
			  	}
			  	
			  	cout << e.what() << endl;
				//cout << "ENTRO" << endl;
				//cout << e.what() << endl;
				//outJson["error"]= errors[5]["error"];

			}



		}else if(len == 1 && inJson["params"][0].is_number_float()){

			double a= inJson["params"][0], b;
			//double b= inJson["params"][1];
			double r= dispatcher.dispatch(mt, a, b);
			outJson["result"]= r;


		}else if(len == 2 && inJson["params"][0].is_number_float() && inJson["params"][1].is_number_float()){

			double a= inJson["params"][0];
			double b= inJson["params"][1];
			double r;

			//try{

				errno= 0;
				//if (math_errhandling & MATH_ERREXCEPT)
					feclearexcept(FE_ALL_EXCEPT);
				cout << "ENTRO" << endl;
				r= pow(a, b);
				cout << "SALIO" << endl;
				//r= dispatcher.dispatch(mt, a, b);
				//r= a / b;
				outJson["result"]= r;
/*
			}catch(exception& e){ //Divide by zero exception

				if (math_errhandling & MATH_ERRNO) {
			    	if (errno == EDOM)
			    		//printf("errno set to EDOM\n");
			    		outJson["error"]= errors[6]["error"];

			    	if (errno == ERANGE)
			    		//printf("errno set to EDOM\n");
			    		outJson["error"]= errors[7]["error"];
				}
				
				if (math_errhandling & MATH_ERREXCEPT) {
					if (fetestexcept(FE_INVALID))
						//printf("FE_INVALID raised\n");
						outJson["error"]= errors[6]["error"];

					if (fetestexcept(FE_DIVBYZERO))
						//printf("FE_INVALID raised\n");
						outJson["error"]= errors[5]["error"];

					if (fetestexcept(FE_UNDERFLOW))
			    		//printf("errno set to EDOM\n");
			    		outJson["error"]= errors[7]["error"];

			    	if (fetestexcept(FE_OVERFLOW))
			    		//printf("errno set to EDOM\n");
			    		outJson["error"]= errors[7]["error"];
			  	}
			  	
			  	cout << e.what() << endl;
				//cout << "ENTRO" << endl;
				//cout << e.what() << endl;
				//outJson["error"]= errors[5]["error"];

			}
*/

		}
	}else{
		if(len == 2 && inJson["params"]["a"].is_number_integer() && inJson["params"]["b"].is_number_integer()){

			int a= inJson["params"]["a"];
			int b= inJson["params"]["b"];
			int r= dispatcher.dispatch(mt, a, b);
			outJson["result"]= r;


		}else if(len == 1 && inJson["params"]["a"].is_number_float()){

			double a= inJson["params"]["a"], b;
			//double b= inJson["params"]["b"];
			double r= dispatcher.dispatch(mt, a, b);
			outJson["result"]= r;


		}else if(len == 2 && inJson["params"]["a"].is_number_float() && inJson["params"]["b"].is_number_float()){

			double a= inJson["params"]["a"];
			double b= inJson["params"]["b"];
			double r= dispatcher.dispatch(mt, a, b);
			outJson["result"]= r;

		}
	}

	return outJson;
		
}

string resolve(const char* str){

	int t;
	json inJson;

	try{
		inJson= json::parse(str);
	}catch(...){
		return errors[0].dump();
	}

	if(inJson.is_object()){

		json outJson;
		t= validate(str);
		cout << t << endl;

		if(t <= PARSE_ERROR){

			outJson= errors[abs(t)];
			if(t != PARSE_ERROR && inJson.find("id") != inJson.end())
				outJson["id"]= inJson["id"];

		}else{
			outJson= dispatch(inJson);
		}

		if(t == NOTIFICATION_OK)
			return "";
		
		return outJson.dump();
		
	}else{

		if(inJson.empty())
			return errors[1].dump();
		
		json outJson;
		vector<json> arrayJson;
		for(json::iterator it= inJson.begin(); it != inJson.end(); ++it){

			t= validate(it->dump());

			if(t <= PARSE_ERROR){
				
				outJson= errors[abs(t)];
				if(t != PARSE_ERROR && it->find("id") != it->end())
					outJson["id"]= (*it)["id"];

			}else{
				outJson= dispatch(*it);
			}

			if(t != NOTIFICATION_OK)
				arrayJson.push_back(outJson);

		}
	
		if(arrayJson.empty())
			return "";
		else
			return json(arrayJson).dump();

	}

}

static void request_completed(void *cls, struct MHD_Connection *connection, void **con_cls, enum MHD_RequestTerminationCode toe){

	MHD_DATA *dataJSON= (MHD_DATA*) *con_cls;

	if (dataJSON == NULL)
    	return;

    if(dataJSON->type != POST)
    	return;
    
	if (dataJSON->type == POST)
    	if (dataJSON->data)
    		free (dataJSON->data);

	free(dataJSON);
	*con_cls = NULL;

}

static int answer_to_connection (void *cls, struct MHD_Connection *connection, const char *url, 
	const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls){

	if (strcmp (method, MHD_HTTP_METHOD_POST) != 0)
		return MHD_NO;

	if(*con_cls == NULL){

			MHD_DATA *dataJSON= (MHD_DATA*) malloc(sizeof(MHD_DATA));
			if(dataJSON == NULL)
				return MHD_NO;
			
			dataJSON->len= 0;
			dataJSON->type= POST;
			dataJSON->data= (char*) malloc(POSTBUFFERSIZE);
			*con_cls = (void*) dataJSON;

      		return MHD_YES;

	}

	MHD_DATA *dataJSON= (MHD_DATA*) *con_cls;

	if(*upload_data_size != 0){
		
        memcpy (dataJSON->data + dataJSON->len, upload_data, *upload_data_size);
        dataJSON->len = dataJSON->len + (*upload_data_size);
        ((char *)(dataJSON->data))[dataJSON->len] = '\0';
        *upload_data_size = 0;
       
        return MHD_YES;

	}

	if(dataJSON->data != NULL){

		cout << "*****************************************************************************************************" << endl;
		cout << "RECIBIDO: " << dataJSON->data << endl;

		string strResponse= resolve(dataJSON->data);
		//strResponse+= "*";

		char *page= (char*) malloc(strResponse.size() + 1);
		if(page == NULL)
			return MHD_NO;

		memcpy (page, strResponse.data(), strResponse.size() + 1);
		page[strResponse.size()]= '\0';

		cout << "ENVIADO: " << page << endl;

		int ret;
		struct MHD_Response *response;
		response = MHD_create_response_from_buffer (strlen (page), (void *) page, MHD_RESPMEM_MUST_FREE);

		if (response == NULL){
      		free (page);
      		return MHD_NO;
    	}

		ret = MHD_queue_response (connection, MHD_HTTP_OK, response);
		MHD_destroy_response (response);
	
		return ret;

	}

}


int main(){
	
	if(init("./MethodSettings.json", "./Errors.json"))
		exit(1);

	struct MHD_Daemon *daemon;
	daemon = MHD_start_daemon (MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL, 
		&answer_to_connection, NULL, MHD_OPTION_NOTIFY_COMPLETED, &request_completed, NULL, MHD_OPTION_END);

	if (daemon == NULL)
		return 1;

	getchar ();
	MHD_stop_daemon (daemon);

	return 0;

}
