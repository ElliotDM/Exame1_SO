/*
PRIMER EXAMEN -- SISTEMAS OPERATIVOS
Elliot Duran Macedo 15/09/2021
*/


#include <stdio.h>
#include <stdlib.h>
#define MEM_TOTAL 4096

int menu();

int main(int argc, char const *argv[])
{
    int opcion = menu();
    printf("%d", opcion);
    return 0;
}

int menu()
{
    int opcion;

    printf("Duran Macedo Elliot\n");
    printf("Sistemas Operativos\n");
    printf("2022-1\n\n");
    printf("Programa de Administracion de memoria\n\n");
    printf("El sistema cuenta con la memoria siguiente:\n");
    printf("Memoria total: %d KB\n\n", MEM_TOTAL);
    printf("Memoria base: \n");
    printf("Memoria programas: \n");
    printf("Memoria disponible: \n\n");
    printf("En el sistema se pueden emplear los siguientes modos de gestion de memoria: \n");
    printf("1.- Particionamiento estatico\n");
    printf("2.- Particionamiento dinamico\n");
    printf("3.- Paginacion de memoria\n");
    printf("4.- Segmentacion de memoria\n\n");
    printf("Por favor selecciona el tipo de gestion de memoria a implementar: \n");
    
    scanf("%d", &opcion);
    return opcion;
}