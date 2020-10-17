#include "common_cifrador.h"

void cifrador_inicializar_cifrado(cifrador_t* self, int method, 
								char* clave){
	self->method = method;

	if (method == 0){
		int key = atoi(clave);
		cesar_crear(&(self->cesar), key);
	}else if (method == 1){
		vigenere_crear(&(self->vigenere), clave);
	}else{
		rc4_crear(&(self->rc4), (unsigned char*)clave, strlen(clave));
	}
}

void cifrador_invocar_cifrado(cifrador_t* self, unsigned char* buffer, 
								size_t resultado){
	if (self->method == 0){
		cesar_cifrar_mensaje(&(self->cesar), buffer, resultado);
	}else if (self->method == 1){
		vigenere_cifrar_mensaje(&(self->vigenere), buffer, resultado);
	}else{
		rc4_cifrar_mensaje(&(self->rc4), buffer, resultado);
	}
}

void cifrador_invocar_descifrado(cifrador_t* self, 
							unsigned char* buffer,size_t resultado){
	if(self->method == 0){
		cesar_descifrar_mensaje(&(self->cesar), (unsigned char*)buffer, 
									resultado);
	} else if (self->method == 1){
		vigenere_descifrar_mensaje(&(self->vigenere), (unsigned char*)buffer, 
									resultado);
	}else{				
		rc4_cifrar_mensaje(&(self->rc4), (unsigned char*)buffer, 
								resultado);
	}
}
