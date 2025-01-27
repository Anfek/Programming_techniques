#include <random>
#include "hash-map.h"

int main(){
    Hash_Map<int, int> table = Hash_Map<int, int>();

    int lim = 30;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 4*lim);

    int buf;
    for(int i = 0; i<lim; i++){
        buf = dist(gen);
        table.push(buf, buf);
        //table.print();
        //std::cout<<std::endl;
    }
    table.print();
    std::cout<<std::endl;
    
    std::cout<<"Maximum load factor = "<<table.get_max_alhpa()<<std::endl;
    std::cout<<"Current load factor = "<<table.get_alhpa()<<std::endl;
    std::cout<<"Current numbers of elements = "<<table.get_size()<<std::endl;
    std::cout<<std::endl;

    std::cout<<"Enter any key to start checks: ";
    std::cin >> buf;
    std::cout<<"Check operator["<<buf<<"]: "<<table[buf]<<std::endl;
    std::cout<<"Check delete by key: "<<std::endl;
    table.delete_by_key(buf);
    std::cout<<std::endl;

    double ch;
    std::cout<<"Enter any value to change the maximum load factor: ";
    std::cin >> ch;
    table.push_max_alpha(ch);
    std::cout<<"Enter any value to change the current load factor: ";
    std::cin >> ch;
    table.push_alpha(ch);
    std::cout<<"MLF = "<<table.get_max_alhpa()<<"\tCLF = "<<table.get_alhpa()<<std::endl;
    std::cout<<std::endl;
    table.print();
    std::cout<<std::endl;

    std::cout<<"Enter any value to change the current numbers of lists: ";
    std::cin >> buf;
    table.push_size_list(buf);
    std::cout<<std::endl;

    std::cout<<"MLF = "<<table.get_max_alhpa()<<"\tCLF = "<<table.get_alhpa()<<std::endl;
    std::cout<<std::endl;
    table.print();
    std::cout<<std::endl;
    
    std::cout<<"Deletion check: "<<std::endl;
    table.delete_all();
    table.print();
}