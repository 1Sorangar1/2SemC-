#pragma once
using namespace std;

class Vector {
public:
    float x;
    float y;

    Vector(float _x, float _y);
    float x_pos();
    float y_pos();
    void set_x(int _x);
    void set_y(int _y);

    Vector operator+(Vector& sum_vector) { 
        return Vector(x + sum_vector.x, y + sum_vector.y); 
    }

};

Vector::Vector(float _x, float _y) {
    x = _x;
    y = _y;
}


float Vector::x_pos() {
    return x;
}

float Vector::y_pos() {
    return y;
}

void Vector::set_x(int _x) {
    x = _x;
}

void Vector::set_y(int _y) {
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