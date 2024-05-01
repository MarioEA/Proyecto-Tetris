#include "Joc.h"

//M�todo de la clase Joc sin retorno que recibe un string con el nombre del fichero que contiene toda la informaci�n del tablero inicial.
//Para iniciar el tablero, se utiliza un m�todo de la clase Tauler al que se le env�a el nombre del fichero, que recibe este m�todo,
//y tambi�n la figura en juego para que se le guarde toda la informaci�n a esta. Finalmente iniciamos la puntuaci�n en 0 junto al nivel.

void Joc::inicialitza(const string& nomFitxer) {

	tauler.incialitzaTauler(nomFitxer,FiguraEnJoc);
	m_puntuacio = 0;
	m_nivell = 0;
}

//M�todo de la clase Joc con retorno booleano que recibe una direcci�n de tipo DireccioGir. Esta direcci�n indica en que sentido tiene que
//girar la figura en juego. Este m�todo utiliza un m�todo de la clase Figura para as� hacer que gire la figura en el tablero correspondiente.
//Por ello, se le env�a como par�metro la direcci�n y el tablero en tiempo real. Si este m�todo devuelve false quiere decir que la figura
//no puede girar en el tablero, si no pone la figura en el tablero en su posici�n correspondiente, por lo tanto, devuelve true.

bool Joc::giraFigura(DireccioGir direccio)
{
	if (FiguraEnJoc.Girar(direccio,tauler))
	{
		tauler.setFiguraTauler(FiguraEnJoc);
		return true;
	}
	else
		return false;
}

//M�todo de la clase Joc con retorno booleano que recibe un variable tipo int (dirx) que indica hacia qu� lado se mueve la figura (Derecha = 1, Izquierda = -1).
//El m�todo hace que se mueva la figura hacia la derecha o izquierda, para ello, hace un cambio de tipo int a DireccioDespla�ar (dirx => direccio) y despu�s utiliza
//un m�todo de la clase Figura para mover la figura en juego hacia el lado indicado y en el tablero correspondiente. Si la figura puede moverse, la instaura en el tablero,
//y devuelve true, si no devuelve lo contrario.

bool Joc::mouFigura(int dirX)
{
	DireccioDesplacar direccio = DireccioDesplacar(dirX);
	if (FiguraEnJoc.desplacarLateral(direccio, tauler))
	{
		tauler.setFiguraTauler(FiguraEnJoc);
			return true;
	}
	else
		return false;
}

//M�todo de la clase Joc con retorno int que no recibe ning�n par�metro. Este m�todo hace que la figura baje una posici�n en el tablero indicado.
//Para ello, se declaran tres variables numFilesEliminades, acabat y numFilesCompletades de tipo int, booleano e int respectivamente. Por lo tanto, se comprueba si la figura en juego no
//puede bajar y si es as� se sit�a la figura en tablero. Seguidamente, se declara un array llamado filesEliminar con dimensi�n m�xima MAX_FILES (8), el cual sirve
//para guardar todas las filas que se tienen que eliminar. Se inicia un bucle while que mientras acabat sea falso se ir� ejecutando. Dentro del bucle, se instaura
//en numFilesCompletades las filas completas en el tablero en ese instante de tiempo. Para eso se utiliza el m�todo filaCompleta de la clase Tauler el cual devuelve
//las filas completas. filaCompleta tambi�n recibe el array filesEliminar y all� guarda en cada posici�n de �l las filas que hay que eliminar. Seguidamente, si las filas completas
//son mayores que cero se procede a eliminar estas, con el m�todo eliminarFiles de la clase tauler y sumar al numFilesEliminades el n�mero de filas completas ya que corresponde al n�mero de filas que se han eliminado.
//Si las filas completas no son mayores que cero acabat se vuelve true y, por lo tanto, se sale del bucle. Si la figura puede bajar, simplemente se sit�a la figura en el tablero. 
//Este m�todo devuelve el n�mero de filas eliminadas.

int Joc::baixaFigura()
{
	int numFilesEliminades = 0;
	int numFilesCompletes;
	bool acabat = false;
	if (!FiguraEnJoc.Baixa(tauler))
	{
		tauler.setFiguraTauler(FiguraEnJoc);
		int filesEliminar[MAX_FILES];
		while (!acabat)
		{
			numFilesCompletes = tauler.filaCompleta(filesEliminar);
			if (numFilesCompletes > 0) {
				tauler.eliminarFiles(filesEliminar, numFilesCompletes);
				numFilesEliminades += numFilesCompletes;
			}
			else
				acabat = true;
		}
	}
	else
		tauler.setFiguraTauler(FiguraEnJoc);

	return numFilesEliminades;
}

//M�todo de la clase Joc sin retorno que recibe par�metro tipo string con el nombre del fichero en el cual tiene que guardar las cosas. Para ello, se declara una variable tipo ofstream llamada
//Fitxer. Despu�s se abre esta variable con el nombre del fichero recibido como par�metro y si se ha abierto correctamente se utiliza el m�todo de la clase Tauler estatTauler para meter dentro
//de Fitxer todo el tablero correspondiente en ese instante de tiempo en concreto. Para ello se env�a como par�metro Fitxer. Finalmente se cierra el fichero.

void Joc::escriuTauler(const string& nomFitxer)
{
	ofstream Fitxer;
	Fitxer.open(nomFitxer);
	if (Fitxer.is_open())
	{
		tauler.estatTauler(Fitxer);
	}
	Fitxer.close();
}