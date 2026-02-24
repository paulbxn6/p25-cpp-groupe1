// Un dernier projet sur les graphes.
// Vous devez représenter un graphe sous la forme de liste d'adjacence, constitué de sommets nommés
// et d'arêtes portant une valeur numérique (double) entre ces sommets.

// Dans un graphe sous la forme de liste d'adjacence:
//    - le graphe possède le vecteur de ses sommets;
//    - chaque sommet possède le vecteurs des arêtes dont il est le sommet de départ.

// Vous devez coder les class Vertex, Edge et Graph, avec les consignes suivantes:
//    0) ne mettez pas d'attributs en public
//       ne mettez pas de méthodes pour accéder aux attributs
//       mais utilisez friend au besoin

//    1) les sommets sont identifiés par leurs noms qui sont des std::string

//    2) vous devez utiliser des std::vector pour les listes de sommets et d'arêtes
//       a) Vous devez donc conserver une correspondance entre le nom d'un sommet et son indice dans le graphe
//          pour cela le graphe possède une std::unordered_map<std::string, int> comme montré ci-dessous

//    3) vous utilisez new et delete pour les Vertex et Edge dans le graphe.

//    4) vous devez proposer une méthode de la classe Graph qui lise un graphe écrit dans un fichier
//       comme exemple, regardez la fonction read_graph ci-dessous

//    5) vous devez implémenter un parcours de ce graphe en profondeur (déjà fait en cours)
//       pour stocker les sommets déjà visités utilisez un std::set

//    6) vos devez implémenter une méthode de Graph qui construit la matrice d'adjacence du graphe
//       vous stockez cette matrice comme attribut du graphe
//       utilisez votre class Matrix ou codez-en une

//    7) appliquez à cette matrice d'adjacence l'Algorithme de Floyd-Warshall
//  https://fr.wikipedia.org/wiki/AlgorithmedeFloyd-Warshall
// qui calcule les plus courts chemins entre tous les sommets d'un graphe

//   8) IA générative:
//    a) N'utilisez pas d'IA générative pour générer votre code sauf pour des choses
//       très ciblées/spécifique mais pas pour générer tout un code !
//    b) quand vous faites générer une partie très spécifique de code, vous devez:
//       i) indiquer que c'est de l'IA
//       ii) relire, debugger, tester et donc comprendre exactement tout le code
//       iii) ne pas laisser de construction c++ que vous ne maîtrisez pas

//   9) une fois le programme complètement codé,
//      i) utilisez une IA générative pour générer un code avec les mêmes contraintes que le vôtre
//         mettez ce code dans un fichier du même nom que celui du projet avec "_IA" avant le .cpp ou le .h
//      ii) relisez-le et notez dans le fichier les endroit que vous ne comprenez pas
//          ou qui sont très différents de ce que vous avez utilisé en cours
//      iii) demandez à l'IA de vous expliquer ces endroits et mettez l'explication dans votre fichier
//      Mettez dans votre repo ce ou ces fichiers aussi (avec donc _IA avant le '.' du suffixe '***_IA.cpp" ou "***_IA.h")

#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <unordered_map>
#include <set>
#include <limits> // Pour l'infini

struct Matrix
{
    const int size;
    std::vector<std::vector<double>> m;
    Matrix(int n) : size(n)
    {
        std::vector<std::vector<double>> matrix;
        for (int i = 0; i < n; i++)
        {
            std::vector<double> ligne;
            for (int j = 0; j < n; j++)
            {
                if (i == j)
                {
                    ligne.push_back(0);
                }
                else
                {
                    ligne.push_back(std::numeric_limits<double>::infinity());
                }
            }
            matrix.push_back(ligne);
        }
        m = matrix;
    }
    Matrix copy()
    {
        Matrix matrix(size);
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                matrix.m[i][j] = m[i][j];
            }
        }
        return matrix;
    }
    void set(int i, int j, double val)
    {
        m[i][j] = val;
    }
    double get(int i, int j)
    {
        return m[i][j];
    }
    void print()
    {
        for (int i = 0; i < size; i++)
        {
            std::cout << "[ ";
            for (int j = 0; j < size; j++)
            {
                std::cout << m[i][j] << " ";
            }
            std::cout << "]" << std::endl;
        }
    }
};

class Vertex;

class Edge
{
    Vertex *s1;
    Vertex *s2;
    double val;
    Edge(Vertex *s1, Vertex *s2, double val) : s1(s1), s2(s2), val(val) {}
    friend class Graph;
    friend class Vertex;
};

class Vertex
{
    std::string nom;
    std::vector<Edge *> aretes_adj;
    Vertex(std::string nom) : nom(nom) {}
    ~Vertex() {
        for (int i=0; i<aretes_adj.size(); i++) {
            delete aretes_adj[i];
        }
    }
    void ajouter_arete(Edge *e)
    {
        aretes_adj.push_back(e);
    }
    friend class Graph;
};

struct Graph
{
    std::vector<Vertex *> sommets;
    std::unordered_map<std::string, int> noms;

    int n; // Nombre de sommets
    Graph() { n = 0; }
    void add_vertex(std::string nom)
    {
        noms[nom] = n;
        Vertex *v = new Vertex(nom);
        sommets.push_back(v);
        n++;
    }

public:
    void add_edge(const std::string &begin, const std::string &end, double value)
    {
        if (noms.find(begin) == noms.end())
        {
            add_vertex(begin);
        }
        if (noms.find(end) == noms.end())
        {
            add_vertex(end);
        }
        Vertex *v1 = sommets[noms[begin]];
        Vertex *v2 = sommets[noms[end]];
        Edge *e = new Edge(v1, v2, value);
        v1->ajouter_arete(e);
    }

    void explore(Vertex *v, std::set<Vertex *> &vus) // fonction auxiliaire servant au dfs
    {
        if (vus.find(v) == vus.end())
        {
            std::cout << v->nom << " ";
            vus.insert(v);
            for (int j = 0; j < v->aretes_adj.size(); j++)
            {
                explore(v->aretes_adj[j]->s2, vus);
            }
        }
    }
    void dfs()
    {
        std::set<Vertex *> vus;
        for (int i = 0; i < n; i++) // Pour explorer toutes les composantes connexes
        {
            explore(sommets[i], vus);
        }
        std::cout << std::endl;
    };
    Matrix to_matrix()
    {
        Matrix matrix = Matrix(n);
        for (int i = 0; i < n; i++)
        {
            Vertex *v = sommets[i];
            for (int j = 0; j < v->aretes_adj.size(); j++)
            {
                matrix.set(i, noms[v->aretes_adj[j]->s2->nom], v->aretes_adj[j]->val);
            }
        }
        return matrix;
    }
};

// Cette fonction read_triplet lit une suite de triplets:
//           from_1 to_1 value_1 from_2 to_2 value_2 ... from_n to_n value_n
//    où les value_i sont des doubles e.g. 3.14159
//    où from_i et to_i sont des mots SANS espace e.g. Le_Havre mais pas Le Havre ou "Le Havre"
// voir fichier graph0.gr

Graph read_triplet(const std::string &filename)
{
    Graph g;
    std::cout << "read_triplet(" << filename << ")" << std::endl;

    // on essaie d'ouvrir le fichier en lecture
    // pour cela on crée un objet de type std::ifstream (input file stream)
    //    et le constructeur ouvre le fichier
    std::ifstream file(filename);

    if (not file.is_open())
    {
        // si le fichier n'a pas pu être ouvert, on s'en va e.g. par une exception
        throw std::runtime_error(std::string("file ") + filename + std::string(" not found"));
    }

    // si on est arrivé là c'est que le fichier est ouvert, on va le lire
    // on sait qu'il contient le graphe sur une ligne sous la forme de triplets: from to value
    // e.g. Paris Lyon 100 Paris Nice 200 Paris ...

    // from, to sont des strings et value un double
    // on réserve trois variables pour lire ces valeurs
    std::string from, to;
    double value;

    while (file >> from >> to >> value) // tant qu'on a un triplet (les 2 strings et l'int) à lire
    // notons que l'expression "file >> var" a comme valeur l'état du fichier après la lecture de var
    {
        std::cout << from << " " << to << " " << value << std::endl;
        g.add_edge(from, to, value);
        // là on l'affiche simplement l'arête, mais il faut l'ajouter au graphe !
        // g.add_vertex(from, to, value);
    }
    std::cout << std::endl;

    file.close(); // on ferme le fichier

    // Attention ça échouera si vous mettez un nom de ville avec un espace (ou une tabulation)
    // (même si vous mettez des " " autour), en effet
    //    - quand une std::string est lue, la lecture se fait jusqu'au premier espace
    //      si vous mettez "Le Havre" ça fera deux mots donc ça échouera
    //      il faudra mettre Le_Havre

    return g;
}

double min(double x, double y)
{
    if (x < y)
    {
        return x;
    }
    else
    {
        return y;
    }
}

Matrix FloydWarshall(Graph g)
{
    Matrix fw = g.to_matrix().copy();
    int n = fw.size;
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                fw.set(i, j, min(fw.get(i, j), fw.get(i, k) + fw.get(k, j)));
            }
        }
    }
    return fw;
}

int main()
{
    Graph graph = read_triplet("graph1.gr");
    graph.dfs();
    Matrix m = graph.to_matrix();
    m.print();
    std::cout << std::endl;
    Matrix fw = FloydWarshall(graph);
    fw.print();
    return 0;
}
