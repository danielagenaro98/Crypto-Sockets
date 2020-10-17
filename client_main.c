#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <getopt.h>
#include "common_socket.h"
#include "common_parseador.h"
#include "common_cifrador.h"

#define BUFFER_SIZE 64

int main(int argc, char *argv[]) {

	unsigned char buffer[BUFFER_SIZE];
	socket_t socket;
	parseo_t parseador;
	cifrador_t cifrador;

	crear_parseador(&parseador, argc, argv, 1);

	socket_connect(&socket, parseador_get_host(&parseador),
					parseador_get_service(&parseador));

	cifrador_inicializar_cifrado(&cifrador, parseador_get_method(&parseador), parseador_get_key(&parseador));

	while(!feof(stdin)){
		size_t resultado = fread(buffer, sizeof(char), BUFFER_SIZE, stdin);

		if (buffer[resultado-1] == 10){
			resultado--;
		}

		cifrador_invocar_cifrado(&cifrador, buffer, resultado);

		ssize_t bytes_sent = socket_send(&socket, buffer, resultado);

		if (bytes_sent == -1){
			break;
		}
	}
	socket_destroy(&socket);
	return 0;
}
