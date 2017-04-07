
#include "ServerStub.h"



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

		string strResponse= "POSIBLE RESPUESTA";

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

	if(Processor::init("./MethodSettings.json", "./Errors.json"))
		return 1;

	struct MHD_Daemon *daemon;
	daemon = MHD_start_daemon (MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL, 
		&answer_to_connection, NULL, MHD_OPTION_NOTIFY_COMPLETED, &request_completed, NULL, MHD_OPTION_END);

	if (daemon == NULL)
		return 1;

	getchar ();
	MHD_stop_daemon (daemon);

	return 0;

}