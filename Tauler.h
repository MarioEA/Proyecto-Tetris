#ifndef TAULER_H
#define TAULER_H
#include <string>
#include <fstream>
#include "Figura.h"
using namespace std;

// Declaraciones de constantes para el máximo de columnas que tiene el tablero del tetris y el máximo de filas.

const int MAX_COLUMNES = 8; 
const int MAX_FILES = 8;

//Clase llamada Tauler que es la encargada de tener toda la información de las figuras en tiempo real 
//en el tablero.Es capaz de eliminar filas, instaurar las figuras en el tablero etc.

class Tauler
{
public:
	Tauler() { for (int f = 0; f < MAX_FILES; f++) { for (int c = 0; c < MAX_COLUMNES; c++) { m_tauler[f][c] = POSICIO_BUIDA; } } } //Constructor por defecto que instaura el tablero vacío por completo.

	void setFiguraTauler(const Figura& FiguraEnJoc); //Método que instaura la figura en juego en el tablero.
	void estatTauler(ofstream& output); //Método que muestra el estado del tablero en ese instante de tiempo t.
	Tauler CopiaTauler()const; //Método que crea una copia del tablero en ese intante t.

	bool FiguraCorrectaTauler(const Figura& FiguraEnJoc)const; //Método que comprueba si la figura esta correctamente posicionada en el tablero (fuera de margenes o choca con otras figuras).
	int filaCompleta(int files[])const; //Método que comprueba si hay filas completas en el tablero.
	void incialitzaTauler(const string& nomFitxer,Figura &FiguraEnJoc); //Método que inicializa el tablero y la figura en juego.
	void eliminarFiles(const int files[], const int& numFiles); //Método que elimina las filas completas indicadas.
	void eliminarFiguraTauler(const Posicio PosFigura[]); //Método que elimina la figura en juego del tablero.
	
private:
	CodiTauler m_tauler[MAX_FILES][MAX_COLUMNES]; //Atributo que consiste en una matriz de tipo CodiTauler (explicada en Figura.h) que contiene el tablero en tiempo real.
};
#endif