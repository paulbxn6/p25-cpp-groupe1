#include <iostream>
#include <vector>

struct Edge;

struct Vertex{
    int num;
    std::vector<Edge*> edges;
    Vertex(int n) : num(n){};
    void print(){
        std::cout << "Vertex " << num << std::endl;
    }
};

struct Edge{
    double val;
    Vertex& begin;
    Vertex& end;
    Edge(double v, Vertex& b, Vertex& e) : val(v), begin(b), end(e) {};
    void print(){
        std::cout << begin.num << "--- " << val << " -->" << end.num << std::endl;
    }
};

struct Graph{
    std::vector<Vertex*> g;
    void add_vertex(int n){
        for (int i = g.size(); i <= n; i++){
            g.push_back(new Vertex(i));
        }
    }
    void add_edge(int a, int b, double x){
        add_vertex(a); add_vertex(b);
        (g[a]->edges).push_back(new Edge(x, *(g[a]), *(g[b])));
    }
    void print(){
        std::cout << g.size() << std::endl;
        for (int s = 0; s < g.size(); s++){
            g[s]->print();
            for (int e = 0; e < g[s]->edges.size(); e++){
                g[s]->edges[e]->print();
            }
        }
    }
    void dfs(){
        std::vector<bool> visited;
        for (int i=0; i<g.size(); i++){
            visited.push_back(false);
        }
        void search(int s){
            if (not visited[s]){
                std::cout << s << " ";
                visited[s] = true;
                for (int i=0; i < g[s]->edges.size(); i++){
                    search(g[s]->edges[i]->end.num);
                }
            }
        }
        for (int s=0; s<g.size(); s++){
            search(s);
        }
        std::cout << std::endl;
    }
};

int main(){
    Graph g1;
    g1.add_edge(2, 5, 17.9);
    g1.dfs();
    return 0;
}