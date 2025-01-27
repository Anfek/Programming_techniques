#pragma onse 
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <cmath>  //для infinity


class Node{
private:
    int number;
    int length;
public:
    void add(int n, int l);
    int get_numb();
    int get_len();
};

class Graph{
public:
    using Type_graph = std::vector<std::list<Node>>;
    Type_graph graph;
    
    std::vector<std::vector<int>> list_to_matrix();
    void PAL(Type_graph new_graph);
    void PAM(std::vector<std::vector<int>>);

public:
    Graph();
    ~Graph();

    void push(int a, int b, int length);

    void print_array_list();
    void print_python_graphics(std::string message);
    void print_adjacency_matrix();
};