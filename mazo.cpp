#include <iostream>
#include <algorithm>
#include "mazo.h"

using namespace std;


void crearMazoVacio(tMazo &mazo){
	//Crea una secuencia vacía de cartas.
	mazo.numeroCartas = MAX_CARTAS;
	mazo.puntero = 0;
}

bool sacarCarta(tMazo &mazo, tCarta &carta){
	//Saca una carta de la parte superior.
	//Devuelve true si se ha podido sacar, false en caso contrario.
	bool ok;
	if (mazo.numeroCartas == 0){
		ok = false;
	}
	else {
		ok = true;
		mazo.puntero = (mazo.puntero + 1) % MAX_CARTAS;
		carta = *mazo.mazoCartas[mazo.puntero];
		mazo.numeroCartas--;
	}
	return ok;
}

void insertarCarta(tMazo &mazo, tCarta &carta){
	//Inserta la carta en la parte inferior del mazo.
	mazo.mazoCartas[(mazo.puntero + mazo.numeroCartas) % (MAX_CARTAS)] = new tCarta;
	*mazo.mazoCartas[(mazo.puntero + mazo.numeroCartas) % (MAX_CARTAS)] = carta;
}

void crearAleatorio(tMazo &mazo){
	//Crea un mazo aleatorio.
	int posActual = 0;
	int i;
	for (i = 0; i < MAX_AVANZA; i++){
		mazo.mazoCartas[i + posActual] = new tCarta;
		*mazo.mazoCartas[i + posActual] = AVANZA;
	}
	posActual += MAX_AVANZA;

	for (i = 0; i < MAX_DERE; i++){
		mazo.mazoCartas[i + posActual] = new tCarta;
		*mazo.mazoCartas[i + posActual] = DERECHA;
	}
	posActual += MAX_DERE;

	for (i = 0; i < MAX_IZQ; i++){
		mazo.mazoCartas[i + posActual] = new tCarta;
		*mazo.mazoCartas[i + posActual] = IZQUIERDA;
	}
	posActual += MAX_IZQ;

	for (i = 0; i < MAX_LASER; i++){
		mazo.mazoCartas[i + posActual] = new tCarta;
		*mazo.mazoCartas[i + posActual] = LASER;
	}
	posActual += MAX_LASER;

	random_shuffle(&(mazo.mazoCartas[0]), &(mazo.mazoCartas[MAX_CARTAS - 1]));
}
void imprimirCarta(const tCarta carta){
	//Convierte la variable carta en 
	if(carta == AVANZA){
		cout << "AVANZA" << endl;
	}
	if(carta == DERECHA){
		cout << "DERECHA" << endl;
	}
	if(carta == IZQUIERDA){
		cout << "IZQUIERDA" << endl;
	}
	if(carta == LASER){
		cout << "LASER" << endl;
	}
}

void liberar(tMazo & mazo){
	for (int i = 0; i < mazo.puntero; i++){
		delete mazo.mazoCartas[i];
		mazo.mazoCartas[i] = NULL;
	}
}

