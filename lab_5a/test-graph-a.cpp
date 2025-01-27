#include <stdio.h>
#include <stdlib.h>
#include <string>
#include<iostream>
#include <random>

#include "graph-a.h" 
//using namespace std; 


int main(int argc, char *argv[]){
    //system("pip install matplotlib");
	//system("python graphics.py");
    int n = 7;    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, n/2);    
    
    Graph_a* graph = new Graph_a();
    int arr[n][n];
    for(int i=0; i<n; i++){
        for(int j=i; j<n; j++){
            arr[i][j] = dist(gen);
            arr[j][i] = arr[i][j];
            if(i==j)
                arr[i][j] = 0;

            if(arr[i][j] != 0){
                graph->add(i, j, arr[i][j]);
                graph->add(j, i, arr[j][i]);
            }
        }
    }

    graph->print_PG();
    graph->print_AL();
    graph->print_AM(); std::cout<<std::endl;

    graph->depth_first_search(); std::cout<<std::endl;
    graph->breadth_first_search(); std::cout<<std::endl;
    graph->Dijkstra(1); std::cout<<std::endl;
    graph->Floyd_Warshall(); std::cout<<std::endl;
    graph->Prim_algorithm(); std::cout<<std::endl;
    graph->Kruskal_algorithm(); std::cout<<std::endl;
}