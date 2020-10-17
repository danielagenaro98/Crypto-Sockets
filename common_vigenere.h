#include <string.h>
#include <stdio.h>
#include <sys/types.h>

// Tipo vigenere_t : contiene la clave con la cual cifrar.
typedef struct {
    unsigned char* key;
} vigenere_t;

//Función para la creación del cifrado de Vigenere.
// Pre: key apunta a un sector válido de memoria.
void vigenere_crear(vigenere_t* self, unsigned char* key);

// Función para cifrar el mensaje con la clave almacenada. 
// Pre: El mensaje apunta a un sector válido de memoria y fue creado el cifrado con vigenere_crear().
int vigenere_cifrar_mensaje(vigenere_t* self, unsigned char* mensaje, ssize_t largo_mensaje); 

// Función para descifrar el mensaje con la clave almacenada. 
// Pre: El mensaje apunta a un sector válido de memoria y fue creado el cifrado con vigenere_crear().
int vigenere_descifrar_mensaje(vigenere_t* self, unsigned char* mensaje, ssize_t largo_mensaje);

// Destruye la instancia self liberando sus recursos.
// Pre: el cifrado de Vigenere fue creado con vigenere_crear() 
void vigenere_destruir();