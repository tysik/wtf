#include "Wtf.h"

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

static const int WINDOWS_HEIGHT = 500;
static const int WINDOWS_WIDTH = 500;

int motion_keys[6] = {0, 0, 0, 0, 0, 0};

void draw_wtf_point(SDL_Renderer* r, const wtf_vec_t* p) {
    int x = (p->x / (p->z + 2.0) + 1.0) * WINDOWS_WIDTH / 2.0;
    int y = (p->y / (p->z + 2.0) + 1.0) * WINDOWS_HEIGHT / 2.0;
    SDL_RenderDrawPoint(r, x, y);
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* win =
        SDL_CreateWindow("WTF Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         WINDOWS_WIDTH, WINDOWS_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren =
        SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // 1. Define the object in its local coordinate frame
    wtf_vec_t cube[8] = {
        wtf_vec_custom(1.0, -1.0, 1.0),  wtf_vec_custom(1.0, 1.0, 1.0),
        wtf_vec_custom(-1.0, 1.0, 1.0),  wtf_vec_custom(-1.0, -1.0, 1.0),
        wtf_vec_custom(1.0, -1.0, -1.0), wtf_vec_custom(1.0, 1.0, -1.0),
        wtf_vec_custom(-1.0, 1.0, -1.0), wtf_vec_custom(-1.0, -1.0, -1.0),
    };

    wtf_scalar_t scaling_factor = 0.25;
    for (int i = 0; i < 8; ++i) {
        cube[i] = wtf_vec_scaled(&cube[i], scaling_factor);
    }

    // 2. Transform the coordinates to the world coordinate frame

    // 3. Transform the coordinates to camera coordinate frame
    // wtf_vec_t from = wtf_vec_custom(3.0, 2.0, -2.0);
    // wtf_vec_t to = wtf_vec_empty();
    // wtf_tf_t camera = wtf_tf_from_to(&from, &to);

    // // 4. Apply perspective

    // wtf_scalar_t angle = 0.01;
    // wtf_vec_t axis = wtf_vec_custom(1.0, 1.0, 1.0);
    // axis = wtf_vec_normalized(&axis);
    // wtf_quat_t rotor = wtf_quat_rotor(&axis, angle);

    wtf_vec_t translation = wtf_vec_custom(0.0, 0.0, -1.0);
    wtf_tf_t translate = wtf_tf_translate(&translation);

    wtf_rot_t rotation = wtf_rot_local_rpy(0.0, 0.0, 1.0);
    wtf_tf_t rotate = wtf_tf_rotate(&rotation);

    wtf_tf_t transformation = wtf_tf_combine(&translate, &rotate);

    while (true) {
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                break;
            }
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_q) {
                    break;
                }
            }
        }

        SDL_SetRenderDrawColor(ren, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 255, 255, 255, SDL_ALPHA_OPAQUE);

        for (int i = 0; i < 8; ++i) {
            // cube[i] = wtf_quat_rotate(&rotor, &cube[i]);
            // draw_wtf_point(ren, &cube[i]);
            // wtf_vec_t point = wtf_tf_apply(&camera, &cube[i]);
            wtf_vec_t point = wtf_tf_apply(&transformation, &cube[i]);
            draw_wtf_point(ren, &point);
        }
        SDL_RenderPresent(ren);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}