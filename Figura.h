#ifndef FIGURA_H
#define FIGURA_H

//Declaraci�n de una constante que es el nombre m�ximo de posiciones que puede tener una figura en el tetris.

const int POS_MAXFIGURA = 4;

//Enumeraci�n para la direcci�n que se quiere despla�ar la figura (Derecha = 1, Izquierda = -1).

typedef enum
{
	MOU_DRETA = 1,
	MOU_ESQUERRA = -1

}DireccioDesplacar;

//Enumeraci�n para la direcci�n en la que se quiere girar la figura. (Horaria = 0, Antihoraria = 1). 

typedef enum
{
	GIR_HORARI = 0,
	GIR_ANTI_HORARI

}DireccioGir;

//Enumeraci�n para tener el codigo del tablero es decir a qu� corresponde cada valor del tablero. (Posici�n vac�a = 0, Color amarillo = 1...)

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

//Lo mismo que la anterior pero para el tipo de figura que est� en juego.

typedef enum 
{
	NO_FIGURA = 0,
	FIGURA_O,
	FIGURA_I,
	FIGURA_T,
	FIGURA_L,
	FIGURA_J,
	FIGURA_Z,
	FIGURA_S,

}TipusFigura;

//Lo mismo pero para el color de la figura.

typedef enum
{
	COLOR_NEGRE = 0,
	COLOR_GROC,
	COLOR_BLAUCEL,
	COLOR_MAGENTA,
	COLOR_TARONJA,
	COLOR_BLAUFOSC,
	COLOR_VERMELL,
	COLOR_VERD,
	NO_COLOR

}ColorFigura;

//Clase Posici�n que contiene toda la informaci�n sobre cada posici�n de una figura del tetris.

class Posicio {
public:
	Posicio() { m_fila = -1; m_columna = -1; }; //Constructor por defecto.
	Posicio(int const& fila, int const& columna) { m_fila = fila; m_columna = columna; }; //Constructor con par�metros.

	void setFila(const int& fila) { m_fila = fila; }; //Instaura la fila de una posici�n de la figura.
	void setColumna(const int& columna) { m_columna = columna; }; //Instaura la columna de una posici�n de la figura.
	int getFila()const { return m_fila; }; //Devuelve la fila de esa posici�n de la figura,
	int getColumna()const { return m_columna; }; //Devuelve la columna de esa posici�n de la figura.

private:
	int m_fila; //Atributo que representa la fila en la que est� esa posici�n.
	int m_columna; //Atributo que representa la columna en la que est� esa posici�n.
};

class Tauler; //Declaraci�n indirecta de la clase Tauler para tener as� la informaci�n para los m�todos.

//Declaraci�n de la clase Figura que contiene toda la informaci�n de la figura en juego (color,tipo,movimientos,giros...).

class Figura
{
public:
	Figura() { Tipus = NO_FIGURA; Color = NO_COLOR;} //Constructor por defecto.
	Figura(TipusFigura const& tipus, ColorFigura const& color, Posicio const Pos[],  Posicio const matriu[]); //Constructor con par�metros.

	Posicio getPosicio(int const& index)const { return PosicioFiguraTauler[index]; }; //M�todo que devuelve una posici�n en concreto de la figura.
	ColorFigura getColor()const { return Color; }; //M�todo que devuelve el color de la figura.

	void inicialitza(TipusFigura const& tipus, ColorFigura const& color, int const& fila, int const& columna,int const& gir); //M�todo que inicializa la figura en el tablero.
	bool desplacarLateral(DireccioDesplacar const& direccio,Tauler& tauler); //M�todo que deplaza hacia un lado la figura.
	bool Baixa(Tauler& tauler); //M�todo que hace bajar a la figura.
	bool Girar(DireccioGir const& dir, Tauler& tauler); //M�todo que gira la figura hacia una direcci�n.

private:
	void traspostaInicial();
	void Baixar(Tauler& tauler); //Subm�todo del m�todo Baixa.
	void desplacarEsquerra(Tauler& tauler); //Subm�todo del m�todo despla�arLateral.
	void desplacarDreta(Tauler&  tauler); //Subm�todo del m�todo despla�arLateral.
	bool potGirar(const Tauler &tauler,const DireccioGir& dir); //Subm�todo del m�todo Girar.
	void invertirFiles(); //Subm�todo de Girar y potGirar.
	void trasposta(Tauler& tauler); //Subm�todo de Girar y potGirar.
	void invertirColumnes(); //Subm�todo de Girar, inicialitza y potGirar.
	bool potDesplacarseEsquerra(const Tauler &tauler); //Subm�todo del m�todo despla�arLateral.
	bool potDesplacarseDreta(const Tauler &tauler); //Subm�todo del m�todo despla�arLateral.
	bool potBaixar(const Tauler &tauler); //Subm�todo de Baixa.
	TipusFigura Tipus; //Atributo de tipo TipusFigura que contiene el tipo de la figura.
	ColorFigura Color; //Atributo de tipo ColorFigura que contiene el color de la figura.
	Posicio PosicioFiguraTauler[POS_MAXFIGURA]; //Array de tipo Posicio que contiene cada posici�n de la figura respecto al tablero.
	Posicio posMatriuFigura[POS_MAXFIGURA]; //Array de tipo Posicio que contiene cada posici�n de la figura respecto a la matriz de cada figura.
	Posicio canvisRespecteTauler[POS_MAXFIGURA]; //Array de tipo Posicio que contiene cuanto se tiene que mover cada posici�n de la figura en el tablero. 
};
#endif