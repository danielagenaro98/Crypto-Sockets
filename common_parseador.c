#include "common_parseador.h"


void crear_parseador(parseo_t* self, int argc, char* argv[], int usa_service){
	_obtener_parametros(self, argc, argv, usa_service);
}


void _obtener_parametros(parseo_t* self, int argc, char* argv[], int usa_service){
	
	int c;
	const char* option;
	char str_method[] = "method";
	char str_key[] = "key"; 
	char str_cesar[] = "cesar";
	char str_vigenere[] = "vigenere";
	char str_rc4[] = "rc4";

	self -> host = argv[1];

	if(usa_service){

		self -> service = argv[2];
	}else{
		self -> service = NULL;
	}

	while (1){

		int option_index = 0;

    	static struct option long_options[] = {
	        {"method", required_argument, 0,  0 },
	        {"key",    required_argument, 0,  0 },
	    };

		c = getopt_long(argc, argv, "-:abc:d::", long_options, &option_index);

	    if (c == -1)
           break;

       	switch (c){

        case 0:
        	option = long_options[option_index].name;

			if(strcmp(option, str_method) == 0){

				if (strcmp(optarg, str_cesar) == 0){
		          	self->method = 0;

				} else if(strcmp(optarg, str_vigenere) == 0){
					self->method = 1;

				} else if(strcmp(optarg, str_rc4) == 0){
					self->method = 2;
				}else{
					printf("No se pasaron metodos\n");
				}

			}else if(strcmp(long_options[option_index].name, str_key) == 0){
				self->key = optarg;
			}
          break;
        }
	}
}


char* parseador_get_host(parseo_t* self){
	return self->host;
}


char* parseador_get_service(parseo_t* self){
	return self->service;
}

char* parseador_get_key(parseo_t* self){
	return self->key;
}


int parseador_get_method(parseo_t* self){
	return self->method;
}