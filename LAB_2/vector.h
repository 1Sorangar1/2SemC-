#pragma once
#include <vector>
using namespace std;

class Vector {
public:
    float x;
    float y;


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

//using namespace std;
//
//class Vector {
//public:
//    float x, y;
//    Vector(float p_x, float p_y);
//    Vector operator+(Vector other_vector) {
//        return Vector(x + other_vector.x, y + other_vector.y);
//    }
//
//};
//
//Vector::Vector(float p_x, float p_y) {
//    x = p_x;
//    y = p_y;
//}