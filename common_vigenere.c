#include "common_vigenere.h"

void vigenere_crear(vigenere_t* self, unsigned char* key){
	self -> key = key;
}

unsigned char * clave_final(unsigned char* clave, int tamanio) {
	int largo_clave = strlen((const char*)clave)-1;
	
	if ( largo_clave < tamanio ){
		int claveContador = 0;
		
		for (int n = 0; n < tamanio; n++) {
			if (claveContador >= largo_clave) {
				claveContador = 0;
			}
			clave[n] = clave[claveContador];
			claveContador++;
		}
	} else { // Si la clave es mas larga que el mensaje se recorta
		for (int n = 0; n < tamanio; n++) {
			clave[tamanio + n] = 0;
		}
	}
	printf("la clave es %s\n", clave);
	return clave;
}

int vigenere_cifrar_mensaje(vigenere_t* self, unsigned char* mensaje, 
								ssize_t largo_mensaje){
	unsigned char* key_aux;	
	ssize_t largo_clave = strlen((const char*)(self->key));

	if (largo_mensaje != largo_clave){
		key_aux = clave_final(self->key, largo_mensaje); 
	}else{
		key_aux = self->key;
	}

	for(int i = 0; i < largo_mensaje; i++){
		mensaje[i] = (mensaje[i] + key_aux[i]) % 256;
	}

	return 0;
}

int vigenere_descifrar_mensaje(vigenere_t* self, unsigned char* mensaje,
								ssize_t largo_mensaje){
	unsigned char* key_aux;	
	ssize_t largo_clave = strlen((const char*)(self->key));

	if (largo_mensaje != largo_clave){
		key_aux = clave_final(self->key, largo_mensaje); 
	}else{
		key_aux = self->key;
	}

	for(int i = 0; i < largo_mensaje; i++){
		mensaje[i] = (mensaje[i] - key_aux[i]) % 256;
	}
	return 0;
}
