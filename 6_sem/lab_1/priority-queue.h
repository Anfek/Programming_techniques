#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <iterator>

template<typename T>
class Priority_queue {
    std::vector<T> binary_heap;

public:

    int size_heap() { 
        return binary_heap.size();
    }

    bool empty() { // проверка на пустоту
        return binary_heap.empty();
    }

    const T& get_max() {
        return binary_heap[0];
    }

private:

    void value_check() { //проверяем не является ли элемент больше своего родителя
        int child = size_heap() - 1;
        int parent = (child - 1) / 2;
        while (binary_heap[parent] < (binary_heap[child]) && child != parent) {
            T buf = binary_heap[parent];
            binary_heap[parent] = binary_heap[child];
            binary_heap[child] = buf;

            child = parent;
            parent = (child - 1) / 2;
        }
    }

    void shreening() { //просеивание
        int parent = 0;
        int child_left = 2 * parent + 1;
        int child_right = 2 * parent + 2;

        while ((binary_heap[parent] < binary_heap[child_left]) && (binary_heap[parent] < binary_heap[child_right])) {
            int max;
            if ((binary_heap[child_left] > binary_heap[parent]) && (binary_heap[child_left] > binary_heap[child_right])) {
                max = child_left;
            }
            else {//if ((binary_heap[child_right] > binary_heap[parent]) && (binary_heap[child_right] > binary_heap[child_left])) {
                max = child_right;
            }

            T buf = binary_heap[parent];
            binary_heap[parent] = binary_heap[max];
            binary_heap[max] = buf;

            parent = max;
            child_left = 2 * parent + 1;
            child_right = 2 * parent + 2;

            if ((child_left >= size_heap()) && (child_right >= size_heap())) {
                break;
            }
        }
    }

    void print(int parent, int lvl) {
        if ((2 * parent + 2) < size_heap()) {
            print(2 * parent + 2, lvl + 1);
        }
        if (lvl != 0) {;
            for (int i = 0; i < lvl*3; i++){
                std::cout << ' ';
            }
        }
        std::cout << binary_heap[parent] << '\n';
        if ((2 * parent + 1) < size_heap()) {
            print(2 * parent + 1, lvl + 1);
        }
    }

public:

    void pop() { //удаление
        binary_heap[0] = binary_heap[size_heap() - 1];
        binary_heap.resize(size_heap() - 1);

        shreening();

    }

    void push(const T& new_element) {//добавление
        binary_heap.push_back(new_element);
        if (size_heap() > 1) {
            value_check();
        }
    }

    void print_heap() {
        if (size_heap() != 0) {
            print(0, 0);
            std::cout << "\n\n";

            std::copy(binary_heap.begin(), binary_heap.end(), std::ostream_iterator<T>(std::cout, " "));
            std::cout << "\n\n";
        }
        else {
            std::cout << "Unfortunately the tree is empty :(";
        }
    }
};