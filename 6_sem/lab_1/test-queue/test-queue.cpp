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
    std::cout << "Проверка на пустоту: " << heap.empty() << "\n\n";

    std::cout << "Заполнение: " << "\n\n";
    srand(time(NULL));
    for (int i = 0; i < 10; i++){
        heap.push((int)rand()%100);
    }
    heap.print_heap();
    std::cout << "Проверка на пустоту: " << heap.empty() << "\n\n";
    std::cout << "Проверка длинны: " << heap.size_heap() << "\n\n";

    std::cout << "Удаление элемента: " << "\n\n";
    heap.pop();
    heap.print_heap();
    std::cout << "Проверка длинны: " << heap.size_heap() << "\n\n";

    return 0;
}
