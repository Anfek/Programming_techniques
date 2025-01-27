#include <iostream>
#include "priority-queue.h"
#include <time.h>

/*
#include <iomanip>
#include <Windows.h>
#include <cstring>
#include <fstream>
*/

int main(){
    //setlocale(LC_ALL, "Russian");
    //SetConsoleCP(1251);
    //SetConsoleOutputCP(866);

    Priority_queue<int> heap;
    std::cout << "Check for emptiness: " << std::boolalpha << heap.empty() << "\n\n";

    std::cout << "Filling: " << "\n\n";
    srand(time(NULL));
    for (int i = 0; i < 50; i++){
        heap.push((int)rand()%100);
    }
    heap.print_heap();
    std::cout << "Check for emptiness: " << heap.empty() << "\n\n";
    std::cout << "Length check: " << heap.size_heap() << "\n\n";


    std::cout << "Delete element: " << "\n\n";
    heap.pop();
    heap.print_heap();
    std::cout << "Length check: " << heap.size_heap() << "\n\n";

    return 0;
}
