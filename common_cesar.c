#include "common_cesar.h"

void cesar_crear(cesar_t* self,int key){
	self->key = key;
}

int cesar_cifrar_mensaje(cesar_t* self, unsigned char* mensaje, 
							ssize_t largo_mensaje){
	int contador = 0;
	while(contador != largo_mensaje){
		mensaje[contador] = (mensaje[contador] + self->key) % 256;
		contador++;
	}
	return 0;
}

int cesar_descifrar_mensaje(cesar_t* self, unsigned char* mensaje, 
								ssize_t largo_mensaje){
	int contador = 0;
	while(contador != largo_mensaje){
		mensaje[contador] = (mensaje[contador] - self->key) % 256;
		contador++;
	}
	return 0;
}

void cesar_cesar_destruir(){
	//No se utiliza memoria dinamica. No hacer nada.
}
