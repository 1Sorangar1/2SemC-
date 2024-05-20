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

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
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
    Vector move = Vector(0,0);
    Vector start(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    Point point = Point(start, CIRCLE_RADIUS);
    std::vector<Point> trails;

    // √лавный цикл программы
    while (run) {
        // ќбработка событий
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) run = false;
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                case SDLK_UP: move.y -= SPEED; break;
                case SDLK_DOWN: move.y += SPEED; break;
                case SDLK_LEFT: move.x -= SPEED; break;
                case SDLK_RIGHT: move.x += SPEED; break;
                }
            }
        }

        point.movePoint(move);
        move.x = 0;
        move.y = 0;
        // ƒобавление новой позиции в вектор следов
        trails.emplace_back(point);

        // ќчистка экрана
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // –исование следов
        for (auto& trail : trails) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            trail.drawCircle(renderer, trail);

            if (trail.getRadius() > 0) {
                trail.setRadius(trail.getRadius()-DISSAPEAR_SPEED);
            }
        }

        // ”даление следов 
        trails.erase(std::remove_if(trails.begin(), trails.end(), [](Point& trail) {
            return trail.getRadius() == 0;
            }), trails.end());

        // –исование круга
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        point.drawCircle(renderer, point);
        SDL_RenderPresent(renderer);
    }

    SDL_Quit();

    return 0;
}

//using namespace std;
//
//const int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;
//
//SDL_Window* win = NULL;
//SDL_Renderer* ren = NULL;
//
//bool init() {
//    bool ok = true;
//
//    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
//        cout << "Can't init: " << SDL_GetError() << endl;
//        ok = false;
//    }
//
//    win = SDL_CreateWindow("Primitive", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//    if (win == NULL) {
//        cout << "Can't create window: " << SDL_GetError() << endl;
//        ok = false;
//    }
//
//    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//    if (ren == NULL) {
//        cout << "Can't create renderer: " << SDL_GetError() << endl;
//        ok = false;
//    }
//
//    SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
//    SDL_RenderClear(ren);
//    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
//
//    return ok;
//
//}
//
//
//void quit() {
//    SDL_DestroyWindow(win);
//    win = NULL;
//
//    SDL_DestroyRenderer(ren);
//    ren = NULL;
//
//    SDL_Quit();
//}
//
//int main(int argc, char* argv[]) {
//
//    if (!init()) {
//        quit();
//        return 1;
//    }
//
//    bool run = true;
//    SDL_Event e;
//
//    int x = 320; // центр круга по оси X
//    int y = 240; // центр круга по оси Y
//    int radius = 100; // радиус круга
//
//    for (int i = 0; i < 360; i++) { // проходимс€ по всем углам от 0 до 360 градусов
//        float ang = i * 3.1415926f / 180; // переводим угол в радианы
//        int dx = (int)(radius * cos(ang)); // вычисл€ем координаты точки на окружности
//        int dy = (int)(radius * sin(ang));
//        SDL_RenderDrawPoint(ren, x + dx, y + dy); // рисуем точку
//    }
//
//    SDL_RenderPresent(ren);
//
//    while (run) {
//        while (SDL_PollEvent(&e) != 0) {
//            if (e.type == SDL_QUIT) run = false;
//        }
//
//        if (e.type == SDL_KEYDOWN) {
//            if (e.key.keysym.sym == SDLK_UP) {
//                y -= 1;
//            }
//            if (e.key.keysym.sym == SDLK_DOWN) {
//                y += 1;
//            }
//            if (e.key.keysym.sym == SDLK_RIGHT) {
//                x += 1;
//            }
//            if (e.key.keysym.sym == SDLK_LEFT) {
//                x -= 1;
//            }
//        }
//        SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
//        SDL_RenderClear(ren);
//        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
//        for (int i = 0; i < 360; i++) { // проходимс€ по всем углам от 0 до 360 градусов
//            float ang = i * 3.1415926f / 180; // переводим угол в радианы
//            int dx = (int)(radius * cos(ang)); // вычисл€ем координаты точки на окружности
//            int dy = (int)(radius * sin(ang));
//            SDL_RenderDrawPoint(ren, x + dx, y + dy); // рисуем точку
//        }
//
//
//        SDL_RenderPresent(ren);
//
//    }
//	
//    quit();
//
//	return 0;
//}



//const int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;
//
//SDL_Window* win = NULL;
//SDL_Renderer* ren = NULL;
//SDL_Texture* flower = NULL;
//
//bool init() {
//    bool ok = true;
//
//    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
//        cout << "Can't init: " << SDL_GetError() << endl;
//        ok = false;
//    }
//
//    win = SDL_CreateWindow("Primitive", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//    if (win == NULL) {
//        cout << "Can't create window: " << SDL_GetError() << endl;
//        ok = false;
//    }
//
//    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//    if (ren == NULL) {
//        cout << "Can't create renderer: " << SDL_GetError() << endl;
//        ok = false;
//    }
//    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
//
//    return ok;
//
//}
//
//
//void quit() {
//    SDL_DestroyWindow(win);
//    win = NULL;
//
//    SDL_DestroyRenderer(ren);
//    ren = NULL;
//
//    SDL_Quit();
//}
//
//int main(int argc, char* argv[]) {
//
//    if (!init()) {
//        quit();
//        return 1;
//    }
// 
//    SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
//    SDL_RenderClear(ren);
//    SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
//
//    SDL_Rect rect1 = { 10, 10, 50, 50 };
//    SDL_RenderFillRect(ren, &rect1);
//
//    SDL_Rect rect2 = { 70, 10, 50, 50 };
//    SDL_RenderDrawRect(ren, &rect2);
//
//    SDL_RenderDrawLine(ren, 10, 70, 640 - 10, 70);
//
//    for (int i = 10; i <= 640 - 10; i += 4) {
//        SDL_RenderDrawPoint(ren, i, 90);
//    }
//
//    SDL_RenderPresent(ren);
//    SDL_Delay(2000);
//
//    quit();
//    return 0;
//}

