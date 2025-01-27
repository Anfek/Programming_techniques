import java.util.ArrayList;
//import java.util.Comparator;
//import java.util.List;

public class priority_queue<T extends Comparable<T>> {
    private ArrayList<T> binary_heap = new ArrayList<T>();

    public int size_heap() { //число элементов в дереве
        return binary_heap.size();
    }

    public boolean empty() { // проверка на пустоту
        if(size_heap()==0){
            return true;
        }
        else{
            return false;
        }
    }

    public T get_max() { //вывод максимального элемента
        return binary_heap.get(0);
    }

    private void shreening() { //просеивание
        int parent = 0;
        int child_left = 2 * parent + 1;
        int child_right = 2 * parent + 2;

        while ((binary_heap.get(parent).compareTo(binary_heap.get(child_left)) < 0) && (binary_heap.get(parent).compareTo(binary_heap.get(child_right)) < 0)) {
            int max;
            if ((binary_heap.get(child_left).compareTo(binary_heap.get(parent)) > 0) && (binary_heap.get(child_left).compareTo(binary_heap.get(child_right)) > 0)) {
                max = child_left;
            }
            else {//if ((binary_heap[child_right] > binary_heap[parent]) && (binary_heap[child_right] > binary_heap[child_left])) {
                max = child_right;
            }

            T buf = binary_heap.get(parent);
            binary_heap.set(parent, binary_heap.get(max));
            binary_heap.set(max, buf);

            parent = max;
            child_left = 2 * parent + 1;
            child_right = 2 * parent + 2;

            if ((child_left >= size_heap()) && (child_right >= size_heap())) {
                break;
            }
        }
    }

    public void pop() { //удаление
        binary_heap.set(0, binary_heap.get(size_heap()-1)); //вставили последний на место первого
        binary_heap.remove(size_heap() - 1); //удалили последний

        shreening();
    }

    private void value_check() { //проверяем не является ли элемент больше своего родителя
        int child = size_heap() - 1;
        int parent = (child - 1) / 2;
        while (binary_heap.get(parent).compareTo(binary_heap.get(child))<0 && child != parent) {
            T buf = binary_heap.get(parent);
            binary_heap.set(parent, binary_heap.get(child));
            binary_heap.set(child, buf);

            child = parent;
            parent = (child - 1) / 2;
        }
    }

    public void push(T new_element) {//добавление
        binary_heap.add(new_element);
        if (size_heap() > 1) {
            value_check();
        }
    }

    private void print(int parent, int lvl){
        if ((2 * parent + 2) < size_heap()) {
            print(2 * parent + 2, lvl + 1);
        }
        String space = new String(new char[lvl*3]).replace('\0', ' ');
        System.out.println(space + "{" + binary_heap.get(parent) + "}");
        if ((2 * parent + 1) < size_heap()) {
            print(2 * parent + 1, lvl + 1);
        }
    }
    public void print_heap(){
        if(size_heap()!=0)
            this.print(0, 0);
        else
            System.out.println("Unfortunately the tree is empty :(");
    }
}