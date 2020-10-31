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

	socket_connect(&socket, parseador.host,
					parseador.service);

	cifrador_inicializar_cifrado(&cifrador, parseador.method, 
							parseador.key);

	cliente_crear(&cliente, NULL);
	cliente_enviar_mensaje(&cliente, &cifrador, &socket, buffer);

	socket_destroy(&socket);
	return 0;
}
