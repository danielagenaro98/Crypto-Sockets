#ifndef COMMON_PARSEADOR
#define COMMON_PARSEADOR
#include <string.h>
#include <stdio.h>
#include <getopt.h>
#include <sys/types.h>

//struct que define los parametros a usar.
typedef struct {  
	char* host;
	char* service;
	char* key;
	int method;
} parseo_t;

//Inicializa el struct parseo_t con los valores adecuados.
void crear_parseador(parseo_t* self, int argc, char* argv[], 
						int usa_service);

//parsea los parametros de la linea de comando almacenandolos 
//en el struct parseo_t.
void _obtener_parametros(parseo_t* self, int argc, char* argv[], 
						int usa_service);

//define host y service a utilizar y los almacena
//en parseo_t.
void _definir_host_service(parseo_t* self, char* argv[], 
							int usa_service);
#endif
