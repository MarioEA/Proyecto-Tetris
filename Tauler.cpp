#include "Tauler.h"

//Método de la clase Tauler sin retorno que recibe como parámetros un string con el nombre del fichero y una variable tipo Figura 
//que es donde hay que guardar toda la información de la figura que está en juego. En consecuencia, este método crea una variable 
//tipo ifstream llamada fitxer, la abre y a partir de ahí va insertando la información del fichero en todas las variables correspondientes 
//(tipo, color...). Seguidamente, utiliza un método de la clase Figura para inicializar la variable FiguraEnJoc (color, tipo, posición en tablero, matriz de ella...).
//Una vez inicializada la figura en juego, va insertando en el tablero toda la información restante del fichero para así inicializarlo correctamente.
//Por último, instaura la figura en juego en su posición inicial en el tablero, calculada en el método inicializa de la clase Figura, y cierra el fichero.

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

//Método de la clase Tauler sin retorno que recibe como parámetro una variable de tipo Figura que representa la figura que está en juego 
//y la que queremos instaurar en el tablero en su posición correspondiente. Por eso mismo, hacemos un bucle para obtener cada posición de la figura 
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

//Método de la clase Tauler sin retorno que recibe como parámetro las posiciones en el tablero de una figura y que con un bucle va eliminando del tablero.

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

//Método de la clase Tauler con retorno booleano, que recibe como parámetro una variable tipo Figura que corresponde a la figura en juego.
//Este método comprueba si cada posición de la figura está correctamente instaurada en él, es decir, si choca con otras figuras o si alguna posición 
//está fuera de los rangos del tablero. Devuelve true si está correcta en el tablero y false en caso contrario, cosa que hace con la variable booleana 
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

//Método de la clase Tauler con retorno tipo int que recibe como parámetro un array tipo int vacío llamado files.
//Este método recorre con el doble bucle todo el tablero en busca de filas completas, para eso usa la variable booleana
//completa que solo será true si todas las posciones de la fila son diferentes a POSICIO_BUIDA. En caso de que la fila sea
//completa la guarda en el array files en la posición correspondiente (si es la primera fila que se guarda en la 0,si es la segunda 1...).
//Finalmente, este método devuelve el número de filas completas en la variable numFilesCompletes.

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


//Método de la clase Tauler sin retorno que recibe como parámetros el array de filas completas (esta vez no está vacío) y el número de las filas eliminadas. Este método tiene la función de eliminar 
//las filas completas que se reciben a través del array files. Para eso se utiliza el primer bucle for donde se ponen a POSICIO_BUIDA todas las posiciones que ocupen las filas correspondientes que 
//están completas según el array files. Una vez se eliminan las filas completas hay que bajar todas las posiciones que estén por encima de cada fila eliminada. Para eso, se utiliza el triple bucle for donde el primero la i representa 
//el índice del array files. En el segundo iniciamos la fila en la fila i eliminada dependiendo del valor de i. Un ejemplo, si i = 2 la fila la iniciaremos en la fila que tiene guardado el array files en la 
//posición 2 y así con todas sucesivamente. Una vez estamos en esa fila en concreta eliminada, vamos recorriendo todas las filas hacia arriba y bajando una posición a todos los bloques de cada fila, hasta que 
//lleguemos a la fila 0 donde la pondremos toda en POSICIO_BUIDA para así conseguir que todos los bloques que están por encima de la fila eliminada bajen una su posición.

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

//Método de la clase Tauler sin retorno que recibe una variable tipo ofstream llamada output.Este método es el encargado de
//meter en esta variable output todo el tablero de ese instante de tiempo.

void Tauler::estatTauler(ofstream& output)
{
	for (int f = 0; f < MAX_FILES; f++)
	{
		for (int c = 0; c < MAX_COLUMNES; c++)
			output << m_tauler[f][c];
	}
}

//Método de la clase Tauler con retorno tipo Tauler que hace una copia del tablero de ese instante de tiempo a una variable tipo Tauler
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