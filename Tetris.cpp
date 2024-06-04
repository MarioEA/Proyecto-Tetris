#include "Tetris.h"
#include "GraphicManager.h"

void Tetris::iniciamodeNormal()
{
	string x, y, z;
	m_partida.inicialitza(0, x, y, z);
}

bool Tetris::jugaModeNormal(double deltaTime,bool& nivell,const bool& retro,const bool& pausa)
{
	bool finalitza;
	finalitza = m_partida.actualitza(0, deltaTime, nivell,retro,pausa);
	
	return finalitza;
}

void Tetris::iniciamodeTest(string const& fitxerInicial, string const& fitxerFigures, string const& fitxerMoviments)
{
	m_partida.inicialitza(1, fitxerInicial, fitxerFigures, fitxerMoviments);
}

bool Tetris::jugaModeTest(double deltaTime,bool& nivell,const bool& pausa)
{
	bool finalitza;
	bool retro;
	finalitza = m_partida.actualitza(1, deltaTime, nivell,retro,pausa);
	return finalitza;
}
void Tetris:: mostraPuntuacio()
{
	if (!m_llista.empty())
	{
		list<LlistaPuntuacio>::iterator index;
		index = m_llista.begin();
		string msg = "LLISTA TOP 10 MILLORS JUGADORS";
		string msgBarra = "-----------------------------------------------------";
		GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
		GraphicManager::getInstance()->drawSprite(GRAFIC_FONS_PERSONALITZAT, 0, -595, false);
		GraphicManager::getInstance()->drawFont(FONT_RED_30, 50, 60, 1.0, msg);
		GraphicManager::getInstance()->drawFont(FONT_RED_30, 50, 80, 1.0, msgBarra);
		int contador = 0;
		int suma = 0;
		int dim = m_llista.size();
		while (contador != 10 and contador < dim)
		{
			int puntuacio = index->getPuntuacio();
			string nom = index->getNom();
			string msg2 = to_string(contador + 1) + "-" + nom + " " + to_string(puntuacio);
			GraphicManager::getInstance()->drawFont(FONT_WHITE_30, 150, 120 + suma, 0.7, msg2);
			suma += 35;
			contador++;
			index++;
		}
	}
	else
	{
		string msg = "NO HI HA CAP JUGADOR REGISTRAT";
		GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
		GraphicManager::getInstance()->drawSprite(GRAFIC_FONS_PERSONALITZAT, 0, -595, false);
		GraphicManager::getInstance()->drawFont(FONT_WHITE_30, 100, 300, 0.7, msg);
	}
	
}


void Tetris::iniciaLlistaPuntuacio(const string& nomFitxer)
{
	ifstream fitxer;
	fitxer.open(nomFitxer);
	if (fitxer.is_open())
	{
		LlistaPuntuacio element;
		int puntuacio;
		string nom;
		while (fitxer >> nom)
		{
			fitxer >> puntuacio;
			element.setNom(nom);
			element.setPuntuacio(puntuacio);
			m_llista.push_back(element);
		}
	}
	fitxer.close();
}

void Tetris::afegeixElementLlista(const LlistaPuntuacio& element,const string& nomFitxer)
{
	int puntuacio = element.getPuntuacio();
	list<LlistaPuntuacio>::iterator index, final;
	index = m_llista.begin();
	final = m_llista.end();
	bool sortir = false ;
	while (index != final and !sortir)
	{
		if (puntuacio > index->getPuntuacio())
			sortir = true;
		else
			index++;
	}
	m_llista.insert(index, element);
	ofstream fitxer;
	fitxer.open(nomFitxer);

	if(fitxer.is_open())
	{ 
		index = m_llista.begin();
		final = m_llista.end();
		while (index != final)
		{
			fitxer << index->getNom() << " " << index->getPuntuacio() << endl;
			index++;
		}
	}
	fitxer.close();
}