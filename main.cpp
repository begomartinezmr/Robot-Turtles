
#include <iostream>
#include<fstream>
#include <string>
#include <conio.h>
#include <time.h>
#include "mazo.h"
#include "puntuaciones.h"
#include "juego.h"
#include "Windows.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "spanish");
	srand(time(NULL));
	string nombre;
	bool ok;
	tJuego mijuego;
	tPuntuaciones misPuntuaciones;
	cargarPuntuaciones(misPuntuaciones);
	int seleccionmenu;
	do {
		tituloJuego();
		seleccionmenu = menu();
		switch (seleccionmenu) {
		case 1:
			if (cargarJuego(mijuego)) {
				mostrarJuego(mijuego);
				if (!ejecutarTurno(mijuego) || (!esFinDePartida)) {
					cout << "Has Ganado" << endl;
					cout << "-----------------------------------" << endl;
					int i = 0, j = 0;
					do {
						ok = mijuego.tablero[i][j].fin;
						i++;
						j++;
					} while (!ok);
					i--;
					j--;
					actualizarPuntuaciones(misPuntuaciones, mijuego.jugador[mijuego.tablero[i][j].tortuga.numero].nombre, mijuego.numeroInicialDeJugadores);
				}
			}
			else {
				cout << "No se ha podido cargar el juego" << endl;
			}
			break;
		case 2:
			int opc;
			cout << "   1- Para ordenar por puntuaciones" << endl << "   2- Para ordenar alfabéticamente " << endl;
			cin >> opc;
			mostrarPuntuaciones(misPuntuaciones, opc);
			break;
		}
	} while (seleccionmenu != 0);
	guardarPuntuaciones(misPuntuaciones);
	liberar(misPuntuaciones);
	for (int i = 0; i < mijuego.numeroInicialDeJugadores; i++){
		liberar(mijuego.jugador[i].mazo);
	}
	system("pause");
	return 0;
}
