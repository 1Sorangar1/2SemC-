#pragma once
#include <C:\Users\User\source\repos\2SemC++\2SemC-\LAB_2\vector.h>
#include <SDL.h>

const int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;
const int CIRCLE_RADIUS = 20;
const int SPEED = 5;
const int DISSAPEAR_SPEED = 1;

class Point {
private:
    Vector position;
    float radius;
public:
    Point() {};
    Point(Vector coordinates, float _radius);

    Vector getPosition();
    float getRadius();
    void setRadius(float _r);
    void setPosition(Vector coordinates);
	
    void drawCircle(SDL_Renderer* renderer, Point point);
    void movePoint(Vector movement);
};

Point::Point(Vector coordinates, float _radius) {
    position.setX(coordinates.xPos());
    position.setY(coordinates.yPos());
    radius = _radius;
}

Vector Point::getPosition() {
    return position;
}

float Point::getRadius() {
    return radius;
}

void Point::setRadius(float _r) {
    radius = _r;
}

void Point::setPosition(Vector coordinates) {
    position.setX(coordinates.xPos());
    position.setY(coordinates.yPos());
}

void Point::drawCircle(SDL_Renderer* renderer, Point point) {
    int dx, dy;
    for (int w = 0; w < point.radius * 2; w++) {
        for (int h = 0; h < point.radius * 2; h++) {
            dx = point.radius - w;
            dy = point.radius - h;
            if ((dx * dx + dy * dy) <= (point.radius * point.radius)) {
                SDL_RenderDrawPoint(renderer, point.position.xPos() + dx, point.position.yPos() + dy);
            }
        }
    }
}

void Point::movePoint(Vector movement) {
    position = position + movement;
}

