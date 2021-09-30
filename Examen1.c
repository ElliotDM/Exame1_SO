/*
PRIMER EXAMEN -- SISTEMAS OPERATIVOS
Elliot Duran Macedo 15/09/2021
*/


#include <stdio.h>
#include <stdlib.h>

#define MEM_TOTAL 4096
#define MEM_SO 1024

#define TRUE 1
#define FALSE !TRUE

struct proceso {
  int id;
  int tamProceso;
};

int menu();
void particion_estatica();
struct proceso crear_proceso(int _id, int _tamProceso);


int main(void)
{
  int opcion = menu();
  particion_estatica();
  
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
  printf("Memoria total: %d KB\n", MEM_TOTAL);
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
  int memRestante = MEM_TOTAL - MEM_SO;
  int numParticiones;
  int tamParticion;

  struct proceso procEstatico;
  int idProc;
  int tamProc;
  
  printf("\n------ PARTICIONAMIENTO ESTATICO ------\n\n");
  printf("Cuantas particiones desea? ");
  scanf("%d", &numParticiones);
  
  int listaParticiones[numParticiones];
  
  for(int i = 0; i < numParticiones; i++)
    {
      printf("\nMemoria disponible: %d KB\n", memRestante);
      printf("De que tamanio desea la particion %d? ", i);
      scanf("%d", &tamParticion);

      if(memRestante-tamParticion < 0)
	{
	  printf("MEMORIA INSUFICIENTE\n");
	  break;
	}
      
      memRestante -= tamParticion;
      listaParticiones[i] = tamParticion;
    }

  while(TRUE)
    {
      printf("\nIngrese el tamanio del proceso: ");
      scanf("%d", &tamProc);

      idProc = rand() % 100;
      procEstatico = crear_proceso(idProc, tamProc);
      printf("\nProceso %d\n", procEstatico.id);
      printf("Tamanio %d\n", procEstatico.tamProceso);
      break;
    } 
}

struct proceso crear_proceso(int _id, int _tamProceso)
{
  struct proceso nuevo;

  nuevo.id = _id;
  nuevo.tamProceso = _tamProceso;

  return nuevo;
}
