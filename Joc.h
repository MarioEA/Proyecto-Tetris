#ifndef JOC_H
#define JOC_H

#include "Figura.h"
#include "Tauler.h"
#include <string>
#include <fstream>
using namespace std;

//Declaraci�n de constantes para que el test main pueda funcionar.

const int MAX_FILA = 8;
const int MAX_COL = 8;

//Clase llamada Joc que tiene toda la informaci�n del juego (movimientos, puntuaci�n, nivel, tablero, figura en juego...).

class Joc 
{
public:
	Joc() { m_puntuacio = 0; m_nivell = 0; } //Constructor per defecte.

	void inicialitza(const string& nomFitxer); //M�todo que sirve para inicializar toda la partida.
	bool giraFigura(DireccioGir direccio); //M�todo que sirve para girar la figura en juego hacia una direcci�n.
	bool mouFigura(int dirX); //M�todo que sirve para mover la figura hacia izquierda o derecha.
	int baixaFigura(); //M�todo que sirve para bajar la figura en juego cada tiempo t.
	void escriuTauler(const string& nomFitxer); //M�todo que sirve para escribir el estado del tablero en ese instante de tiempo t que se le pida.

private:
	Tauler tauler; //Atributo de tipo Tauler que contiene toda la informaci�n del tablero.
	int m_puntuacio; //Atributo de tipo int que sirve para guardar la puntuaci�n del jugador.
	Figura FiguraEnJoc; //Atributo de tipo Figura que sirve para guardar la figura en juego en tiempo real.
	int m_nivell; //Atributo que sirve para tener el nivel que se encuentra la partida en un instante t.
};
#endif