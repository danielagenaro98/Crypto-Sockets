#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdbool.h>
#include <stdlib.h>

// Tipo cesar_t: constructor del cifrado de Cesar, contiene la clave a utilizar.
typedef struct {
    unsigned int key;
} cesar_t;

//Función para la creación del cifrado de Cesar.
// Pre: key apunta a un sector válido de memoria.
void cesar_crear(cesar_t* self, int key);

// Función para cifrar el mensaje con la clave almacenada. 
// Pre: El mensaje apunta a un sector válido de memoria y fue creado 
// el cifrado con cesar_crear().
int cesar_cifrar_mensaje(cesar_t* self, unsigned char* mensaje, 
							ssize_t largo_mensaje); 

// Función para descifrar el mensaje con la clave almacenada. 
// Pre: El mensaje apunta a un sector válido de memoria y fue creado 
// el cifrado con cesar_crear().
int cesar_descifrar_mensaje(cesar_t* self, unsigned char* mensaje, 
									ssize_t largo_mensaje);

// Destruye la instancia self liberando sus recursos.
// Pre: el cifrado de Cesar fue creado con cesar_crear() 
// void cesar_cesar_destruir();
