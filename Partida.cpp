#include "Partida.h"
#include "InfoJoc.h"
#include"GraphicManager.h"



void FitxerFigures::operator=(const FitxerFigures& figura) {
    fitxer_tipus = figura.fitxer_tipus;
    fitxer_fila = figura.fitxer_fila;
    fitxer_columna = figura.fitxer_columna;
    fitxer_gir = figura.fitxer_gir;
}

Partida::Partida()
{
    m_temps = 0;
    m_puntuacio = 0;
    m_nivell = 0;
    m_intervalTemps = 0.8;
    m_pujaNivell = 1000;
    m_progresiu = 0.8;
    progresiu = true;
}
bool Partida::actualitzaFiguraAleatoria()
{
   bool finalitza;
   finalitza = m_joc.actualitzaAleatori(m_fila,m_columna);
   return finalitza;
}
bool Partida::actualitzaFiguraFitxer()
{
    bool finalitza;
    NodeFigura* NodeEliminar;
    NodeEliminar = m_figures;
    FitxerFigures figura = m_figures->getFigura();
    m_figures = m_figures->getNext();
    delete NodeEliminar;
    int gir;
    TipusFigura tipus;
    ColorFigura color;
    figura.retornaFiguraFitxer(tipus, m_fila, m_columna, gir);
    color = ColorFigura(tipus);
    Figura figuraSeguent;
    figuraSeguent.inicialitza(tipus, color, m_fila, m_columna, gir);
    finalitza = m_joc.actualitzaFiguraFitxer(figuraSeguent, m_fila, m_columna);
    return finalitza;
}
TipusMoviment Partida::getMoviment()
{
    NodeMoviment* NodeEliminar;
    NodeEliminar = m_moviment;
    TipusMoviment mov = m_moviment->getMoviment();
    m_moviment = m_moviment->getNext();
    delete NodeEliminar;
    return mov;
}

void Partida::inicialitza(int mode, const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments)
{
    if (mode == 1)
    {
        m_joc.inicialitzaFitxer(fitxerInicial,m_fila,m_columna);
        ifstream figuresFitxer;
        figuresFitxer.open(fitxerFigures);
        if (figuresFitxer.is_open())
        {
            m_figures = new NodeFigura;
            NodeFigura* NodeActual;
            NodeFigura* NouNode;
            TipusFigura tipus;
            int Tipus, fila, columna, gir;
            FitxerFigures figura;
            figuresFitxer >> Tipus >> fila >> columna >> gir;
            tipus = TipusFigura(Tipus);
            Figura figuraSeguent;
            ColorFigura color = ColorFigura(tipus);
            figuraSeguent.inicialitza(tipus, color, fila, columna, gir);
            m_joc.inicialitzaSeguentFiguraFitxer(figuraSeguent);
            figuresFitxer >> Tipus >> fila >> columna >> gir;
            tipus = TipusFigura(Tipus);
            figura.iniciaFiguraFitxer(tipus, fila, columna, gir);
            m_figures->setFigura(figura);
            
            while (figuresFitxer >> Tipus)
            {
               NodeActual = m_figures;

               while (NodeActual->getNext() != nullptr) 
                   NodeActual = NodeActual->getNext();

               NouNode = new NodeFigura;
               figuresFitxer >> fila >> columna >> gir;
               tipus = TipusFigura(Tipus);
               figura.iniciaFiguraFitxer(tipus, fila, columna, gir);
               NouNode->setFigura(figura);
               NodeActual->setNext(NouNode);
            }
        }
        figuresFitxer.close();

        ifstream movimentsFitxer;
        movimentsFitxer.open(fitxerMoviments);
        if (movimentsFitxer.is_open())
        {
            m_moviment = new NodeMoviment;
            NodeMoviment* NodeActual;
            NodeMoviment* NouNode;
            TipusMoviment moviment;
            int mov;
            movimentsFitxer >> mov;
            moviment = TipusMoviment(mov);
            m_moviment->setMoviment(moviment);
            while (movimentsFitxer >> mov)
            {
                NodeActual = m_moviment;
                while (NodeActual->getNext() != nullptr)
                    NodeActual = NodeActual->getNext();

                NouNode = new NodeMoviment;
                moviment = TipusMoviment(mov);
                NouNode->setMoviment(moviment);
                NodeActual->setNext(NouNode);
            }
        }
        movimentsFitxer.close();
    }
    else
        if(mode==0)
            m_joc.inicialitzaAleatori(m_fila, m_columna);    
}


bool Partida::actualitza(int mode,double deltaTime,bool& nivell, const bool& retro, const bool& pausa)
{
    if (mode == 1)
    {
        GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
        GraphicManager::getInstance()->drawSprite(GRAFIC_FONS_PERSONALITZAT, 0, -595, false);
        GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER, false);
        
        string msg = "Fila: " + to_string(m_fila) + ", Columna: " + to_string(m_columna);
        GraphicManager::getInstance()->drawFont(FONT_GREEN_30, POS_X_TAULER, POS_Y_TAULER - 50, 0.5, msg);
        string msg2 = "Puntuacio: " + to_string(m_puntuacio);
        GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER, POS_Y_TAULER - 70, 0.5, msg2);
        string msg3 = "Nivell: " + to_string(m_nivell);
        GraphicManager::getInstance()->drawFont(FONT_RED_30, POS_X_TAULER + 200, POS_Y_TAULER - 50, 0.5, msg3);

        Figura figuraSeguent = m_joc.getFiguraSeguent();
        
        for (int i = 0; i < POS_MAXFIGURA; i++)
        {
            ColorFigura color = figuraSeguent.getColor();
            IMAGE_NAME quadrat = IMAGE_NAME(color + 1);
            Posicio pos = figuraSeguent.getPosicioMatriu(i);
            int f = pos.getFila();
            int c = pos.getColumna();
            GraphicManager::getInstance()->drawSprite(quadrat, POS_X_TAULER + ((14 + c) * MIDA_QUADRAT), POS_Y_TAULER + (f * MIDA_QUADRAT), false);
        }

        Tauler m_tauler = m_joc.getTauler();
        for (int f = 0; f < MAX_FILES; f++)
        {
            for (int c = 0; c < MAX_COLUMNES; c++)
            {
                if (m_tauler.getPosicioTauler(f, c) != POSICIO_BUIDA)
                {
                    CodiTauler codi = m_tauler.getPosicioTauler(f, c);
                    IMAGE_NAME quadrat = IMAGE_NAME(codi + 1);
                    GraphicManager::getInstance()->drawSprite(quadrat, POS_X_TAULER + ((c + 1) * MIDA_QUADRAT), POS_Y_TAULER + (f * MIDA_QUADRAT), false);
                }

            }
        }
        m_joc.actualitzaFiguraTransparent();

        Figura figuraTransparent = m_joc.getFiguraTransparent();
        for (int i = 0; i < POS_MAXFIGURA; i++)
        {
            Posicio pos = figuraTransparent.getPosicio(i);
            int f = pos.getFila();
            int c = pos.getColumna();
            GraphicManager::getInstance()->drawSprite(GRAFIC_QUADRAT_PERSONALITZAT, POS_X_TAULER + ((c + 1) * MIDA_QUADRAT), POS_Y_TAULER + (f * MIDA_QUADRAT), false);
        }

        if (m_moviment != nullptr and m_figures != nullptr)
        {
            if(!pausa)
            {
                TipusMoviment mov = getMoviment();

                switch (mov)
                {
                case MOVIMENT_ESQUERRA:
                {
                    m_joc.mouFigura(0);
                    m_columna--;
                }break;

                case MOVIMENT_DRETA:
                {
                    m_joc.mouFigura(1);
                    m_columna++;
                }break;

                case MOVIMENT_GIR_HORARI:
                    m_joc.giraFigura(GIR_HORARI);
                    break;

                case MOVIMENT_GIR_ANTI_HORARI:
                    m_joc.giraFigura(GIR_ANTI_HORARI);
                    break;

                case MOVIMENT_BAIXA:
                {
                    if (m_joc.baixaFigura(m_puntuacio))
                        m_fila++;
                    else
                    {
                        if (actualitzaFiguraFitxer())
                        {
                            string msg4 = "GAME OVER";
                            GraphicManager::getInstance()->drawFont(FONT_RED_30, POS_X_TAULER + 50, POS_Y_TAULER + 50, 1.5, msg4);
                            return true;
                        }
                    }
                }break;
                case MOVIMENT_BAIXA_FINAL:
                {
                    m_joc.baixaFiguraFinal(m_fila, m_puntuacio);
                    if (actualitzaFiguraFitxer())
                    {
                        string msg4 = "GAME OVER";
                        GraphicManager::getInstance()->drawFont(FONT_RED_30, POS_X_TAULER + 50, POS_Y_TAULER + 100, 1.5, msg4);
                        return true;
                    }
                }break;
                default:
                    break;
                }

                nivell = false;
                if (m_puntuacio >= m_pujaNivell)
                {
                    nivell = true;
                    string msg6 = "NEXT LEVEL!";
                    GraphicManager::getInstance()->drawFont(FONT_RED_30, POS_X_TAULER + 50, POS_Y_TAULER + 50, 1.5, msg6);
                    m_nivell++;
                    m_pujaNivell += 1000;
                }
            }           
        }
        else
            return true;
    }
    else
    {
        GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
        GraphicManager::getInstance()->drawSprite(GRAFIC_FONS_PERSONALITZAT, 0, -595, false);
        GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER, false);

        string msg = "Fila: " + to_string(m_fila) + ", Columna: " + to_string(m_columna);
        GraphicManager::getInstance()->drawFont(FONT_GREEN_30, POS_X_TAULER, POS_Y_TAULER - 50, 0.5, msg);
        string msg2 = "Puntuacio: " + to_string(m_puntuacio);
        GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER, POS_Y_TAULER - 70, 0.5, msg2);
        string msg3 = "Nivell: " + to_string(m_nivell);
        GraphicManager::getInstance()->drawFont(FONT_RED_30, POS_X_TAULER + 200, POS_Y_TAULER - 50, 0.5, msg3);

        Figura figuraSeguent = m_joc.getFiguraSeguent();
    
        for (int i = 0; i < POS_MAXFIGURA; i++)
        {
            ColorFigura color = figuraSeguent.getColor();
            IMAGE_NAME quadrat = IMAGE_NAME(color + 1);
            Posicio pos = figuraSeguent.getPosicioMatriu(i);
            int f = pos.getFila();
            int c = pos.getColumna();
            GraphicManager::getInstance()->drawSprite(quadrat, POS_X_TAULER + ((14+c) * MIDA_QUADRAT), POS_Y_TAULER +(f*MIDA_QUADRAT), false);
        }
        
        m_temps += deltaTime;
        
        Tauler m_tauler = m_joc.getTauler();
        for (int f = 0; f < MAX_FILES; f++)
        {
            for (int c = 0; c < MAX_COLUMNES; c++)
            {
                if (m_tauler.getPosicioTauler(f, c) != POSICIO_BUIDA)
                {
                    CodiTauler codi = m_tauler.getPosicioTauler(f, c);
                    IMAGE_NAME quadrat = IMAGE_NAME(codi + 1);
                    GraphicManager::getInstance()->drawSprite(quadrat, POS_X_TAULER + ((c + 1) * MIDA_QUADRAT), POS_Y_TAULER + (f * MIDA_QUADRAT), false);
                }

            } 
        }
       
        if (!retro)
        {
            m_joc.actualitzaFiguraTransparent();
            Figura figuraTransparent = m_joc.getFiguraTransparent();
            for (int i = 0; i < POS_MAXFIGURA; i++)
            {
                Posicio pos = figuraTransparent.getPosicio(i);
                int f = pos.getFila();
                int c = pos.getColumna();
                GraphicManager::getInstance()->drawSprite(GRAFIC_QUADRAT_PERSONALITZAT, POS_X_TAULER + ((c + 1) * MIDA_QUADRAT), POS_Y_TAULER + (f * MIDA_QUADRAT), false);
            }
        }
        
        if (!pausa)
        {
            if (Keyboard_GetKeyTrg(KEYBOARD_LEFT))
            {
                if (m_joc.mouFigura(0))
                    m_columna--;
            }
            else
                if (Keyboard_GetKeyTrg(KEYBOARD_RIGHT))
                {
                    if (m_joc.mouFigura(1))
                        m_columna++;
                }
                else
                    if (Keyboard_GetKeyTrg(KEYBOARD_UP))
                        m_joc.giraFigura(GIR_ANTI_HORARI);
                    else
                        if (Keyboard_GetKeyTrg(KEYBOARD_DOWN))
                            m_joc.giraFigura(GIR_HORARI);
                        else
                            if (Keyboard_GetKeyTrg(KEYBOARD_SPACE))
                            {
                                m_joc.baixaFiguraFinal(m_fila, m_puntuacio);
                                if (actualitzaFiguraAleatoria())
                                {
                                    string msg4 = "GAME OVER";
                                    GraphicManager::getInstance()->drawFont(FONT_RED_30, POS_X_TAULER + 50, POS_Y_TAULER + 100, 1.5, msg4);
                                    return true;
                                }
                            }

            if (Keyboard_GetKeyTrg(KEYBOARD_LCTRL) and progresiu)
            {
                m_progresiu -= 0.2;
                if (m_temps > m_progresiu)
                {
                    if (m_joc.baixaFigura(m_puntuacio))
                        m_fila++;
                    else
                    {
                        progresiu = false;
                        if (actualitzaFiguraAleatoria())
                        {
                            string msg4 = "GAME OVER";
                            GraphicManager::getInstance()->drawFont(FONT_RED_30, POS_X_TAULER + 50, POS_Y_TAULER + 50, 1.5, msg4);
                            return true;
                        }
                    }
                    m_temps = 0.0;
                }
            }
            else
            {
                if (m_temps > m_intervalTemps)
                {
                    if (m_joc.baixaFigura(m_puntuacio))
                    {
                        progresiu = true;
                        m_fila++;
                    }
                    else
                    {
                        if (actualitzaFiguraAleatoria())
                        {
                            string msg4 = "GAME OVER";
                            GraphicManager::getInstance()->drawFont(FONT_RED_30, POS_X_TAULER + 50, POS_Y_TAULER + 50, 1.5, msg4);
                            return true;
                        }
                    }
                    m_temps = 0.0;
                }
            }

            nivell = false;
            if (m_puntuacio >= m_pujaNivell and m_nivell < 24)
            {
                nivell = true;
                m_intervalTemps -= 0.032;
                m_progresiu -= 0.032;
                string msg6 = "NEXT LEVEL!";
                GraphicManager::getInstance()->drawFont(FONT_RED_30, POS_X_TAULER + 50, POS_Y_TAULER + 50, 1.5, msg6);
                m_nivell++;
                m_pujaNivell += 1000;
            }
            else
                if (m_puntuacio >= m_pujaNivell)
                {
                    nivell = true;
                    string msg6 = "NEXT LEVEL!";
                    GraphicManager::getInstance()->drawFont(FONT_RED_30, POS_X_TAULER + 50, POS_Y_TAULER + 50, 1.5, msg6);
                    m_nivell++;
                    m_pujaNivell += 1000;
                }
        }
    }      
    return false;
}

