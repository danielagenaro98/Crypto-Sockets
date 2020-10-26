#include "client_tda.h"


void cliente_crear(cliente_t *self, FILE* archivo){
	if(archivo == NULL){
		self->fd = stdin;
	}else{
		self->fd = archivo;
	}
}

void cliente_enviar_mensaje(cliente_t *self, 
		cifrador_t *cifrador, socket_t *socket, unsigned char buffer[]){

	while(!feof(self->fd)){
		size_t resultado = fread(buffer, 1, 
								BUFFER_SIZE, self->fd);
		if (buffer[resultado-1] == 10){
			resultado--;
		}

		cifrador_invocar_cifrado(cifrador, buffer, resultado);
		ssize_t bytes_sent = socket_send(socket, buffer, resultado);

		if (bytes_sent == -1){
			break;
		}
	}
}
