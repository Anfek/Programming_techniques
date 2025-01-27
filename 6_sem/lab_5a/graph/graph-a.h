#pragma onse 
#include "graph.h"

class Graph_a {
private:
    Graph* gr;
    void DFS(Graph* new_graph, std::vector<bool> D, int i);
    void BFS(Graph* new_graph, std::vector<int> D, int i);
    void alg_D(int n, std::vector<int> D);
    void alg_P(int n, std::vector<int> D, std::vector<int> Parent);
    int min(int a, int b);

    struct kru_graph {
        int start, end, lenght;
    };
    bool orientaton_check(std::vector<std::vector<int>> arr);
    void sorting_by_length(std::vector<kru_graph> kru_gr, int size);
public:
    Graph_a();
    ~Graph_a();

    void add(int a, int b, int length);

    void depth_first_search();
    void breadth_first_search();
    void Dijkstra(int s);
    void Floyd_Warshall();
    void Prim_algorithm();
    void Kruskal_algorithm();

    void print_AL();
    void print_PG();
    void print_AM();
};
