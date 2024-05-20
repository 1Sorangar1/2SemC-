//#pragma once
//#include"vector.h"
//
//#define WINDOW_WIDTH 800
//#define WINDOW_HEIGTH 600
//#define MOVE_SPEED 1.5f
//#define RADIUS 4
//
//class Point {
//public:
//    Vector position;
//    std::vector<Vector> trail;
//    const float trail_length = 200;
//
//    Point(float x, float y) : position(x, y) {}  //  конструктор
//
//    void TrailEdition();  //  изменение следа точки
//    void PointMovement(Vector move_vector);  //  изменение напрадения движения точки
//};
//
//void Point::TrailEdition() {
//    trail.push_back(position);
//    if (trail.size() > trail_length)
//        trail.erase(trail.begin());
//}
//void Point::PointMovement(Vector move_vector) {
//    if (position.x < WINDOW_WIDTH + MOVE_SPEED && position.x > WINDOW_WIDTH - MOVE_SPEED) position.x = 0;
//    else if (position.x < MOVE_SPEED) position.x = WINDOW_WIDTH;
//    if (position.y < WINDOW_HEIGTH + MOVE_SPEED && position.y > WINDOW_HEIGTH - MOVE_SPEED) position.y = 0;
//    else if (position.y < MOVE_SPEED) position.y = WINDOW_HEIGTH;
//    position = position + move_vector;
//}
//
//class Union {
//public:
//    Point point;  //  начальные координаты объекта
//    sf::CircleShape point_share;  //  форма/вид объекта
//    sf::CircleShape trail_share;  //  форма/вид следа
//
//    Union(float x, float y, float R) : point(x, y), point_share(R), trail_share(R) {
//        point_share.setFillColor(sf::Color::Magenta);
//    }
//
//    void SetTrail(int i);
//};
//
//void Union::SetTrail(int i) {
//    trail_share.setRadius(i * RADIUS / point.trail.size());
//    trail_share.setFillColor(sf::Color(255, 0, 255, i * 255 / point.trail.size()));
//    trail_share.setPosition(point.trail[i].x, point.trail[i].y);
//}

#pragma once
#include <C:\Users\User\source\repos\2SemC++\2SemC-\LAB_2\vector.h>
#include <SDL.h>

const int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;
const int CIRCLE_RADIUS = 20;
const int SPEED = 5;

class Point {
public:
	Vector position;
    //std::vector<Vector> trails;
    Point() {};
    Point(Vector coordinates);
    void drawCircle(SDL_Renderer* renderer, Point point, float radius);
    void movePoint(Vector movement);
	
};

Point::Point(Vector coordinates) {
    position.x = coordinates.x;
    position.y = coordinates.y;
}

void Point::drawCircle(SDL_Renderer* renderer, Point point, float radius) {
    int dx, dy;
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            dx = radius - w;
            dy = radius - h; 
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, point.position.x + dx, point.position.y + dy);
            }
        }
    }
}

void Point::movePoint(Vector movement) {
    position = position + movement;
}

