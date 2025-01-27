#include <stdio.h>
#include <stdlib.h>
#include <string>
#include<iostream>
#include <random>

#include "graph-a.h" 
//using namespace std; 


int main(int argc, char* argv[]) {
    //system("pip install matplotlib");
    //system("python graphics.py");
    int n = 7;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, n / 2);
    std::string str = "python3 test.py " + std::to_string(n) + ' ';

    Graph_a* graph = new Graph_a();
    std::vector<std::vector<int>> arr;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            arr[i][j] = dist(gen);
            arr[j][i] = arr[i][j];
            if (i == j)
                arr[i][j] = 0;

            if (arr[i][j] != 0) {
                graph->add(i, j, arr[i][j]);
                graph->add(j, i, arr[j][i]);
            }
            str += (std::to_string(arr[i][j]) + ' ');
        }
    }
    std::cout << str << std::endl;
    const char* command = str.c_str();

    graph->print_AL();
    graph->print_PG();
    //system(command);
}