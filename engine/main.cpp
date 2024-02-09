#include <iostream>
#include "add.hpp"

int main() {
    std::cout << "Hello world!";
	std::cout << add(2, 3) << "\0";
    return 0;
}
