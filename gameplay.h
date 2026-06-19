/**
 * \file gameplay.h
 *
 * A jatek folyamatat levezeto fuggvenyek deklaralasa
 *
 */
#include "memtrace.h"
#ifndef CPORTA
#ifndef GAMEPLAY_H_INCLUDED
#define GAMEPLAY_H_INCLUDED

#include "inputHandler.h"
#include "level.h"
#include "menu.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

void sdl_init(char const *felirat, int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer);

bool mainMenu(const char* path);

bool playLevel(Level& lvl);

#endif // GAMEPLAY_H_INCLUDED
#endif // CPORTA
