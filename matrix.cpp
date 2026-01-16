#include <iostream>

struct Buffer
{
    int size;
    double *tab;
    int nb_refs = 1;
    Buffer(int s) : size(s)
    {
        tab = new double[size];
    }
    ~Buffer()
    {
        delete[] tab;
    }
};

struct Matrix
{
    int lines;
    int cols;
    Buffer *buffer;

    Matrix(int l, int c, Buffer *b) : lines(l), cols(c), buffer(b)
    {
    }
    Matrix(int l, int c) : lines(l), cols(c)
    {
        buffer = new Buffer(l * c);
    }
    int flatten_index(int i, int j)
    {
        return cols * i + j;
    }
    void set(int i, int j, double v)
    {
        buffer->tab[flatten_index(i, j)] = v;
    }
    double get(int i, int j)
    {
        return buffer->tab[flatten_index(i, j)];
    }
    Matrix reshape(int n, int m)
    {
        buffer->nb_refs = buffer->nb_refs + 1;
        return Matrix(n, m, buffer);
    }
    ~Matrix()
    {
        buffer->nb_refs = buffer->nb_refs - 1;
        if (buffer->nb_refs == 0)
        {
            delete buffer;
        }
    }
    void print()
    {
        std::cout << buffer->nb_refs << std::endl;
        for (int i = 0; i < lines; i++)
        { std::cout << "[ ";
            for (int j = 0; j < cols; j++)
            {
                std::cout << get(i, j) << " ";
            }
            std::cout << "]" << std::endl;
        }
    }
};

int main ()
{
    Matrix m = Matrix(3, 2);
    m.set(0, 0, 1); m.set(0, 1, 2);
    m.set(1, 0, 3); m.set(1, 1, 3);
    m.set(2, 0, 3); m.set(2, 1, 3);
    Matrix m2 = m.reshape(2, 3);
    m2.print();
    return 0;
}