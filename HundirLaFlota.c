/**
* Autor: Adrián Pérez García
**/

/**
* Objetivo Actual:
* Montando la estructura del Main y los menus antes de empezar a trabajar con los punteros
**/

// Inclusión de todas las constantes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Definición de la estructura del jugador
struct Jugador{
	char nombre[30];
	int *tableroPropio, *tableroRival;
};

// Prototipos de todas las funciones
void desplegarCabecera();
int menu();
void jugarSolo(int filas, int columnas);
void jugarEntreMaquinas(int filas, int columnas);
void inicializarTablero(int *tablero, int filas, int columnas);

// Main con las llamadas a las funciones necesarias para el juego
int main(int argc, char const *argv[]){
	if (argc != 3){
		printf("Error: Parametros incorrectos.\n");
		printf("Se debe enviar solamente las filas y columnas que tendra el tablero en ese orden.\n");
		return -1;
	}
	int filas = atoi(argv[1]), columnas = atoi(argv[2]);
	else{
		if ( (filas < 6) || (columnas < 6) ){
			printf("Error: Parametros incorrectos.\n");
			printf("El numero de filas y columnas debe ser mayor que cinco para poder jugar.\n");
			return -1;
		}
	}
	srand(time(NULL));
	int opcion;
	desplegarCabecera();
	//Recojo la opcion del menu y ejecuto el modo de juego escogido;
	do
		opcion = menu();
		switch(opcion){
			case 1:
			jugarSolo(filas, columnas);
			break;
			case 2:
			jugarEntreMaquinas(filas, columnas);
			break;
			default:
			printf("Error: Unexpected\n");
			opcion = -1;
		}
	while(opcion != -1);
	return 0;
}

// Funciones en el mismo orden que estaban definidas
void desplegarCabecera(){
	printf("---------------------\n");
	printf("|  Hundir la Flota  |\n");
	printf("---------------------\n");
	printf("\t\t\t Adrián Pérez\n");
	printf("\n");
}

int menu(){
	int opcion;
	do{
		printf("Introduce una opción para comenzar el juego:\n");
		printf("[1] - Player VS IA\n");
		printf("[2] - IA VS IA\n");
		printf("[3] - Salir\n");
		scanf("%d", &opcion);
		switch(opcion){
			case 1: case 2:
				break;
			case 3:
				return 0;
			break;
			default:
				printf("Error: Opción no valida.\n"); 
				printf("Relanzado menu.\n");
				printf("\n");
			break;
		}
	}while( (opcion!=1) && (opcion!=2) && (opcion!=3));
	return opcion;
}

void jugarSolo(int filas, int columnas){
	struct Jugador jugador, bot1;
	//Inicializo los nombres y reservo la memoria para tableros de cada una de las estructuras
	printf("Introduzca su nombre (Máx 30 caracteres): ");
	jugador.nombre = fgets(nombre, 30, stdin);
	bot1.nombre = "Bot";
	printf("Dara comienzo la batalla entre %s y %s.\n", jugador.nombre, bot1.nombre);
	jugador.tableroPropio = (int*)malloc(sizeof(int)*filas*columnas);
	jugador.tableroRival = (int*)malloc(sizeof(int)*filas*columnas);
	bot1.tableroPropio = (int*)malloc(sizeof(int)*filas*columnas);
	bot1.tableroRival = (int*)malloc(sizeof(int)*filas*columnas);
	//Inicializo a cero todas las posiciones de los tableros
	inicializarTablero(jugador.tableroPropio);
	inicializarTablero(jugador.tableroRival);
	inicializarTablero(bot1.tableroPropio);
	inicializarTablero(bot1.tableroRival);

}

void inicializarTablero(int *tablero, int filas, int columnas){
	int i=0;
	//Igualo a 0 todas las posiciones del puntero con un bucle for
	for (i = 0; i < (filas*columnas); i++){
		*(tablero+i) = 0;
	}
}