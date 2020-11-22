
const int MAX_AVANZA = 18;
const int MAX_DERE = 8;
const int MAX_IZQ = 8;
const int MAX_LASER = 4;
const int MAX_CARTAS = 38;
const int MAX_MANOJUGADOR = 3;

typedef enum tCarta {AVANZA, DERECHA, IZQUIERDA, LASER};
typedef tCarta * tMazoCartas[MAX_CARTAS];

typedef struct{
	tMazoCartas mazoCartas;
	int numeroCartas;
	int puntero;
}tMazo;

void crearMazoVacio(tMazo &mazo);
bool sacarCarta(tMazo &mazo, tCarta &carta);
void insertarCarta(tMazo &mazo, tCarta &carta);
void crearAleatorio(tMazo &mazo);
void imprimirCarta(const tCarta carta);
void liberar(tMazo & mazo);