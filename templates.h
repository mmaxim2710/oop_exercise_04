#ifndef TEMPLATES_H
#define TEMPLATES_H

#include <tuple>
#include <type_traits>
#include <cassert>

#include "vertex.h"
#include "figures.h"


template<class T, class = void>
struct has_points : std::false_type {};

template<class T>
struct has_points<T, std::void_t<decltype(std::declval<const T&>().points)>> : std::true_type {};

template<class T>
struct is_figurelike_tuple : std::false_type {};

template<class Head, class... Tail>
struct is_figurelike_tuple<std::tuple<Head, Tail...>> : std::conjunction<is_vertex<Head>, std::is_same<Head, Tail>...> {};

template<size_t Id, class T>
void print_tuple(const T& figure, std::ostream& os) {
   if constexpr (Id >= std::tuple_size<T>::value) {
   } else {
       os << std::get<Id>(figure) << " ";
       print_tuple<Id + 1>(figure, os);
   }
}

template <class T>
void print(const T& figure, std::ostream& os) {
    if constexpr (has_points<T>::value) {
        for (auto point : figure.points) {
            os << point << " ";
        }
    } else if constexpr (is_figurelike_tuple<T>::value) {
        print_tuple<0>(figure, os);
    } else throw std::logic_error("error");
}


template<size_t Id, class T>
vertex<double> tuple_center(const T& figure) {
    if constexpr (Id >= std::tuple_size<T>::value) {
        return vertex<double> {0, 0};
    } else {
        vertex<double> res = std::get<Id>(figure);
        return res + tuple_center<Id+1>(figure);
    }
}

template <class T>
vertex<double> center(const T& figure) {
    vertex<double> res{0.0, 0.0};
    int i = 0;
    if constexpr (has_points<T>::value) {
        for (auto point : figure.points) {
            res += point;
            ++i;
        }
        res /= i;
        return res;
    } else if constexpr (is_figurelike_tuple<T>::value) {
        res = tuple_center<0>(figure);
        res /= std::tuple_size_v<T>;
        return res;
    } else throw std::logic_error ("error");
}


template<size_t Id, class T>
double tuple_area(const T& figure) {
    if constexpr (Id >= std::tuple_size<T>::value - 1) {
        return 0.0;
    } else {
        double res = (std::get<Id>(figure).x * std::get<Id+1>(figure).y) - (std::get<Id+1>(figure).x * std::get<Id>(figure).y);
        return res + tuple_area<Id+1>(figure);
    }
}

template <class T>
double area(const T& figure) {
    double res = 0.0;
    if constexpr (has_points<T>::value) {
        for (int i = 0; i < figure.size-1; ++i) {
            res += (figure.points[i].x * figure.points[i+1].y) - (figure.points[i+1].x * figure.points[i].y);
        }
        res += (figure.points[figure.size-1].x * figure.points[0].y) - (figure.points[0].x * figure.points[figure.size-1].y);
        return std::abs(res) / 2;
    } else if constexpr (is_figurelike_tuple<T>::value) {
        res = tuple_area<0>(figure);
        res += (std::get<std::tuple_size<T>::value - 1>(figure).x * std::get<0>(figure).y) - (std::get<0>(figure).x * std::get<std::tuple_size<T>::value - 1>(figure).y);
        return std::abs(res) / 2;
    } else {
        throw std::logic_error ("error");
    }
}


#endif //TEMPLATES_H