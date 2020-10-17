#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdbool.h>
#include <stdlib.h>
#include "common_cesar.h"
#include "common_vigenere.h"
#include "common_rc4.h"

// Tipo cifrador_t: constructor del manejador de cifrados, contiene
// el metodo a utilizar.
typedef struct {
    cesar_t cesar;
	vigenere_t vigenere;
	rc4_t rc4;
	int method;
} cifrador_t;

//Inicializa el metodo pasado por method con la clave key.
void cifrador_inicializar_cifrado(cifrador_t* self, int method, char* clave);

//Invoca el metodo almacenado en method.
//El cifrador debe haber sido inicializado con un metodo 
//en cifrador_inicializar_cifrado
void cifrador_invocar_cifrado(cifrador_t* self, unsigned char* buffer, 
								size_t resultado);

void cifrador_invocar_descifrado(cifrador_t* self, 
							unsigned char* buffer,size_t resultado);
