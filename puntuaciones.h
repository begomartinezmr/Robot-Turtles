#include <string>
const int MAX_JUGADORES = 4;


typedef struct {
	std::string nombre;
	int puntos;
}tPuntJugador;

typedef struct {
	tPuntJugador * jugadores;
	int numeroJugadoresPuntuaciones;
	int capacidad;
}tPuntuaciones;

bool cargarPuntuaciones(tPuntuaciones & pun);
bool guardarPuntuaciones (tPuntuaciones & pun);
void mostrarPuntuaciones( tPuntuaciones &pun,int opc);
int buscarJugador(const tPuntuaciones &pun, std::string nombre);
int buscarMenor(tPuntuaciones &pun, std::string nombre);
bool actualizarPuntuaciones(tPuntuaciones &pun, std::string &nombre, int nuevos);
void redimensionar(tPuntuaciones & clasificacion);
void liberar(tPuntuaciones & clasificacion);
tPuntuaciones listaVacia();
void insertar(tPuntuaciones & clasificacion, const tPuntJugador & j);
void ordenarPorPuntuaciones(tPuntuaciones & puntuaciones);
void ordenarPorOrdenAlfabetico(tPuntuaciones & puntuaciones);