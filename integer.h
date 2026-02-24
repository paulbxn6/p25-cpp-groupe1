struct Int // pareil avec class Int
{ 
    int value = 0;
    void incr();              // Déclaration sans définiton
    void decr() { value--; }; // Déclaration avec définiton
    int &get() { return value; }
};

void Int::incr() { value++; } // Définition en-dehors de la classe
