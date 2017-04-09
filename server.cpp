

#include <cstdio>
#include <string>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <microhttpd.h>


#include "ServerStub.cpp"

using namespace std;


//#define GET 0
//#define POST 1
#define PORT 8888
#define POSTBUFFERSIZE  512

typedef enum CONNECTION_TYPE{

	GET= 0,
	POST

}CONNECTION_TYPE;

struct MHD_DATA{

	//char *page;
	char *data;
	size_t len;
	CONNECTION_TYPE type;

};

ServerStub *serverStub;


static void request_completed(void *cls, struct MHD_Connection *connection, void **con_cls, enum MHD_RequestTerminationCode toe){

	MHD_DATA *dataJSON= (MHD_DATA*) *con_cls;

	if (NULL == dataJSON){
		int t;
		cout << "CASO 1" << endl;
		cin >> t;
    	return;
	}

    if(dataJSON->type != POST){
    	int t;
		cout << "CASO 2" << endl;
		cin >> t;
    	return;
    }

	//cout << "type: " << dataJSON->type << endl;

	if (dataJSON->type == POST){

    	//MHD_destroy_post_processor (dataJSON->postprocessor);
    	if (dataJSON->data){
    		//cout << "ENTRO 2" << endl;
    		free (dataJSON->data);
    		//dataJSON->data= NULL;
    		//cout << "SALIO 2" << endl;
    	}

    /*	if (dataJSON->page){
    		//cout << "ENTRO 2" << endl;
    		free (dataJSON->page);
    		dataJSON->page= NULL;
    		//cout << "SALIO 2" << endl;
    	}*/

    	//cout << "Datos limpios" << endl;

    }else{
    	int t;
		cout << "CASO 3" << endl;
		cin >> t;
    }

    //cout << "ENTRO" << endl;
	free (dataJSON);
	*con_cls = NULL;
	//cout << "SALIO" << endl;

  //cout << "Eliminado" << endl;

}

static int answer_to_connection (void *cls, struct MHD_Connection *connection, const char *url, 
	const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls){

	if (strcmp (method, MHD_HTTP_METHOD_POST) != 0)
		return MHD_NO;

	//MHD_DATA *dataJSON= (MHD_DATA*) *con_cls;

	if(*con_cls == NULL){

			//cout << "Entro1" << endl;

			struct MHD_DATA *dataJSON= (MHD_DATA*) malloc(sizeof(MHD_DATA));

			if(dataJSON == NULL)
				return MHD_NO;
			
			dataJSON->len= 0;
			dataJSON->type= POST;
			dataJSON->data= (char*) malloc(POSTBUFFERSIZE);

			*con_cls = (void*) dataJSON;

			//cout << "Salio1" << endl;

      		return MHD_YES;

	}


	struct MHD_DATA *dataJSON= (MHD_DATA*) *con_cls;

	if(*upload_data_size != 0){
		
		//cout << "Entro2" << endl;


		//const char * param = MHD_lookup_connection_value (connection, MHD_HEADER_KIND, MHD_HTTP_HEADER_CONTENT_LENGTH); 
		//cout << "param: " << param << endl;
		//int content_len = atoi(param);
		/*
		cout << "[Antes] JSON: " << dataJSON << endl;
		cout << "[Antes] Data: " << dataJSON->data << endl;
		cout << "[Antes] Lenght: " << dataJSON->len << endl;
		cout << "[Antes] Type: " << dataJSON->type << endl;
		*/
        memcpy (dataJSON->data + dataJSON->len, upload_data, *upload_data_size);
        dataJSON->len = dataJSON->len + (*upload_data_size);
        ((char *)(dataJSON->data))[dataJSON->len] = '\0';
        /* indicate that we have processed */
        *upload_data_size = 0;
        /*
        cout << "[Despues] JSON: " << dataJSON << endl;
		cout << "[Despues] Data: " << dataJSON->data << endl;
		cout << "[Despues] Lenght: " << dataJSON->len << endl;
		cout << "[Despues] Type: " << dataJSON->type << endl;

        cout << "Salio2" << endl;
		*/
        return MHD_YES;

	}else if(dataJSON->data != NULL){

		//cout << "Entro3" << endl;

		//
		cout << "*****************************************************************************************************" << endl;
		cout << "RECIBIDO: " << dataJSON->data << endl;

		string strResponse= serverStub->dispatch(dataJSON->data);

		//const char *page = "<html><body>Hello, browser!</body></html>";
		//const char *page = "{\"jsonrpc\": \"2.0\", \"result\": 3, \"id\": 1}";
		//char *page=  (char*) malloc(strResponse.size());
		char *page= (char*) malloc(strResponse.size() + 1);

		if(page == NULL)
			return MHD_NO;

		memcpy (page, strResponse.data(), strResponse.size() + 1);
		page[strResponse.size()]= '\0';

		cout << "ENVIADO: " << page << endl;

		int ret;
		struct MHD_Response *response;

		

		//cout << "ENTRO 1" << endl;
		response = MHD_create_response_from_buffer (strlen (page), (void *) page, MHD_RESPMEM_MUST_FREE);

		if (response == NULL){
      		free (page);
      		return MHD_NO;
    	}

		//cout << "PASO 1" << endl;
		//response = MHD_create_response_from_buffer (strlen (dataJSON->page), (void *) dataJSON->page, MHD_RESPMEM_MUST_COPY);
		//cout << "Aqui" << endl;
		ret = MHD_queue_response (connection, MHD_HTTP_OK, response);
		//cout << "PASO 2" << endl;
		MHD_destroy_response (response);
		//cout << "PASO 3" << endl;
		//if(page != NULL)
		//	free(page);
		//cout << "SALIO 1" << endl;

		//cout << "Salio3" << endl;

		return ret;

	}

	//cout << "No debería ocurrir" << endl;

}


int main(){
	
	serverStub= new ServerStub("./MethodSettings.json", "./Errors.json");

	struct MHD_Daemon *daemon;
	daemon = MHD_start_daemon (MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL, 
		&answer_to_connection, NULL, MHD_OPTION_NOTIFY_COMPLETED, &request_completed, NULL, MHD_OPTION_END);

	if (NULL == daemon)
		return 1;

	getchar ();
	MHD_stop_daemon (daemon);
	delete serverStub;

	return 0;

}
