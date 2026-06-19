/**
 * \file inputHandler.cpp
 *
 * A getInput fuggveny definialasa
 *
 */
#include "memtrace.h"
#ifndef CPORTA
#include "inputHandler.h"

/**
 * \brief   Atalakitja az SDL-tol kapott event-et egy enum tipusra amit konnyebben lehet integralni a kodba
 * \param ev SDL event-je ebbol lehet kiolvasni tobbek kozott azt, hogy meylik billentyu volt leutve
 * \return A billentyu utesbol atalakitott input enum
 */

input getInput(const SDL_Event& ev){

    input input = nothing;
    switch(ev.type){
        case SDL_KEYDOWN:
            if(ev.key.repeat != 0) break;
            switch(ev.key.keysym.sym){
                case SDLK_w: input = up; break;
                case SDLK_a: input = left; break;
                case SDLK_s: input = down; break;
                case SDLK_d: input = right; break;
                case SDLK_u: input = undo; break;
                case SDLK_e: input = undo; break;
                case SDLK_q: input = quit; break;
                case SDLK_ESCAPE: input = quit; break;
                case SDLK_RETURN: input = enter; break;
                case SDLK_SPACE: input = enter; break;
                default: break;
            }
            break;
        case SDL_QUIT: input = quit; break;
        default: break;
    }
    return input;
}

#endif
