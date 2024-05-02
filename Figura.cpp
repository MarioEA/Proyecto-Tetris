#include "Tauler.h"


//M�todo de la clase Figura sin retorno que recibe como par�metro una variable de tipo Tauler que representa 
//el tablero en juego en ese instante de tiempo en concreto. Este m�todo sirve para hacer que la figura en juego 
//baje una posici�n. Para ello, primero se elimina la figura del tablero con el m�todo de la clase Tauler 
//eliminaFiguraTauler y seguidamente con un bucle for se va incrementando en uno las filas de cada posici�n de la figura.

void Figura::Baixar(Tauler& tauler)
{
	tauler.eliminarFiguraTauler(PosicioFiguraTauler);
	for (int i = 0; i < POS_MAXFIGURA; i++) {
		
		int fila = PosicioFiguraTauler[i].getFila() + 1;
		PosicioFiguraTauler[i].setFila(fila);
	}
}

//M�todo de la clase Figura sin retorno que recibe como par�metro una variable de tipo Tauler que representa 
//el tablero en juego en ese instante de tiempo en concreto. Este m�todo sirve para hacer que la figura en juego 
//se mueva una posici�n hacia la derecha. Para ello, primero se elimina la figura del tablero con el m�todo de la clase Tauler 
//eliminaFiguraTauler y seguidamente con un bucle for se va incrementando en uno las columnas de cada posici�n de la figura.

void Figura::desplacarDreta(Tauler& tauler)
{
	tauler.eliminarFiguraTauler(PosicioFiguraTauler);
	for (int i = 0; i < POS_MAXFIGURA; i++) {
		int columna = PosicioFiguraTauler[i].getColumna() + 1;
		PosicioFiguraTauler[i].setColumna(columna);
	}
}

//M�todo de la clase Figura sin retorno que recibe como par�metro una variable de tipo Tauler que representa 
//el tablero en juego en ese instante de tiempo en concreto. Este m�todo sirve para hacer que la figura en juego 
//se mueva una posici�n hacia la izquierda. Para ello, primero se elimina la figura del tablero con el m�todo de la clase Tauler 
//eliminaFiguraTauler y seguidamente con un bucle for se va decrementando en uno las columnas de cada posici�n de la figura.

void Figura::desplacarEsquerra(Tauler& tauler)
{
	tauler.eliminarFiguraTauler(PosicioFiguraTauler);
	for (int i = 0; i < POS_MAXFIGURA; i++) {
		int columna = PosicioFiguraTauler[i].getColumna() - 1;
		PosicioFiguraTauler[i].setColumna(columna);
	}
}

//M�todo de la clase Figura sin retorno que recibe como par�metros el tipo de la figura, el color, la fila donde se encuentra la posici�n de referencia de la figura, la columna, y el 
//en que giro se encuentra. Este m�todo inicia cada atributo de la clase Figura con los par�metros recibidos (tipo, color...). Y seguidamente dependiendo del tipo de la figura utiliza un 
//switch case para iniciar las posiciones de la figura respecto al tablero (utilizando la fila y la columna recibidas como par�metros) y a su vez las posiciones de la figura respecto a la matriz 
//propia 3x3 (4x4 si es la figura I). Todo eso se guarda en los arrays tipo Posicio: PosicioFiguraTauler y posMatriuFigura. Finalmente, una vez se inicia la figura en su giro = 0 se ejecuta un bucle 
//for para hacer los giros hoararios correspondientes en los que en teor�a la figura est� iniciada, seg�n la variable gir recibida como par�metro. Para hacer los giros de la figura en concreto se 
//hace la traspuesta y seguidamente se invierten las columnas que son dos m�todos de la clase Figura tambi�n.

void Figura::inicialitza(TipusFigura const& tipus, ColorFigura const& color, int const& fila, int const& columna, int const& gir)
{
	Tipus = tipus;
	Color = color;
	int nPosicio = 0;
	switch (Tipus)
	{
	case FIGURA_O:
	{
		for (int f = fila-1; f < fila + 2; f++)
		{
			for (int c = columna; c < columna + 2; c++)
			{
				PosicioFiguraTauler[nPosicio].setFila(f);
				PosicioFiguraTauler[nPosicio].setColumna(c);
				nPosicio++;
			}
		}
	}
	break;
	case FIGURA_I:
	{
		for (int f = fila; f < fila + 1; f++)
		{
			for (int c = columna - 1; c < columna + 3; c++)
			{
				PosicioFiguraTauler[nPosicio].setFila(f);
				PosicioFiguraTauler[nPosicio].setColumna(c);
				nPosicio++;
			}
		}
		for (int k = 1; k < 2; k++)
		{
			for (int x = 0; x < 4; x++)
			{
				posMatriuFigura[x].setFila(k);
				posMatriuFigura[x].setColumna(x);
			}
		}
	}
	break;
	case FIGURA_T:
	{
		bool primer = true;
		int c = columna - 1;
		for (int i = 0; i < POS_MAXFIGURA; i++)
		{
			if (primer)
			{
				PosicioFiguraTauler[i].setFila(fila - 1);
				PosicioFiguraTauler[i].setColumna(columna);
				primer = false;
			}
			else
			{
				PosicioFiguraTauler[i].setFila(fila);
				PosicioFiguraTauler[i].setColumna(c);
				c++;
			}
		}
		primer = true;
		c = 0;
		for (int i = 0; i < POS_MAXFIGURA; i++)
		{
			if (primer)
			{
				posMatriuFigura[i].setFila(0);
				posMatriuFigura[i].setColumna(1);
				primer = false;
			}
			else
			{
				posMatriuFigura[i].setFila(1);
				posMatriuFigura[i].setColumna(c);
				c++;
			}
		}
	}
	break;
	case FIGURA_L:
	{
		bool primer = true;
		int c = columna - 1;
		for (int i = 0; i < POS_MAXFIGURA; i++)
		{
			if (primer)
			{
				PosicioFiguraTauler[i].setFila(fila - 1);
				PosicioFiguraTauler[i].setColumna(columna + 1);
				primer = false;
			}
			else
			{
				PosicioFiguraTauler[i].setFila(fila);
				PosicioFiguraTauler[i].setColumna(c);
				c++;
			}
		}
		primer = true;
		c = 0;
		for (int i = 0; i < POS_MAXFIGURA; i++)
		{
			if (primer)
			{
				posMatriuFigura[i].setFila(0);
				posMatriuFigura[i].setColumna(2);
				primer = false;
			}
			else
			{
				posMatriuFigura[i].setFila(1);
				posMatriuFigura[i].setColumna(c);
				c++;
			}
		}

	}
	break;
	case FIGURA_J:
	{
		bool primer = true;
		int c = columna - 1;
		for (int i = 0; i < POS_MAXFIGURA; i++)
		{
			if (primer)
			{
				PosicioFiguraTauler[i].setFila(fila - 1);
				PosicioFiguraTauler[i].setColumna(columna - 1);
				primer = false;
			}
			else
			{
				PosicioFiguraTauler[i].setFila(fila);
				PosicioFiguraTauler[i].setColumna(c);
				c++;
			}
		}
		primer = true;
		c = 0;
		for (int i = 0; i < POS_MAXFIGURA; i++)
		{
			if (primer)
			{
				posMatriuFigura[i].setFila(0);
				posMatriuFigura[i].setColumna(0);
				primer = false;
			}
			else
			{
				posMatriuFigura[i].setFila(1);
				posMatriuFigura[i].setColumna(c);
				c++;
			}
		}
	}
	break;
	case FIGURA_Z:
	{
		bool primer = true;
		int c = columna;
		int r = 1;
		for (int i = 0; i < POS_MAXFIGURA; i++)
		{
			if (primer)
			{
				PosicioFiguraTauler[i].setFila(fila - 1);
				PosicioFiguraTauler[i].setColumna(columna - r);
				r--;
				if (i == 1)
				{
					primer = false;
				}
			}
			else
			{
				PosicioFiguraTauler[i].setFila(fila);
				PosicioFiguraTauler[i].setColumna(c);
				c++;
			}
		}
		c = 1;
		r = 0;
		primer = true;
		for (int i = 0; i < POS_MAXFIGURA; i++)
		{
			if (primer)
			{
				posMatriuFigura[i].setFila(0);
				posMatriuFigura[i].setColumna(0 + r);
				r++;
				if (i == 1)
				{
					primer = false;
				}
			}
			else
			{
				posMatriuFigura[i].setFila(1);
				posMatriuFigura[i].setColumna(c);
				c++;
			}
		}
	}
	break;
	case FIGURA_S:
	{
		bool primer = true;
		int c = columna - 1;
		int r = 0;
		for (int i = 0; i < POS_MAXFIGURA; i++)
		{
			if (primer)
			{
				PosicioFiguraTauler[i].setFila(fila - 1);
				PosicioFiguraTauler[i].setColumna(columna + r);
				r++;
				if (i == 1)
				{
					primer = false;
				}
			}
			else
			{
				PosicioFiguraTauler[i].setFila(fila);
				PosicioFiguraTauler[i].setColumna(c);
				c++;
			}
		}
		c = 0;
		r = 0;
		primer = true;
		for (int i = 0; i < POS_MAXFIGURA; i++)
		{
			if (primer)
			{
				posMatriuFigura[i].setFila(0);
				posMatriuFigura[i].setColumna(1 + r);
				r++;
				if (i == 1)
				{
					primer = false;
				}
			}
			else
			{
				posMatriuFigura[i].setFila(1);
				posMatriuFigura[i].setColumna(c);
				c++;
			}
		}

	}break;
	}
		for (int k = 0; k < gir; k++)
		{
			traspostaInicial();
			invertirColumnes();
		}	
}

//Constructor con par�metros de la clase Figura que evidentemente recibe todos los par�metros necesarios para hacer una copia de la Figura.
//Este constructor inicia la nueva figura con todos los par�metros recibidos, para as� hacer una copia de la figura que env�as sus atributos como par�metros.

Figura::Figura(TipusFigura const& tipus, ColorFigura const& color, Posicio const Pos[],Posicio const matriu[])
{
	Tipus = tipus;
	Color = color;
	
	for (int i = 0; i < POS_MAXFIGURA; i++)
	{
		PosicioFiguraTauler[i].setColumna(Pos[i].getColumna());
		PosicioFiguraTauler[i].setFila(Pos[i].getFila());
		posMatriuFigura[i].setColumna(matriu[i].getColumna());
		posMatriuFigura[i].setFila(matriu[i].getFila());
	}
}
//M�todo de la clase Figura con retorno booleano que recibe como par�metros una variable tipo Tauler que representa el tablero en juego y la direcci�n del giro.
//Este m�todo sirve para comprobar si la figura puede hacer el giro horario o antihorario correspondiente. Para hacer esa comprovaci�n se hace una copia de la figura en juego
//en ese instante con el constructor con par�metros y a la vez se utiliza el m�todo de la clase Tauler CopiaTauler para hacer la copia del mismo. Con esas copias dependiendo del 
//giro que se quiera ejercer (horario o antihorario) se hace una cosa u otra. En el primer caso se hace la traspuesta de la copia de la figura en la copia del tablero 
//y se le invierte las columnas y despu�s con el m�todo de la clase tauler FiguraCorrectaTauler se comprueba que la copia de la figura est� correctamente situada en la copia del tablero. 
//En el segundo caso se hace exactamente lo mismo solo que en vez de invertir columnas
//se invierten las filas. El m�todo devuelve la variable booleana pot dependiendo si se puede ejercer el giro o no.

bool Figura::potGirar(const Tauler &tauler,DireccioGir const& dir)
{
	bool pot = true;
	Figura temp(Tipus, Color, PosicioFiguraTauler,posMatriuFigura);
	Tauler copiaTauler = tauler.CopiaTauler();
	if (dir == GIR_HORARI)
	{
		temp.trasposta(copiaTauler);
		temp.invertirColumnes();
		pot = copiaTauler.FiguraCorrectaTauler(temp);
		
	}
	else
	{
		temp.trasposta(copiaTauler);
		temp.invertirFiles();
		pot = copiaTauler.FiguraCorrectaTauler(temp);

	}
	return pot;
}

//M�todo de la clase Figura sin retorno y sin ning�n par�metro que sirve para invertir las filas de la figura.
//Para ello, se distinguen dos casos, cuando el tipo de figura es I, y cuando no lo es. Cuando no lo es el m�todo lo �nico
//que hace es invertir las filas de las posiciones de la figura respecto a la matriz y al tablero. Es decir, si una posici�n 
//tiene la fila 0 se intercambia con la que tiene la fila 2, y en las del tablero tambi�n. La posici�n respecto al tablero
//que corresponda a la que tiene la fila 0 en la matriz, se le sumar� dos a la fila y la que corresponda a la que tenga la fila 2, se le restar� y as� sucesivamente.
//Hay que aclarar que las posiciones de la matriz est�n ordenadas de la misma manera que las de respecto al tablero. Es decir, los cambios 
//que se hagan en las posiciones de la matriz tambi�n se hacen en la del tablero. Por ejemplo, si la posici�n 3 de la matriz tiene la fila = 0 y se le pone la fila 2, por ende la posici�n 3 del
//tablero se le sumar� dos a su fila y as� con todas las posiciones. De esa manera se consigue que las filas se inviertan tanto en la matriz como en el tablero. Como son todas 3x3 las que le correspondan la fila 1 no se tocar�n.
//En el caso de cuando el tipo es la figura I la �nica diferencia es que la que tenga la fila 0 se cambiar� con la que tenga la 3, la 1 con la 2, pero haciendo 
//el mismo procedimiento anteriormente explicado. 

void Figura::invertirFiles()
{
	if (Tipus != FIGURA_I) {
		for (int i = 0; i < POS_MAXFIGURA; i++) {
			if (posMatriuFigura[i].getFila() == 0) {
				posMatriuFigura[i].setFila(2);
				PosicioFiguraTauler[i].setFila(PosicioFiguraTauler[i].getFila() + 2);
			}
			else
			{
				if (posMatriuFigura[i].getFila() == 2) {
					posMatriuFigura[i].setFila(0);
					PosicioFiguraTauler[i].setFila(PosicioFiguraTauler[i].getFila() - 2);
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < POS_MAXFIGURA; i++) {

			switch (posMatriuFigura[i].getFila()) {
			case 0:
			{
				posMatriuFigura[i].setFila(3);
				PosicioFiguraTauler[i].setFila(PosicioFiguraTauler[i].getFila() + 3);
			}break;

			case 1:
			{
				posMatriuFigura[i].setFila(2);
				PosicioFiguraTauler[i].setFila(PosicioFiguraTauler[i].getFila() + 1);

			}break;
			case 2:
			{
				posMatriuFigura[i].setFila(1);
				PosicioFiguraTauler[i].setFila(PosicioFiguraTauler[i].getFila() - 1);
			}break;
			case 3:
			{
				posMatriuFigura[i].setFila(0);
				PosicioFiguraTauler[i].setFila(PosicioFiguraTauler[i].getFila() - 3);
			}break;
			}
		}
	}
}

//M�todo de la clase Figura sin retorno y sin ning�n par�metro que sirve para invertir las columnas de la figura.
//Para ello, se distinguen dos casos, cuando el tipo de figura es I, y cuando no lo es. Cuando no lo es el m�todo lo �nico
//que hace es invertir las columnas de las posiciones de la figura respecto a la matriz y al tablero. Es decir, si una posici�n 
//tiene la columna 0 se intercambia con la que tiene la columna 2, y en las del tablero tambi�n. La posici�n respecto al tablero
//que corresponda a la que tiene la columna 0 en la matriz, se le sumar� dos a la columna y la que corresponda a la que tenga la columna 2, se le restar� y as� sucesivamente.
//Hay que aclarar que las posiciones de la matriz est�n ordenadas de la misma manera que las de respecto al tablero. Es decir, los cambios 
//que se hagan en las posiciones de la matriz tambi�n se hacen en la del tablero. Por ejemplo, si la posici�n 3 de la matriz tiene la columna = 0 y se le pone la columna 2, por ende la posici�n 3 del
//tablero se le sumar� dos a su columna y as� con todas las posiciones. De esa manera se consigue que las columnas se inviertan tanto en la matriz como en el tablero. Como son todas 3x3 las que le correspondan la columna 1 no se tocar�n.
//En el caso de cuando el tipo es la figura I la �nica diferencia es que la que tenga la columna 0 se cambiar� con la que tenga la 3, la 1 con la 2, pero haciendo 
//el mismo procedimiento anteriormente explicado. 

void Figura::invertirColumnes()
{
	if (Tipus != FIGURA_I) {
		for (int i = 0; i < POS_MAXFIGURA; i++) {
			if (posMatriuFigura[i].getColumna() == 0) {
				posMatriuFigura[i].setColumna(2);
				PosicioFiguraTauler[i].setColumna(PosicioFiguraTauler[i].getColumna() + 2);
			}
			else
			{
				if (posMatriuFigura[i].getColumna() == 2) {
					posMatriuFigura[i].setColumna(0);
					PosicioFiguraTauler[i].setColumna(PosicioFiguraTauler[i].getColumna() - 2);
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < POS_MAXFIGURA; i++) {
			
			switch (posMatriuFigura[i].getColumna()) {
			case 0:
			{
				posMatriuFigura[i].setColumna(3);
				PosicioFiguraTauler[i].setColumna(PosicioFiguraTauler[i].getColumna() + 3);
			}break;

			case 1: 
			{
				posMatriuFigura[i].setColumna(2);
				PosicioFiguraTauler[i].setColumna(PosicioFiguraTauler[i].getColumna() + 1);

			}break;
			case 2:
			{
				posMatriuFigura[i].setColumna(1);
				PosicioFiguraTauler[i].setColumna(PosicioFiguraTauler[i].getColumna() - 1);
			}break;
			case 3:
			{
				posMatriuFigura[i].setColumna(0);
				PosicioFiguraTauler[i].setColumna(PosicioFiguraTauler[i].getColumna() - 3);
			}break;
			}
		}
	}	
}
				
//M�todo de la clase Figura que recibe como par�metro el tablero y que sirve para hacer la traspuesta de la figura.
//Primero elimina la figura del tablero, y seguidamente intercambia la fila y la columna de cada posici�n de la figura.
//Para hacer el giro de la figura en el tablero lo que se hace es antes de hacer la traspuesta en la matriz se guarda en array de 
//tipo Posicio llamado PoscioAntigua la posici�n original. Despu�s se hace la traspuesta solo con las posiciones de la matriz y en un array tipo
//Posicio llamado canvisRespecteTauler se va guardando la diferencia que hay entre la posici�n final y la original guardada en PosicioAntigua para as� saber cuanto se mueve la posici�n en la matriz. Evidentemente se hace 
//con la fila y la columna, y de esa manera se sabe cuanto se tiene que mover en el tablero, cada posici�n en el tablero. Ya que por ejemplo si antes ten�a la fila = 1 y despu�s 
//de invertir tiene la fila 0, la diferencia de 0 - 1 = -1, por lo tanto, sabemos que en esa posici�n en concreto a la fila hay que restarle uno en el tablero.
//Hay que aclarar que las posiciones de la matriz est�n ordenadas de la misma manera que las de respecto al tablero. Es decir, los cambios 
//que se hagan en las posiciones de la matriz tambi�n se hacen en la del tablero.

void Figura::trasposta(Tauler& tauler)
{
	    tauler.eliminarFiguraTauler(PosicioFiguraTauler);
		int temp;
		Posicio PosicioAntigua[POS_MAXFIGURA];
		for (int i = 0; i < POS_MAXFIGURA; i++)
		{
			PosicioAntigua[i] = posMatriuFigura[i];
			temp = posMatriuFigura[i].getFila();
			posMatriuFigura[i].setFila(posMatriuFigura[i].getColumna());
			posMatriuFigura[i].setColumna(temp);
			canvisRespecteTauler[i].setColumna(posMatriuFigura[i].getColumna() - PosicioAntigua[i].getColumna());
			canvisRespecteTauler[i].setFila(posMatriuFigura[i].getFila() - PosicioAntigua[i].getFila());
			PosicioFiguraTauler[i].setColumna(PosicioFiguraTauler[i].getColumna() + canvisRespecteTauler[i].getColumna());
			PosicioFiguraTauler[i].setFila(PosicioFiguraTauler[i].getFila() + canvisRespecteTauler[i].getFila());
		}
}

//M�todo exactamente igual que el de arriba, solo difiere en que no recibe el tablero y no se elimina la figura, ya que como se utiliza en el m�todo 
//Inicializa no hace falta tener el tablero.

void Figura::traspostaInicial()
{
	int temp;
	Posicio PosicioAntigua[POS_MAXFIGURA];
	for (int i = 0; i < POS_MAXFIGURA; i++)
	{
		PosicioAntigua[i] = posMatriuFigura[i];
		temp = posMatriuFigura[i].getFila();
		posMatriuFigura[i].setFila(posMatriuFigura[i].getColumna());
		posMatriuFigura[i].setColumna(temp);
		canvisRespecteTauler[i].setColumna(posMatriuFigura[i].getColumna() - PosicioAntigua[i].getColumna());
		canvisRespecteTauler[i].setFila(posMatriuFigura[i].getFila() - PosicioAntigua[i].getFila());
		PosicioFiguraTauler[i].setColumna(PosicioFiguraTauler[i].getColumna() + canvisRespecteTauler[i].getColumna());
		PosicioFiguraTauler[i].setFila(PosicioFiguraTauler[i].getFila() + canvisRespecteTauler[i].getFila());
	}
}

//M�todo de la clase Figura que recibe como par�metro una variable de tipo Tauler que representa el tablero en juego.
//Este m�todo es muy parecido a potGirar, simplemente que en vez de hacer el giro se hace que baje la copia de la figura en juego en la copia del tablero 
//y se comprueba si est� correcta en el tablero. O sea, comprueba si la figura puede seguir bajando.

bool Figura::potBaixar(const Tauler& tauler)
{
	bool pot = true;
	Figura temp(Tipus, Color, PosicioFiguraTauler,posMatriuFigura);
	Tauler copiaTauler = tauler.CopiaTauler();
	temp.Baixar(copiaTauler);
	pot = copiaTauler.FiguraCorrectaTauler(temp);
	return pot;
}

//Igual que la de arriba pero desplazando hacia la izquierda. Es decir,
//comprueba si se puede desplazar hacia la izquierda.

bool Figura::potDesplacarseEsquerra(const Tauler& tauler)
{
	bool pot = true;
	Figura temp(Tipus, Color, PosicioFiguraTauler,posMatriuFigura);
	Tauler copiaTauler = tauler.CopiaTauler();
	temp.desplacarEsquerra(copiaTauler);
	pot = copiaTauler.FiguraCorrectaTauler(temp);
	return pot;
}

//Igual pero hacia la derecha.

bool Figura::potDesplacarseDreta(const Tauler& tauler)
{
	bool pot = true;
	Figura temp(Tipus, Color, PosicioFiguraTauler,posMatriuFigura);
	Tauler copiaTauler = tauler.CopiaTauler();
	temp.desplacarDreta(copiaTauler);
	pot = copiaTauler.FiguraCorrectaTauler(temp);
	return pot;
}


//M�todo de la clase Figura que recibe como par�metro la direcci�n en la cual se quiere mover la figura, y el tablero, y dependiendo de
//a que lado se quiera mover comprueba si se puede mover hacia ese lado y si puede la desplaza hacia ese lado. El m�todo devuelve true si 
//se puede desplazar hacia un lado y false en caso contrario.

bool Figura::desplacarLateral(DireccioDesplacar const& direccio, Tauler& tauler)
{   
	bool potDespla�arse = true;
	if (direccio == MOU_DRETA)
	{
		if (potDesplacarseDreta(tauler))
			desplacarDreta(tauler);
		else
			potDespla�arse = false;
	}
	else {
		if (potDesplacarseEsquerra(tauler)) 	
			desplacarEsquerra(tauler);
		else 
			potDespla�arse = false;
	}
	return potDespla�arse;
}

//M�todo de la clase Figura que recibe como par�metro el tablero, comprueba si puede bajar y si puede hace que baje la figura en el tablero.
//El m�todo devuelve true si puede bajar y false en caso contrario.

bool Figura::Baixa(Tauler& tauler)
{
	bool Baixa = true;
	if (potBaixar(tauler))
	{
		Baixar(tauler);
	}
	else
		Baixa = false;

	return Baixa;
}

//M�todo de la clase Figura que recibe como par�metro la direcci�n donde quiere hacer el giro de la figura y el tablero.
//El m�todo comprueba si puede girar hacia la direcci�n indicada y si puede dependiendo de la direcci�n la gira hacia ese sentido.
//El m�todo devuelve true si se ha podido hacer el giro y false en caso contrario.

bool Figura::Girar(DireccioGir const& dir, Tauler& tauler)
{
	if (potGirar(tauler,dir))
	{
			if (dir == GIR_HORARI)
			{
				trasposta(tauler);
				invertirColumnes();
			}
			else
			{
				trasposta(tauler);
				invertirFiles();
			}
		return true;
	}
	else
		return false;	
}