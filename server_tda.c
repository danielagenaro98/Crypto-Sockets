#include "server_tda.h"


void server_crear(server_t *self, FILE* archivo){
	if(archivo == NULL){
		self->fd = stdout;
	}else{
		self->fd = archivo;
	}
}

void server_recibir_mensajes(server_t *self, 
		cifrador_t *cifrador, socket_t *socket, socket_t *peer,
		char* buffer){
	size_t bytes = 0;

	while((bytes = socket_receive(peer, buffer, sizeof(buffer)))!= 0){
		cifrador_invocar_descifrado(cifrador, (unsigned char*)buffer, bytes);

		fwrite(buffer, 1, bytes, self->fd);
	}
}