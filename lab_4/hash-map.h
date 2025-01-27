#include <vector>
#include <functional>
#include <list>
#include <cmath> 
#include <iostream>
#include <cstdio>

template<typename K, typename V, typename Hash = std::hash<K>>
class Hash_Map{
    using Type_list = std::list<std::pair<K, V>>;
    using Type_table = std::vector<Type_list>;
    Type_table table;
    Hash hash_func;
    int size_elements, size_list;
    double alpha_max = 2.0;

public:
    Hash_Map(){
        size_elements = 0;
        table.resize(1);
        size_list = table.size();
    }

    Hash_Map(Type_table another_table){
        this.table = another_table.table;
    }

    int get_size(){ //возвращает число элементов
        return size_elements;
    }

    double get_alhpa(){ //возвращает уровень загруженности
        return size_elements/((double)size_list);
    }

    void push_alpha(double const alpha){ //изменяет уровень загруженности
        func_resize((int)(size_elements/alpha));
    }

    void push_size_list(int new_size_list){ //изменяет число списков
        func_resize(new_size_list);
    }

    double get_max_alhpa(){ //возвращает коэффициент максимальной загруженности
        return alpha_max;
    }

    void push_max_alpha(double const alpha){ //изменяет коэффициент максимальной загруженности
        alpha_max = alpha;
    }

    void delete_all(){
        for(int i=0; i<size_list; i++){
            table[i].clear();
        }
        table.resize(0);
        size_list = table.size();
        size_elements = 0;
    }

private:
    bool primality_check(int a){
        double sq = sqrt(a);
        for(int i = 2; i<=sq; i++){
            if(a%i == 0)
                return false;
        }
        return true;
    }

    void func_resize(int new_size_list){
        while(alpha_max < size_elements/(double)new_size_list) //проверяем не перегружен ли список
            new_size_list++;
        
        if(new_size_list%2 == 0)
            new_size_list++;
        for(size_list = new_size_list; !primality_check(size_list); size_list+=2){}// делаем размер простым числом

        Type_table new_table;
        new_table.resize(size_list);
        
        for(int i=0; i<table.size(); i++){
            for(auto iter = table[i].begin(); iter != table[i].end(); ++iter){
                int h = hash_func((*iter).first)%size_list;
                new_table[h].push_back(std::make_pair((*iter).first, (*iter).second));
            }
        }
        table = new_table;
    }

public:
    void push(K key, V data){
        int numb = hash_func(key)%size_list;

        for(auto iter = table[numb].begin(); iter != table[numb].cend(); ++iter){
            if((*iter).first == key){
                table[numb].erase(iter);
                table[numb].push_back(std::make_pair(key, data));
                return;
            }
        }

        table[numb].push_back(std::make_pair(key, data));
        size_elements++;

        if(alpha_max <= (size_elements/(double)size_list)){
            func_resize(2*size_list+1);
        }
    }

    void delete_by_key(K key){
        int numb = hash_func(key)%size_list;

        for(auto iter = table[numb].begin(); iter != table[numb].cend(); ++iter){
            if((*iter).first == key){
                table[numb].erase(iter);
                size_elements--;
                return;
            }
        }
    }

    V& operator[](const K &key){
        int numb = hash_func(key)%size_list;

        for(auto iter = table[numb].begin(); iter != table[numb].cend(); ++iter){
            if((*iter).first == key){
                return (*iter).second;
            }
        }
        //return (V)NULL;

        table[numb].push_back(std::make_pair(key, V())); //нет элемента - добавляем в список значение "по умолчанию"
        return table[numb].back().second; //возвращаем ссылку на последний (добавленный) элемент списка
    }

    void print(){
        for(int i=0; i<table.size(); i++){
            std::cout<<'['<<i<<"]:\t";
            for(auto iter = table[i].begin(); iter != table[i].end(); iter++){
                std::cout << "->  (" << (*iter).first << ", " << (*iter).second << ")  ";
            }
            std::cout<<std::endl;
        }
    }
};