#pragma onse 
#include "graph.h"

class Graph_b: private Graph{
private:
    struct Visit_Stack{
        std::vector<bool> visit;
        std::vector<int> stack;
    };
    class Edges {
    public:
        int start, end, lenght;
        Edges(int a, int b, int len);
    };
    struct cycle_search_assistant{
        std::vector<int> color;
        std::vector<int> p;
        std::vector<std::vector<std::pair<int, int>>> cycle;
        std::vector<std::vector<std::pair<int, int>>> g;
        int ncycle;
    };
     
    
    Visit_Stack dfs_inv(Visit_Stack VS, int x);

    int search_len(int a, int b, cycle_search_assistant CSA);
    cycle_search_assistant add_cycle(int cycle_end, int cycle_st, cycle_search_assistant CSA);
    cycle_search_assistant dfs(cycle_search_assistant CSA, int v);
    std::vector<Edges*> find_cycles(std::vector<Edges*> edges);
    
    bool graph_vertices(std::vector<int> peaks, int i);
    bool connectivity_check(std::vector<Edges*> edges);
    std::vector<Edges*> Graph_to_edges_Euler_check(std::string algorithm);

    std::pair<std::vector<Edges*>, std::vector<int>> FindEulerPath(std::pair<std::vector<Edges*>, std::vector<int>> LBA, int v);
    
public:
    Graph_b();

    void Tarjan_algorithm();
    void Fleury_algorithm();
    void Loop_based_algorithm();
    void Kosaraju_algorithm();

    void add(int a, int b, int length);
    void print_AL();
    void print_PG();
    void print_AM();
};