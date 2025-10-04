#include <SDL2/SDL.h>
#include <stdio.h>

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_StartTextInput(); // enable text input

    SDL_Window *window = SDL_CreateWindow("SDL Text Input",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 400, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int running = 1;
    SDL_Event e;
    char inputText[256] = {0}; // buffer to store user input
    int pos = 0;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = 0;
            }
            else if (e.type == SDL_TEXTINPUT) {
                // append new text
                if (pos < 255) {
                    strcat(inputText, e.text.text);
                    pos += strlen(e.text.text);
                }
            }
            else if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_BACKSPACE && pos > 0) {
                    // remove last character
                    inputText[--pos] = '\0';
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        // Here you can render `inputText` using SDL_ttf to show it
        SDL_RenderPresent(renderer);
    }

    SDL_StopTextInput();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

