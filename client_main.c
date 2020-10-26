#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <getopt.h>
#include "common_socket.h"
#include "common_parseador.h"
#include "common_cifrador.h"
#include "client_tda.h"

#define BUFFER_SIZE 64

int main(int argc, char *argv[]) {
	unsigned char buffer[BUFFER_SIZE];
	socket_t socket;
	parseo_t parseador;
	cifrador_t cifrador;
	cliente_t cliente;

	crear_parseador(&parseador, argc, argv, 1);

	socket_connect(&socket, parseador_get_host(&parseador),
					parseador_get_service(&parseador));

	cifrador_inicializar_cifrado(&cifrador, parseador_get_method(&parseador), 
							parseador_get_key(&parseador));

	cliente_crear(&cliente, NULL);
	cliente_enviar_mensaje(&cliente, &cifrador, &socket, buffer);

	socket_destroy(&socket);
	return 0;
}
