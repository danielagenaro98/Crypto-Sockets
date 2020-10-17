#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/types.h>
#include<netdb.h>
#include <sys/types.h>

typedef struct {
	int fd;
} socket_t;

void socket_create(socket_t* self, int fileDescriptor);

void socket_bind_and_listen(socket_t *self, const char *host, 
								const char* service);

void socket_accept(socket_t* self, socket_t *peer);

void socket_connect(socket_t *self, const char *host, const char *service);

ssize_t socket_send(socket_t *self, const unsigned char *buffer, size_t length);

ssize_t socket_receive(socket_t *self, char *buffer, size_t length);

void socket_destroy(socket_t *self);
