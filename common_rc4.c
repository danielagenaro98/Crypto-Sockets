#include "common_rc4.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void swap(unsigned char *s, unsigned char i, unsigned char j) {
    unsigned char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}

void rc4_crear_key(rc4_t* self, unsigned char* key, unsigned int key_length, unsigned char* S){
	
	unsigned char j = 0;

	for (int i = 0; i < 256; i++){
		S[i] = i;
	}

	for (int i = 0; i < 256; i++) {
		j = (j + key[i % key_length] + S[i]) % 256;
		swap(S, i, j);
	}
}

void rc4_crear(rc4_t* self, unsigned char* key, unsigned int key_length){
	rc4_crear_key(self, key, key_length, self->S);
	self->i = 0;
	self->j = 0;
}

int rc4_cifrar_mensaje(rc4_t* self, unsigned char* mensaje, ssize_t largo_mensaje){

	for (int y = 0; y < largo_mensaje; y++){

		self->i = (self->i + 1) % 256;
    	self->j = (self->j + self->S[self->i]) % 256;

    	swap(self->S, self->i, self->j);

    	mensaje[y] = mensaje[y] ^ self->S[(self->S[self->i] + self->S[self->j]) % 256];
	}

	return 0;

}

int rc4_descifrar_mensaje(rc4_t* self, unsigned char* mensaje, ssize_t largo_mensaje){
	//RC4 no lleva descifrado, se puede utilizar nuevamente rc4_cifrar_mensaje.
	return 0;
}


void rc4_destruir(){
	//NADA.
}