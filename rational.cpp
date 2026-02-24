#include <iostream>

struct Rational
{
    int num;
    int denom;
    Rational(int n, int d) : num(n), denom(d) // liste d'initialisation
    {
        // Corps du constructeur, ici vide
    }

    void print()
    {
        std::cout << num << "/" << denom << std::endl;
    }
}; // Ne pas oublier le ;

struct IntStack
{
    int size;
    int nb;
    int *tab;
    IntStack(int n) : size(n), nb(0), tab(new int[size])
    {
    }
    ~IntStack ()
    {
        delete tab;
    }

    void print()
    {
        for (int i = 0; i < nb; i++)
        {
            std::cout << tab[i] << " ";
        }
        std::cout << std::endl;
    }

    bool is_empty() // renvoie true si la pile est vide, false sinon
    {
        return nb == 0;
    }

    bool is_full() // renvoie true si la pile est pleine, false sinon
    {
        return nb >= size;
    }

    void push(int v)
    {
        if (nb < size)
        {
            nb = nb + 1;
            tab[nb] = v;
        }
    }

    int top(... /* les arguments ici */) // (cette fonction ne dépile pas)
    // cette fonction retourne l'entier en haut de la pile (le dernier empilé)
    // à la sortie de cette fonction l'élément retourné reste dans la pile
    // elle doit s'assurer que la pile n'est pas vide avant de la dépiler
    // elle lance une exception si problème
    {
        // votre code ici
    }

    int pop(... /* les arguments ici */) // (cette fonction dépile)
    // cette fonction retourne l'entier en haut de la pile (le dernier empilé)
    // à la sortie de cette fonction l'élément retourné n'est plus compté dans la pile
    // elle doit s'assurer que la pile n'est pas vide avant de la dépiler
    // elle lance une exception si problème
    {
        // votre code ici
    }
};

int main()
{

    Rational r(1, 2);
    r.print();
    return 0;
}