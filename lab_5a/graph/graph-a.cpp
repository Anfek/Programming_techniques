#include "graph-a.h"

Graph_a::Graph_a() {
    gr = new Graph();
}


void Graph_a::DFS(Graph* new_gr, std::vector<bool> D, int i) {
    D[i] = true;
    for (auto iter = gr->graph[i].begin(); iter != gr->graph[i].cend(); ++iter) {
        if (!D[(*iter).get_numb()]) {
            Node node;
            node.add((*iter).get_numb(), (*iter).get_len());
            new_gr->graph[i].push_back(node);
            DFS(new_gr, D, (*iter).get_numb());
        }
    }
}

void Graph_a::depth_first_search() {
    Graph* new_gr = new Graph();
    new_gr->graph.resize(gr->graph.size());
    std::vector<bool> D;
    D.resize(gr->graph.size());
    for (int i = 0; i < gr->graph.size(); i++)
        D[i] = false;

    DFS(new_gr, D, 0);

    std::cout << "depth-first search:" << std::endl;
    //gr->PAL(new_gr->graph);
    new_gr->print_array_list();
}

void Graph_a::BFS(Graph* new_gr, std::vector<int> D, int i) {
    for (auto iter = gr->graph[i].begin(); iter != gr->graph[i].cend(); ++iter) {
        if (D[(*iter).get_numb()] != 0)
            D[(*iter).get_numb()] = 1;
    }

    for (auto iter = gr->graph[i].begin(); iter != gr->graph[i].cend(); ++iter) {
        if (D[(*iter).get_numb()] == 1) {
            Node node;
            node.add((*iter).get_numb(), (*iter).get_len());
            new_gr->graph[i].push_back(node);
            D[(*iter).get_numb()] = 2;
            BFS(new_gr, D, (*iter).get_numb());
        }
    }
}

void Graph_a::breadth_first_search() {
    Graph* new_gr = new Graph();
    new_gr->graph.resize(gr->graph.size());

    std::vector<int> D;
    D.resize(gr->graph.size());
    D[0] = 2;
    for (int i = 1; i < gr->graph.size(); i++)
        D[i] = 0;
    BFS(new_gr, D, 0);

    std::cout << "breadth-first search:" << std::endl;
    //gr->PAL(new_gr->graph);
    new_gr->print_array_list();
}

void Graph_a::alg_D(int n, std::vector<int> D) {
    for (auto iter = gr->graph[n].begin(); iter != gr->graph[n].cend(); ++iter) {
        if (D[(*iter).get_numb()] > (D[n] + (*iter).get_len())) {
            D[(*iter).get_numb()] = D[n] + (*iter).get_len();
        }
    }
    for (auto iter = gr->graph[n].begin(); iter != gr->graph[n].cend(); ++iter) {
        alg_D((*iter).get_numb(), D);
    }
}

void Graph_a::Dijkstra(int s) {
    s -= 1;
    std::vector<std::vector<int>> D;
    D.resize(1); D[0].resize(gr->graph.size());
    for (int i = 0; i < gr->graph.size(); i++)
        D[0][i] = (int)INFINITY;
    D[0][s] = 0;
    alg_D(s, D[0]);

    std::cout << "Algorithm Dijkstra:" << std::endl;
    gr->PAM(D);
}

int Graph_a::min(int a, int b) {
    if (a < b)
        return a;
    else
        return b;
}


void Graph_a::Floyd_Warshall() {
    std::vector<std::vector<int>> arr = gr->list_to_matrix();

    for (int k = 0; k < gr->graph.size(); k++)
        for (int i = 0; i < gr->graph.size(); i++)
            for (int j = 0; j < gr->graph.size(); j++)
                arr[i][j] = min(arr[i][j], arr[i][k] + arr[k][j]);

    std::cout << "Algorithm Floyd-Warshall:" << std::endl;
    gr->PAM(arr);
}

void Graph_a::alg_P(int n, std::vector<int> D, std::vector<int> Parent) {
    for (auto iter = gr->graph[n].begin(); iter != gr->graph[n].cend(); ++iter) {
        if (D[(*iter).get_numb()] > (*iter).get_len()) {
            D[(*iter).get_numb()] = (*iter).get_len();
            Parent[(*iter).get_numb()] = n;
        }
    }
    for (auto iter = gr->graph[n].begin(); iter != gr->graph[n].cend(); ++iter) {
        alg_P((*iter).get_numb(), D, Parent);
    }
}

void Graph_a::Prim_algorithm() {
    std::vector<int> D, Parent;
    D.resize(gr->graph.size());
    Parent.resize(gr->graph.size());
    D[0] = 0; Parent[0] = 0;
    for (int i = 1; i < gr->graph.size(); i++) {
        D[i] = (int)INFINITY;
        Parent[i] = i;
    }
    for (int i = 0; i < gr->graph.size(); i++)
        alg_P(i, D, Parent);

    Graph* new_gr = new Graph();
    new_gr->graph.resize(gr->graph.size());
    for (int i = 0; i < gr->graph.size(); i++) {
        Node node;
        node.add(i, D[i]);
        new_gr->graph[Parent[i]].push_back(node);
    }

    std::cout << "Prim's algorithm:" << std::endl;
    //gr->PAL(new_gr->graph);
    new_gr->print_array_list();
}

bool Graph_a::orientaton_check(std::vector<std::vector<int>> arr) {
    bool ch = true;
    for (int i = 0; i < arr.size(); i++) {
        for (int j = i; j < arr.size(); j++) {
            if (arr[i][j] == arr[j][i])
                ch = ch && true;
            else
                ch = ch && false;
        }
    }
    return ch;
}

void Graph_a::sorting_by_length(std::vector<kru_graph> mass, int size) {
    for (int i = 1; i < size; ++i){
        for (int r = 0; r < size - i; r++) {
            if (mass[r].lenght < mass[r + 1].lenght) {
                kru_graph temp = mass[r];
                mass[r] = mass[r + 1];
                mass[r + 1] = temp;
            }
        }
    }
}

//bool Graph_a::sorting_by_length(kru_graph a, kru_graph b) { return (a.lenght < b.lenght); }

void Graph_a::Kruskal_algorithm() {
    std::vector<std::vector<int>> arr = gr->list_to_matrix();
    if (!orientaton_check(arr)) //граф не ориентированный
        return;

    std::vector<kru_graph> kru_gr;
    std::vector<bool> visited;
    kru_gr.resize(gr->graph.size());
    visited.resize(gr->graph.size());
    int size_kru = 0;
    for (int i = 0; i < gr->graph.size(); i++) {
        for (int j = 0; j < gr->graph.size(); j++) {
            if (arr[i][j] != (int)INFINITY) {
                kru_gr[size_kru].start = i;
                kru_gr[size_kru].end = j;
                kru_gr[size_kru].lenght = arr[i][j];
                size_kru++;
            }
        }
    }
    kru_gr.resize(size_kru);
    //std::sort(kru_gr.begin(), kru_gr.begin()+size_kru, sorting_by_length);
    sorting_by_length(kru_gr, size_kru);
    Graph* new_gr = new Graph();
    //int min_graph_len = 0;
    for (int i = 0; i < size_kru; i++) {
        if (!visited[kru_gr[i].start] || !visited[kru_gr[i].end]) {
            //min_graph_len += kru_gr[i].lenght;
            visited[kru_gr[i].start] = true;
            visited[kru_gr[i].end] = true;
            new_gr->push(kru_gr[i].start, kru_gr[i].end, kru_gr[i].lenght);
        }
    }
    new_gr->print_adjacency_matrix();
}


void Graph_a::add(int a, int b, int lenght) { gr->push(a, b, lenght); }
void Graph_a::print_AL() { gr->print_array_list(); }
void Graph_a::print_PG() { gr->print_python_graphics(); }
void Graph_a::print_AM() { gr->print_adjacency_matrix(); }
