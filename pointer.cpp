#include <iostream>

void push(int* tab, int size, int& nb, int x) {
    if (nb >= size){
        std::cerr << "Pile pleine" << std::endl;
    } else {
        tab[nb] = x;
        nb = nb + 1;
    }
}

int pop(int* tab, int size, int& nb) {
    if (nb <= 0){
        std::cerr << "Pile vide" << std::endl;
        return -1;
    } else {
        nb = nb - 1;
        return tab[nb];
    }
}

void print(int* tab, int nb){
    std::cout << "[ ";
    for (int i=0; i < nb; i++){
        std::cout << tab[i] << " ";
    }
    std::cout << "[" << std::endl;
}

int main () {
    int size = 5;
    int tab[size]; // pile (LIFO)
    int nb = 0;
    print(tab, nb);
    push(tab, size, nb, -27);
    print(tab, nb);
    push(tab, size, nb, 90);
    print(tab, nb);
    int e = pop(tab, size, nb);
    print(tab, nb);
    std::cout << e << std::endl;
    return 0;
}