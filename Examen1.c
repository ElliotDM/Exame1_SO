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

typedef struct {
  int id;
  int tamProceso;
} proceso;

void menu();
void particion_estatica();
proceso crear_proceso(int _id, int _tamProceso);


int main(void)
{
  menu();
  return 0;
}

void menu()
{
  int opcion;

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
  printf("[1] Particionamiento estatico\n");
  printf("[2] Particionamiento dinamico\n");
  printf("[3] Paginacion de memoria\n");
  printf("[4] Segmentacion de memoria\n\n");
  printf("Por favor selecciona el tipo de gestion de memoria a implementar: ");

  scanf("%d", &opcion);

  while(TRUE)
    {
      if(opcion == 1)
	{
	  particion_estatica();
	  break;
	}

      printf("Por favor seleccione una opcion valida: ");
      scanf("%d", &opcion);
    }
}

void particion_estatica()
{
  int memRestante = MEM_TOTAL - MEM_SO;
  int numParticiones;
  int tamParticion;
  int idx;
  int contador = 0;

  proceso procEstatico;
  int idProc;
  int tamProc;
  
  printf("\n------ PARTICIONAMIENTO ESTATICO ------\n\n");
  printf("Memoria disponible: %d KB\n", memRestante);
  printf("Cuantas particiones desea? ");
  scanf("%d", &numParticiones);
  
  int listaParticiones[numParticiones];
  
  for(idx = 0; idx < numParticiones; idx++)
    {
      printf("\nDe que tamanio desea la particion %d? ", idx);
      scanf("%d", &tamParticion);

      if(memRestante-tamParticion < 0)
	{
	  printf("MEMORIA INSUFICIENTE\n");
	  break;
	}
      
      memRestante -= tamParticion;
      printf("Memoria disponible: %d KB\n", memRestante);
      listaParticiones[idx] = tamParticion;
    }

  printf("\nParticion\t\tTamanio\n");
  printf("-------------------------------\n");

  for(idx = 0; idx < numParticiones; idx++)
    {
      printf("Particion %d\t\t%d KB\n", idx, listaParticiones[idx]);
    }

  while(contador <= numParticiones)
    {
      printf("\nIngrese el tamanio del proceso: ");
      scanf("%d", &tamProc);

      idProc = rand() % 16;
      procEstatico = crear_proceso(idProc, tamProc);
      printf("\nProceso %d\n", procEstatico.id);
      printf("Tamanio %d\n", procEstatico.tamProceso);

      for(int i = 0; i < numParticiones; i++)
	{
	  if(tamProc <= listaParticiones[i])
	    {
	      listaParticiones[i] = -1;
	      contador++;
	      break;
	    }
	}

      if(contador == numParticiones)
	{
	  printf("\nMEMORIA INSUFICIENTE\n");
	  printf("Se han utilizado todas las particiones disponibles\n\n");
	  break;
	}
    } 
}

proceso crear_proceso(int _id, int _tamProceso)
{
  proceso nuevo;

  nuevo.id = _id;
  nuevo.tamProceso = _tamProceso;

  return nuevo;
}
