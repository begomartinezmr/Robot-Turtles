const int MAX_TECLAS = 38;
const int MAX_CASILLAS = 8;

enum tDir {NORTE, SUR, ESTE, OESTE};
enum tEstadoCasilla {VACIA, HIELO, MURO, CAJA, JOYA, TORTUGA};
const int PALETA[6 + MAX_JUGADORES] = { 1, 11, 7, 4, 12,10, 13, 9, 3, 5 };


typedef struct {
	int numero;
	tDir direccion;
}tTortuga;

typedef struct {
	tEstadoCasilla estado;
	tTortuga tortuga;
	bool fin;
}tCasilla;

typedef tCasilla tTablero[MAX_CASILLAS][MAX_CASILLAS];

typedef struct {
	int fila;
	int columna;
}tCoord;

typedef struct {
	int numeroAvanzas;
	int numeroGirosDerecha;
	int numeroGirosIzquierda;
	int numeroLasers;
}tMano;


typedef struct {
	std::string nombre;
	tMazo mazo;
	tMano mano;
	tCoord coord;
	bool finPartida;
}tJugador;

typedef struct {
	int numeroInicialDeJugadores;
	int turno; //Jugador al que le toca jugar
	tJugador jugador[MAX_JUGADORES];
	tTablero tablero;

}tJuego;


enum tTecla { FLECHA_ARRIBA, FLECHA_IZQUIERDA, FLECHA_DERECHA, ESPACIO, ENTER, OTRA };
typedef struct {
	tTecla listaDeTeclas[38];
	int numeroDeTeclas;
	int puntero;
}tsecuenciaDeTeclas;

tTecla leerTecla();

void imprimirTecla(tTecla tecla);
void inicializarTeclas(tsecuenciaDeTeclas &secuenciaDeTeclas);
void mostrarJuego(const tJuego &juego);
bool cargarJuego(tJuego &juego);
bool ejecutarTurno(tJuego &juego);
bool accionRobar(tJuego &juego, int numeroDelJugador);
bool accionSecuencia(tJuego &juego, tMazo &cartas, int numeroDelJugador);
void cambiarTurno(tJuego &juego);
bool esFinDePartida(tJuego &juego);
void incluirCarta(tMano &mano, tCarta carta);
void visualizarTablero(const tTablero &tablero);
bool actualizarMano(tMano &mano, const tTecla &tecla);
bool validarSecuenciaDeTeclas(tMano mano, const tsecuenciaDeTeclas &secuenciaDeTeclas);
bool ejecutarTecla(tTablero &tablero, const tTecla &tecla, tJugador &jugador);
tDir calcularDireccionFlechaIzquierda(tDir direccion);
tDir calcularDireccionFlechaDerecha(tDir direccion);
void dispararLaser(tTablero &tablero, const tCoord &coordenadaDelJugador, const tDir &direccionDelJugador);
bool moverTortugaTablero(tJugador &jugador, tTablero &tablero, const tsecuenciaDeTeclas &secuenciaDeTeclas);
bool validarSecuenciaEnTablero(tTablero &tablero, const tsecuenciaDeTeclas &secuenciaDeTeclas, tJugador &jugador);
void copiaTablero(const tTablero &tableroInput, tTablero &tableroOutput);
void mostrarJugador(const tJugador &jugador, const tTablero &tablero);
int menu();
void tituloJuego();