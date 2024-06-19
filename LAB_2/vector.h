#pragma once
#include <vector>
using namespace std;

class Vector {
private:
    float x;
    float y;
public:
    Vector() {};
    Vector(float _x, float _y);

    float xPos();
    float yPos();
    void setX(int _x);
    void setY(int _y);

    Vector operator+(Vector& sum_vector) {
        return Vector(x + sum_vector.x, y + sum_vector.y);
    }
};

Vector::Vector(float _x, float _y) {
    x = _x;
    y = _y;
}


float Vector::xPos() {
    return x;
}

float Vector::yPos() {
    return y;
}

void Vector::setX(int _x) {
    x = _x;
}

void Vector::setY(int _y) {
    y = _y;
}