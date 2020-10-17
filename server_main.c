#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "common_socket.h"
#include "common_cesar.h"
#include "common_vigenere.h"
#include "common_rc4.h"
#include "common_parseador.h"

int main(int argc, char* argv[]){
	socket_t socket;
	socket_t peer;
	parseo_t parseador;

	char buffer[64];
	ssize_t bytes = 0;

	crear_parseador(&parseador, argc, argv, 0);

	socket_bind_and_listen(&socket, NULL, parseador_get_host(&parseador));
	socket_accept(&socket, &peer);

	cesar_t cesar;
	vigenere_t vigenere;
	rc4_t rc4;

	if (parseador_get_method(&parseador) == 0){
		int key = atoi(parseador_get_key(&parseador));
		cesar_crear(&cesar, key);
	}else if (parseador_get_method(&parseador) == 1){
		vigenere_crear(&vigenere,parseador_get_key(&parseador));
	}else{
		rc4_crear(&rc4, (unsigned char*)parseador_get_key(&parseador), 
							strlen(parseador_get_key(&parseador)));
	}

	while((bytes = socket_receive(&peer, buffer, sizeof(buffer)))!= 0){
		if(parseador_get_method(&parseador) == 0){
			cesar_descifrar_mensaje(&cesar, (unsigned char*)buffer, bytes);
		} else if (parseador_get_method(&parseador) == 1){
			vigenere_descifrar_mensaje(&vigenere, (unsigned char*)buffer, bytes);
		}else{				
			rc4_cifrar_mensaje(&rc4, (unsigned char*)buffer, bytes);
		}
		fwrite(buffer, 1, bytes, stdout);
	}

	socket_destroy(&socket);

	return 0;
}
