#include <iostream>
#include <random>
#include <math.h>
#include "map.h"

int main(){
    Map<int, int, comparator<int>> *map;
    map = new Map<int, int, comparator<int>>();
    std::cout << "Check for emptiness: " << std::boolalpha << map->empty() << "\n\n";
    
    int lim = 15;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 4*lim);
    
    for (int i = 0; i < lim; i++){
        int buf = dist(gen);
        map->push(buf, buf);
    }
    std::cout << "The number of elements is: "<< lim <<";\tHeight three: " << map->height_three() << ";\t lim = " << 1.45 * std::log2(lim+2) << std::endl;
    std::cout << "\n\n";
    map->print_map();
    std::cout << "\n\n";


    std::cout << "Enter a key to search the tree" <<std::endl;
    int number_search;
    std::cin >> number_search;
    number_search = map->operator[](number_search);
    std::cout << "The value of this key in the tree:\t" << number_search << std::endl;


    Map<int, int, comparator<int>>::Iterator* iter = new Map<int, int, comparator<int>>::Iterator(map->get_begin());
    iter->end();
    int e = **iter;
    iter->begin();
    int b = **iter;
    std::cout << "\nTEST iterator: " << "begin = " << b <<"\tend = " << e << std::endl;
    std::cout << "from beginning to end" << std::endl;
    for (int i = b; i < e; i=**iter){
        std::cout << i << '\t';
        ++*iter;
    }
    std::cout << (e = **iter);
    std::cout << std::endl;

    std::cout << "end to start" << std::endl;
    for (int i = e; i > b; i=**iter){
        std::cout << i << '\t';
        --*iter;
    }
    std::cout << (b = **iter);
    std::cout << std::endl;

    int *g = iter->operator->();
    std::cout <<"TEST pointer: " << g <<std::endl;
    

    std::cout << "Deleting all elements: " << std::endl;
    map->deleting_all_elements();    
    std::cout << "Check for emptiness: " << std::boolalpha << map->empty() << "\n\n";
    std::cout <<"\nIf you see this message, then everything is working as it should. \nPut 5 please :)."<<std::endl;
}