#include "Tauler.h"

//M�todo de la clase Tauler sin retorno que recibe como par�metros un string con el nombre del fichero y una variable tipo Figura 
//que es donde hay que guardar toda la informaci�n de la figura que est� en juego. En consecuencia, este m�todo crea una variable 
//tipo ifstream llamada fitxer, la abre y a partir de ah� va insertando la informaci�n del fichero en todas las variables correspondientes 
//(tipo, color...). Seguidamente, utiliza un m�todo de la clase Figura para inicializar la variable FiguraEnJoc (color, tipo, posici�n en tablero, matriz de ella...).
//Una vez inicializada la figura en juego, va insertando en el tablero toda la informaci�n restante del fichero para as� inicializarlo correctamente.
//Por �ltimo, instaura la figura en juego en su posici�n inicial en el tablero, calculada en el m�todo inicializa de la clase Figura, y cierra el fichero.

void Tauler::incialitzaTauler(const string& nomFitxer,Figura &FiguraEnJoc) 
{
	ifstream fitxer;
	fitxer.open(nomFitxer);
	if (fitxer.is_open())
	{
		int tipus;
		int fila, columna;
		int gir;
		fitxer >> tipus >> fila >> columna >> gir;
		TipusFigura Tipus = TipusFigura(tipus);
		ColorFigura Color = ColorFigura(tipus);		
		FiguraEnJoc.inicialitza(Tipus, Color, fila, columna, gir);

			for(int f = 0; f < MAX_FILES; f++)
			{
				for (int c = 0; c < MAX_COLUMNES; c++)
				{
					int codi;
					fitxer >> codi;
					m_tauler[f][c] = CodiTauler(codi);
				}
			}

			for (int i = 0; i < POS_MAXFIGURA; i++)
			{
				Posicio x = FiguraEnJoc.getPosicio(i);
				int fila = x.getFila();
				int columna = x.getColumna();
				m_tauler[fila][columna] = CodiTauler(Color);
			}
	}
	fitxer.close();
}

//M�todo de la clase Tauler sin retorno que recibe como par�metro una variable de tipo Figura que representa la figura que est� en juego 
//y la que queremos instaurar en el tablero en su posici�n correspondiente. Por eso mismo, hacemos un bucle para obtener cada posici�n de la figura 
//y la vamos metiendo en el tablero.

void Tauler::setFiguraTauler(const Figura& FiguraEnJoc)
{
	for (int i = 0; i < POS_MAXFIGURA; i++)
	{
		Posicio pos = FiguraEnJoc.getPosicio(i);
		int fila = pos.getFila();
		int columna = pos.getColumna();
		CodiTauler codi = CodiTauler(FiguraEnJoc.getColor());
		m_tauler[fila][columna] = codi;
	}
}

//M�todo de la clase Tauler sin retorno que recibe como par�metro las posiciones en el tablero de una figura y que con un bucle va eliminando del tablero.

void Tauler::eliminarFiguraTauler(const Posicio posFigura[])
{
	for (int i = 0; i < POS_MAXFIGURA; i++)
	{
		Posicio pos = posFigura[i];
		int fila = pos.getFila();
		int columna = pos.getColumna();
		m_tauler[fila][columna] = POSICIO_BUIDA;
	}

}

//M�todo de la clase Tauler con retorno booleano, que recibe como par�metro una variable tipo Figura que corresponde a la figura en juego.
//Este m�todo comprueba si cada posici�n de la figura est� correctamente instaurada en �l, es decir, si choca con otras figuras o si alguna posici�n 
//est� fuera de los rangos del tablero. Devuelve true si est� correcta en el tablero y false en caso contrario, cosa que hace con la variable booleana 
//pot.

bool Tauler::FiguraCorrectaTauler(const Figura& FiguraEnJoc)const
{
	bool pot = true;
	int i = 0;
	while (i < POS_MAXFIGURA and pot)
	{
		Posicio PosTemp;
		PosTemp = FiguraEnJoc.getPosicio(i);
		int fila = PosTemp.getFila();
		int columna = PosTemp.getColumna();
		if (m_tauler[fila] [columna] != POSICIO_BUIDA or columna > 7 or fila > 7 or columna < 0)
		{
			pot = false;
		}
		else
			i++;
	}
	return pot;
}

//M�todo de la clase Tauler con retorno tipo int que recibe como par�metro un array tipo int vac�o llamado files.
//Este m�todo recorre con el doble bucle todo el tablero en busca de filas completas, para eso usa la variable booleana
//completa que solo ser� true si todas las posciones de la fila son diferentes a POSICIO_BUIDA. En caso de que la fila sea
//completa la guarda en el array files en la posici�n correspondiente (si es la primera fila que se guarda en la 0,si es la segunda 1...).
//Finalmente, este m�todo devuelve el n�mero de filas completas en la variable numFilesCompletes.

int Tauler::filaCompleta(int files[])const
{
	int numFilesCompletes = 0;
	bool completa;
	int c = 0;
	for (int f = 0; f < MAX_FILES; f++)
	{
		c = 0;
		completa = true;
		while(c < MAX_COLUMNES and completa)
		{
			if (m_tauler[f][c] != POSICIO_BUIDA) {
				completa = true;
				c++;
			}
			else
				completa = false;
		}
		if (completa)
		{
			files[numFilesCompletes++] = f;
		}
	}
	return numFilesCompletes;
}


//M�todo de la clase Tauler sin retorno que recibe como par�metros el array de filas completas (esta vez no est� vac�o) y el n�mero de las filas eliminadas. Este m�todo tiene la funci�n de eliminar 
//las filas completas que se reciben a trav�s del array files. Para eso se utiliza el primer bucle for donde se ponen a POSICIO_BUIDA todas las posiciones que ocupen las filas correspondientes que 
//est�n completas seg�n el array files. Una vez se eliminan las filas completas hay que bajar todas las posiciones que est�n por encima de cada fila eliminada. Para eso, se utiliza el triple bucle for donde el primero la i representa 
//el �ndice del array files. En el segundo iniciamos la fila en la fila i eliminada dependiendo del valor de i. Un ejemplo, si i = 2 la fila la iniciaremos en la fila que tiene guardado el array files en la 
//posici�n 2 y as� con todas sucesivamente. Una vez estamos en esa fila en concreta eliminada, vamos recorriendo todas las filas hacia arriba y bajando una posici�n a todos los bloques de cada fila, hasta que 
//lleguemos a la fila 0 donde la pondremos toda en POSICIO_BUIDA para as� conseguir que todos los bloques que est�n por encima de la fila eliminada bajen una su posici�n.

void Tauler::eliminarFiles(const int files[],const int& numFiles)
{
	int j, r;
	bool haDeBaixar;
	for (int f = 0; f < numFiles; f++)
	{
		for (int c = 0; c < MAX_COLUMNES; c++)
			m_tauler[files[f]][c] = POSICIO_BUIDA;
	}

	for (int i = 0; i < numFiles; i++)
	{
		for (int f = files[i]; f > -1; f--)
		{
			for (int c = 0; c < MAX_COLUMNES; c++)
			{
				if (f != 0)
				{
					m_tauler[f][c] = m_tauler[f - 1][c];
				}
				else
					m_tauler[f][c] = POSICIO_BUIDA;
				
			}
				
		}
	}
	
}

//M�todo de la clase Tauler sin retorno que recibe una variable tipo ofstream llamada output.Este m�todo es el encargado de
//meter en esta variable output todo el tablero de ese instante de tiempo.

void Tauler::estatTauler(ofstream& output)
{
	for (int f = 0; f < MAX_FILES; f++)
	{
		for (int c = 0; c < MAX_COLUMNES; c++)
			output << m_tauler[f][c];
	}
}

//M�todo de la clase Tauler con retorno tipo Tauler que hace una copia del tablero de ese instante de tiempo a una variable tipo Tauler
//llamada copiaTauler y la devuelve.

Tauler Tauler::CopiaTauler()const
{
	Tauler copiaTauler;
	for (int f = 0; f < MAX_FILES; f++)
	{
		for (int c = 0; c < MAX_COLUMNES; c++)
		{
			copiaTauler.m_tauler[f][c] = m_tauler[f][c];
		}
	}
	return copiaTauler;
}