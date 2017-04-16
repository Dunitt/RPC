
#include "ClientStub.h"

unsigned int ClientStub::id;

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp){

	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *)userp;

	//cout << "RECIBIENDO: " << ClientStub::id << endl;
	//json *resp= (json*)userp;
	//cout << "Se recibió: " << (char*) contents << endl;
	//*resp= json::parse((char*)contents); //POSIBLE CONVERSIÓN
	//*resp= "{\"jsonrpc\": \"2.0\", \"result\": 3, \"id\": 1}"_json;

	mem->memory = (char*) realloc(mem->memory, mem->size + realsize + 1);
	if(mem->memory == NULL) {
	/* out of memory! */ 
		printf("Not enough memory (realloc returned NULL)\n");
		return 0;
	}

	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	return realsize;

}

ClientStub::ClientStub(const char* _url, unsigned int _port= 12345){

	id= 0;
	url= NULL;
	curl= NULL;
	error= false;
	chunk.size= 0;
	batch= INACTIVE;
	chunk.memory= (char*)malloc(1);
	request["jsonrpc"]= "2.0";

	if(_url == NULL)
		return;

	port= _port;
	url= (char*) _url;

	curl = curl_easy_init();
	string str= string(url) + ':' + to_string(port);
	//string str= string(url);
	
	//cout << _url << endl;
	//cout << str << endl;

	curl_easy_setopt(curl, CURLOPT_URL, str.c_str());

	/* send all data to this function  */ 
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	 
	/* we pass our 'chunk' struct to the callback function */ 
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

	curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);

	curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

}

ClientStub::~ClientStub(){

	curl_easy_cleanup(curl);

}

bool ClientStub::send(const char* str, long size){

	if(!this->isReady())
		return true;

	 curl_easy_setopt(curl, CURLOPT_POSTFIELDS, str);
 
    /* if we don't provide POSTFIELDSIZE, libcurl will strlen() by
       itself */ 

	//cout << "size: " << size << endl;
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, size);
 
    /* Perform the request, res will get the return code */ 
    res = curl_easy_perform(curl);

    //cout << "OCURRE: " << id << endl;

    /* Check for errors */ 
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

  	cout << "RECIBIDO: " << chunk.memory << endl;

  	try{
		response= json::parse(chunk.memory);
		free(chunk.memory);
		chunk.memory= (char*)malloc(1);
		chunk.size= 0;
		cout << "BIEN" << endl;
		//return false;
	}catch(...){
		cout << "MAL" << endl;
		cout << "PARSE ERROR" << endl;
		free(chunk.memory);
		chunk.memory= (char*)malloc(1);
		chunk.size= 0;
		throw "Parse error";
		return true; //NO SE VA A EJECUTAR
	}

	if(batch == READY){
		batch= RECEIVED;
		return false;
	}

	if(response.find("result") != response.end()){
		return false;
	}
	else{
		cout << "RARO" << endl;
		cout << "JSON: " << response << endl;
		throw "Invalid response";
		return true; //NO SE VA A EJECUTAR
	}


}

bool ClientStub::isReady(){

	return (curl ? true:false);

}

bool ClientStub::isError(){
	return error;
}

void ClientStub::beginBatch(){
	batch= ACTIVE;
	request= json::array({});
	//cout << request << endl;
}

void ClientStub::endBatch(){
	
	if(batch != ACTIVE)
		return;

	batch= READY;
	string str= request.dump();
	send(str.data(), str.size());
	batch= RECEIVED;

}

int ClientStub::getBatch(unsigned int idx, int *result){

	if(batch != RECEIVED)
		throw "There are not batch";

	cout << idx << endl;
	if(idx > response.size()-1)
		throw "Index out of range";

	json outJson= response[idx];
	if(outJson.find("result") != outJson.end())
		*result= outJson["result"].get<int>();
	else
		if(outJson["code"]["error"] == -32000)
			throw "Division by zero";

		else if(outJson["code"]["error"] == -32001)
			throw "Domain error";

		else if(outJson["code"]["error"] == -32000)
			throw "Division by zero";

		else if(outJson["code"]["error"] == -32600)
				throw "Invalid Request";

		else if(outJson["code"]["error"] == -32601)
			throw "Method not found";

		else if(outJson["code"]["error"] == -32602)
			throw "Invalid params";

		else if(outJson["code"]["error"] == -32002)
			throw "Unexpected error";
		else
			throw "Invalid response";

	return 0;

}

int ClientStub::getBatch(unsigned int idx, double *result){

	if(batch != RECEIVED)
		throw "There are not batch";

	cout << idx << endl;
	if(idx > response.size()-1)
		throw "Index out of range";

	json outJson= response[idx];
	if(outJson.find("result") != outJson.end())
		*result= outJson["result"].get<double>();
	else
		if(outJson["code"]["error"] == -32000)
			throw "Division by zero";

		else if(outJson["code"]["error"] == -32001)
			throw "Domain error";

		else if(outJson["code"]["error"] == -32000)
			throw "Division by zero";

		else if(outJson["code"]["error"] == -32600)
				throw "Invalid Request";

		else if(outJson["code"]["error"] == -32601)
			throw "Method not found";

		else if(outJson["code"]["error"] == -32602)
			throw "Invalid params";

		else if(outJson["code"]["error"] == -32002)
			throw "Unexpected error";
		else
			throw "Invalid response";

	return 0;

}

int ClientStub::getBatch(unsigned int idx, complex<double> *result){

	if(batch != RECEIVED)
		throw "There are not batch";

	cout << idx << endl;
	if(idx > response.size()-1)
		throw "Index out of range";

	json outJson= response[idx];
	if(outJson.find("result") != outJson.end())
		*result= complex<double>(outJson["result"][0].get<double>(), outJson["result"][1].get<double>());
	else
		if(outJson["code"]["error"] == -32000)
			throw "Division by zero";

		else if(outJson["code"]["error"] == -32001)
			throw "Domain error";

		else if(outJson["code"]["error"] == -32000)
			throw "Division by zero";

		else if(outJson["code"]["error"] == -32600)
				throw "Invalid Request";

		else if(outJson["code"]["error"] == -32601)
			throw "Method not found";

		else if(outJson["code"]["error"] == -32602)
			throw "Invalid params";

		else if(outJson["code"]["error"] == -32002)
			throw "Unexpected error";
		else
			throw "Invalid response";

	return 0;

}

int ClientStub::sum(int a, int b, bool notification= false){

	if(batch == RECEIVED)
		batch= INACTIVE;

	json outJson= {{"jsonrpc", "2.0"}};
	//cout << outJson << endl;
	outJson["method"]= "sum";
	outJson["params"]= {a, b};
	if(!notification)
		outJson["id"]= id++;
	//request["prueba1"]= "dato1";

	string str= outJson.dump();
	//str="[" + str + "]";
//	cout << "ENVIADO: " << request << endl;
	cout << "ENVIADO: " << str << endl;

	if(batch == ACTIVE){
		request.push_back(outJson);
		cout << request << endl;
		return 0;
	}

	error= send(str.c_str(), str.size());
	if(!error && response["result"].is_number_integer())
		return response["result"].get<int>();

	//cout << response << endl;

}

double ClientStub::sum(double a, double b, bool notification= false){

	if(batch == RECEIVED)
		batch= INACTIVE;

	json outJson= {{"jsonrpc", "2.0"}};
	//cout << outJson << endl;
	outJson["method"]= "sum";
	outJson["params"]= {a, b};
	if(!notification)
		outJson["id"]= id++;
	//request["prueba1"]= "dato1";

	string str= outJson.dump();
	//str="[" + str + "]";
//	cout << "ENVIADO: " << request << endl;
	cout << "ENVIADO: " << str << endl;

	if(batch == ACTIVE){
		request.push_back(outJson);
		cout << request << endl;
		return 0;
	}

	//str= "\"id\":0,\"jsonrpc\":\"2.0\",\"method\":\"sum\",\"params\":[1.0,2.0]}";
	error= send(str.c_str(), str.size());
	if(!error && response["result"].is_number_float())
		return response["result"].get<double>();

	//cout << response << endl;

}
