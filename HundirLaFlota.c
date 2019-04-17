/**
* Autor: Adrián Pérez García
**/

/**
* Commit Actual:
* Montando la estructura del Main y los menus antes de empezar a trabajar con los punteros
**/

// Inclusión de todas las constantes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Prototipos de todas las funciones
void desplegarCabecera();
int menu();
void jugarSolo();
void jugarEntreMaquinas();

// Main con las llamadas a las funciones necesarias para el juego
int main(int argc, char const *argv[]){
	int opcion;
	desplegarCabecera();
	//Recojo la opcion del menu y ejecuto el modo de juego escogido;
	do
		opcion = menu();
		switch(opcion){
			case 1:
			jugarSolo();
			break;
			case 2:
			jugarEntreMaquinas();
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