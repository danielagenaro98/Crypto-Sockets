#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <getopt.h>
#include "common_socket.h"
#include "common_cesar.h"
#include "common_vigenere.h"
#include "common_rc4.h"
#include "common_parseador.h"

#define BUFFER_SIZE 64

int main(int argc, char *argv[]) {
	unsigned char buffer[BUFFER_SIZE];
	socket_t socket;
	parseo_t parseador;

	crear_parseador(&parseador, argc, argv, 1);

	socket_connect(&socket, parseador_get_host(&parseador),
					parseador_get_service(&parseador));

	cesar_t cesar;
	vigenere_t vigenere;
	rc4_t rc4;

	if (parseador_get_method(&parseador) == 0){
		int key = atoi(parseador_get_key(&parseador));
		cesar_crear(&cesar, key);
	}else if (parseador_get_method(&parseador) == 1){
		vigenere_crear(&vigenere, (unsigned char*)parseador_get_key(&parseador));
	}else{
		rc4_crear(&rc4, (unsigned char*)parseador_get_key(&parseador), 
						strlen(parseador_get_key(&parseador)));
	}

	while(!feof(stdin)){
		size_t resultado = fread(buffer, sizeof(char), BUFFER_SIZE, stdin);

		if (buffer[resultado-1] == 10){
			resultado--;
		}

		if (parseador_get_method(&parseador) == 0){
			cesar_cifrar_mensaje(&cesar, buffer, resultado);
		}else if (parseador_get_method(&parseador) == 1){
			vigenere_cifrar_mensaje(&vigenere, buffer, resultado);
		}else{
			rc4_cifrar_mensaje(&rc4, buffer, resultado);
		}

		ssize_t bytes_sent = socket_send(&socket, buffer, resultado);

		if (bytes_sent == -1){
			break;
		}
	}
	socket_destroy(&socket);
	return 0;
}
