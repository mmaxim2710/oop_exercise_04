#include <iostream>
#include "templates.h"
#include "vertex.h"
#include "process.h"


int main() {
    char key = 'a';
    while (key != '0') {
        std::cout << "1. triangle" << '\n' << "2. square" << '\n' << "3. octagon" << '\n' << "4. tuple" << '\n' << "0 for exit" << std::endl;
        std::cin >> key;
        switch (key) {
            case '0':
                break;
            case '1': {
                process<Triangle<double>>(std::cin, std::cout);
                break;
            }
            case '2': {
                process<Square<double>>(std::cin, std::cout);
                break;
            }
            case '3': {
                process<Octagon<double>>(std::cin, std::cout);
                break;
            }
            case '4': {
                process<std::tuple<vertex<double>>>(std::cin, std::cout);
                break;
            }
            default: {
                std::cout << "you write the wrong key!" << std::endl;
                break;
            }
        }
    }

    return 0;
}