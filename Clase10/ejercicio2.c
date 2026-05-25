#include <string.h>
#include <stdio.h>

int main() {
    char destino[100];
    char origen[] = "Este texto es muy largo";
    
    //strcpy(destino, origen); // PELIGRO: escribe más de 10 bytes
    // en C corrompe memoria
       
    // Alternativa segura:
    strncpy(destino, origen, sizeof(destino)-1);
    destino[sizeof(destino)-1] = '\0'; // se pone su fin de cadena
    printf("destino es %s", destino);
    return 0;
}