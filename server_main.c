#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "common_socket.h"
#include "common_cesar.h"
#include "common_vigenere.h"
#include "common_rc4.h"
#include "common_parseador.h"

void descifrar_mensaje_cesar(char* clave, unsigned char* mensaje,
								 size_t largo_mensaje){
	cesar_t cesar;
	int key = atoi(clave);

	cesar_crear(&cesar, key);
	cesar_descifrar_mensaje(&cesar, mensaje, largo_mensaje);
}

void descifrar_mensaje_vigenere(char* clave, unsigned char* mensaje,
									 size_t largo_mensaje){
	vigenere_t vigenere;
	
	vigenere_crear(&vigenere, (unsigned char*)clave);
	vigenere_descifrar_mensaje(&vigenere, mensaje, largo_mensaje);
}

void descifrar_mensaje_rc4(char* clave, unsigned char* mensaje,
								 size_t largo_mensaje){
	rc4_t rc4;
	
	rc4_crear(&rc4, (unsigned char*)clave, strlen(clave));
	rc4_cifrar_mensaje(&rc4, mensaje, largo_mensaje);
}

int main(int argc, char* argv[]){
	socket_t socket;
	socket_t peer;
	parseo_t parseador;

	char buffer[64];
	ssize_t bytes = 0;

	crear_parseador(&parseador, argc, argv, 0);

	socket_bind_and_listen(&socket, NULL, parseador_get_host(&parseador));
	socket_accept(&socket, &peer);

	while((bytes = socket_receive(&peer, buffer, sizeof(buffer)))!= 0){
		if(parseador_get_method(&parseador) == 0){
			descifrar_mensaje_cesar(parseador_get_key(&parseador),
										 (unsigned char*)buffer, bytes);
		} else if (parseador_get_method(&parseador) == 1){
			descifrar_mensaje_vigenere(parseador_get_key(&parseador), 
										(unsigned char*)buffer, bytes);
		}else{				
			descifrar_mensaje_rc4(parseador_get_key(&parseador), 
									(unsigned char*)buffer, bytes);
		}
		fwrite(buffer, 1, bytes, stdout);
	}

	socket_destroy(&socket);

	return 0;
}
