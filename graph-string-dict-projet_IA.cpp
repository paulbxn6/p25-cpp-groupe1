#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <fstream>
#include <limits>

class Vertex;
class Edge;
class Graph;

//////////////////////////////////////////////////////////////
///////////////////////// EDGE ///////////////////////////////
//////////////////////////////////////////////////////////////

class Edge {
private:
    Vertex* destination;
    double weight;

    Edge(Vertex* dest, double w) : destination(dest), weight(w) {}

    friend class Graph;
    friend class Vertex;
};

//////////////////////////////////////////////////////////////
///////////////////////// VERTEX /////////////////////////////
//////////////////////////////////////////////////////////////

class Vertex {
private:
    std::string name;
    std::vector<Edge*> edges;

    Vertex(const std::string& n) : name(n) {}

    ~Vertex() {
        for (Edge* e : edges)
            delete e;
    }

    friend class Graph;
};

//////////////////////////////////////////////////////////////
///////////////////////// GRAPH //////////////////////////////
//////////////////////////////////////////////////////////////

class Graph {
private:
    std::vector<Vertex*> vertices;
    std::unordered_map<std::string, int> index_map;
    std::vector<std::vector<double>> adjacency_matrix;

public:
    Graph() {}

    ~Graph() {
        for (Vertex* v : vertices)
            delete v;
    }

    //////////////////////////////////////////////////////////
    // Ajouter un sommet s'il n'existe pas
    //////////////////////////////////////////////////////////
    void add_vertex(const std::string& name) {
        if (index_map.find(name) == index_map.end()) {
            Vertex* v = new Vertex(name);
            vertices.push_back(v);
            index_map[name] = vertices.size() - 1;
        }
    }

    //////////////////////////////////////////////////////////
    // Ajouter une arête
    //////////////////////////////////////////////////////////
    void add_edge(const std::string& from,
                  const std::string& to,
                  double weight)
    {
        add_vertex(from);
        add_vertex(to);

        Vertex* v_from = vertices[index_map[from]];
        Vertex* v_to   = vertices[index_map[to]];

        Edge* e = new Edge(v_to, weight);
        v_from->edges.push_back(e);
    }

    //////////////////////////////////////////////////////////
    // Lecture depuis fichier
    //////////////////////////////////////////////////////////
    void read_graph(const std::string& filename) {
        std::ifstream file(filename);
        std::string from, to;
        double weight;

        while (file >> from >> to >> weight) {
            add_edge(from, to, weight);
        }

        file.close();
    }

    //////////////////////////////////////////////////////////
    // DFS récursif
    //////////////////////////////////////////////////////////
    void dfs_util(Vertex* v, std::set<std::string>& visited) {
        visited.insert(v->name);
        std::cout << v->name << " ";

        for (Edge* e : v->edges) {
            if (visited.find(e->destination->name) == visited.end()) {
                dfs_util(e->destination, visited);
            }
        }
    }

    void dfs(const std::string& start) {
        if (index_map.find(start) == index_map.end())
            return;

        std::set<std::string> visited;
        dfs_util(vertices[index_map[start]], visited);
        std::cout << std::endl;
    }

    //////////////////////////////////////////////////////////
    // Construction matrice d'adjacence
    //////////////////////////////////////////////////////////
    void build_adjacency_matrix() {
        int n = vertices.size();
        adjacency_matrix.assign(n, std::vector<double>(n, std::numeric_limits<double>::infinity()));

        for (int i = 0; i < n; ++i)
            adjacency_matrix[i][i] = 0.0;

        for (int i = 0; i < n; ++i) {
            for (Edge* e : vertices[i]->edges) {
                int j = index_map[e->destination->name];
                adjacency_matrix[i][j] = e->weight;
            }
        }
    }

    //////////////////////////////////////////////////////////
    // Floyd-Warshall
    //////////////////////////////////////////////////////////
    void floyd_warshall() {
        int n = adjacency_matrix.size();

        for (int k = 0; k < n; ++k)
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    if (adjacency_matrix[i][k] + adjacency_matrix[k][j]
                        < adjacency_matrix[i][j])
                        adjacency_matrix[i][j] =
                            adjacency_matrix[i][k] + adjacency_matrix[k][j];
    }

    //////////////////////////////////////////////////////////
    // Affichage matrice
    //////////////////////////////////////////////////////////
    void print_matrix() {
        int n = adjacency_matrix.size();

        std::cout << "Matrice des plus courts chemins:\n";
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (adjacency_matrix[i][j] ==
                    std::numeric_limits<double>::infinity())
                    std::cout << "INF ";
                else
                    std::cout << adjacency_matrix[i][j] << " ";
            }
            std::cout << "\n";
        }
    }
};

//////////////////////////////////////////////////////////////
///////////////////////// MAIN ///////////////////////////////
//////////////////////////////////////////////////////////////

int main() {
    Graph g;

    g.read_graph("graph1.gr");

    std::cout << "DFS depuis A:\n";
    g.dfs("A");

    g.build_adjacency_matrix();
    g.floyd_warshall();
    g.print_matrix();

    return 0;
}