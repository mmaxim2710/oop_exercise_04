#ifndef FIGURES_H
#define FIGURES_H

#include "vertex.h"
#include <type_traits>
#include <iostream>

template <class T>
class Octagon {
public:
    vertex<T> points[8];
    int size = 8;
    explicit Octagon<T>(std::istream& is) {
        for (auto & point : points) {
            is >> point;
        }
    }
};

template <class T>
class Triangle {
public:
    vertex<T> points[3];
    int size = 3;
    explicit Triangle<T>(std::istream& is) {
        for (auto & point : points) {
            is >> point;
        }
    }
};

template <class T>
class Square {
public:
    vertex<T> points[4];
    int size = 4;
    explicit Square<T>(std::istream& is) {
        for (auto & point : points) {
            is >> point;
        }
        if (!is_square(points)) {
            throw std::logic_error("this is not square");
        }
    }
};

template<class T>
bool is_square (vertex<T> points[4]) {
    bool check = ((length(points[0], points[1]) == length(points[1], points[2])) && (length(points[2], points[3]) == length(points[3], points[0])) && (length(points[0], points[1]) == length(points[3], points[0])) ) && (((points[0].x - points[1].x) * (points[2].x - points[1].x) + (points[0].y - points[1].y) * (points[2].y - points[1].y)) == 0);
    return check;
}

#endif // FIGURES_H