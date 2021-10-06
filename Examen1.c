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
  int tam;
  int paginas;
} proceso;

void menu();
void particion_estatica();
void particion_dinamica();
void paginacion();
proceso crear_proceso(int _id, int _tam, int _paginas);


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
  printf("[4] Segmentacion de memoria\n");
  printf("[5] Salir\n\n");
  printf("Por favor selecciona el tipo de gestion de memoria a implementar: ");

  scanf("%d", &opcion);

  while(TRUE)
    {
      if(opcion == 1)
	{
	  particion_estatica();
	  break;
	}
      else if(opcion == 2)
	{
	  particion_dinamica();
	  break;
	}
      else if(opcion == 3)
	{
	  paginacion();
	  break;
	}

      else if(opcion == 5)
	{
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
  int bandera = TRUE;

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

  while(TRUE)
    {
      printf("\nIngrese el tamanio del proceso: ");
      scanf("%d", &tamProc);

      idProc = rand() % 16;
      procEstatico = crear_proceso(idProc, tamProc, 0);

      printf("\nProceso %d\n", procEstatico.id);
      printf("Tamanio %d KB\n", procEstatico.tam);

      for(idx = 0; idx < numParticiones; idx++)
	{
	  if(tamProc <= listaParticiones[idx])
	    {
	      listaParticiones[idx] = -1;
	      contador++;
	      bandera = FALSE;
	      break;
	    }
	}

      if(contador == numParticiones)
	{
	  printf("\nMEMORIA INSUFICIENTE\n");
	  printf("Se han utilizado todas las particiones disponibles\n\n");
	  break;
	}

      if(bandera)
	{
	  printf("\nMEMORIA INSUFICIENTE\n");
	  printf("El tamanio del proceso sobrepasa el de las particiones\n");
	}

      bandera = TRUE;
    }  
}

void particion_dinamica()
{
  int memRestante = MEM_TOTAL - MEM_SO;

  proceso procDinamico;
  int idProc;
  int tamProc;

  printf("\n------ PARTICIONAMIENTO DINAMICO ------\n\n");
  printf("Memoria disponible: %d KB\n", memRestante);

  while(TRUE)
    {
      printf("Ingrese el tamanio del proceso: ");
      scanf("%d", &tamProc);

      if(memRestante < tamProc)
	{
	  printf("\nMEMORIA INSUFICIENTE\n\n");
	  break;
	}
      else
	{
	  idProc = rand() % 16;
	  procDinamico = crear_proceso(idProc, tamProc, 0);

	  printf("\nProceso %d\n", procDinamico.id);
	  printf("Tamanio %d KB\n", procDinamico.tam);

	  memRestante -= tamProc;
	  printf("Memoria disponible: %d KB\n\n", memRestante);
	}
    }
}

void paginacion()
{
  int memRestante = MEM_TOTAL - MEM_SO;
  int paginas;
  int marcos;

  proceso procPaginacion;
  int idProc;
  int tamProc;
  int pagProc;

  printf("\n------ PAGINACION DE MEMORIA ------\n\n");
  printf("El sistema operativo maneja los siguientes tamanios de paginacion:\n");
  printf("4 KB\t8 KB\t16 KB\t32 KB\n\n");
  printf("De que tamanio desea las paginas? ");
  scanf("%d", &paginas);

  marcos = memRestante / paginas;
  printf("Total de marcos de pagina: %d\n", marcos);

  while(TRUE)
    {
      printf("\nIngrese el tamanio del proceso: ");
      scanf("%d", &tamProc);

      idProc = rand() % 100;
      pagProc = tamProc / paginas;
      procPaginacion = crear_proceso(idProc, tamProc, pagProc);

      if(marcos-pagProc < 0)
	{
	  printf("\nMEMORIA INSUFICIENTE\n");
	  printf("Se han agotado los marcos de pagina\n\n");
	  break;
	}
      else
	{
	  printf("\nProceso %d", procPaginacion.id);
	  printf("\nTamanio %d KB", procPaginacion.tam);
	  printf("\nPaginas %d", procPaginacion.paginas);
	}

      marcos -= pagProc;
      printf("\nMarcos disponibles: %d\n", marcos);
    }
}

proceso crear_proceso(int _id, int _tam, int _paginas)
{
  proceso nuevo;

  nuevo.id = _id;
  nuevo.tam = _tam;
  nuevo.paginas = _paginas;

  return nuevo;
}
