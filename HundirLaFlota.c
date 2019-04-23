/**
* Autor: Adrián Pérez García
**/

/**
* Objetivo Actual:
* Imprimir en Archivo
**/

// Inclusión de todas las constantes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Definición de la estructura del jugador
struct Jugador{
	int *tableroPropio;
};

// Prototipos de todas las funciones
void desplegarCabecera();
int menu();
int volverAJugar();
void jugarSolo(int filas, int columnas);
void jugarEntreMaquinas(int filas, int columnas);
void inicializarTablero(int *tablero, int filas, int columnas);
void colocarBarcosManual(int *tablero, int filas, int columnas);
void colocarBarcosAuto(int *tablero, int filas, int columnas);
void imprimirMatriz(int *matrizp, int filasp, int columnasp);
void colocarBarcos1(int *tablero, int filas, int columnas);
void colocarBarcos2(int *tablero, int filas, int columnas);
void colocarBarcos3(int *tablero, int filas, int columnas);
int partidaFinalizada(int *tablero, int filas, int columnas);
void imprimirTableroRival(int *tablero,int filas,int columnas);
void imprimirJugadaArchivo(int i, int j, int posDir, int contador, FILE *archivo);
void imprimirTableroArchivo(int *tablero, int filas, int columnas, FILE *archivo);
void juegoNuevoArchivo(FILE *archivo);

// Main con las llamadas a las funciones necesarias para el juego
int main(int argc, char const *argv[]){
	if (argc != 3){
		printf("Error: Parametros incorrectos.\n");
		printf("Se debe enviar solamente las filas y columnas que tendra el tablero en ese orden.\n");
		return -1;
	}
	else{
		if ( (atoi(argv[1]) < 6) || (atoi(argv[2]) < 6) ){
			printf("Error: Parametros incorrectos.\n");
			printf("El numero de filas y columnas debe ser mayor que cinco para poder jugar.\n");
			return -1;
		}
	}
	//Limpio el archivo antes de empezar a escribirlo
	FILE *file;
	file = fopen("Log.txt", "w");
	fclose(file);
	//Cambio la semilla de generación de numeros aleatorios
	srand(time(NULL));
	int filas = atoi(argv[1]), columnas = atoi(argv[2]);
	int opcion;
	//Recojo la opcion del menu y ejecuto el modo de juego escogido junto a la opcion de volver a jugar
	do{
		desplegarCabecera();
		opcion = menu();
		switch(opcion){
			case 1:
				jugarSolo(filas, columnas);
				opcion = volverAJugar(file);
			break;
			case 2:
				jugarEntreMaquinas(filas, columnas);
				opcion = volverAJugar(file);
			break;
			case 3:
				opcion = -1;
			break;
			default:
			printf("Error: Unexpected\n");
			opcion = -1;
		}
	}while(opcion != -1);
	printf("Cerrando aplicación.\n");
	return 0;
}

// Funciones en el mismo orden que estaban definidas
void desplegarCabecera(){ 
	printf("╔╦╗╔╦═════╦╦╦══╦╦══╦═╦╦══╦╦═══╗\n");
	printf("║║╚╝╠╗╔╦═╦╝╠╬═╗║╠═╗║═╣╠═╦╣╠╦═╗║\n");
	printf("║║╔╗║╚╝║║║║║║╠╝║╠╝║║╔╣║║╠╗╔╬╝║║\n");
	printf("║╚╝╚╩══╩╩╩═╩╩╝ ╚╩═╝╚╝╚╩═╝╚═╩═╝║\n");
	printf("╚═════════════════════════════╝\n");  
	printf("Adrián Pérez García - 2019\n\n");                                                                                                                        
}

int menu(){
	int opcion;
	do{
		printf("Introduce una opción para comenzar el juego:\n");
		printf("[1] - Player VS IA\n");
		printf("[2] - IA VS IA\n");
		printf("[3] - Salir\n");
		scanf("%d", &opcion);
		if ( (opcion!=1) && (opcion!=2) && (opcion!=3) ){
			printf("Error: Opción no valida.\n"); 
			printf("Relanzado menu.\n");
			printf("\n");
		}
	}while( (opcion!=1) && (opcion!=2) && (opcion!=3));
	return opcion;
}

int volverAJugar(FILE *file){
	file = fopen("Log.txt", "at");
	int seleccionador;
	do{
		printf("\n¿Quiere volver a jugar?\n");
		printf("[1] - Si\n");
		printf("[2] - No\n");
		scanf("%d", &seleccionador);
		switch(seleccionador){
			case 1:
				printf("Volviendo a jugar.\n\n");
				seleccionador = 0;
				juegoNuevoArchivo(file);
			break;
			case 2:
				seleccionador = -1;
			break;
			default:
				printf("Error: Opción no valida.\n");
				printf("Relanzando menu\n");
				seleccionador = 1;
			break;
		}
	}while( (seleccionador!=0) && (seleccionador!=-1));
	return seleccionador;
}

void imprimirMatriz(int *matrizp, int filasp, int columnasp){
	int i,j,k, contador = 1;
	for (k = 0; k <= columnasp; k++){
		printf("%d\t", k);
	}
	printf("\n\n");
	for (i = 0; i < filasp ; i++){
		printf("%d\t", contador);
		for (j = 0; j < columnasp; j++){
			printf("%d\t",*(matrizp+(i*columnasp)+j));
		}
		printf("\n\n");
		contador++;
	}
}

void inicializarTablero(int *tablero, int filas, int columnas){
	int i=0;
	//Igualo a 0 todas las posiciones del puntero con un bucle for
	for (i = 0; i < (filas*columnas); i++){
		*(tablero+i) = 0;
	}
}

void jugarSolo(int filas, int columnas){
	FILE *file;
	file = fopen("log.txt", "at");
	struct Jugador jugador, bot1;
	int colocacion;
	char *nombreJug=(char*)malloc(sizeof(char)*20);
	printf("Introduzca su nombre [Max 20 caracteres]: ");
	scanf(" %s", nombreJug);
	//Inicializo los nombres y reservo la memoria para tableros de cada una de las estructuras
	printf("\nDara comienzo la batalla entre %s y Bot1.\n\n", nombreJug);
	fprintf(file, "Comiezo del juego manual\n");
	fprintf(file, "Partido entre %s y Bot1\n",nombreJug);
	jugador.tableroPropio = (int*)malloc(sizeof(int)*filas*columnas);
	bot1.tableroPropio = (int*)malloc(sizeof(int)*filas*columnas);
	//Inicializo a cero todas las posiciones de los tableros
	inicializarTablero(jugador.tableroPropio, filas, columnas);
	inicializarTablero(bot1.tableroPropio, filas, columnas);
	//Menu para seleccionar que funcion se usara para colocar los barcos
	do{
		printf("¿Como desea colocar los barcos %s?\n", nombreJug);
		printf("[1] - De forma manual\n");
		printf("[2] - Aleatoriamente\n");
		printf("Nota: Los barcos de Bot1 siempre seran colocados de forma aleatoria.\n");
		scanf("%d", &colocacion);
		switch(colocacion){
			case 1:
				colocarBarcosManual(jugador.tableroPropio, filas, columnas);
			break;
			case 2:
				colocarBarcosAuto(jugador.tableroPropio, filas, columnas);
				printf("Su tablero ha sido generado de la siguiente forma: \n");
				imprimirMatriz(jugador.tableroPropio, filas, columnas);
			break;
			default:
				printf("Error: Opción incorrecta\n");
				printf("Introduce un valor del 1 a 2\n");
				printf("Relanzado menu\n");
			break;
		}
	}while( (colocacion!=1) && (colocacion!=2) );
	//Se generar los barcos del bot de forma automática
	colocarBarcosAuto(bot1.tableroPropio, filas, columnas);
	printf("Barcos de Bot1 generados automaticamente\n\n");
	//Comienzo del juego en si
	desplegarCabecera();
	fprintf(file, "Tablero de %s:\n", nombreJug);
	imprimirTableroArchivo(jugador.tableroPropio, filas, columnas, file);
	fprintf(file, "Tablero de Bot1:\n");
	imprimirTableroArchivo(bot1.tableroPropio, filas, columnas, file);
	printf("Tableros generados, da comiezo el juego entre %s y Bot1.\n", nombreJug);
	printf("Leyenda:\n");
	printf("Las casillas de valor 0 simbolizaran agua.\n");
	printf("Las casillas de valor 8 simbolizaran agua ya disparada.\n");
	printf("Las casillas de valor 1 o -1 simbolizaran barcos de 1 posicion intactos o disparados respectivamente.\n");
	printf("Las casillas de valor 2 o -2 simbolizaran barcos de 2 posiciones intactos o disparados respectivamente.\n");
	printf("Las casillas de valor 3 o -3 simbolizaran barcos de 3 posiciones intactos o disparados respectivamente.\n");
	printf("Las casillas de valor ? simbolizaran posiciones del tablero con valor desconocido.\n");
	//Da comienzo el bucle que decide la partida
	int valido = 0, ii, jj, posDir = 0, contador = 0, avanceMax = 1, avance = 1, i, j, opcion;
	while((partidaFinalizada(jugador.tableroPropio, filas, columnas) != 1) && (partidaFinalizada(bot1.tableroPropio, filas, columnas) != 1)){
		if((contador%2) == 0){
			printf("Turno para %s.\n", nombreJug);
			printf("La situacion de los tableros es la siguiente:\n\n");
			printf("Tablero de %s\n", nombreJug);
			imprimirMatriz(jugador.tableroPropio, filas, columnas);
			printf("\nTablero de Bot1\n");
			imprimirTableroRival(bot1.tableroPropio, filas, columnas);
			do{
			avanceMax=1;
				do{
					avance = 1;
					printf("Indique la posicion de disparo en el eje horizontal:\n");
					scanf("%d", &j);
					j--;
					if ( (j<0) || (j>=columnas) ){
						printf("Error: posición no valida.\n");
						printf("La posición no puede ser menor que 0 o mayor que el numero de columnas establecidas.\n");
						printf("Relanzando menu.\n");
						avance = 0;
					}
				}while(avance!=1);
				do{	
					printf("Indique la posicion de disparo en el eje vertical:\n");
					scanf("%d", &i);
					i--;
					if ( (i<0) || (i>=filas) || ( *(bot1.tableroPropio+(i*columnas)+j) == 8 || *(bot1.tableroPropio+(i*columnas)+j) < 0)){
						printf("Error: posición no valida.\n");
						if( *(bot1.tableroPropio+(i*columnas)+j) == 8 || *(bot1.tableroPropio+(i*columnas)+j) < 0){
							printf("Esa posición ya fue disparada.\n");
							do{
								printf("¿Que acción desea realizar?\n");
								printf("[1] - Cambiar posicion dentro de la misma columna\n");
								printf("[2] - Cambiar posicion completa\n");
								scanf("%d", &opcion);
								switch(opcion){
									case 1:
									avance = 0;
									break;
									case 2:
									avanceMax = 0;
									break;
									default:
										printf("Error: Opción no valida.\n");
										printf("Relanzando menu.\n");
									break;
								}
							}while( (opcion!=1) && (opcion!=2) );
						}
						else{
							printf("La posición no puede ser menor que 0 o mayor que el numero de filas establecidas.\n");
							printf("Relanzando menu.\n");
							avance = 0;
						}
					}
					else{
						avance = 1;
					}
				}while(avance!=1);
		}while(avanceMax!=1);
			posDir = *(bot1.tableroPropio+(i*columnas)+j);
			switch(posDir){
				case 0:
					printf("AGUA\n");
					*(bot1.tableroPropio+(i*columnas)+j) = 8;
				break;
				case 1:
					printf("TOCADO\n");
					printf("Barco de 1\n");
					*(bot1.tableroPropio+(i*columnas)+j) = -1;
				break;
				case 2:
					printf("TOCADO\n");
					printf("Barco de 2\n");
					*(bot1.tableroPropio+(i*columnas)+j) = -2;
				break;
				case 3:
					printf("TOCADO\n");
					printf("Barco de 3\n");
					*(bot1.tableroPropio+(i*columnas)+j) = -3;
				break;
				default:
					printf("Error: Unexpected\n");
				break;
			}
			fprintf(file, "Turno de %s (Numero de %d)\n", nombreJug,contador);
			imprimirJugadaArchivo(i, j, posDir, contador, file);
		}
		else{
			printf("Turno para Bot1.\n");
			valido = 0;
			do{
				ii = 1+rand()%(filas+1);
				jj = 1+rand()%(columnas+1);
				printf("Generada aleatoriamente la posición (%d,%d)\n",(ii),(jj));
				ii--;
				jj--;
				if (*(jugador.tableroPropio+(ii*columnas)+jj)>=0 && *(jugador.tableroPropio+(ii*columnas)+jj)!=8){
					valido = 1;
				}
				else{
					valido = 0;
				}
			} while (valido!=1);
			posDir = *(jugador.tableroPropio+(ii*columnas)+jj);
			switch(posDir){
				case 0:
					printf("AGUA\n");
					*(jugador.tableroPropio+(ii*columnas)+jj) = 8;
				break;
				case 1:
					printf("TOCADO\n");
					printf("Barco de 1\n");
					*(jugador.tableroPropio+(ii*columnas)+jj) = -1;
				break;
				case 2:
					printf("TOCADO\n");
					printf("Barco de 2\n");
					*(jugador.tableroPropio+(ii*columnas)+jj) = -2;
				break;
				case 3:
					printf("TOCADO\n");
					printf("Barco de 3\n");
					*(jugador.tableroPropio+(ii*columnas)+jj) = -3;
				break;
				default:
					printf("Error: Unexpected\n");
				break;
			}
			printf("\n");
			fprintf(file, "Turno de %s (Numero de %d)\n", nombreJug,contador);
			imprimirJugadaArchivo(ii, jj, posDir, contador, file);
		}
		contador++;
	}
	printf("\n\nFINAL (%d turnos)\n", contador);
	fprintf(file, "Final del partido (%d turnos)", contador);
	if( (contador%2) != 0 ){
		printf("El ganador del partido es %s.\n\n", nombreJug);
		fprintf(file, "Ha ganado %s\n", nombreJug);
	}
	else{
		printf("El ganado del partido es Bot1.\n\n");
		fprintf(file, "Ha ganado Bot1\n");
	}
}

void colocarBarcosManual(int *tablero, int filas, int columnas){
	int barcos1=4, barcos2=2, barcos3=1, contador, seleccionador;
	//Menu para colocar los barcos que varía según se van acabando los tipos de barcos
	while( (barcos1>0) || (barcos2>0) || (barcos3>0) ){
		contador = 1;
		printf("El estado actual del tablero es:\n\n");
		imprimirMatriz(tablero, filas, columnas);
		printf("\n\n¿Que barco deseas colocar?\n");
		if(barcos1>0){
			printf("[%d] - Barco de 1 (Barcos restantes: %d)\n", contador, barcos1);
			contador++;
		}
		if(barcos2>0){
			printf("[%d] - Barco de 2 (Barcos restantes: %d)\n", contador, barcos2);
			contador++;
		}
		if(barcos3>0){
			printf("[%d] - Barco de 3 (Barcos restantes: %d)\n", contador, barcos3);
			contador++;
		}
		printf("Nota: Los barcos de 2 o más espacios siempre se colocaran arriba y a la derecha según la orientación.\n");
		scanf("%d",&seleccionador);
		switch(seleccionador){
			case 1:
				if (barcos1>0){
					colocarBarcos1(tablero, filas, columnas);
					barcos1--;
				}
				else{
					if(barcos2>0){
						colocarBarcos2(tablero, filas, columnas);
						barcos2--;
					}
					else{
						if(barcos3 > 0){
							colocarBarcos3(tablero, filas, columnas);
							barcos3--;
						}
						else{
							printf("Error: Opción no valida\n");
							printf("Relanzando menu\n");	
						}
					}
				}
			break;
			case 2:
				if (barcos1 > 0 && barcos2 > 0){
					colocarBarcos2(tablero, filas, columnas);
					barcos2--;
				}
				else{
					if (barcos1 > 0 && barcos2 < 0 && barcos3 > 0){
						colocarBarcos3(tablero, filas, columnas);
						barcos3--;
					}
					else{
						if (barcos1 < 0 && barcos2 >0){
							colocarBarcos3(tablero,filas,columnas);
							barcos3--;
						}
						else{
							printf("Error: Opción no valida\n");
							printf("Relanzando menu\n");
						}
					}
				}
			break;
			case 3:
				if(barcos1 > 0 && barcos2 > 0){
					colocarBarcos3(tablero, filas, columnas);
					barcos3--;
				}
				else{
					printf("Error: Opción no valida\n");
					printf("Relanzando menu\n");
				}
			break;
			default:
				printf("Error: Opción no valida\n");
				printf("Relanzando menu\n");
			break;
		}
	}
}

void colocarBarcos1(int *tablero, int filas, int columnas){
	int j, i, avance = 1, avanceMax = 1, opcion;
	do{
		avanceMax=1;
		do{
			avance = 1;
			printf("Indique la posicion en la que quieras colocar el barco en el eje horizontal:\n");
			scanf("%d", &j);
			j--;
			if ( (j<0) || (j>=filas) ){
				printf("Error: posición no valida.\n");
				printf("La posición no puede ser menor que 0 o mayor que el numero de columnas establecidas.\n");
				printf("Relanzando menu.\n");
				avance = 0;
			}
		}while(avance!=1);
		do{	
			printf("Indique la posicion en la que quieras colocar el barco en el eje vertical:\n");
			scanf("%d", &i);
			i--;
			if ( ((i<0) || (i>=columnas)) || (*(tablero+(i*columnas)+j) != 0)){
				printf("Error: posición no valida.\n");
				if( *(tablero+(i*columnas)+j) != 0 ){
					printf("Esa posición ya esta ocupada.\n");
					do{
						printf("¿Que acción desea realizar?\n");
						printf("[1] - Cambiar posicion dentro de la misma columna\n");
						printf("[2] - Cambiar posicion completa\n");
						scanf("%d", &opcion);
						switch(opcion){
							case 1:
							avance = 0;
							break;
							case 2:
							avanceMax = 0;
							break;
							default:
								printf("Error: Opción no valida.\n");
								printf("Relanzando menu.\n");
							break;
						}
					}while( (opcion!=1) && (opcion!=2) );
				}
				else{
					printf("La posición no puede ser menor que 0 o mayor que el numero de filas establecidas.\n");
					printf("Relanzando menu.\n");
					avance = 0;
				}
			}
			else{
				avance = 1;
			}
		}while(avance!=1);
	}while(avanceMax!=1);
	*(tablero+(i*columnas)+j) = 1;
	printf("Barco de 1 establecido en la posicion (%d,%d).\n", (i+1), (j+1));
}

void colocarBarcos2(int *tablero, int filas, int columnas){
	int orientacion;
	do{
		printf("¿Como desea colocar los barcos?\n");
		printf("[1] - Horizontalmente\n");
		printf("[2] - Verticalmente\n");
		scanf("%d", &orientacion);
		if ((orientacion!=1 && orientacion!=2)){
			printf("Error: Valor no valido\n");
			printf("Relanzando menu\n");
		}
	}while( (orientacion!=1 && orientacion!=2) );
	int i, j, avance, avanceMax, opcion, i2, j2;
	do{
		avanceMax=1;
		do{
			avance = 1;
			printf("Indique la posicion en la que quieras colocar el barco en el eje horizontal:\n");
			scanf("%d", &j);
			j--;
			if ( (j<0) || (j>=filas) ){
					printf("Error: posición no valida.\n");
					printf("La posición no puede ser menor que 0 o mayor que el numero de columnas establecidas.\n");
					printf("Relanzando menu.\n");
					avance = 0;
			}

			if(orientacion == 1){
				if ( j == (columnas-1) ){
					printf("Error: posición no valida.\n");
					printf("Has seleccionado orientacion horizontal, por lo que no se puede colocar en la ultima columna.\n");
					printf("Relanzando menu.\n");
					avance = 0;
				}
			}
		}while(avance!=1);
		do{	
			avance = 1;
			printf("Indique la posicion en la que quieras colocar el barco en el eje vertical:\n");
			scanf("%d", &i);
			i--;
			if (orientacion == 2){
				if (i == 0){
					printf("Error: posición no valida\n");
					printf("Has seleccionado orientacion vertical, por lo que no se puede colocar en la primera fila.\n");
					avance = 0;
				}
			}
			if (orientacion == 2){
			if (*(tablero+(i*columnas)+j) !=0 || *(tablero+((i-1)*columnas)+j) != 0){
				printf("Error: posición no valida\n");
				printf("Alguna de las posiciones ya esta ocupada.\n");
				do{
					printf("¿Que acción desea realizar?\n");
					printf("[1] - Cambiar posicion dentro de la misma columna\n");
					printf("[2] - Cambiar posicion completa\n");
					scanf("%d", &opcion);
					switch(opcion){
						case 1:
							avance = 0;
						break;
						case 2:
							avanceMax = 0;
						break;
						default:
							printf("Error: Opción no valida.\n");
							printf("Relanzando menu.\n");
						break;
					}
				}while( (opcion!=1) && (opcion!=2) );
			}
			else{
				if( (i<0) || (i>=filas)){
					printf("La posición no puede ser menor que 0 o mayor que el numero de filas establecidas.\n");
					printf("Relanzando menu.\n");
					avance = 0;
				}
			}
		}
		else{
			if (*(tablero+(i*columnas)+j)!=0 || *(tablero+(i*columnas)+(j+1)) != 0){
					printf("Error: posición no valida\n");
					printf("Alguna de las posiciones ya esta ocupada.\n");
					do{
						printf("¿Que acción desea realizar?\n");
						printf("[1] - Cambiar posicion dentro de la misma columna\n");
						printf("[2] - Cambiar posicion completa\n");
						scanf("%d", &opcion);
						switch(opcion){
							case 1:
								avance = 0;
							break;
							case 2:
								avanceMax = 0;
							break;
							default:
								printf("Error: Opción no valida.\n");
								printf("Relanzando menu.\n");
							break;
						}
					}while( (opcion!=1) && (opcion!=2) );
				}
				else{
					if( (i<0) || (i>=filas)){
						printf("La posición no puede ser menor que 0 o mayor que el numero de filas establecidas.\n");
						printf("Relanzando menu.\n");
						avance = 0;
					}
			}
		}
		}while(avance!=1);
	}while(avanceMax!=1);
	*(tablero+(i*columnas)+j) = 2;
	if (orientacion == 1){
		j2 = j+1;
		i2 = i;
		*(tablero+(i2*columnas)+j2) = 2;
	}
	else{
		j2 = j;
		i2 = i-1;
		*(tablero+(i2*columnas)+j2) = 2;
	}
	printf("Barco de dos posiciones colocado en (%d,%d) y (%d,%d).\n", (i+1), (j+1), (i2+1), (j2+1));
}

void colocarBarcos3(int *tablero, int filas, int columnas){
	int orientacion;
	do{
		printf("¿Como desea colocar los barcos?\n");
		printf("[1] - Horizontalmente\n");
		printf("[2] - Verticalmente\n");
		scanf("%d", &orientacion);
		if ((orientacion!=1 && orientacion!=2)){
			printf("Error: Valor no valido\n");
			printf("Relanzando menu\n");
		}
	}while( (orientacion!=1 && orientacion!=2) );
	int i, j, avance, avanceMax, opcion, i2, j2, i3, j3;
	do{
		avanceMax=1;
		do{
			avance = 1;
			printf("Indique la posicion en la que quieras colocar el barco en el eje horizontal:\n");
			scanf("%d", &j);
			j--;
			if ( (j<0) || (j>=filas) ){
					printf("Error: posición no valida.\n");
					printf("La posición no puede ser menor que 0 o mayor que el numero de columnas establecidas.\n");
					printf("Relanzando menu.\n");
					avance = 0;
			}

			if(orientacion == 1){
				if ( j == (columnas-1)  || j == (columnas-2) ){
					printf("Error: posición no valida.\n");
					printf("Has seleccionado orientacion horizontal, por lo que no se puede colocar en las dos ultimas columnas.\n");
					printf("Relanzando menu.\n");
					avance = 0;
				}
			}
		}while(avance!=1);
		do{	
			avance = 1;
			printf("Indique la posicion en la que quieras colocar el barco en el eje vertical:\n");
			scanf("%d", &i);
			i--;
			if (orientacion == 2){
				if (i == 0 || i == 1){
					printf("Error: posición no valida\n");
					printf("Has seleccionado orientacion vertical, por lo que no se puede colocar en las dos primeras filas.\n");
					avance = 0;
				}
				if (*(tablero+(i*columnas)+j) !=0 || *(tablero+((i-1)*columnas)+j) != 0 || *(tablero+((i-2)*columnas)+j) != 0){
					printf("Error: posición no valida\n");
					printf("Alguna de las posiciones ya esta ocupada.\n");
					do{
						printf("¿Que acción desea realizar?\n");
						printf("[1] - Cambiar posicion dentro de la misma columna\n");
						printf("[2] - Cambiar posicion completa\n");
						scanf("%d", &opcion);
						switch(opcion){
							case 1:
								avance = 0;
							break;
							case 2:
								avanceMax = 0;
							break;
							default:
								printf("Error: Opción no valida.\n");
								printf("Relanzando menu.\n");
							break;
						}
					}while( (opcion!=1) && (opcion!=2) );
				}
				else{
					if( (i<0) || (i>=filas)){
						printf("La posición no puede ser menor que 0 o mayor que el numero de filas establecidas.\n");
						printf("Relanzando menu.\n");
						avance = 0;
					}
				}
			}
			else{
				if (*(tablero+(i*columnas)+j)!=0 || *(tablero+(i*columnas)+(j+1)) != 0 || *(tablero+(i*columnas)+(j+2)) != 0){
						printf("Error: posición no valida\n");
						printf("Alguna de las posiciones ya esta ocupada.\n");
						do{
							printf("¿Que acción desea realizar?\n");
							printf("[1] - Cambiar posicion dentro de la misma columna\n");
							printf("[2] - Cambiar posicion completa\n");
							scanf("%d", &opcion);
							switch(opcion){
								case 1:
									avance = 0;
								break;
								case 2:
									avanceMax = 0;
								break;
								default:
									printf("Error: Opción no valida.\n");
									printf("Relanzando menu.\n");
								break;
							}
						}while( (opcion!=1) && (opcion!=2) );
					}
					else{
						if( (i<0) || (i>=filas)){
							printf("La posición no puede ser menor que 0 o mayor que el numero de filas establecidas.\n");
							printf("Relanzando menu.\n");
							avance = 0;
						}
				}
			}
		}while(avance!=1);
	}while(avanceMax!=1);
	*(tablero+(i*columnas)+j) = 3;
	if (orientacion == 1){
		i2 = i;
		j3 = j+2;
		j2 = j+1;
		*(tablero+(i2*columnas)+j2) = 3;
		*(tablero+(i2*columnas)+j3) = 3;
	}
	else{
		j2 = j;
		i2 = i-1;
		i3 = i-2;
		*(tablero+(i2*columnas)+j2) = 3;
		*(tablero+(i3*columnas)+j2) = 3;
	}
	printf("Barco de dos posiciones colocado en (%d,%d) , (%d,%d) y (%d,%d).\n", (i+1), (j+1), (i2+1), (j2+1), (i3+1), (j3+1));
}

void colocarBarcosAuto(int *tablero, int filas, int columnas){
	int tamanio = filas*columnas;
	//Coloco todos los barcos de 1
	int random, random2, barcos1, barcos2, barcos3;
	barcos1 = 4;
	barcos2 = 2;
	barcos3 = 1;
	while(barcos1>0){
		random = (rand()%tamanio);
		if (*(tablero+random) == 0){
			*(tablero+random) = 1;
			barcos1--;
		}
	}
	//Coloco todos los barcos de 2
	while(barcos2>0){
		random2 = (rand()%2);
		if(random2 == 0){
			//Posición horizontal
			random = (rand()%tamanio);
			if ((random+1-(columnas-1))%(columnas) == 0 || ((random-(columnas-1))%(columnas)) == 0){
				if (*(tablero+random)==0 && *(tablero+random-1)==0){
					*(tablero+random) = 2;
					*(tablero+random-1) = 2;
					barcos2--;
				}
			}
			else{
				if (*(tablero+random)==0 && *(tablero+random+1)==0){
					*(tablero+random) = 2;
					*(tablero+random+1) = 2;
					barcos2--;
				}
			}
		}
		else{
			//Posición vertical
			random = columnas+(rand()%(tamanio-columnas));
			if (*(tablero+random)==0 && *(tablero+random-(columnas))==0){
					*(tablero+random) = 2;
					*(tablero+random-columnas) = 2;
					barcos2--;
				}
		}
	}
	//Coloco todos los barcos de 3
	while(barcos3>0){
		random2 = (rand()%2);
		if(random2 == 0){
			//Posición horizontal
			random = (rand()%tamanio);
			if (((random+1)-(columnas-1))%(columnas) == 0 || ((random+2)-(columnas-1))%(columnas) == 0 || ((random)-(columnas-1))%(columnas) == 0){
				if (*(tablero+random)==0 && *(tablero+random-1)==0 && *(tablero+random-2)==0){
					*(tablero+random) = 3;
					*(tablero+random-1) = 3;
					*(tablero+random-2) = 3;
					barcos3--;
				}
			}
			else{
				if (*(tablero+random)==0 && *(tablero+random+1)==0 && *(tablero+random+2)==0){
					*(tablero+random) = 3;
					*(tablero+random+1) = 3;
					*(tablero+random+2) = 3;
					barcos3--;
				}
			}
		}
		else{
			//Posición vertical
			random = 2*columnas+(rand()%(tamanio-(2*columnas)));
			if (*(tablero+random)==0 && *(tablero+random-columnas)==0 && *(tablero+random-(2*columnas))==0){
					*(tablero+random) = 3;
					*(tablero+random-columnas) = 3;
					*(tablero+random-2*(columnas)) = 3;
					barcos3--;
				}
		}
	}
}

void jugarEntreMaquinas(int filas, int columnas){
	struct Jugador bot1, bot2;
	bot2.tableroPropio = (int*)malloc(sizeof(int)*filas*columnas);
	bot1.tableroPropio = (int*)malloc(sizeof(int)*filas*columnas);
	FILE *file;
	file = fopen("log.txt", "at");
	fprintf(file, "Comienza el juego automatico\n");
	//Inicializo a cero todas las posiciones de los tableros
	inicializarTablero(bot1.tableroPropio, filas, columnas);
	inicializarTablero(bot2.tableroPropio, filas, columnas);
	//Se generar los barcos del bot de forma automática
	colocarBarcosAuto(bot1.tableroPropio, filas, columnas);
	colocarBarcosAuto(bot2.tableroPropio, filas, columnas);
	printf("Barcos de ambos bots generados automaticamente\n\n");
	//Comienzo del juego en si
	desplegarCabecera();
	printf("Tableros generados, da comiezo el juego entre Bot1 y Bot2.\n");
	printf("Leyenda:\n");
	printf("Las casillas de valor 0 simbolizaran agua.\n");
	printf("Las casillas de valor 8 simbolizaran agua ya disparada.\n");
	printf("Las casillas de valor 1 o -1 simbolizaran barcos de 1 posicion intactos o disparados respectivamente.\n");
	printf("Las casillas de valor 2 o -2 simbolizaran barcos de 2 posiciones intactos o disparados respectivamente.\n");
	printf("Las casillas de valor 3 o -3 simbolizaran barcos de 3 posiciones intactos o disparados respectivamente.\n");
	printf("Las casillas de valor ? simbolizaran posiciones del tablero con valor desconocido.\n");
	fprintf(file,"Tablero del Bot1:\n");
	imprimirTableroArchivo(bot1.tableroPropio, filas, columnas, file);
	fprintf(file,"Tablero del Bot2:\n");
	imprimirTableroArchivo(bot2.tableroPropio, filas, columnas, file);
	//Da comienzo el bucle que decide la partida
	int valido = 0, ii, jj, posDir = 0, contador = 0, avanceMax = 1, avance = 1, i, j, opcion;
	while((partidaFinalizada(bot2.tableroPropio, filas, columnas) != 1) && (partidaFinalizada(bot1.tableroPropio, filas, columnas) != 1)){
		if((contador%2) == 0){
			printf("Turno para Bot1.\n");
			valido = 0;
			do{
				ii = 1+rand()%(filas+1);
				jj = 1+rand()%(columnas+1);
				printf("Generada aleatoriamente la posición (%d,%d)\n",(ii),(jj));
				ii--;
				jj--;
				if (*(bot2.tableroPropio+(ii*columnas)+jj)>=0 && *(bot2.tableroPropio+(ii*columnas)+jj)!=8){
					valido = 1;
					printf("Disparando\n");
				}
				else{
					valido = 0;
					printf("No valido, generando otra.\n");
				}
			} while (valido!=1);
			posDir = *(bot2.tableroPropio+(ii*columnas)+jj);
			switch(posDir){
				case 0:
					printf("AGUA\n");
					*(bot2.tableroPropio+(ii*columnas)+jj) = 8;
				break;
				case 1:
					printf("TOCADO\n");
					printf("Barco de 1\n");
					*(bot2.tableroPropio+(ii*columnas)+jj) = -1;
				break;
				case 2:
					printf("TOCADO\n");
					printf("Barco de 2\n");
					*(bot2.tableroPropio+(ii*columnas)+jj) = -2;
				break;
				case 3:
					printf("TOCADO\n");
					printf("Barco de 3\n");
					*(bot2.tableroPropio+(ii*columnas)+jj) = -3;
				break;
				default:
					printf("Error: Unexpected\n");
				break;
			}
			imprimirJugadaArchivo(ii, jj, posDir, contador, file);
			printf("\n");
			contador++;
		}
		else{
			printf("Turno para Bot2.\n");
				valido = 0;
				do{
					ii = 1+rand()%(filas+1);
					jj = 1+rand()%(columnas+1);
					printf("Generada aleatoriamente la posición (%d,%d)\n",(ii),(jj));
					ii--;
					jj--;
					if (*(bot1.tableroPropio+(ii*columnas)+jj)>=0 && *(bot1.tableroPropio+(ii*columnas)+jj)!=8){
						valido = 1;
						printf("Disparando\n");
					}
					else{
						valido = 0;
						printf("No valido, generando otra.\n");
					}
				} while (valido!=1);
			posDir = *(bot1.tableroPropio+(ii*columnas)+jj);
			switch(posDir){
				case 0:
					printf("AGUA\n");
					*(bot1.tableroPropio+(ii*columnas)+jj) = 8;
				break;
				case 1:
					printf("TOCADO\n");
					printf("Barco de 1\n");
					*(bot1.tableroPropio+(ii*columnas)+jj) = -1;
				break;
				case 2:
					printf("TOCADO\n");
					printf("Barco de 2\n");
					*(bot1.tableroPropio+(ii*columnas)+jj) = -2;
				break;
				case 3:
					printf("TOCADO\n");
					printf("Barco de 3\n");
					*(bot1.tableroPropio+(ii*columnas)+jj) = -3;
				break;
				default:
					printf("Error: Unexpected\n");
				break;
			}
			imprimirJugadaArchivo(ii, jj, posDir, contador, file);
			printf("\n");
			contador++;
		}
		
	}
	printf("\n\nFINAL (%d turnos)\n", contador);
	fprintf(file, "Final (%d turnos)\n", contador);
	if( (contador%2) != 0 ){
		printf("El ganador del partido es Bot1.\n\n");
		fprintf(file, "Ha ganado Bot1\n");
	}
	else{
		printf("El ganado del partido es Bot2.\n\n");
		fprintf(file, "Ha ganado Bot2\n");
	}
	printf("Los tableros finalmente han quedado tal que así:\n");
	printf("Tablero de Bot1:\n");
	imprimirMatriz(bot1.tableroPropio, filas, columnas);
	printf("Tablero de Bot2:\n\n");
	imprimirMatriz(bot2.tableroPropio, filas, columnas);
}

int partidaFinalizada(int *tablero, int filas, int columnas){
	/**
	* Metodo que comprueba si la partida ha finalizado
	* Devuelve 1 si ha finalizado (No queda ninguna posición de valor 1, 2 o 3)
	**/
	int resultado, i, contador = 0;
	for (i = 0; i < (filas*columnas); i++){
		if (*(tablero+i) > 0){
			contador++;
		}
		if (*(tablero+i) == 8){
			contador--;
		}
	}
	if (contador == 0){
		resultado = 1;
	}
	else{
		resultado = 0;
	}
	return resultado;
}

void imprimirTableroRival(int *tablero,int filas,int columnas){
	int i,j,k, contador = 1;
	for (k = 0; k <= columnas; k++){
		printf("%d\t", k);
	}
	printf("\n\n");
	for (i = 0; i < filas; i++){
		printf("%d\t", contador);
		for (j = 0; j < columnas; j++){
			if(*(tablero+(i*columnas)+j) >= 0 && *(tablero+(i*columnas)+j) != 8){
				printf("?\t");
			}
			else{
				printf("%d\t",*(tablero+(i*columnas)+j));
			}
		}
		printf("\n\n");
		contador++;
	}
}

void imprimirJugadaArchivo(int i, int j, int posDir, int contador, FILE *archivo){
	switch(posDir){
		case 0:
			if (contador%2 == 0){
				fprintf(archivo, "Tira el Jugador 1: (%d,%d) Agua\n\n", i+1, j+1);
			}
			else{
				fprintf(archivo, "Tira el Jugador 2: (%d,%d) Agua\n\n", i+1, j+1);
			}	
		break;
		case 1:
			if (contador%2 == 0){
				fprintf(archivo, "Tira el Jugador 1: (%d,%d) Tocado (barco de 1 posiciones)\n\n", i+1, j+1);
			}
			else{
				fprintf(archivo, "Tira el Jugador 2: (%d,%d) Tocado (barco de 1 posiciones)\n\n", i+1, j+1);
			}
		break;
		case 2:
			if (contador%2 == 0){
				fprintf(archivo, "Tira el Jugador 1: (%d,%d) Tocado (barco de 2 posiciones)\n\n", i+1, j+1);
			}
			else{
				fprintf(archivo, "Tira el Jugador 2: (%d,%d) Tocado (barco de 2 posiciones)\n\n", i+1, j+1);
			}
		break;
		case 3:
			if (contador%2 == 0){
				fprintf(archivo, "Tira el Jugador 1: (%d,%d) Tocado (barco de 3 posiciones)\n\n", i+1, j+1);
			}
			else{
				fprintf(archivo, "Tira el Jugador 2: (%d,%d) Tocado (barco de 3 posiciones)\n\n", i+1, j+1);
			}
		break;
	}
	fprintf(archivo,"\n\n");
}

void imprimirTableroArchivo(int *tablero, int filas, int columnas, FILE *archivo){
	int i, j;
	for (i = 0; i < filas ; i++){
		for (j = 0; j < columnas; j++){
			fprintf(archivo,"%d\t",*(tablero+(i*columnas)+j));
		}
		fprintf(archivo,"\n");
	}
	fprintf(archivo,"\n");
}

void juegoNuevoArchivo(FILE *archivo){
	int i;
	fprintf(archivo, "---------------------------------------------------------\n");
	for(i = 0; i < 8; i++){
		fprintf(archivo, "\n");
	}
	fprintf(archivo, "---------------------------------------------------------\n\n");
}