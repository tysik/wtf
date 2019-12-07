#include "Wtf.h"

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

int WINDOWS_HEIGHT = 500;
int WINDOWS_WIDTH = 500;

void draw_wtf_point(SDL_Renderer* r, const wtf_vec_t* p) {
    int x = (p->x + 1.0) * WINDOWS_WIDTH / 2.0;
    int y = (p->y + 1.0) * WINDOWS_HEIGHT / 2.0;
    SDL_RenderDrawPoint(r, x, y);
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* win = SDL_CreateWindow("WTF?", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                       WINDOWS_WIDTH, WINDOWS_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren =
        SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    wtf_vec_t cube[8] = {
        wtf_custom_vec(1.0, -1.0, 1.0),  wtf_custom_vec(1.0, 1.0, 1.0),
        wtf_custom_vec(-1.0, 1.0, 1.0),  wtf_custom_vec(-1.0, -1.0, 1.0),
        wtf_custom_vec(1.0, -1.0, -1.0), wtf_custom_vec(1.0, 1.0, -1.0),
        wtf_custom_vec(-1.0, 1.0, -1.0), wtf_custom_vec(-1.0, -1.0, -1.0),
    };

    wtf_scalar_t scaling_factor = 0.25;
    for (int i = 0; i < 8; ++i) {
        cube[i] = wtf_vec_scaled(&cube[i], scaling_factor);
    }

    wtf_scalar_t angle = 0.01;
    wtf_vec_t axis = wtf_custom_vec(1.0, 1.0, 1.0);
    axis = wtf_vec_normalized(&axis);
    wtf_quat_t rotor = wtf_rotor_quat(&axis, angle);

    while (true) {
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                break;
            }
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    break;
                }
            }
        }

        SDL_SetRenderDrawColor(ren, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 255, 255, 255, SDL_ALPHA_OPAQUE);

        for (int i = 0; i < 8; ++i) {
            cube[i] = wtf_quat_rotate(&rotor, &cube[i]);
            draw_wtf_point(ren, &cube[i]);
        }
        SDL_RenderPresent(ren);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}