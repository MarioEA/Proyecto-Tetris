#ifndef TETRIS_H
#define TETRIS_H
#include "Partida.h"
#include <list>

class LlistaPuntuacio
{
public:
	int getPuntuacio()const { return m_puntuacio; }
	string getNom()const { return m_nom; }
	void setPuntuacio(const int& puntuacio) { m_puntuacio = puntuacio; }
	void setNom(const string& nom) { m_nom = nom; }
private:
	int m_puntuacio;
	string m_nom;
};

class Tetris
{
public:
	void iniciamodeNormal();
	bool jugaModeNormal(double deltaTime,bool& nivell, const bool& retro, const bool& pausa);
	void mostraPuntuacio();
	void iniciaLlistaPuntuacio(const string& nomFitxer);
	bool jugaModeTest(double deltaTime,bool& nivell,const bool& pausa);
	void iniciamodeTest(string const& fitxerInicial, string const& fitxerFigures, string const& fitxerMoviments);
	void afegeixElementLlista(const LlistaPuntuacio& element,const string& nomFitxer);
	int getPuntuacioPartida()const { return m_partida.getPuntuacio();}
private:
	Partida m_partida;
	list<LlistaPuntuacio> m_llista;
};

#endif 