#include <string.h>
#include <stdio.h>
#include <sys/types.h>

// Tipo rc4_t : contiene la clave con la cual cifrar.
typedef struct {
    unsigned char S[256];
    unsigned char i;
    unsigned char j;
} rc4_t;

//Función para la creación del cifrado de rc4.
// Pre: key apunta a un sector válido de memoria.
void rc4_crear(rc4_t* self, unsigned char* key, unsigned int key_length);

// Función para cifrar el mensaje con la clave almacenada. 
// Pre: El mensaje apunta a un sector válido de memoria y fue creado el cifrado con rc4_crear().
int rc4_cifrar_mensaje(rc4_t* self, unsigned char* mensaje, ssize_t largo_mensaje); 

// Función para descifrar el mensaje con la clave almacenada. 
// Pre: El mensaje apunta a un sector válido de memoria y fue creado el cifrado con rc4_crear().
int rc4_descifrar_mensaje(rc4_t* self, unsigned char* mensaje, ssize_t largo_mensaje);

// Destruye la instancia self liberando sus recursos.
// Pre: el cifrado de rc4 fue creado con rc4_crear() 
void rc4_destruir();