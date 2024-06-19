#include <iostream>
#include <C:\Users\User\source\repos\2SemC++\2SemC-\LAB_2\point.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool init() {
    bool ok = true;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << "Can't init: " << SDL_GetError() << endl;
        ok = false;
    }

    window = SDL_CreateWindow("Primitive", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        cout << "Can't create window: " << SDL_GetError() << endl;
        ok = false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        cout << "Can't create renderer: " << SDL_GetError() << endl;
        ok = false;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    return ok;

}


void quit() {
    SDL_DestroyWindow(window);
    window = NULL;

    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_Quit();
}


int main(int argc, char* args[]) {

    if (!init()) {
        quit();
        return 1;
    }

    bool run = true;
    SDL_Event e;
    Vector move = Vector(0, 0);
    Vector start(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    Point point = Point(start, CIRCLE_RADIUS);
    std::vector<Point> trails;

    // Ãëàâíûé öèêë ïðîãðàììû
    while (run) {
        // Îáðàáîòêà ñîáûòèé
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) run = false;
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                case SDLK_UP: move.setY(move.yPos() - SPEED); break;
                case SDLK_DOWN: move.setY(move.yPos() + SPEED); break;
                case SDLK_LEFT: move.setX(move.xPos() - SPEED); break;
                case SDLK_RIGHT: move.setX(move.xPos() + SPEED); break;
                }
            }
        }

        point.movePoint(move);
        move.setX(0);
        move.setY(0);

        //Äîáàâëåíèå íîâîé ïîçèöèè â âåêòîð ñëåäîâ
        trails.emplace_back(point);

        //Î÷èñòêà ýêðàíà
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //Ðèñîâàíèå ñëåäîâ
        for (auto& trail : trails) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            trail.drawCircle(renderer, trail);

            if (trail.getRadius() > 0) {
                trail.setRadius(trail.getRadius() - DISSAPEAR_SPEED);
            }
        }

        //Óäàëåíèå ñëåäîâ 
        trails.erase(std::remove_if(trails.begin(), trails.end(), [](Point& trail) {
            return trail.getRadius() == 0;
            }), trails.end());

        //Ðèñîâàíèå êðóãà
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        point.drawCircle(renderer, point);
        SDL_RenderPresent(renderer);
    }

    quit();

    return 0;
}