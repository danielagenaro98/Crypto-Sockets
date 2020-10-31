#include "common_parseador.h"

#define STR_METHOD "method"
#define STR_KEY "key"
#define STR_CESAR "cesar"
#define STR_VIGENERE "vigenere"
#define STR_RC4 "rc4"


void crear_parseador(parseo_t* self, int argc, char* argv[], int usa_service){
	_obtener_parametros(self, argc, argv, usa_service);
}

void _definir_host_service(parseo_t* self, char* argv[], int usa_service){
	self -> host = argv[1];

	if (usa_service){
		self -> service = argv[2];
	}else{
		self -> service = NULL;
	}
}

void _obtener_parametros(parseo_t* self, int argc, char* argv[], 
							int usa_service){	
	const char* option;
	_definir_host_service(self, argv, usa_service);

	while (1){

		int option_index = 0;

    	static struct option long_options[] = {
	        {"method", required_argument, 0,  0 },
	        {"key",    required_argument, 0,  0 },
	    };
		int c = getopt_long(argc, argv, "-:abc:d::", long_options, &option_index);

	    if (c == -1)
           break;

       	switch (c){
        case 0:
        	option = long_options[option_index].name;

			if (strcmp(option, STR_METHOD) == 0){
				if (strcmp(optarg, STR_CESAR) == 0){
		          	self->method = 0;
				} else if (strcmp(optarg, STR_VIGENERE) == 0){
					self->method = 1;

				} else if (strcmp(optarg, STR_RC4) == 0){
					self->method = 2;
				} else{
					printf("No se pasaron metodos\n");
				}
			}else if (strcmp(long_options[option_index].name, STR_KEY) == 0){
				self->key = optarg;
			}
          break;
        }
	}
}
