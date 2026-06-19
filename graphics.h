/**
 * \file graphics.h
 *
 * A grafikai fuggvenyek deklaralasa
 *
 * Ezek a fuggvenyek a palya es a menu grafikus
 * kirajzolasanal vannak csak hasznalva
 *
 */
#include "memtrace.h"
#ifndef CPORTA
#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

void drawPlayer(SDL_Renderer* renderer, int x, int y);
void drawBox(SDL_Renderer* renderer, int x, int y);
void drawFinish(SDL_Renderer* renderer, int x, int y);
void drawWall(SDL_Renderer* renderer, int x, int y);
void drawGround(SDL_Renderer* renderer, int x, int y);
void drawMenu(SDL_Renderer* renderer, int levelCount);

#endif // GRAPHICS_H_INCLUDED
#endif // CPORTA
