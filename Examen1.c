/*
PRIMER EXAMEN -- SISTEMAS OPERATIVOS
Elliot Duran Macedo 25/10/2021
*/


#include <stdio.h>
#include <stdlib.h>

#define MEM_TOTAL 4096
#define MEM_BASE 640
#define MEM_PROG 384
#define MEM_DISP 3072

#define TRUE 1
#define FALSE !TRUE

typedef struct {
  char *id;
  int tam;
  int paginas;
  int sDatos;
  int sCodigo;
  int sPila;
} proceso;

void menu();
void particion_estatica();
void particion_dinamica();
void paginacion();
void segmentacion();

char *conversor(int numero);
char *concatenar(char *cadena, char caracter);

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
  printf("Memoria total: %d KB\n\n", MEM_TOTAL);
  printf("Memoria base: %d KB\n", MEM_BASE);
  printf("Memoria programas: %d KB\n", MEM_PROG);
  printf("Memoria disponible: %d KB\n\n", MEM_DISP);
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
      else if(opcion == 4)
	{
	  segmentacion();
	  break;
	}
      else if(opcion == 5)
	{
	  break;
	}
      else
	{
	  printf("Por favor seleccione una opcion valida: ");
	  scanf("%d", &opcion);
	}
    }
}

void particion_estatica()
{
  int memRestante = MEM_DISP;
  int numParticiones;
  int tamParticion;
  int idx;
  int contador = 0;
  int bandera = TRUE;
  proceso procEst;
    
  printf("\n------ PARTICIONAMIENTO ESTATICO ------\n\n");
  printf("Memoria disponible: %d KB\n\n", memRestante);
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
	  printf("El tamanio de la particion supera el de la memoria disponible\n\n");
	  break;
	}
      
      memRestante -= tamParticion;
      printf("Memoria disponible: %d KB\n", memRestante);
      listaParticiones[idx] = tamParticion;
    }

  while(TRUE)
    {
      printf("\nIngrese el tamanio del proceso: ");
      scanf("%d", &procEst.tam);
      procEst.id = conversor(rand() % 100);

      if(contador == numParticiones)
	{
	  printf("\nMEMORIA INSUFICIENTE\n");
	  printf("Se han utilizado todas las particiones disponibles\n\n");
	  break;
	}

      for(idx = 0; idx < numParticiones; idx++)
	{
	  if(procEst.tam <= listaParticiones[idx])
	    {
	      printf("\nProceso %s\n", procEst.id);
	      printf("Tamanio %d KB\n\n", procEst.tam);

	      listaParticiones[idx] = -1;
	      contador++;
	      bandera = FALSE;

	      break;
	    }
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
  int memRestante = MEM_DISP;
  proceso procDin;

  printf("\n------ PARTICIONAMIENTO DINAMICO ------\n\n");
  printf("Memoria disponible: %d KB\n", memRestante);

  while(TRUE)
    {
      if(memRestante == 0)
	{
	  printf("\nMEMORIA INSUFICIENTE\n");
	  printf("Se ha agotado la memoria\n\n");
	  break;
	} 
          
      printf("\nIngrese el tamanio del proceso: ");
      scanf("%d", &procDin.tam);

      if(memRestante < procDin.tam)
	{
	  printf("\nMEMORIA INSUFICIENTE\n");
	  printf("Se ha agotado la memoria\n\n");
	  break;
	}
      else
	{
	  procDin.id = conversor(rand() % 100);

	  printf("\nProceso %s\n", procDin.id);
	  printf("Tamanio            %d KB\n", procDin.tam);

	  memRestante -= procDin.tam;
	  printf("Memoria disponible %d KB\n\n", memRestante);
	}
    }
}

void paginacion()
{
  int memRestante = MEM_DISP;
  int paginas;
  int marcos;
  proceso procPag;

  printf("\n------ PAGINACION DE MEMORIA ------\n\n");
  printf("El sistema operativo maneja los siguientes tamanios de paginacion:\n");
  printf("4 KB\t8 KB\t16 KB\t32 KB\n\n");
  printf("De que tamanio desea las paginas? ");
  scanf("%d", &paginas);

  marcos = memRestante / paginas;
  printf("Total de marcos de pagina: %d\n", marcos);

  while(TRUE)
    {
      if(marcos == 0)
	{
	  printf("\nMEMORIA INSUFICIENTE\n");
	  printf("Se han agotado los marcos de pagina\n\n");
	  break;
	}
            
      printf("\nIngrese el tamanio del proceso: ");
      scanf("%d", &procPag.tam);

      procPag.id = conversor(rand() % 100);

      if(procPag.tam <= paginas)
	{
	  procPag.paginas = 1;
	}
      else
	{
	  procPag.paginas = procPag.tam / paginas;
	}
	  
      if(marcos-procPag.paginas < 0)
	{
	  printf("\nMEMORIA INSUFICIENTE\n");
	  printf("Se han agotado los marcos de pagina\n\n");
	  break;
	}
      else
	{
	  printf("\nProceso %s\n", procPag.id);
	  printf("\nTamanio %d KB", procPag.tam);
	  printf("\nPaginas %d\n", procPag.paginas);
	}

      marcos -= procPag.paginas;
      printf("\nMarcos disponibles  %d\n\n", marcos);
    }
}

void segmentacion()
{
  int memRestante = MEM_DISP;
  proceso procSeg;

  printf("\n------ SEGMENTACION DE MEMORIA ------\n\n");
  printf("Memoria disponible: %d KB\n\n", memRestante);

  while(TRUE)
    {
      if(memRestante == 0)
	{
	  printf("\nMEMORIA INSUFICIENTE\n");
	  printf("Se ha agotado la memoria\n\n");
	  break;
	} 
      
      printf("Ingrese el tamanio del proceso: ");
      scanf("%d", &procSeg.tam);

      if(memRestante < procSeg.tam)
	{
	  printf("\nMEMORIA INSUFICIENTE\n");
	  printf("Se ha agotado la memoria\n\n");
	  break;
	}
      else
	{
	  procSeg.id = conversor(rand() % 100);
	  procSeg.sDatos = procSeg.tam * 0.3;
	  procSeg.sCodigo = procSeg.tam * 0.5;
	  procSeg.sPila = procSeg.tam * 0.2;

	  printf("\nProceso %s\n\n", procSeg.id);
	  printf("Tamanio             %d KB\n", procSeg.tam);
	  printf("Segmento de datos   %d KB\n", procSeg.sDatos);
	  printf("Segmento de codigo  %d KB\n", procSeg.sCodigo);
	  printf("Segmento de pila    %d KB\n\n", procSeg.sPila);

	  memRestante -= procSeg.tam;
	  printf("Memoria disponible  %d KB\n\n", memRestante);
	}
    }
}

char *conversor(int numero)
{
  char *binario = "";
  char c;
  
  if(numero > 0)
    {
      while(numero > 0)
	{
	  if(numero % 2 == 0)
	    {
	      c = '0';
	      binario = concatenar(binario, c);
	    }
	  else
	    {
	      c = '1';
	      binario = concatenar(binario, c);
	    }

	  numero = (int) numero / 2;
	}
    }
  else
    {
      binario = "0";
    }

   return binario;
}

char *concatenar(char *cadena, char caracter)
{
  char *aux;
  int i;
  int longitud = 0;

  while(cadena[++longitud] != 0);
  
  aux = (char*)malloc(longitud + 2);
  aux[0] = caracter;

  for(i = 1; cadena[i-1] != '\0'; i++)
    {
      aux[i] = cadena[i-1];
    }

  aux[i++] = '\0';

  return aux; 
}
