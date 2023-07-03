#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library\n";
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("SDL2 Window",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          680, 480,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    SDL_SetWindowSize(window, 200, 600);

    if (!window)
    {
        std::cout << "Failed to create window\n";
        return -1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    if (TTF_Init() < 0)
    {
        std::cout << "Failed to initialize SDL_ttf\n";
        return -1;
    }

    TTF_Font *font = TTF_OpenFont("../assets/fonts/Montserrat-Black.ttf", 24);
    if (!font)
    {
        std::cout << "Failed tod load font: " << (bool)font << std::endl;
        return -1;
    }

    SDL_Color textColor = {0xf, 0xf, 0xf};
    SDL_Surface *surface = TTF_RenderText_Solid(font, "Score is: 0", textColor);
    if (!surface)
    {
        std::cout << "Failed to create surface for text\n";
        return -1;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture)
    {
        std::cout << "Failed to create texture for text\n";
        return -1;
    }

    SDL_FreeSurface(surface);

    SDL_Rect square;
    square.x = (680 / 2) - 50;
    square.y = (480 / 2) - 50;
    square.w = 100;
    square.h = 100;

    int speed = 2;
    int direction = 1;
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    SDL_Event event;
    bool running = true;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN)
            {

                SDL_PumpEvents(); // update keyState array

                if (keyState[SDL_SCANCODE_UP] && keyState[SDL_SCANCODE_LEFT])
                {
                    square.y -= 10;
                    square.x -= 10;
                }
                else if (keyState[SDL_SCANCODE_UP] && keyState[SDL_SCANCODE_RIGHT])
                {
                    square.y -= 10;
                    square.x += 10;
                }
                else if (keyState[SDL_SCANCODE_DOWN] && keyState[SDL_SCANCODE_LEFT])
                {
                    square.y += 10;
                    square.x -= 10;
                }
                else if (keyState[SDL_SCANCODE_DOWN] && keyState[SDL_SCANCODE_RIGHT])
                {
                    square.y += 10;
                    square.x += 10;
                }
                else if (keyState[SDL_SCANCODE_UP])
                {
                    square.y -= 10;
                }
                else if (keyState[SDL_SCANCODE_DOWN])
                {
                    square.y += 10;
                }
                else if (keyState[SDL_SCANCODE_LEFT])
                {
                    square.x -= 10;
                }
                else if (keyState[SDL_SCANCODE_RIGHT])
                {
                    square.x += 10;
                }
            }
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                int newWidth = event.window.data1;
                int newHeight = event.window.data2;

                // Update the square's position to the center of the window
                square.x = newWidth / 2 - square.w / 2;
                square.y = newHeight / 2 - square.h / 2;
            }
        }
        SDL_SetRenderDrawColor(renderer, 100, 100, 255, 255);
        SDL_RenderClear(renderer);

        SDL_Rect textRect;
        textRect.x = 10;
        textRect.y = 10;

        SDL_QueryTexture(texture, NULL, NULL, &textRect.w, &textRect.h);
        SDL_RenderCopy(renderer, texture, NULL, &textRect);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &square);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
    TTF_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
