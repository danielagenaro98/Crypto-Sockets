#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "common_socket.h"
#include "common_parseador.h"
#include "common_cifrador.h"
#include "server_tda.h"

int main(int argc, char* argv[]){
	socket_t socket;
	socket_t peer;
	parseo_t parseador;
	cifrador_t cifrador;
	server_t server;

	char buffer[64];

	crear_parseador(&parseador, argc, argv, 0);

	socket_bind_and_listen(&socket, NULL, parseador_get_host(&parseador));
	socket_accept(&socket, &peer);

	cifrador_inicializar_cifrado(&cifrador, parseador_get_method(&parseador), 
								parseador_get_key(&parseador));

	server_crear(&server, NULL);
	server_recibir_mensajes(&server, &cifrador, &socket, &peer, buffer);

	socket_destroy(&socket);
	socket_destroy(&peer);
	return 0;
}
