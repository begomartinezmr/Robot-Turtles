#include <iostream>
#include <fstream>
#include "puntuaciones.h"

using namespace std;

bool cargarPuntuaciones(tPuntuaciones & pun){ 
	// Carga las puntuaciones de los jugadores desde el fichero.
	bool cargar = false;
	ifstream archivo;
	int i = 0;
	pun = listaVacia();

	pun.numeroJugadoresPuntuaciones = 0;

	archivo.open("puntuaciones.txt");
	if(archivo.is_open()) {
		while(!archivo.eof()) {
			tPuntJugador jugador;
			archivo >> jugador.nombre;
			archivo >> jugador.puntos;
			insertar(pun, jugador);
			
		}
		cargar = true;
		archivo.close();
	}
	else {
		cout << "No se ha podido abrir puntuaciones.txt" << endl;
	}

	return cargar;
}

bool guardarPuntuaciones(tPuntuaciones & pun) {
	bool guardar = false;
	ofstream archivo;
	archivo.open("puntuaciones.txt");
	ordenarPorPuntuaciones(pun);
	if (archivo.is_open()){
		for (int i = 0; i < pun.numeroJugadoresPuntuaciones; i++){
			archivo << pun.jugadores[i].nombre << " " << pun.jugadores[i].puntos << endl; 
			
		}
	}
	else {
		cout << "No se ha podido abrir puntuaciones.txt" << endl;
	}
	archivo.close();
	return guardar;
}

void mostrarPuntuaciones( tPuntuaciones &pun, int opc) {

	if (opc == 1)
		ordenarPorPuntuaciones(pun);
	else
		ordenarPorOrdenAlfabetico(pun);

	for (int i = 0; i < pun.numeroJugadoresPuntuaciones; i++) {
		cout << "La puntuacion de " << pun.jugadores[i].nombre << " es de " << pun.jugadores[i].puntos << endl;
	}
}

int buscarJugador(const tPuntuaciones &pun, string nombre){
	int pos = -1;
	bool encontrado = false;
	tPuntJugador jugador;
	int i = 0;
	while ((i < MAX_JUGADORES) && (!encontrado)){
		if (nombre == pun.jugadores[i].nombre){
			pos = i;
			encontrado = true;
		}
		else{
			i++;
		}
		return pos;
	}
}

int buscarMenor(tPuntuaciones &pun , string nombre){
	int menor = -1;
	int i = 0;
	for (i = 0; i < pun.numeroJugadoresPuntuaciones; i++){
		if (pun.jugadores[i].nombre == nombre){
			menor = i;
		}
	}
	return menor;
}

bool actualizarPuntuaciones(tPuntuaciones &pun, string &nombre, int nuevos){

	bool actualizar = true;
	int pos;
	int menor;
	int i = 0;
	tPuntJugador jugador;
	jugador.puntos = 0;
	pos = buscarMenor(pun, nombre);
	

	if(pos >= 0){            
		pun.jugadores[pos].puntos += nuevos;
	}
	else{
		jugador.puntos = nuevos;
		jugador.nombre = nombre;
		insertar(pun, jugador);
	}
	ordenarPorPuntuaciones(pun);
	return actualizar;
}

tPuntuaciones listaVacia() {
	tPuntuaciones result;
	result.jugadores = new tPuntJugador[4];
	result.numeroJugadoresPuntuaciones = 0;
	result.capacidad = 4;
	return result;
};

void redimensionar(tPuntuaciones & clasificacion) {
	tPuntJugador * newDatos = new tPuntJugador[clasificacion.capacidad + 4];
	for (int i = 0; i< clasificacion.numeroJugadoresPuntuaciones; i++) {
		newDatos[i] = clasificacion.jugadores[i];
	}
	delete[] clasificacion.jugadores;
	clasificacion.jugadores = newDatos;
	clasificacion.capacidad = clasificacion.capacidad + 4;
};


void liberar(tPuntuaciones & clasificacion) {
	delete[] clasificacion.jugadores;
	clasificacion.numeroJugadoresPuntuaciones = 0;
	clasificacion.capacidad = 0;
	clasificacion.jugadores = NULL;
}

void insertar(tPuntuaciones & clasificacion, const tPuntJugador & j) {
	if (clasificacion.capacidad == clasificacion.numeroJugadoresPuntuaciones){
		redimensionar(clasificacion);
	}
	clasificacion.jugadores[clasificacion.numeroJugadoresPuntuaciones] = j;
	clasificacion.numeroJugadoresPuntuaciones++;
}

void ordenarPorPuntuaciones(tPuntuaciones & puntuaciones){
	int i, min,j;
	tPuntJugador aux;
	for (i = 0; i<puntuaciones.numeroJugadoresPuntuaciones - 1; i++)
	{
		min = i;
		for (j = i + 1; j<puntuaciones.numeroJugadoresPuntuaciones; j++)
			if (puntuaciones.jugadores[min].puntos < puntuaciones.jugadores[j].puntos)
				min = j;

		aux = puntuaciones.jugadores[min];
		puntuaciones.jugadores[min] = puntuaciones.jugadores[i];
		puntuaciones.jugadores[i] = aux;
	}

}
	

void ordenarPorOrdenAlfabetico(tPuntuaciones & puntuaciones){
	int i, min, j;
	tPuntJugador aux;
	for (i = 0; i<puntuaciones.numeroJugadoresPuntuaciones - 1; i++)
	{
		min = i;
		for (j = i + 1; j<puntuaciones.numeroJugadoresPuntuaciones; j++)
			if (puntuaciones.jugadores[min].nombre > puntuaciones.jugadores[j].nombre)
				min = j;

		aux = puntuaciones.jugadores[min];
		puntuaciones.jugadores[min] = puntuaciones.jugadores[i];
		puntuaciones.jugadores[i] = aux;
	}
}