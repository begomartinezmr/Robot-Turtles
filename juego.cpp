
//ELENA CERRO DEL PINO Y MARIA BEGOÑA MARTINEZ MARTIN
// GRUPO 1ºE

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
void tituloJuego() {

	cout << "BIENVENIDO AL JUEGO ROBOT TURTLES " << endl;
	cout << "================================= " << endl << endl;
}

int menu() {
	//Mostrar el menu por pantalla.
	int smenu;
	do {

		cout << "1. Jugar" << endl;
		cout << "2. Mostrar Puntuaciones" << endl << endl;
		cout << "0. Salir" << endl << endl;
		cout << "Elige una opción: " << endl;
		cin >> smenu;
	} while ((smenu < 0) || (smenu > 2));

	return smenu;

}


void colorFondo(int color) {

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15 | (color << 4));
}

bool cargarJuego(tJuego &juego) {
	//Solicita al usuario el nombre del fichero y el numero de jugadores, y carga el tablero correspondiente desde ese fichero.
	//Tambien inicializa los mazos y manos de los jugadores.


	string nomfichero;
	bool cargarJuego = false;
	bool reconocido = false;
	char lectura;
	tCarta carta;
	ifstream fichero;
	int jugadoresAsignados = 0;
	juego.turno = 0;
	string nombreJugadores;

	cout << "Introduza el nombre del fichero: " << endl;
	cin >> nomfichero;

	if ((juego.numeroInicialDeJugadores > 0) && (juego.numeroInicialDeJugadores <= 4)){
		for (int i = 0; i < juego.numeroInicialDeJugadores; i++){
			liberar(juego.jugador[i].mazo);
		}
	}

	do {
		cout << "Introduzca el número de jugadores: " << endl;
		cin >> juego.numeroInicialDeJugadores;
	} while ((juego.numeroInicialDeJugadores <= 0) || (juego.numeroInicialDeJugadores > 4));

	for (int i = 0; i < juego.numeroInicialDeJugadores; i++) {
		cout << "Introduzca el nombre del jugador " << i + 1 << " : ";
		cin >> nombreJugadores;
		juego.jugador[i].nombre = nombreJugadores;
	}


	fichero.open(nomfichero);
	if (!fichero.is_open()) {
		cout << "No he podido abrir el fichero" << endl;
	}
	else {
		int contadorDeTortugas = 0;
		while ((!reconocido) && (!fichero.eof())) {
			fichero >> lectura;
			if (lectura - '0' == juego.numeroInicialDeJugadores) {
				for (int x = 0; x < MAX_CASILLAS; x++) {
					for (int y = 0; y < MAX_CASILLAS; y++) {

						fichero >> lectura;

						switch (lectura) {
						case '#':
							juego.tablero[x][y].estado = MURO;
							juego.tablero[x][y].fin = false;
							break;
						case '@':
							juego.tablero[x][y].estado = HIELO;
							juego.tablero[x][y].fin = false;
							break;
						case '*':
							juego.tablero[x][y].estado = VACIA;
							juego.tablero[x][y].fin = false;
							break;
						case '$':
							juego.tablero[x][y].estado = JOYA;
							juego.tablero[x][y].fin = false;
							break;
						case 'C':
							juego.tablero[x][y].estado = CAJA;
							juego.tablero[x][y].fin = false;
							break;
						case 'D':
							juego.tablero[x][y].fin = false;
							juego.tablero[x][y].estado = TORTUGA;
							juego.tablero[x][y].tortuga.direccion = SUR;
							juego.tablero[x][y].tortuga.numero = contadorDeTortugas;
							juego.jugador[jugadoresAsignados].coord.columna = y;
							juego.jugador[jugadoresAsignados].coord.fila = x;
							contadorDeTortugas++;
							jugadoresAsignados++;
							break;
						case 'R':
							juego.tablero[x][y].fin = false;
							juego.tablero[x][y].estado = TORTUGA;
							juego.tablero[x][y].tortuga.direccion = ESTE;
							juego.tablero[x][y].tortuga.numero = contadorDeTortugas;
							juego.jugador[jugadoresAsignados].coord.columna = y;
							juego.jugador[jugadoresAsignados].coord.fila = x;
							contadorDeTortugas++;
							jugadoresAsignados++;
							break;
						case 'L':
							juego.tablero[x][y].fin = false;
							juego.tablero[x][y].estado = TORTUGA;
							juego.tablero[x][y].tortuga.direccion = OESTE;
							juego.tablero[x][y].tortuga.numero = contadorDeTortugas;
							juego.jugador[jugadoresAsignados].coord.columna = y;
							juego.jugador[jugadoresAsignados].coord.fila = x;
							contadorDeTortugas++;
							jugadoresAsignados++;

							break;
						case 'U':
							juego.tablero[x][y].fin = false;
							juego.tablero[x][y].estado = TORTUGA;
							juego.tablero[x][y].tortuga.direccion = NORTE;
							juego.tablero[x][y].tortuga.numero = contadorDeTortugas;
							juego.jugador[jugadoresAsignados].coord.columna = y;
							juego.jugador[jugadoresAsignados].coord.fila = x;
							contadorDeTortugas++;
							jugadoresAsignados++;
							break;
						}
						reconocido = true;
					}
				}
			}
		}
		cargarJuego = true;
	}
	//Para inicializar el mazo y la mano.

	for (int i = 0; i < juego.numeroInicialDeJugadores; i++) {
		crearMazoVacio(juego.jugador[i].mazo);
		crearAleatorio(juego.jugador[i].mazo);
		juego.jugador[i].mano.numeroAvanzas = 0;
		juego.jugador[i].mano.numeroGirosDerecha = 0;
		juego.jugador[i].mano.numeroGirosIzquierda = 0;
		juego.jugador[i].mano.numeroLasers = 0;
		
		for (int j = 0; j < MAX_MANOJUGADOR; j++) {
			if (!sacarCarta(juego.jugador[i].mazo, carta)) {
				cout << "No se ha podido sacar la carta " << j << "de la mano del jugador" << i << endl;
			}
			incluirCarta(juego.jugador[i].mano, carta);
			
		}


	}


	return cargarJuego;
}
void visualizarTablero(const tTablero &tablero) {

	for (int x = 0; x < MAX_CASILLAS; x++) {
		for (int y = 0; y < MAX_CASILLAS; y++) {
			colorFondo(PALETA[tablero[x][y].estado]);
			switch (tablero[x][y].estado) {
			case MURO:
				cout << "||";
				break;
			case CAJA:
				cout << "[]";
				break;
			case VACIA:
				cout << "  ";
				break;
			case JOYA:
				cout << "00";
				break;
			case HIELO:
				cout << "**";
				break;
			case TORTUGA:
				colorFondo(PALETA[TORTUGA + tablero[x][y].tortuga.numero]);
				switch (tablero[x][y].tortuga.direccion) {
				case NORTE:
					cout << "^^";
					break;
				case SUR:
					cout << "vv";
					break;
				case ESTE:
					cout << ">>";
					break;
				case OESTE:
					cout << "<<";
					break;
				}

				break;
			}

			colorFondo(0);
		}
		cout << endl;
	}

}

void mostrarJugador(const tJugador &jugador, const tTablero &tablero) {

	colorFondo(PALETA[TORTUGA + tablero[jugador.coord.fila][jugador.coord.columna].tortuga.numero]);
	cout << " " << jugador.nombre << ":";
	colorFondo(0);
	cout << jugador.mano.numeroAvanzas;
	colorFondo(PALETA[TORTUGA + tablero[jugador.coord.fila][jugador.coord.columna].tortuga.numero]);
	cout << " ^ ";
	colorFondo(0);
	cout << jugador.mano.numeroGirosDerecha;
	colorFondo(PALETA[TORTUGA + tablero[jugador.coord.fila][jugador.coord.columna].tortuga.numero]);
	cout << " < ";
	colorFondo(0);
	cout << jugador.mano.numeroGirosIzquierda;
	colorFondo(PALETA[TORTUGA + tablero[jugador.coord.fila][jugador.coord.columna].tortuga.numero]);
	cout << " > ";
	colorFondo(0);
	cout << jugador.mano.numeroLasers;
	colorFondo(PALETA[TORTUGA + tablero[jugador.coord.fila][jugador.coord.columna].tortuga.numero]);
	cout << " ~ " << endl;
	colorFondo(0);

}
void mostrarJuego(const tJuego &juego) {
	//Visualiza el estado actual del juego.

	system("cls");
	visualizarTablero(juego.tablero);
	for (int i = 0; i < juego.numeroInicialDeJugadores; i++) {
		if (juego.turno == i) {
			cout << "> ";
		}
		cout << i + 1;
		mostrarJugador(juego.jugador[i], juego.tablero);
	}
}
void inicializarTeclas(tsecuenciaDeTeclas &secuenciaDeTeclas) {
	secuenciaDeTeclas.puntero = 0;
	secuenciaDeTeclas.numeroDeTeclas = 0;
}

tTecla leerTecla() {
	int dir;
	cin.sync();
	tTecla tecla;
	dir = _getch();

	if (dir == 0xe0) {
		dir = _getch();
		switch (dir) {
		case 72: tecla = FLECHA_ARRIBA;
			break;
		case 77: tecla = FLECHA_DERECHA;
			break;
		case 75: tecla = FLECHA_IZQUIERDA;
			break;

		}

	}
	else {
		if (dir == 32) {
			tecla = ESPACIO;
		}
		else if (dir == 13) {
			tecla = ENTER;
		}
		else {
			tecla = OTRA;
		}

	}
	return tecla;

}

void imprimirTecla(tTecla tecla) {

	switch (tecla) {
	case FLECHA_ARRIBA:
		cout << "^" << endl;
		break;
	case FLECHA_IZQUIERDA:
		cout << "<" << endl;
		break;
	case FLECHA_DERECHA:
		cout << ">" << endl;
		break;
	case ESPACIO:
		cout << "~" << endl;
		break;

	}


}



bool ejecutarTurno(tJuego &juego) {
	//Lee la acción del jugador actual y la ejecuta.
	//El booleano indica si el jugador que tiene el turno ha alcanzado una joya.
	bool turno = false;
	char opturno;
	tMazo cartas;

	while (!esFinDePartida(juego)) {
		for (int i = 0; i < juego.numeroInicialDeJugadores; i++) {
			do {
				cout << "Es el turno de: " << juego.jugador[i].nombre << endl;
				cout << "r: robar" << endl;
				cout << "e: crear y ejecutar una secuencia" << endl;
				cout << "¿ Qué tipo de jugada quieres realizar ?" << endl;
				cin >> opturno;
			} while ((opturno != 'r') && (opturno != 'e'));

			switch (opturno) {
			case 'r':
				accionRobar(juego, i);
				break;

			case'e':
				accionSecuencia(juego, cartas, i);
				break;

			}
			cambiarTurno(juego);
			mostrarJuego(juego);
			if (esFinDePartida(juego)) {
				cout << "Enhorabuena, has ganado!!" << endl;
				i = juego.numeroInicialDeJugadores;
			}
		}

	}

	return turno;
}
bool accionRobar(tJuego &juego, int numeroDelJugador) {
	//El jugador con el turno roba una carta de su mazo si hay cartas disponibles.
	//El booleano indica si ha sido posible robar la carta.
	bool accionRobar = false;
	tCarta carta;
	if (!sacarCarta(juego.jugador[numeroDelJugador].mazo, carta)) {
		cout << "No se ha podido sacar la carta" << endl;
	}
	else {
		incluirCarta(juego.jugador[numeroDelJugador].mano, carta);
		accionRobar = true;
	}

	return accionRobar;

}

bool accionSecuencia(tJuego &juego, tMazo &cartas, int numeroDelJugador) {
	//El jugador con el turno ejecuta una secuencia de cartas.
	//El segundo parámetro contiene un subconjunto de las cartas del jugador actual y se va consumiendo a medida que se ejecuta.
	//El booleano indica si el jugador que tiene el turno ha alcanzado una joya en la ejecución de esta secuencia.
	bool accionSecuencia = true;
	tTecla optecla;
	tsecuenciaDeTeclas secuenciaDeTeclas;
	cout << "Escribe la secuencia que quieres realizar " << endl;
	cout << "^ Avanza " << endl;
	cout << "> Gira derecha" << endl;
	cout << "< Gira Izquierda " << endl;
	cout << "~ Láser " << endl;
	cout << "Pulsa ENTER para finalizar la secuencia " << endl;
	inicializarTeclas(secuenciaDeTeclas);
	do {
		optecla = leerTecla();
		imprimirTecla(optecla);
		if (optecla == OTRA) {
			cout << "La tecla no es válida." << endl;
		}
		else {
			secuenciaDeTeclas.listaDeTeclas[secuenciaDeTeclas.puntero] = optecla;
			secuenciaDeTeclas.puntero++;
			secuenciaDeTeclas.numeroDeTeclas++;
		}
	} while (optecla != ENTER);
	if (!validarSecuenciaDeTeclas(juego.jugador[numeroDelJugador].mano, secuenciaDeTeclas)) {
		accionSecuencia = false;
	}
	else {
		tTablero CopiaDelTablero;
		copiaTablero(juego.tablero, CopiaDelTablero);
		if (moverTortugaTablero(juego.jugador[numeroDelJugador], CopiaDelTablero, secuenciaDeTeclas)) {
			copiaTablero(CopiaDelTablero, juego.tablero);
		}
	}
	return accionSecuencia;
}

void copiaTablero(const tTablero &tableroInput, tTablero &tableroOutput) {
	for (int x = 0; x < MAX_CASILLAS; x++) {
		for (int y = 0; y < MAX_CASILLAS; y++) {
			tableroOutput[x][y] = tableroInput[x][y];
		}
	}
}

bool moverTortugaTablero(tJugador &jugador, tTablero &tablero, const tsecuenciaDeTeclas &secuenciaDeTeclas) {
	bool moverTortugaTablero = true;
	if (!validarSecuenciaEnTablero(tablero, secuenciaDeTeclas, jugador)) {
		moverTortugaTablero = false;
	}
	return moverTortugaTablero;
}

bool validarSecuenciaEnTablero(tTablero &tablero, const tsecuenciaDeTeclas &secuenciaDeTeclas, tJugador &jugador) {
	bool validar=true;
	for (int i = 0; i < secuenciaDeTeclas.numeroDeTeclas; i++) {
		tTecla tecla = secuenciaDeTeclas.listaDeTeclas[i];
		if (!ejecutarTecla(tablero, tecla, jugador)) {
			cout << "Jugada no válida" << endl;
			validar = false;
		}
	}
	return validar;
}

bool intercambiaCasillas(tTablero &tablero, int filaorigen, int columnaorigen, tDir direccion) {
	bool ok = false;
	int i, j;
	tCasilla auxiliar;
	if (direccion == NORTE) {
		if (tablero[filaorigen][columnaorigen].estado == CAJA) {
			if ((filaorigen - 1) >= 0) {
				if (tablero[filaorigen - 1][columnaorigen].estado == CAJA) {
					ok = false;
				}
				else if (tablero[filaorigen - 1][columnaorigen].estado != VACIA) {
					ok = false;
				}
				else {
					tablero[filaorigen - 1][columnaorigen].estado = CAJA;
					ok = true;
				}
			}
		}
	}
	else if (direccion == SUR) {
		if (tablero[filaorigen][columnaorigen].estado == CAJA) {
			if ((filaorigen + 1) < MAX_CASILLAS) {
				if (tablero[filaorigen + 1][columnaorigen].estado == CAJA) {
					ok = false;
				}
				else if (tablero[filaorigen + 1][columnaorigen].estado != VACIA) {
					ok = false;
				}
				else {
					tablero[filaorigen + 1][columnaorigen].estado = CAJA;
					ok = true;
				}
			}
		}
	}
	else if (direccion == ESTE) {
		if (tablero[filaorigen][columnaorigen].estado == CAJA) {
			if ((columnaorigen + 1) < MAX_CASILLAS) {
				if (tablero[filaorigen][columnaorigen + 1].estado == CAJA) {
					ok = false;
				}
				else if (tablero[filaorigen][columnaorigen + 1].estado != VACIA) {
					ok = false;
				}
				else {
					tablero[filaorigen][columnaorigen + 1].estado = CAJA;
					ok = true;
				}
			}
		}
	}
	else if (direccion == OESTE) {
		if (tablero[filaorigen][columnaorigen].estado == CAJA) {
			if ((columnaorigen - 1) >= 0) {
				if (tablero[filaorigen][columnaorigen - 1].estado == CAJA) {
					ok = false;
				}
				else if (tablero[filaorigen][columnaorigen - 1].estado != VACIA) {
					ok = false;
				}
				else {
					tablero[filaorigen][columnaorigen - 1].estado = CAJA;
					ok = true;
				}
			}
		}
	}


	return ok;
}
bool comprobarSiguienteCasilla(tTablero &tablero, int fila, int columna, tDir direccion) {
	bool comprobado;
	switch (tablero[fila][columna].estado) {
	case VACIA:
		comprobado = true;

		break;
	case CAJA:
		return(intercambiaCasillas(tablero, fila, columna, direccion));
		tablero[fila][columna].estado = TORTUGA;
		break;
	case TORTUGA:
		cout << "No se puede ejecutar la secuencia, hay una tortuga." << endl;
		comprobado = false;
		break;
	case HIELO:
		cout << "No se puede ejecutar la secuencia, hay un muro de hielo." << endl;
		comprobado = false;
		break;
	case MURO:
		cout << "No se puede ejecutar la secuencia, hay un muro." << endl;
		comprobado = false;
		break;
	case JOYA:
		cout << "Enhorabuena, ¡Has ganado!" << endl;
		tablero[fila][columna].fin = true;
		comprobado = true;
		break;
	}
	return comprobado;
}

bool ejecutarTecla(tTablero &tablero, const tTecla &tecla, tJugador &jugador) {

	bool ok;
	switch (tecla) {
	case FLECHA_ARRIBA:
		switch (tablero[jugador.coord.fila][jugador.coord.columna].tortuga.direccion) {
		case NORTE:
			if ((jugador.coord.fila - 1) >= 0) {
				if (comprobarSiguienteCasilla(tablero, jugador.coord.fila - 1, jugador.coord.columna, NORTE)) {
					tablero[jugador.coord.fila - 1][jugador.coord.columna].estado = TORTUGA;
					tablero[jugador.coord.fila - 1][jugador.coord.columna].tortuga = tablero[jugador.coord.fila][jugador.coord.columna].tortuga;
					tablero[jugador.coord.fila][jugador.coord.columna].estado = VACIA;
					jugador.coord.fila = jugador.coord.fila - 1;
					jugador.coord.columna = jugador.coord.columna;
					jugador.mano.numeroAvanzas--;
					tCarta L = AVANZA;
					insertarCarta(jugador.mazo, L);
				}
			}

			break;
		case SUR:
			if ((jugador.coord.fila + 1) < MAX_CASILLAS) {
				if (comprobarSiguienteCasilla(tablero, jugador.coord.fila + 1, jugador.coord.columna, SUR)) {
					tablero[jugador.coord.fila + 1][jugador.coord.columna].estado = TORTUGA;
					tablero[jugador.coord.fila + 1][jugador.coord.columna].tortuga = tablero[jugador.coord.fila][jugador.coord.columna].tortuga;
					tablero[jugador.coord.fila][jugador.coord.columna].estado = VACIA;
					jugador.coord.fila = jugador.coord.fila + 1;
					jugador.coord.columna = jugador.coord.columna;
					jugador.mano.numeroAvanzas--;
					tCarta L = AVANZA;
					insertarCarta(jugador.mazo, L);
				}
			}
			break;
		case ESTE:
			if ((jugador.coord.columna + 1) < MAX_CASILLAS) {
				if (comprobarSiguienteCasilla(tablero, jugador.coord.fila, jugador.coord.columna + 1, ESTE)) {
					tablero[jugador.coord.fila][jugador.coord.columna + 1].estado = TORTUGA;
					tablero[jugador.coord.fila][jugador.coord.columna + 1].tortuga = tablero[jugador.coord.fila][jugador.coord.columna].tortuga;
					tablero[jugador.coord.fila][jugador.coord.columna].estado = VACIA;
					jugador.coord.fila = jugador.coord.fila;
					jugador.coord.columna = jugador.coord.columna + 1;
					jugador.mano.numeroAvanzas--;
					tCarta L = AVANZA;
					insertarCarta(jugador.mazo, L);
				}
			}
			break;
		case OESTE:
			if ((jugador.coord.columna - 1) >= 0) {
				if (comprobarSiguienteCasilla(tablero, jugador.coord.fila, jugador.coord.columna - 1, OESTE)) {
					tablero[jugador.coord.fila][jugador.coord.columna - 1].estado = TORTUGA;
					tablero[jugador.coord.fila][jugador.coord.columna - 1].tortuga = tablero[jugador.coord.fila][jugador.coord.columna].tortuga;
					tablero[jugador.coord.fila][jugador.coord.columna].estado = VACIA;
					jugador.coord.fila = jugador.coord.fila;
					jugador.coord.columna = jugador.coord.columna - 1;
					jugador.mano.numeroAvanzas--;
					tCarta L = AVANZA;
					insertarCarta(jugador.mazo, L);
				}
			}
			break;
		}

		break;
	case FLECHA_DERECHA: {
		tDir laDireccion = tablero[jugador.coord.fila][jugador.coord.columna].tortuga.direccion;
		tDir laNuevaDireccion = calcularDireccionFlechaIzquierda(laDireccion);
		tablero[jugador.coord.fila][jugador.coord.columna].tortuga.direccion = laNuevaDireccion;
		ok = true;
		tCarta L = IZQUIERDA;
		jugador.mano.numeroGirosDerecha--;
		insertarCarta(jugador.mazo, L);
	}
						   break;
	case FLECHA_IZQUIERDA: {
		tDir laDireccion = tablero[jugador.coord.fila][jugador.coord.columna].tortuga.direccion;
		tDir laNuevaDireccion = calcularDireccionFlechaDerecha(laDireccion);
		tablero[jugador.coord.fila][jugador.coord.columna].tortuga.direccion = laNuevaDireccion;
		ok = true;
		tCarta L = DERECHA;
		jugador.mano.numeroGirosIzquierda--;
		insertarCarta(jugador.mazo, L);
	}
						 break;
	case ESPACIO:
		dispararLaser(tablero, jugador.coord, tablero[jugador.coord.fila][jugador.coord.columna].tortuga.direccion);
		jugador.mano.numeroLasers--;
		tCarta L = LASER;
		insertarCarta(jugador.mazo, L);
		break;

	}

	ok = true;
	return ok;
}


bool HayMuroDeHielo(tTablero &tablero, int fila, int colum) {
	bool haymuro;

	if (tablero[fila][colum].estado == HIELO) {
		tablero[fila][colum].estado = VACIA;
		haymuro = true;
	}
	haymuro = false;
	return haymuro;
}
void dispararLaser(tTablero &tablero, const tCoord &coordenadaDelJugador, const tDir &direccionDelJugador) {
	tCoord coorde;
	bool ok = false;
	switch (direccionDelJugador) {
	case ESTE:

		coorde.columna = coordenadaDelJugador.columna + 1;
		coorde.fila = coordenadaDelJugador.fila;
		do {
			if (tablero[coorde.fila][coorde.columna].estado == VACIA) {
				coorde.columna++;
			}
			else if (tablero[coorde.fila][coorde.columna].estado != HIELO) {
				ok = true;
			}
			else {
				HayMuroDeHielo(tablero, coorde.fila, coorde.columna);
				ok = true;
			}
		} while (!ok);

		break;
	case OESTE:

		coorde.columna = coordenadaDelJugador.columna - 1;
		coorde.fila = coordenadaDelJugador.fila;
		do {
			if (tablero[coorde.fila][coorde.columna].estado == VACIA) {
				coorde.columna--;
			}
			else if (tablero[coorde.fila][coorde.columna].estado != HIELO) {
				ok = true;
			}
			else {
				HayMuroDeHielo(tablero, coorde.fila, coorde.columna);
				ok = true;
			}
		} while (!ok);

		break;
	case NORTE:

		coorde.columna = coordenadaDelJugador.columna;
		coorde.fila = coordenadaDelJugador.fila - 1;
		do {
			if (tablero[coorde.fila][coorde.columna].estado == VACIA) {
				coorde.fila--;
			}
			else if (tablero[coorde.fila][coorde.columna].estado != HIELO) {
				ok = true;
			}
			else {
				HayMuroDeHielo(tablero, coorde.fila, coorde.columna);
				ok = true;
			}
		} while (!ok);

		break;

	case SUR:

		coorde.columna = coordenadaDelJugador.columna;
		coorde.fila = coordenadaDelJugador.fila + 1;
		do {
			if (tablero[coorde.fila][coorde.columna].estado == VACIA) {
				coorde.fila++;
			}
			else if (tablero[coorde.fila][coorde.columna].estado != HIELO) {
				ok = true;
			}
			else {
				HayMuroDeHielo(tablero, coorde.fila, coorde.columna);
				ok = true;
			}
		} while (!ok);

		break;
	}

}
tDir calcularDireccionFlechaIzquierda(tDir direccion) {
	switch (direccion) {
	case ESTE:
		return NORTE;
		break;
	case OESTE:
		return SUR;
		break;
	case NORTE:
		return OESTE;
		break;
	case SUR:
		return ESTE;
		break;

	}

}
tDir calcularDireccionFlechaDerecha(tDir direccion) {
	switch (direccion) {
	case ESTE:
		return SUR;
		break;
	case OESTE:
		return NORTE;
		break;
	case NORTE:
		return ESTE;
		break;
	case SUR:
		return OESTE;
		break;

	}

}

bool validarSecuenciaDeTeclas(tMano mano, const tsecuenciaDeTeclas &secuenciaDeTeclas) {
	bool validarSecuenciaDeTeclas = true;
	for (int i = 0; i < secuenciaDeTeclas.numeroDeTeclas; i++) {
		tTecla tecla = secuenciaDeTeclas.listaDeTeclas[i];
		if (!actualizarMano(mano, tecla)) {
			cout << "La secuencia introducida no es válida por las cartas" << endl;
			validarSecuenciaDeTeclas = false;
		}

	}
	return validarSecuenciaDeTeclas;
}
bool actualizarMano(tMano &mano, const tTecla &tecla) {
	bool actualizarMano = true;
	switch (tecla) {
	case FLECHA_ARRIBA:
		mano.numeroAvanzas--;
		if (mano.numeroAvanzas < 0) {
			actualizarMano = false;
		}
		break;
	case FLECHA_IZQUIERDA:
		mano.numeroGirosIzquierda--;
		if (mano.numeroGirosIzquierda < 0) {
			actualizarMano = false;
		}
		break;
	case FLECHA_DERECHA:
		mano.numeroGirosDerecha--;
		if (mano.numeroGirosDerecha < 0) {
			actualizarMano = false;
		}
		break;
	case ESPACIO:
		mano.numeroLasers--;
		if (mano.numeroLasers < 0) {
			actualizarMano = false;
		}
		break;

	}
	return actualizarMano;
}

void cambiarTurno(tJuego &juego) {
	//Cambia el turno al jugador siguiente.
	juego.turno = ((juego.turno + 1) % juego.numeroInicialDeJugadores);

}
bool esFinDePartida(tJuego &juego) {
	bool ok = false;
	for (int i = 0; i < MAX_CASILLAS; i++) {
		for (int j = 0; j < MAX_CASILLAS; j++) {
			if (juego.tablero[i][j].fin) {
				ok = true;
				
			}
		}
	}
	return ok;
}

void incluirCarta(tMano &mano, tCarta carta) {
	//Incluye una nueva carta en la mano del jugador
	switch (carta) {
	case AVANZA:
		mano.numeroAvanzas++;
		break;
	case DERECHA:
		mano.numeroGirosDerecha++;
		break;
	case IZQUIERDA:
		mano.numeroGirosIzquierda++;
		break;
	case LASER:
		mano.numeroLasers++;
		break;
	}
}



