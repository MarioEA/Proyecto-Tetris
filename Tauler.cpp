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

//Método de la clase Tauler sin retorno que recibe el array anterior files (esta vez no está vacío) y número de filas que se tienen que eliminar, ya que están completas.
//Por eso, con el primer bucle elimina las filas correspondientes del array files y después calcula de esas filas eliminadas cuál es la máxima. Esto se hace para saber desde qué fila
//hay que empezar a recorrer el tablero para hacer que las figuras de arriba se bajen tantas veces como filas eliminadas (si numFiles es 2 las figuras de arriba de la fila máxima eliminada tendrán que bajar 2
//posiciones siempre y cuando puedan y no choquen con otras figuras o sobrepasen la fila máxima que se ha eliminado). Para hacer lo comentado anteriormente, se utiliza el triple bucle (for, for y while).
//En el primer for se inicia la variable k, que representa las filas del tablero, en la fila máxima eliminada anteriormente menos uno (ya que hay que mirar a partir de esta) y se va restando en uno hasta que llegue a la fila 0 que corresponderá que se ha 
//comprobado todo el tablero desde la fila máxima hacia arriba. El segundo bucle es otro for pero para ir recorriendo todas las columnas de la fila en concreto. Por lo tanto, si encontramos una posición que 
//no está vacía, iniciamos una variable llamada j en uno y otra llamada r en cero. Aplicamos un bucle while que mientras esta variable j sea menor al número de filas eliminadas más uno o esa posición pueda
//bajar se irá ejecutando. Esta variable j representa cuantas veces va a bajar la posición respecto a la fila inicial, por eso mismo si j es 2 y el numFiles + 1 = 2 se saldrá porque no tiene que bajar más, ya que habrá bajado 1 vez que 
//es lo máximo que tenía que bajar en ese caso concreto la posición, ya que numFiles = 1. La variable r representa la posición en la que está en ese momento de la iteración respecto a la fila inicial. Por eso mismo, una vez dentro del bucle, 
//se comprueba si la siguiente posición está disponible para que baje => "if (m_tauler[k+j][x] == POSICIO_BUIDA)" y si es así si la fila a la que va a bajar es mayor a la fila máxima no tiene que bajar más => "if (k + j > filaMax)". En caso contrario, baja en una la posición, y se incrementan las variables
//j y r. Hay que aclarar que todo se hace respecto a la posición inicial, por eso existen las variables j y r. Ya que por ejemplo, si ya ha bajado una vez la posición r = 1 (ya que la posición referencia donde está en ese momento es la fila original +1) y j = 2 (ya que la posición donde tiene que moverse es fila original + 2), por lo tanto, al sumar =>
//si fila original k=4 => m_tauler[k+j][x] que corresponde la siguiente posición que tiene que bajar, será igual a (fila = 6, columna = x) y m_tauler[k+r][x] que corresponde a la posición en la que está en esa
//iteración, será igual a (fila = 5, columna = x), de esa manera se comprueba en cada iteración si puede bajar y si no es así se quedará en la posición en la que estaba.

void Tauler::eliminarFiles(const int files[],const int& numFiles)
{
	int j, r;
	bool haDeBaixar;
	for (int f = 0; f < numFiles; f++)
	{
		for (int c = 0; c < MAX_COLUMNES; c++)
			m_tauler[files[f]][c] = POSICIO_BUIDA;
	}

	int filaMax = files[0];
	for (int i = 1; i < numFiles; i++)
	{
		if (files[i] > filaMax)
			filaMax = files[i];
	}

	for (int k = filaMax - 1; k > -1; k--)
	{
		for (int x = 0; x < MAX_COLUMNES; x++)
		{
			if (m_tauler[k][x] != POSICIO_BUIDA)
			{
				j = 1;
				r = 0;
				haDeBaixar = true;
				while (j < (numFiles +1) and haDeBaixar)
				{
					if (m_tauler[k+j][x] == POSICIO_BUIDA )
					{
						if (k + j > filaMax) {
							haDeBaixar = false;
						}
						else
						{
							m_tauler[k+j][x] = m_tauler[k+r][x];
							m_tauler[k+r][x] = POSICIO_BUIDA;
							j++;
							r++;
						}
					}
					else
						haDeBaixar=false;
				}
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