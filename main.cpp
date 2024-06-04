//
//  main.cpp
//
//  Copyright � 2018 Compiled Creations Limited. All rights reserved.
//

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined  (_WIN64)

#include <thread>
#include <chrono>
#include <iostream>
//Definicio necesaria per poder incloure la llibreria i que trobi el main
#define SDL_MAIN_HANDLED
#include <windows.h>
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#include <conio.h>      /* getch */ 

#elif __APPLE__
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <SDL2/SDL.h>
#pragma clang diagnostic pop

#endif

#include "./Partida.h"
#include "./InfoJoc.h"
#include "GraphicManager.h"
#include "Tetris.h"
#include "../Graphic Lib/sound.h"

int main(int argc, const char* argv[])
{
    //Instruccions necesaries per poder incloure la llibreria i que trobi el main
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);

    //Inicialitza un objecte de la classe Screen que s'utilitza per gestionar la finestra grafica
    Screen pantalla(SCREEN_SIZE_X, SCREEN_SIZE_Y);
    //Mostrem la finestra grafica
    pantalla.show();
    
    bool finalitza = false;
    bool nivell, sortir;
    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double deltaTime = 0;
    srand((unsigned)time(NULL));
    
    do {
       
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());
        pantalla.processEvents();
        sortir = false;
        GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
        GraphicManager::getInstance()->drawSprite(GRAFIC_FONS_PERSONALITZAT, 0, -595, false);
        string msg1 = "Menu Tetris";
        GraphicManager::getInstance()->drawFont(FONT_WHITE_30, 150, 60, 1.2, msg1);
        string msg2 = "1-Mode Normal";
        GraphicManager::getInstance()->drawFont(FONT_RED_30, 100, 140, 0.7, msg2);
        string msg3 = "2-Mode Test";
        GraphicManager::getInstance()->drawFont(FONT_GREEN_30, 100, 180, 0.7, msg3);
        string msg4 = "3-Mostrar Millors Puntuacions";
        GraphicManager::getInstance()->drawFont(FONT_RED_30, 100, 220, 0.7, msg4);
        string msg5 = "4-Sortir";
        GraphicManager::getInstance()->drawFont(FONT_GREEN_30, 100, 260, 0.7, msg5);
        pantalla.update();
        
        if (Keyboard_GetKeyTrg(KEYBOARD_1))
        {
            pantalla.processEvents();
            bool retro = false;
            bool pausa = false;
            GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
            GraphicManager::getInstance()->drawSprite(GRAFIC_FONS_PERSONALITZAT, 0, -595, false);
            string msg12 = "Mode Normal (Pulsa N) o Mode Retro (Pulsa R)";
            GraphicManager::getInstance()->drawFont(FONT_WHITE_30, 50, 300, 0.7, msg12);
            pantalla.update();

            while (!Keyboard_GetKeyTrg(KEYBOARD_R) and !Keyboard_GetKeyTrg(KEYBOARD_N))
                pantalla.processEvents();
            
            if (Keyboard_GetKeyTrg(KEYBOARD_R))
                retro = true;

            Tetris tetris;
            tetris.iniciamodeNormal();
            
            do
            {
                LAST = NOW;
                NOW = SDL_GetPerformanceCounter();
                deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());

                // Captura tots els events de ratolí i teclat de l'ultim cicle
                pantalla.processEvents();
                if (Keyboard_GetKeyTrg(KEYBOARD_P))
                    pausa = !pausa;
                       
                    finalitza = tetris.jugaModeNormal(deltaTime, nivell, retro, pausa);
                    // Actualitza la pantalla
                    if(!pausa)
                    pantalla.update();

                    if (finalitza)
                    {
                        Sleep(3000);
                        GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
                        GraphicManager::getInstance()->drawSprite(GRAFIC_FONS_PERSONALITZAT, 0, -595, false);
                        string msg9 = "Introdueix el teu nickname (a la terminal)";
                        GraphicManager::getInstance()->drawFont(FONT_WHITE_30, 50, 300, 0.7, msg9);
                        pantalla.update();
                        string nickname;
                        while (!(cin >> nickname));
                        LlistaPuntuacio element;
                        element.setNom(nickname);
                        int puntuacio = tetris.getPuntuacioPartida();
                        element.setPuntuacio(puntuacio);
                        string nomFitxer = "puntuacions.txt";
                        tetris.iniciaLlistaPuntuacio(nomFitxer);
                        tetris.afegeixElementLlista(element, nomFitxer);
                    }
                    else
                        if (nivell)
                            Sleep(200);
                        else
                            if (pausa)
                            {
                                string msg18 = "PAUSA";
                                GraphicManager::getInstance()->drawFont(FONT_RED_30, POS_X_TAULER + 100, POS_Y_TAULER + 150, 1.5, msg18);
                                pantalla.update();
                            }else
                                if (Keyboard_GetKeyTrg(KEYBOARD_ESCAPE))
                                {
                                    string msg20 = "Segur que vols sortir de la partida?(S/N)";
                                    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, 150, 300, 0.5, msg20);
                                    pantalla.update();
                                    while (!Keyboard_GetKeyTrg(KEYBOARD_S) and !Keyboard_GetKeyTrg(KEYBOARD_N))
                                        pantalla.processEvents();
                                    if (Keyboard_GetKeyTrg(KEYBOARD_S))
                                        sortir = true;

                                }

            } while (!sortir and !finalitza);

        }else
            if (Keyboard_GetKeyTrg(KEYBOARD_2))
            {
                string fitxerInicial;
                string fitxerFigures;
                string fitxerMoviments;
                Tetris tetris;
                bool pausa = false;
                    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
                    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS_PERSONALITZAT, 0, -595, false);
                    
                    string msg8 = "Introdueix els noms del fitxers del test (a la terminal)";
                    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, 50, 300, 0.7, msg8);
                    pantalla.update();
                    bool sortir = false;
                    while ((!(cin >> fitxerInicial) or !(cin >> fitxerFigures) or !(cin >> fitxerMoviments)));
                                                           
                        tetris.iniciamodeTest(fitxerInicial, fitxerFigures, fitxerMoviments);
                        do
                        {
                            pantalla.processEvents();

                            if (Keyboard_GetKeyTrg(KEYBOARD_P))
                                pausa = !pausa;

                            finalitza = tetris.jugaModeTest(deltaTime, nivell, pausa);
                            // Actualitza la pantalla
                            if (!pausa)
                            {
                                pantalla.update();
                                Sleep(350);
                            }

                            if (finalitza)
                                Sleep(3000);
                            else
                                if (nivell)
                                    Sleep(200);
                                else
                                    if (pausa)
                                    {
                                        string msg18 = "PAUSA";
                                        GraphicManager::getInstance()->drawFont(FONT_RED_30, POS_X_TAULER + 100, POS_Y_TAULER + 150, 1.5, msg18);
                                        pantalla.update();
                                    }
                                    else
                                    {
                                        if (Keyboard_GetKeyTrg(KEYBOARD_ESCAPE))
                                        {
                                            string msg20 = "Segur que vols sortir de la partida?(S/N)";
                                            GraphicManager::getInstance()->drawFont(FONT_WHITE_30, 150, 300, 0.5, msg20);
                                            pantalla.update();
                                            while (!Keyboard_GetKeyTrg(KEYBOARD_S) and !Keyboard_GetKeyTrg(KEYBOARD_N))
                                                pantalla.processEvents();
                                            if (Keyboard_GetKeyTrg(KEYBOARD_S))
                                                sortir = true;
                                        }
                                    }

                        } while (!sortir and !finalitza);
            }else
                if (Keyboard_GetKeyTrg(KEYBOARD_3))
                {
                    string nomFitxer = "puntuacions.txt";
                    Tetris tetris;
                    
                    tetris.iniciaLlistaPuntuacio(nomFitxer);

                    do {
                        pantalla.processEvents();
                        tetris.mostraPuntuacio();
                        pantalla.update();
                    } while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE));     
                }
        // Sortim del bucle si pressionem ESC
    } while (!Keyboard_GetKeyTrg(KEYBOARD_4));
    
    //Instruccio necesaria per alliberar els recursos de la llibreria 
    SDL_Quit();
    return 0;
}

