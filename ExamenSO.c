/*
PRIMER EXAMEN -- SISTEMAS OPERATIVOS
Elliot Duran Macedo 15/09/2021
*/


#include <stdio.h>
#include <stdlib.h>

#define MEM_TOTAL 4096
#define MEM_SO 1024

int menu();
void particion_estatica();

int main(void)
{
    int opcion = menu();
    
    if(opcion)
    {
        particion_estatica();
    } else {
        printf("Algo salio mal :(\n");
    }

    return 0;
}

int menu()
{
    int opc;

    printf("Duran Macedo Elliot\n");
    printf("Sistemas Operativos\n");
    printf("2022-1\n\n");
    printf("Programa de Administracion de memoria\n\n");
    printf("El sistema cuenta con la memoria siguiente:\n");
    printf("Memoria total: \n");
    printf("Memoria base: \n");
    printf("Memoria programas: \n");
    printf("Memoria disponible: \n\n");
    printf("En el sistema se pueden emplear los siguientes modos de gestion de memoria: \n");
    printf("1.- Particionamiento estatico\n");
    printf("2.- Particionamiento dinamico\n");
    printf("3.- Paginacion de memoria\n");
    printf("4.- Segmentacion de memoria\n\n");
    printf("Por favor selecciona el tipo de gestion de memoria a implementar: ");
    
    scanf("%d", &opc);
    return opc;
}

void particion_estatica()
{
    int memSO;
    int memRestante;
    int numParticiones;
    int listaParticiones[numParticiones];
    int tamanioParticion;
    int contador = 0;

    printf("Cuanta memoria ocupa el Sistema Operativo? ");
    scanf("%d", &memSO);
    memRestante = MEM_TOTAL - memSO;

    printf("\nCuantas particiones desea? ");
    scanf("%d", &numParticiones);

    for(int i = 0; i<numParticiones; i++)
    {
        printf("De que tamanio desea la particion %d? ", i);
        scanf("%d", &tamanioParticion);
        contador += tamanioParticion;
        
       /* if(memRestante-contador <= 0)
        {
            printf("Particion muy grande, queda %d de memoria\n", memRestante);
	    printf("De que tamanio desea la particion %d? ", i);
	    scanf("%d", &tamanioParticion);
	    listaParticiones[i] = tamanioParticion;
        } else {
            listaParticiones[i] = tamanioParticion;
        }*/

	listaParticiones[i] = tamanioParticion;	
    }

    for(int i = 0; i<numParticiones; i++)
    {
	printf("Particion %d: %d\n", i, listaParticiones[i]);
    }
}
