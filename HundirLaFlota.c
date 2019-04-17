/**
* Autor: Adrián Pérez García
**/

#include <stdio.h>
#include <stdlib.h>

void desplegarCabecera();
int menu();

int main(int argc, char const *argv[]){
	int opcion;
	desplegarCabecera();
	//Recojo la opcion del menu y ejecuto el modo de juego escogido;
	opcion = menu();
	switch(opcion){
		case 1:

		break;
		case 2:

		break;
		default:
		printf("Error: Unexpected\n");
		return (-1);
	}
	return 0;
}

void desplegarCabecera{
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