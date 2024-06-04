#ifndef JOC_H
#define JOC_H

#include "Figura.h"
#include "Tauler.h"
#include <string>
#include <fstream>


using namespace std;

//Declaración de constantes para que el test main pueda funcionar.

const int MAX_FILA = 21;
const int MAX_COL = 11;

//Clase llamada Joc que tiene toda la información del juego (movimientos, puntuación, nivel, tablero, figura en juego...).

class Joc 
{
public:
	Joc() {} //Constructor per defecte.

	Tauler getTauler()const { return tauler; }
	Figura getFiguraTransparent()const { return figuraTransparent; }
	Figura getFiguraSeguent()const { return figuraSeguent; }

	void inicialitzaSeguentFiguraFitxer(const Figura& figura);
	bool actualitzaFiguraFitxer(const Figura& Figura, int& fila,int& columna);
	
	void ActualitzaSeguentFigura();
	void inicialitzaAleatori(int& fila, int& columna);
	bool actualitzaAleatori(int& fila, int& columna);
	void inicialitzaFitxer(const string& nomFitxer, int& fila,int& columna); //Método que sirve para inicializar toda la partida.
	bool giraFigura(DireccioGir direccio); //Método que sirve para girar la figura en juego hacia una dirección.
	bool mouFigura(int dirX); //Método que sirve para mover la figura hacia izquierda o derecha.
	bool baixaFigura(int& puntuacio); //Método que sirve para bajar la figura en juego cada tiempo t.
	void escriuTauler(const string& nomFitxer); //Método que sirve para escribir el estado del tablero en ese instante de tiempo t que se le pida.
	void baixaFiguraFinal(int& fila, int& puntuacio);
	void actualitzaFiguraTransparent();

private:
	Tauler tauler; //Atributo de tipo Tauler que contiene toda la información del tablero.
	Figura FiguraEnJoc; //Atributo de tipo Figura que sirve para guardar la figura en juego en tiempo real.
	Figura figuraSeguent;
	Figura figuraTransparent;
};
#endif