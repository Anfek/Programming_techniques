#include <stdio.h>
#include <stdlib.h>
#include <string>
#include<iostream>
#include <random>

#include "graph-b.h" 
//using namespace std; 


int main(int argc, char *argv[]){
    //system("pip install matplotlib");
	//system("python graphics.py");
    int n = 7;    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, n/2);   
    
    Graph_b* graph = new Graph_b();
    int arr[n][n];
    for(int i=0; i<n; i++){  //средней руки попытка создания связгого графа с чётными степенями вершин, но тут не исключается вероятность несвязности. 
        std::uniform_int_distribution<> vartex(i+1, n-1); 
        for(int j=i; j<n; j++){
            arr[i][j]=0;
            if(vartex(gen)%2==0 && i!=j){
                arr[i][j] = dist(gen);
                graph->add(i, j, arr[i][j]);
                graph->add(j, i, arr[i][j]);
            }
            arr[j][i] = arr[i][j];
        }
        int ch = 0;
        for(int j=0; j<n; j++)
            if(arr[i][j]!=0)
                ch++;
                
        if(ch%2 != 0 && i<n-1 && ch<n){
            int j = vartex(gen);
            while (arr[i][j]!=0)
                j = vartex(gen);
            arr[i][j] = dist(gen);
            graph->add(i, j, arr[i][j]);
            graph->add(j, i, arr[i][j]);
            arr[j][i] = arr[i][j];
        }
        else if(ch == 0 && i<n-2){
            int j = vartex(gen);
            
            arr[i][j] = dist(gen);
            graph->add(i, j, arr[i][j]);
            graph->add(j, i, arr[i][j]);
            arr[j][i] = arr[i][j];

            int k = vartex(gen);
            while (j==k)
                k = vartex(gen);
            arr[i][k] = dist(gen);
            graph->add(i, k, arr[i][k]);
            graph->add(k, i, arr[i][k]);
            arr[k][i] = arr[i][k];
        }
    }
    std::cout<<"\n\t\t\t\tUNDIRECTED GRAPH\n\n"<<std::endl;
    graph->print_PG();
    graph->print_AL();
    graph->print_AM(); 
    

    graph->Tarjan_algorithm();
    graph->Fleury_algorithm();
    graph->Loop_based_algorithm();

    graph = new Graph_b();
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(dist(gen)%2 == 0 && i!=j){
                graph->add(i, j, dist(gen));
            }
        }
    }
    std::cout<<"\n\t\t\t\tDIRECTED GRAPH\n\n"<<std::endl;
    graph->print_PG();
    graph->print_AL();
    graph->print_AM();

    graph->Kosaraju_algorithm();
    graph->Tarjan_algorithm();
}