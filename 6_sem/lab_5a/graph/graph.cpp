#include "graph.h"

void Node::add(int n, int l) {
    this->number = n;
    this->length = l;
}

int Node::get_numb() { return number; }
int Node::get_len() { return length; }

Graph::Graph() {
    graph.resize(1);
}

Graph::~Graph() {

}


void Graph::push(int a, int b, int lenght) {
    if (a >= graph.size())
        graph.resize(a + 1);
    Node node;
    node.add(b, lenght);
    graph[a].push_back(node);
}


std::vector<std::vector<int>> Graph::list_to_matrix() {
    std::vector<std::vector<int>> arr;
    arr.resize(graph.size());
    for (int i = 0; i < graph.size(); i++) {
        arr[i].resize(graph.size());
        for (int j = 0; j < graph.size(); j++)
            arr[i][j] = (int)INFINITY;
    }

    for (int i = 0; i < graph.size(); i++) {
        for (auto iter = graph[i].begin(); iter != graph[i].end(); iter++) {
            arr[i][(*iter).get_numb()] = (*iter).get_len();
        }
    }

    return arr;
}



void Graph::PAM(std::vector<std::vector<int>> arr) {
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr[i].size(); j++) {
            if (arr[i][j] != INFINITY)
                std::cout << arr[i][j] << "\t";
            else
                std::cout << "inf" << "\t";
        }
        std::cout << std::endl;
    }
}

void Graph::print_adjacency_matrix() {
    std::vector<std::vector<int>> arr = list_to_matrix();
    PAM(arr);
}

void Graph::print_python_graphics() {
    std::vector<std::vector<int>> arr = list_to_matrix();

    std::string str = "python3 graphics.py " + std::to_string(graph.size()) + ' ';
    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph.size(); j++) {
            if (arr[i][j] != (int)INFINITY)
                str += (std::to_string(arr[i][j]) + ' ');
            else
                str += ("0 ");
        }
    }
    const char* command = str.c_str();
    system(command);
}

void Graph::PAL(Type_graph new_graph) {
    for (int i = 0; i < new_graph.size(); i++) {
        std::cout << '[' << i + 1 << "]:\t";
        for (auto iter = new_graph[i].begin(); iter != new_graph[i].end(); iter++) {
            std::cout << "->  (" << (*iter).get_numb() + 1 << ", len=" << (*iter).get_len() << ")  ";
        }
        std::cout << std::endl;
    }
}

void Graph::print_array_list() {
    for (int i = 0; i < graph.size(); i++) {
        std::cout << '[' << i + 1 << "]:\t";
        for (auto iter = graph[i].begin(); iter != graph[i].end(); iter++) {
            std::cout << "->  (" << (*iter).get_numb() + 1 << ", len=" << (*iter).get_len() << ")  ";
        }
        std::cout << std::endl;
    }
}
