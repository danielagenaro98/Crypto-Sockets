#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "common_socket.h"
#include "common_parseador.h"
#include "common_cifrador.h"

int main(int argc, char* argv[]){
	socket_t socket;
	socket_t peer;
	parseo_t parseador;
	cifrador_t cifrador;

	char buffer[64];
	size_t bytes = 0;

	crear_parseador(&parseador, argc, argv, 0);

	socket_bind_and_listen(&socket, NULL, parseador_get_host(&parseador));
	socket_accept(&socket, &peer);

	cifrador_inicializar_cifrado(&cifrador, parseador_get_method(&parseador), 
								parseador_get_key(&parseador));

	while((bytes = socket_receive(&peer, buffer, sizeof(buffer)))!= 0){
		cifrador_invocar_descifrado(&cifrador, (unsigned char*)buffer, bytes);

		fwrite(buffer, 1, bytes, stdout);
	}

	socket_destroy(&socket);
	socket_destroy(&peer);
	return 0;
}
