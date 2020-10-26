#ifndef SERVER_TDA
#define SERVER_TDA
#include <string.h>
#include <stdio.h>
#include "common_socket.h"
#include "common_cifrador.h"

#define BUFFER_SIZE 64

// Tipo server_t : contiene el file descriptor en el 
// cual almacenar los mensajes.
typedef struct {
	FILE* fd;
} server_t;

void server_crear(server_t *self, FILE* archivo);

void server_recibir_mensajes(server_t *self, 
		cifrador_t *cifrador, socket_t *socket, socket_t *peer,
		char buffer[]);
#endif
