/**
 * \file graphics.cpp
 *
 * A grafikai fuggvenyek definicioja
 *
 */
#include "memtrace.h"
#ifndef CPORTA
#include "graphics.h"

/** \brief Kirajzolja a jatekost, egy 40 sugaru piros pontkent, egy cella 100x100 meretu
 * \param renderer Az SDL renderer-e ahova a jatekos ki lesz rajzolva
 * \param x A jatekos x koordinataja az eltarolt matrixban
 * \param y A jatekos y koordinataja az eltarolt matrixban
 */

void drawPlayer(SDL_Renderer* renderer, int x, int y){
    filledCircleRGBA(renderer, x*100 + 50, y*100 + 50, 40, 200, 0, 0, 255);
}

/** \brief Kirajzolja a dobozt, egy sargas-barna negyzetkent amiben van egy kereszt
 * \param renderer Az SDL renderer-e ahova a jatekos ki lesz rajzolva
 * \param x A doboz x koordinataja az eltarolt matrixban
 * \param y A doboz y koordinataja az eltarolt matrixban
 */
void drawBox(SDL_Renderer* renderer, int x, int y){
    thickLineRGBA (renderer, x*100 + 50, y*100 + 5, x*100 + 50, (y+1)*100 - 5, 90, 200, 100, 30, 255);
    thickLineRGBA (renderer, x*100 + 5, y*100 + 5, x*100 + 5, (y+1)*100 - 5, 5, 250, 100, 30, 255);
    thickLineRGBA (renderer, (x+1)*100 - 5, y*100 + 5, (x+1)*100 - 5, (y+1)*100 - 5, 5, 250, 100, 30, 255);
    thickLineRGBA (renderer, x*100 + 5, y*100 + 5, (x+1)*100 - 5, y*100 + 5, 5, 250, 100, 30, 255);
    thickLineRGBA (renderer, x*100 + 5, (y+1)*100 - 5, (x+1)*100 - 5, (y+1)*100 - 5, 5, 250, 100, 30, 255);
    thickLineRGBA (renderer, x*100 + 5, (y+1)*100 - 5, (x+1)*100 - 5, y*100 + 5, 5, 250, 100, 30, 255);
    thickLineRGBA (renderer, x*100 + 5, y*100 + 5, (x+1)*100 - 5, (y+1)*100 - 5, 5, 250, 100, 30, 255);
}

/** \brief Kirajzolja a celt, egy zold negyzetkent amiben ket koncentrikus mas arnyalatu kor van
 * \param renderer Az SDL renderer-e ahova a jatekos ki lesz rajzolva
 * \param x A cel x koordinataja az eltarolt matrixban
 * \param y A cel y koordinataja az eltarolt matrixban
 */
void drawFinish(SDL_Renderer* renderer, int x, int y){
    thickLineRGBA (renderer, x*100 + 50, y*100, x*100 + 50, (y+1)*100, 100, 0, 150, 0, 255);
    filledCircleRGBA(renderer, x*100 + 50, y*100 + 50, 45, 0, 170, 0, 255);
    filledCircleRGBA(renderer, x*100 + 50, y*100 + 50, 20, 0, 175, 0, 255);
}

/** \brief Kirajzolja a falat, egy teglas mintakent
 * \param renderer Az SDL renderer-e ahova a jatekos ki lesz rajzolva
 * \param x A fal x koordinataja az eltarolt matrixban
 * \param y A fal y koordinataja az eltarolt matrixban
 */
void drawWall(SDL_Renderer* renderer, int x, int y){
    thickLineRGBA (renderer, x*100 + 50, y*100, x*100 + 50, (y+1)*100, 100, 150, 150, 150, 255);
    thickLineRGBA (renderer, x*100 + 5, y*100 + 25, (x+1)*100 - 5, y*100 + 25, 40 , 75, 20, 20, 255);
    thickLineRGBA (renderer, x*100, (y+1)*100 - 25, x*100 + 45, (y+1)*100 - 25, 40 , 75, 20, 20, 255);
    thickLineRGBA (renderer, (x+1)*100 - 45, (y+1)*100 - 25, (x+1)*100, (y+1)*100 - 25, 40 , 75, 20, 20, 255);
}
/** \brief Kirajzolja a talajt, egy sotet, kicsit kekes szinben
 * \param renderer Az SDL renderer-e ahova a jatekos ki lesz rajzolva
 * \param x A doboz x koordinataja az eltarolt matrixban
 * \param y A doboz y koordinataja az eltarolt matrixban
 */
void drawGround(SDL_Renderer* renderer, int x, int y){
    thickLineRGBA (renderer, x*100 + 50, y*100, x*100 + 50, (y+1)*100, 100, 25, 25, 30, 255);
}

/** \brief Kirajzolja a menut, egy palyat egy szurke kor reprezental
 * \param renderer Az SDL renderer-e ahova a jatekos ki lesz rajzolva
 * \param levelCount A kirajzolando palyak szama
 */
void drawMenu(SDL_Renderer* renderer, int levelCount){
    for(int i = 0; i < levelCount; i++){
        filledCircleRGBA(renderer, (i%5)*100 + 75, (i  / 5 + 1 )* 100 - 25, 40, 100, 100, 100, 255);
    }
}
#endif // CPORTA
