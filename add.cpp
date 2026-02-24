#include <iostream>

int main (int argc, char* argv []) {
    if (argc <= 0) {
        std::cerr << "not enough arguments" << std::endl;
        return -1; 
    }
    int sum = 0;
    for (int i = 0; i < argc; i++) {
        sum = sum + std::atoi(argv[i]);
    }
    std::cout << sum << std::endl;
    return 0;
}

