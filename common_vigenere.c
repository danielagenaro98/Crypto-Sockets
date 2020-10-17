#include "common_vigenere.h"

void vigenere_crear(vigenere_t* self, char* key){
	self -> key = (unsigned char*)key;
	self-> len_key = strlen(key);
	self -> indice = 0;
}

int vigenere_cifrar_mensaje(vigenere_t* self, unsigned char* mensaje, 
								ssize_t largo_mensaje){
	for(int i = 0; i < largo_mensaje; i++){
		mensaje[i] = (mensaje[i] + self->key[self->indice % self->len_key]) % 256;
		self->indice++;
	}

	return 0;
}

int vigenere_descifrar_mensaje(vigenere_t* self, unsigned char* mensaje,
								ssize_t largo_mensaje){
	for(int i = 0; i < largo_mensaje; i++){
		mensaje[i] = (mensaje[i] - self->key[self->indice % self->len_key]) % 256;
		self->indice++;
	}

	return 0;
}
