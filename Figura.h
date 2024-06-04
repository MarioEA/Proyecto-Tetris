#ifndef FIGURA_H
#define FIGURA_H
#include"InfoJoc.h"

//Declaración de una constante que es el nombre máximo de posiciones que puede tener una figura en el tetris.

const int POS_MAXFIGURA = 4;

//Enumeración para la dirección que se quiere desplaçar la figura (Derecha = 1, Izquierda = -1).

typedef enum
{
	MOU_DRETA = 1,
	MOU_ESQUERRA = -1

}DireccioDesplacar;

//Enumeración para la dirección en la que se quiere girar la figura. (Horaria = 0, Antihoraria = 1). 

typedef enum
{
	GIR_HORARI = 0,
	GIR_ANTI_HORARI

}DireccioGir;

//Enumeración para tener el codigo del tablero es decir a qué corresponde cada valor del tablero. (Posición vacía = 0, Color amarillo = 1...)

typedef enum
{
	POSICIO_BUIDA = 0,
	COLOR_GROC_TAULER,
	COLOR_BLAUCEL_TAULER,
	COLOR_MAGENTA_TAULER,
	COLOR_TARONJA_TAULER,
	COLOR_BLAUFOSC_TAULER,
	COLOR_VERMELL_TAULER,
	COLOR_VERD_TAULER

}CodiTauler;

//Clase Posición que contiene toda la información sobre cada posición de una figura del tetris.

class Posicio {
public:
	Posicio() { m_fila = -1; m_columna = -1; }; //Constructor por defecto.
	Posicio(int const& fila, int const& columna) { m_fila = fila; m_columna = columna; }; //Constructor con parámetros.

	void operator=(const Posicio& pos);
	void setFila(const int& fila) { m_fila = fila; }; //Instaura la fila de una posición de la figura.
	void setColumna(const int& columna) { m_columna = columna; }; //Instaura la columna de una posición de la figura.
	int getFila()const { return m_fila; }; //Devuelve la fila de esa posición de la figura,
	int getColumna()const { return m_columna; }; //Devuelve la columna de esa posición de la figura.

private:
	int m_fila; //Atributo que representa la fila en la que está esa posición.
	int m_columna; //Atributo que representa la columna en la que está esa posición.
};

class Tauler; //Declaración indirecta de la clase Tauler para tener así la información para los métodos.

//Declaración de la clase Figura que contiene toda la información de la figura en juego (color,tipo,movimientos,giros...).

class Figura
{
public:
	Figura() { Tipus = NO_FIGURA; Color = NO_COLOR; m_columna = 0; } //Constructor por defecto.
	Figura(TipusFigura const& tipus, ColorFigura const& color, Posicio const Pos[],  Posicio const matriu[]); //Constructor con parámetros.

	void operator=(const Figura& figura);
	Posicio getPosicio(int const& index)const { return PosicioFiguraTauler[index]; }; //Método que devuelve una posición en concreto de la figura.
	ColorFigura getColor()const { return Color; }; //Método que devuelve el color de la figura.
	Posicio getPosicioMatriu(int const& index)const { return posMatriuFigura[index]; }
	int getColumna()const { return m_columna; }
	void inicialitza(TipusFigura const& tipus, ColorFigura const& color, int const& fila, int const& columna,int const& gir); //Método que inicializa la figura en el tablero.
	bool desplacarLateral(DireccioDesplacar const& direccio,Tauler& tauler); //Método que deplaza hacia un lado la figura.
	bool Baixa(Tauler& tauler); //Método que hace bajar a la figura.
	bool Girar(DireccioGir const& dir, Tauler& tauler); //Método que gira la figura hacia una dirección.
	bool BaixaFiguraTransparent(const Tauler& tauler);

private:
	void traspostaInicial();
	void Baixar(Tauler& tauler); //Submétodo del método Baixa.
	void desplacarEsquerra(Tauler& tauler); //Submétodo del método desplaçarLateral.
	void desplacarDreta(Tauler&  tauler); //Submétodo del método desplaçarLateral.
	bool potGirar(const Tauler &tauler,const DireccioGir& dir); //Submétodo del método Girar.
	void invertirFiles(); //Submétodo de Girar y potGirar.
	void trasposta(Tauler& tauler); //Submétodo de Girar y potGirar.
	void invertirColumnes(); //Submétodo de Girar, inicialitza y potGirar.
	bool potDesplacarseEsquerra(const Tauler &tauler); //Submétodo del método desplaçarLateral.
	bool potDesplacarseDreta(const Tauler &tauler); //Submétodo del método desplaçarLateral.
	bool potBaixar(const Tauler &tauler); //Submétodo de Baixa.
	TipusFigura Tipus; //Atributo de tipo TipusFigura que contiene el tipo de la figura.
	ColorFigura Color; //Atributo de tipo ColorFigura que contiene el color de la figura.
	Posicio PosicioFiguraTauler[POS_MAXFIGURA]; //Array de tipo Posicio que contiene cada posición de la figura respecto al tablero.
	Posicio posMatriuFigura[POS_MAXFIGURA]; //Array de tipo Posicio que contiene cada posición de la figura respecto a la matriz de cada figura.
	Posicio canvisRespecteTauler[POS_MAXFIGURA]; //Array de tipo Posicio que contiene cuanto se tiene que mover cada posición de la figura en el tablero. 
	int m_columna;
};
#endif