#include "graph-a.h"

Graph_a::Graph_a() {
    gr = new Graph();
}


Graph_a::Type_FS Graph_a::DFS(Type_FS D, int i) {
    D.second[i] = 1;
    for (auto iter = gr->graph[i].begin(); iter != gr->graph[i].cend(); ++iter) {
        if (D.second[(*iter).get_numb()] == 0  && (*iter).get_len()!=(int)INFINITY) {
            D.first[(*iter).get_numb()]=i;
            D = DFS(D, (*iter).get_numb());
        }
    }
    return D;
}

void Graph_a::depth_first_search() {
    std::vector<std::vector<int>> arr = gr->list_to_matrix();
    Type_FS rd;
    rd.second.resize(gr->graph.size());
    rd.first.resize(gr->graph.size());
    for (int i = 0; i < gr->graph.size(); i++){
        rd.second[i] = 0;
        rd.first[i] = i;
    }

    rd = DFS(rd, 0);

    Graph* new_gr = new Graph();
    for (int i = 0; i < gr->graph.size(); i++){
        if(i!=rd.first[i])
            new_gr->push(rd.first[i], i, arr[rd.first[i]][i]);
    }
    new_gr->graph.resize(gr->graph.size());

    std::cout << "depth-first search:" << std::endl;
    new_gr->print_array_list();
}

Graph_a::Type_FS Graph_a::BFS(Type_FS D, int i) {
    for (auto iter = gr->graph[i].begin(); iter != gr->graph[i].cend(); ++iter) {
        if (D.second[(*iter).get_numb()]== 0){
            D.second[(*iter).get_numb()] = 1;
            D.first[(*iter).get_numb()]=i;
        }
    }

    for (auto iter = gr->graph[i].begin(); iter != gr->graph[i].cend(); ++iter) {
        if (D.second[(*iter).get_numb()] == 1) {
            D.second[(*iter).get_numb()] = 2;
            D = BFS(D, (*iter).get_numb());
        }
    }
    return D;
}

void Graph_a::breadth_first_search() {
    std::vector<std::vector<int>> arr = gr->list_to_matrix();
    Type_FS rd;
    rd.first.resize(gr->graph.size());
    rd.second.resize(gr->graph.size());
    for (int i = 0; i < gr->graph.size(); i++){
        rd.second[i] = 0;
        rd.first[i] = i;
    }
    rd.second[0] = 2;
    rd = BFS(rd, 0);

    Graph* new_gr = new Graph();
    for (int i = 0; i < gr->graph.size(); i++){
        if(i!=rd.first[i])
            new_gr->push(rd.first[i], i, arr[rd.first[i]][i]);
    }
    new_gr->graph.resize(gr->graph.size());


    std::cout << "breadth-first search:" << std::endl;
    new_gr->print_array_list();
}

Graph_a::Type_FS Graph_a::alg_D(int n, Type_FS D) {
    D.second[n] = 1;
    for (auto iter = gr->graph[n].begin(); iter != gr->graph[n].cend(); ++iter) {
        if (D.first[(*iter).get_numb()] > (D.first[n] + (*iter).get_len()) && D.second[(*iter).get_numb()]==0) {
            D.first[(*iter).get_numb()] = D.first[n] + (*iter).get_len();
        }
    }
    for (auto iter = gr->graph[n].begin(); iter != gr->graph[n].cend(); ++iter) {
        if(D.second[(*iter).get_numb()]==0)
            D = alg_D((*iter).get_numb(), D);
    }
    return D;
}

void Graph_a::Dijkstra(int s) {
    s -= 1;

    Type_FS rd;
    rd.first.resize(gr->graph.size());
    rd.second.resize(gr->graph.size());

    for (int i = 0; i < gr->graph.size(); i++){
        rd.first[i] = (int)INFINITY;
        rd.second[i] = 0;
    }
    rd.first[s] = 0;

    rd = alg_D(s, rd);

    std::vector<std::vector<int>> D;
    D.resize(1);
    D[0].resize(gr->graph.size());

    std::cout << "Algorithm Dijkstra:" << std::endl;
    for (int i = 0; i < gr->graph.size(); i++){
        std::cout << i+1 << '\t';
        D[0][i] = rd.first[i];
    }
    std::cout << std::endl;
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
                if(arr[i][k] != (int)INFINITY && arr[k][j] != (int)INFINITY && i!=j)
                    arr[i][j] = min(arr[i][j], arr[i][k] + arr[k][j]);

    std::cout << "Algorithm Floyd-Warshall:" << std::endl;
    gr->PAM(arr);
}


void Graph_a::Prim_algorithm(){
    std::vector<std::vector<int>> arr = gr->list_to_matrix();
    if (!orientaton_check(arr)) //граф не ориентированный
        return;

    std::vector<bool> belongs;
    belongs.resize(gr->graph.size());
    Type_vec_edges edges;
    int size_edges = 0;
    for (int i = 0; i < gr->graph.size(); i++) {
        belongs[i] = false;
        for (int j = i; j < gr->graph.size(); j++) {
            if (arr[i][j] != (int)INFINITY) {
                edges.resize(size_edges+1);
                edges[size_edges].start = i;
                edges[size_edges].end = j;
                edges[size_edges].lenght = arr[i][j];
                size_edges++;
            }
        }
    }
    edges = sorting_by_length(edges, size_edges);

    Graph* new_gr = new Graph();
    std::cout << "Prim's algorithm:" << std::endl;
    belongs[edges[0].start] = true;
    for (int i = 0; i < size_edges; i++){
        if(belongs[edges[i].start] && !belongs[edges[i].end] || !belongs[edges[i].start] && belongs[edges[i].end]){
            belongs[edges[i].start] = true;
            belongs[edges[i].end] = true;
            new_gr->push(edges[i].start, edges[i].end, edges[i].lenght);
            new_gr->push(edges[i].end, edges[i].start, edges[i].lenght);
            std::cout <<'('<< edges[i].start+1 <<", "<< edges[i].end+1 <<", len="<< edges[i].lenght <<')'<< std::endl;
        }
    }
    new_gr->print_python_graphics("Prim's algorithm:");
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

Graph_a::Type_vec_edges Graph_a::sorting_by_length(Type_vec_edges mass, int size) {
    for (int i = 1; i < size; ++i){
        for (int r = 0; r < size - i; r++) {
            if (mass[r].lenght > mass[r + 1].lenght) {
                edges temp = mass[r];
                mass[r] = mass[r + 1];
                mass[r + 1] = temp;
            }
        }
    }
    return mass;
}

Graph_a::kru_nodes Graph_a::helper_function_kru(int n, kru_nodes N){
    if (N.nodes[n]<0){
        N.last_n = n;
        N.c = N.nodes[n];
        return N;
    }
    N = helper_function_kru(N.nodes[n], N);
    N.nodes[n] = N.last_n;
    return N;
}

void Graph_a::Kruskal_algorithm() {
    std::vector<std::vector<int>> arr = gr->list_to_matrix();
    if (!orientaton_check(arr)) //граф не ориентированный
        return;

    kru_nodes kru_N;
    kru_N.nodes.resize(gr->graph.size());
    Type_vec_edges edges;
    int size_edges = 0;
    for (int i = 0; i < gr->graph.size(); i++) {
        kru_N.nodes[i] = -1-i;
        for (int j = i; j < gr->graph.size(); j++) {
            if (arr[i][j] != (int)INFINITY) {
                edges.resize(size_edges+1);
                edges[size_edges].start = i;
                edges[size_edges].end = j;
                edges[size_edges].lenght = arr[i][j];
                size_edges++;
            }
        }
    }
    edges = sorting_by_length(edges, size_edges);
    
    std::cout << "Kruskal's algorithm:" << std::endl;
    Graph* new_gr = new Graph();
    for (int i = 0; i < size_edges; i++){
        kru_N = helper_function_kru(edges[i].end, kru_N);
        int c2 = kru_N.c;
        kru_N = helper_function_kru(edges[i].start, kru_N);
        if(kru_N.c != c2){
            kru_N.nodes[kru_N.last_n] = edges[i].end;
            new_gr->push(edges[i].start, edges[i].end, edges[i].lenght);
            new_gr->push(edges[i].end, edges[i].start, edges[i].lenght);
            std::cout <<'('<< edges[i].start+1 <<", "<< edges[i].end+1 <<", len="<< edges[i].lenght <<')'<< std::endl;
        }
    }
    new_gr->print_python_graphics("Kruskal's algorithm:");
}


void Graph_a::add(int a, int b, int lenght) { gr->push(a, b, lenght); }
void Graph_a::print_AL() { gr->print_array_list(); }
void Graph_a::print_PG() { gr->print_python_graphics("You graph: "); }
void Graph_a::print_AM() { gr->print_adjacency_matrix(); }
