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

void cifrar_mensaje_cesar(char* clave, unsigned char* mensaje,
							size_t largo_mensaje){
	cesar_t cesar;
	int key = atoi(clave);

	cesar_crear(&cesar, key);
	cesar_cifrar_mensaje(&cesar, mensaje, largo_mensaje);
}

void cifrar_mensaje_vigenere(char* clave, unsigned char* mensaje, 
								size_t largo_mensaje){
	vigenere_t vigenere;
	
	vigenere_crear(&vigenere, (unsigned char*)clave);
	vigenere_cifrar_mensaje(&vigenere, mensaje, largo_mensaje);
}

void cifrar_mensaje_rc4(char* clave, unsigned char* mensaje, 
							size_t largo_mensaje){
	rc4_t rc4;
	
	rc4_crear(&rc4, (unsigned char*)clave, strlen(clave));
	rc4_cifrar_mensaje(&rc4, mensaje, largo_mensaje);
}


int main(int argc, char *argv[]) {
	unsigned char buffer[BUFFER_SIZE];
	socket_t socket;
	parseo_t parseador;

	crear_parseador(&parseador, argc, argv, 1);

	LARGOsocket_connect(&socket, parseador_get_host(&parseador), parseador_get_service(&parseador));

	while(!feof(stdin)){
		size_t resultado = fread(buffer, sizeof(char), BUFFER_SIZE, stdin);

		if( parseador_get_method(&parseador) == 0){
			cifrar_mensaje_cesar(parseador_get_key(&parseador), buffer, resultado);
		}else if( parseador_get_method(&parseador) == 1){
			cifrar_mensaje_vigenere(parseador_get_key(&parseador), buffer, resultado);
		}else{	
			cifrar_mensaje_rc4(parseador_get_key(&parseador), buffer, resultado);
		}

		ssize_t bytes_sent = socket_send(&socket, buffer, resultado);

		if (bytes_sent == -1){
			break;
		}
	}

	socket_destroy(&socket);

	return 0;
}
