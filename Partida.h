#ifndef PARTIDA_H
#define PARTIDA_H

#include <stdio.h>
#include <string>
#include "InfoJoc.h"
#include "Joc.h"

using namespace std;

class FitxerFigures
{
public:
    FitxerFigures() { fitxer_tipus = NO_FIGURA; fitxer_fila = 0; fitxer_columna = 0; fitxer_gir = 0; }


    void iniciaFiguraFitxer(const TipusFigura& tipus, const int& fila, const int& columna, const int& gir) { fitxer_tipus = tipus; fitxer_fila = fila; fitxer_columna = columna; fitxer_gir = gir; }
    void retornaFiguraFitxer(TipusFigura& tipus, int& fila, int& columna, int& gir)const { tipus = fitxer_tipus; fila = fitxer_fila; columna = fitxer_columna; gir = fitxer_gir; }
    void operator=(const FitxerFigures& figura);
private:
    TipusFigura fitxer_tipus;
    int fitxer_fila;
    int fitxer_columna;
    int fitxer_gir;
};

class NodeMoviment
{
public:
    NodeMoviment() { m_next = nullptr;}
    ~NodeMoviment() {};

    TipusMoviment& getMoviment() { return m_moviment; }
    NodeMoviment* getNext() { return m_next; }
    void setMoviment(const TipusMoviment& moviment) { m_moviment = moviment; }
    void setNext(NodeMoviment* next) { m_next = next; }
private:
    TipusMoviment m_moviment;
    NodeMoviment* m_next;
    
};
class NodeFigura
{
public:
    NodeFigura() { m_next = nullptr; }
    ~NodeFigura() {};

    FitxerFigures& getFigura(){ return m_figura; }
    NodeFigura* getNext(){ return m_next; }
    void setFigura(const FitxerFigures& figura) { m_figura = figura; }
    void setNext(NodeFigura* next) { m_next = next; }
    
private:
    FitxerFigures m_figura;
    NodeFigura* m_next;
};


class Partida 
{
public:
    Partida();

    TipusMoviment getMoviment();
    bool actualitzaFiguraFitxer();
    bool actualitzaFiguraAleatoria();
    
    int getPuntuacio()const { return m_puntuacio; }
    void inicialitza(int mode, const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments);
    bool actualitza(int mode,double deltaTime,bool& nivell,const bool& retro, const bool& pausa);

private:
    double m_temps;
    Joc m_joc;
    int m_puntuacio;
    int m_nivell;
    NodeMoviment* m_moviment;    
    NodeFigura* m_figures;
    int m_fila;
    int m_columna;
    float m_intervalTemps;
    int m_pujaNivell;
    float m_progresiu;
    bool progresiu;
};

#endif 
