#ifndef PROCESS_H_
#define PROCESS_H_

#include <tuple>
#include <iostream>
#include "vertex.h"
#include "figures.h"
#include "templates.h"

template<class T>
void process(std::istream& is, std::ostream& os) {
    if constexpr (has_points<T>::value) {
        T figure(is);
        
        print(figure, os);
        os << std::endl;
        os << area(figure) << std::endl;
        os << center(figure) << std::endl;
    } else if constexpr (is_figurelike_tuple<T>::value) {
        size_t number;
        os << "Please, write number of angles: ";
        is >> number;

        switch(number) {
            case 3: {
                vertex<double> points[3];
                for (auto & i : points) {
                    is >> i;
                }
                auto[p1, p2, p3] = points;
                auto figure = std::make_tuple(p1, p2, p3);

                print(figure, os);
                os << std::endl;
                os << area(figure) << std::endl;
                os << center(figure) << std::endl;

                break;
            }
            case 4: {
                vertex<double> points[4];
                for (auto & i : points) {
                    is >> i;
                }
                if (!is_square(points)) {
                    throw std::logic_error ("this is not square");
                }
                auto[p1, p2, p3, p4] = points;
                auto figure = std::make_tuple(p1, p2, p3, p4);

                print(figure, os);
                os << std::endl;
                os << area(figure) << std::endl;
                os << center(figure) << std::endl;
                
                break;
            }
            case 8: {
                vertex<double> points[8];
                for (auto & i : points) {
                    is >> i;
                }
                auto[p1, p2, p3, p4, p5, p6, p7, p8] = points;
                auto figure = std::make_tuple(p1, p2, p3, p4, p5, p6, p7, p8);
                
                print(figure, os);
                os << std::endl;
                os << area(figure) << std::endl;
                os << center(figure) << std::endl;
                
                break;
            }
            default:
                throw std::logic_error("number of angles must be 3, 4, 8");
        }
    } else {
        throw std::logic_error ("trying to process something wrong");
    }
}

#endif //PROCESS_H_