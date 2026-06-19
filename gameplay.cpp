/**
 * \file gameplay.h
 *
 * A jatek folyamatat levezeto fuggvenyek definialasa
 *
 */
#ifndef CPORTA
#include "gameplay.h"
#include "memtrace.h"

/**
 * \brief Egy SDL ablak megnyitasat es inicializalasat elvegzo fuggveny
 */
void sdl_init(char const *felirat, int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow(felirat, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szeles, magas, 0);
    if (window == NULL) {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);

    *pwindow = window;
    *prenderer = renderer;
}

/** \brief A fo menu kezelese
 * \param path A betoltendo palyak katalogusa
 * \return Hamissal ter vissza ha nem akarjuk ujra a menut megnyitni egy palyabol kilepes utan. Ha a jatekos elvegezte a palyat vagy megnyomta az X-et a kilepeshez, akkor alapbol kilep.
 */
bool mainMenu(const char* path){
    Menu menu(path);
    SDL_Window *window;
    SDL_Renderer *renderer;
    Coordinate menuSize((menu.getLevelCount() >= 5) ? 5 : menu.getLevelCount(), (menu.getLevelCount() - 1) / 5 + 1);
    sdl_init("Sokoban", menuSize.x * 100 + 50, menuSize.y * 100 + 50, &window, &renderer);
    drawMenu(renderer, menu.getLevelCount());
    SDL_Event ev;
    SDL_PollEvent(&ev);
    input d;
    d = getInput(ev);
    Coordinate selected;
    while(d != quit && d != enter){
        SDL_PollEvent(&ev);
        d = getInput(ev);
        rectangleRGBA(renderer, selected.x*100 + 25, selected.y*100 + 25, (selected.x+1)*100 + 25, (selected.y+1)*100 + 25, 0, 0, 0, 255);
        Coordinate dir;
        if(d == quit) break;
        switch(d){
            case up: dir = Coordinate(0, -1); break;
            case down: dir = Coordinate(0, 1); break;
            case left: dir = Coordinate(-1, 0); break;
            case right: dir = Coordinate(1, 0); break;
            default: dir = Coordinate(0, 0); break;
        }
        if(!(selected + dir < Coordinate(0,0) || selected + dir > menuSize - Coordinate(1,1))) {
            if((selected.y + dir.y == menuSize.y - 1 && !selected.x + dir.x == menu.getLevelCount() % 5) || selected.y + dir.y < menuSize.y - 1)
                selected = selected + dir;
        }
        rectangleRGBA(renderer, selected.x*100 + 25, selected.y*100 + 25, (selected.x+1)*100 + 25, (selected.y+1)*100 + 25, 255, 255, 255, 255);
        SDL_RenderPresent(renderer);
    }
    SDL_Quit();
    menu.goToLevel(selected.x + selected.y * 5);
    if(d == enter){
        bool quit = playLevel(*menu.getCurrentLevel());
        if(menu.getCurrentLevel()->isComplete()) menu.getCurrentLevel()->saveScore(menu.getCurrentLevelInt(), menu.getLevelCount());
        return !quit;
    }
    else
        return false;
}
/**
 * \brief Egy kivalasztott palya lejatszasat bonyolitja le
 * \param lvl A lejatszando palya
 * \return Hamis, ha a jatekos az X-re kattintva lep ki, vagy vegigjatszotta a palyat
 */

bool playLevel(Level& lvl){
    SDL_Window *window;
    SDL_Renderer *renderer;
    sdl_init("Sokoban", lvl.getSize().x * 100,lvl.getSize().y * 100, &window, &renderer);
    SDL_Event ev;

    int moveCount = 0;
    input d;
    lvl.render(renderer);
    SDL_RenderPresent(renderer);
    while(!lvl.isComplete() && d != quit){
        SDL_PollEvent(&ev);
        Coordinate dir;
        d = getInput(ev);
        switch(d){
            case up: dir = Coordinate(0, -1); break;
            case left: dir = Coordinate(-1, 0); break;
            case down: dir = Coordinate(0, 1); break;
            case right: dir = Coordinate(1, 0); break;
            case undo: if(lvl.undo()) moveCount--; lvl.render(renderer); break;
            default: dir = Coordinate(0, 0); break;
        }
        if(lvl.movePlayer(dir)) {
            moveCount++;
            lvl.render(renderer);
            if(d == quit){
                std::cout << "QUIT\n";
            }
        }
        SDL_RenderPresent(renderer);
    }
    SDL_Quit();
    return lvl.isComplete() || ev.type == SDL_QUIT;
}

#endif // CPORTA
