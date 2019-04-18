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
void colocarBarcosManual(int *tablero, int filas, int columnas);
void colocarBarcosAuto(int *tablero, int filas, int columnas);
void imprimirMatriz(int *matrizp, int filasp, int columnasp);

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
	int colocacion, final;
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
	do{
		printf("¿Como desea colocar los barcos %s?\n", jugador.nombre);
		printf("[1] - De forma manual\n");
		printf("[2] - Aleatoriamente\n");
		printf("Nota: Los barcos de %s siempre seran colocados de forma aleatoria.\n", bot1.nombre);
		scanf("%d", &colocacion);
		switch(colocacion){
			case 1:
				colocarBarcosManual(jugador.tableroPropio, filas, columnas);, int filas, int columnas
			break;
			case 2:
				colocarBarcosAuto(jugador.tableroPropio, filas, columnas);, int filas, int columnas
			break;
			default:
				printf("Error: Opción incorrecta\n");
				printf("Introduce un valor del 1 a 2\n");
				printf("Relanzado menu\n");
			break;
		}
	}while( (colocacion!=1) && (colocacion!=2) );
	colocarBarcosAuto(bot1.tableroPropio);
	//Convierto los tableros generados a tableros rivales para el otro
	bot1.tableroPropio = jugador.tableroRival;
	jugador.tableroRival = bot1.tableroPropio;
	printf("Tableros generados, da comiezo el juego.\n");

	//Libero todos los punteros tras el juego por si se repite la partida
	free(jugador.tableroPropio);
	free(jugador.tableroRival);
	free(bot1.tableroPropio);
	free(bot1.tableroRival);
}

void inicializarTablero(int *tablero, int filas, int columnas){
	int i=0;
	//Igualo a 0 todas las posiciones del puntero con un bucle for
	for (i = 0; i < (filas*columnas); i++){
		*(tablero+i) = 0;
	}
}

void colocarBarcosManual(int *tablero, int filas, int columnas){
	int barcos1=4, barcos2=2, barcos3=1;
	//Menu para colocar los barcos que varía según se van acabando los tipos de barcos
	printf("El estado actual del tablero es:\n");
	imprimirMatriz(*tablero, filas, columnas);
	printf("\n¿Que barco deseas colocar?\n");
	while( (barcos1>0) && (barcos2>0) && (barcos3>0) ){
		contador = 1;
		while(barcos1>0){
			printf("[%d] - Barco de 1 (Barcos restantes: %d)\n", contador, barcos1);
			contador++;
		}
		while(barcos2>0){
			printf("[%d] - Barco de 2 (Barcos restantes: %d)\n", contador, barcos2);
			contador++;
		}
		while(barcos3>0){
			printf("[%d] - Barco de 3 (Barcos restantes: %d)\n", contador, barcos3);
			contador++;
		}
		printf("Nota: Los barcos de 2 o más espacios siempre se colocaran arriba y a la derecha según la orientación.\n");
		scanf("%d",&seleccionador);
		switch(seleccionador){
			case 1:
			int avanze = colocarBarcos1()
		}
	}
}

void colocarBarcosAuto(int *tablero, int filas, int columnas){
	*(tablero+(rand()*(filas*columnas))) = 1;
	//Genero un numero aleatorio entre los valores del tablero para colocar el barco de 1
}

void imprimirMatriz(int *matrizp, int filasp, int columnasp){
	int i,j,k, contador = 1;
	for (k = 0; k < count; k++){
		printf("%d\t", contador);
		contador++;
	}
	printf("\n");
	contador = 1;
	for (j = 0; j < filasp ; j++){
		printf("%d\t", contador);
		for (i = 0; i < columnasp; i++){
			printf("%d\t",*(matrizp+i*filasp+j));
		}
		printf("\n");
		contador++;
	}
}

void colocarBarcos1(){
	do{
					printf("Indique la posicion en la que quieras colocar el barco en el eje vertical:\n");
					scanf
				}
}