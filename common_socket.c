#define _POSIX_C_SOURCE 200112L
#define SERVER_FLAGS AI_PASSIVE
#define CLIENT_FLAGS 0
#include "common_socket.h"

struct addrinfo* get_addr_info(socket_t *self, const char *host, const char* service, int flags){

	struct addrinfo *result;	
	struct addrinfo hints;

	memset(&hints, 0, sizeof(struct addrinfo));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;
	hints.ai_flags = flags;

	int s = getaddrinfo(host, service, &hints, &result);

     if (s != 0) {
        fprintf(stderr, "getaddrinfo fail\n");
    }

	return result;
}

void socket_create(socket_t* self, int fileDescriptor){
	self->fd = fileDescriptor;
}

void socket_bind_and_listen(socket_t *self, const char *host, const char* service){

	int sfd;
	int value = 1;

	struct addrinfo* lista = get_addr_info(self, host, service, SERVER_FLAGS);

	for (struct addrinfo* rp = lista ; rp != NULL; rp = rp->ai_next) {

		sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

		setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value));
		
		if (sfd == -1){
			continue;
		}

		if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0){
			break; 
		}

		close(sfd);
    }

    freeaddrinfo(lista); 

    socket_create(self, sfd);

    listen(self->fd, 10);
}

void socket_accept(socket_t* self, socket_t* peer){

	//el peer es para crear la semilla con la cual se comunica el servidor con el cliente.

	puts("Waiting for incoming connections...");

	int sock = accept(self->fd, NULL, NULL);

    if (sock < 0)
    {
        perror("accept failed");
    }

    socket_create(peer, sock);
}

void socket_connect(socket_t *self, const char *host, const char *service){

	int sfd;

	struct addrinfo* lista = get_addr_info(self, host, service, CLIENT_FLAGS);

	for (struct addrinfo* rp = lista; rp != NULL; rp = rp->ai_next) {

		sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol); 

		if (sfd == -1){
			continue;
		}

		if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1){
			break;
		}

		close(sfd);
	}

	freeaddrinfo(lista);

	socket_create(self, sfd);
}


ssize_t socket_send(socket_t *self, const unsigned char *buffer, size_t length){
    
    if (length == 0){
    	return 0;
    }
   
    ssize_t bytes_sent = 0;
    ssize_t bytes = 0;
    ssize_t remaining_bytes = length;

    while ((bytes = send(self->fd, &buffer[bytes_sent], remaining_bytes, MSG_NOSIGNAL)) != 0) {

        if (bytes == -1) {
            bytes_sent = -1;
            break;
        }

        bytes_sent += bytes;
        remaining_bytes -= bytes;

        if(remaining_bytes == 0){
        	break;
        }
    }

    return bytes_sent;
}

ssize_t socket_receive(socket_t *self, char *buffer, size_t length){

	if (length == 0){
    	return 0;
    }

 	ssize_t bytes_received = 0;
    int remaining_bytes = length;
    ssize_t bytes = 0;

    while (bytes_received < length) {

    	bytes = recv(self->fd, &buffer[bytes_received], remaining_bytes, 0);

        if (bytes == 0) {
            break;
        }

        if (bytes == -1) {
            bytes_received = -1;
            break;
        }

        bytes_received += bytes;
        remaining_bytes -= bytes;
    }

    return bytes_received;
}

void socket_destroy(socket_t *self){

	if (!self) return;

    if (shutdown(self->fd, SHUT_RDWR) == -1) {
		//fprintf(stderr, "socket destroy !shutdown: %s\n", strerror(errno));
    }
    if (close(self->fd) == -1) {
		//fprintf(stderr, "socket destroy !close: %s\n", strerror(errno));
    }
}