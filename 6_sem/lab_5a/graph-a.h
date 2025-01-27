#pragma onse 
#include "graph.h"

class Graph_a/*::Graph*/ {
private:
    Graph* gr;
    using Type_FS = std::pair<std::vector<int>, std::vector<int>>;
    struct edges {
        int start, end, lenght;
    };
    struct kru_nodes {
        int last_n, c;
        std::vector<int> nodes;
    };
    using Type_vec_edges = std::vector<edges>;
    Type_FS DFS(Type_FS D, int i);
    Type_FS BFS(Type_FS D, int i);
    Type_FS alg_D(int n, Type_FS D);

    int min(int a, int b);

    bool orientaton_check(std::vector<std::vector<int>> arr);
    Type_vec_edges sorting_by_length(Type_vec_edges vec_edges, int size);
    kru_nodes helper_function_kru(int n, kru_nodes N);
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
