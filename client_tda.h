#ifndef CLIENT_TDA
#define CLIENT_TDA
#include <string.h>
#include <stdio.h>
#include "common_socket.h"
#include "common_cifrador.h"

#define BUFFER_SIZE 64

// Tipo cliene_t : contiene el file descriptor
// a partir del cual enviar mensajes.
typedef struct {
	FILE* fd;
} cliente_t;

void cliente_crear(cliente_t *self, FILE* archivo);

void cliente_enviar_mensaje(cliente_t *self, 
		cifrador_t *cifrador, socket_t *socket,unsigned char buffer[]);
#endif
