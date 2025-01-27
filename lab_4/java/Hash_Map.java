import java.util.*;

public class Hash_Map<TKeyType extends Comparable<TKeyType>, TDataType>{
    private static class Node<TKey, TData>{
        private TKey key;
        private TData data;

        public Node(TKey _key, TData _data){
            this.key  = _key;
            this.data = _data;
        }
    }

    ArrayList<Node<TKeyType, TDataType>>[] table;
    int size_elements, size_list;
    double alpha_max = 2.0; 

    public Hash_Map(){
        size_elements = 0;
        size_list = 1;
        table = new ArrayList[size_list];
        for (int i = 0; i < size_list; i++)
            table[i] = new ArrayList<>();
    }
    
    public Hash_Map(Hash_Map<TKeyType, TDataType> another_table){
        this.table = another_table.table;
    }

    public int get_size(){ //возвращает число элементов
        return size_elements;
    }

    public double get_alhpa(){ //возвращает уровень загруженности
        return size_elements/((double)size_list);
    }

    public void push_alpha(double alpha){ //изменяет уровень загруженности
        func_resize((int)(size_elements/alpha));
    }

    public void push_size_list(int new_size_list){ //изменяет число списков
        func_resize(new_size_list);
    }

    public double get_max_alhpa(){ //возвращает коэффициент максимальной загруженности
        return alpha_max;
    }

    public void push_max_alpha(double alpha){ //изменяет коэффициент максимальной загруженности
        alpha_max = alpha;
    }

    public void delete_all(){
        for(int i=0; i<size_list; i++){
            Iterator<Node<TKeyType, TDataType>> it = table[i].iterator();
            while (it.hasNext()){
                it.next();
                it.remove();
            }
        }
        size_elements = 0;
        size_list = 1;
        table = new ArrayList[size_list];
        for (int i = 0; i < size_list; i++)
            table[i] = new ArrayList<>();
    }

    private boolean primality_check(int a){
        double sq = Math.sqrt(a);
        for(int i = 2; i<=sq; i++){
            if(a%i == 0)
                return false;
        }
        return true;
    }

    private void func_resize(int new_size_list){
        int old_size = size_list;
        while(alpha_max < size_elements/(double)new_size_list) //проверяем не перегружен ли список
            new_size_list++;
        
        if(new_size_list%2 == 0)
            new_size_list++;
        for(size_list = new_size_list; !primality_check(size_list); size_list+=2){}// делаем размер простым числом

        
        ArrayList<Node<TKeyType, TDataType>>[] new_table = new ArrayList[size_list];
        for (int i = 0; i < size_list; i++)
            new_table[i] = new ArrayList<>();
        
        for(int i=0; i<old_size; i++){
            Iterator<Node<TKeyType, TDataType>> it = table[i].iterator();
            while (it.hasNext()){
                Node<TKeyType, TDataType> node = it.next();
                int h = node.key.hashCode()%size_list;
                new_table[h].add(node);
            }
        }
        table = new_table;
    }

    public void push(TKeyType key, TDataType data){
        int numb = key.hashCode()%size_list;
        
        Iterator<Node<TKeyType, TDataType>> it = table[numb].iterator();
        while (it.hasNext()){
            Node<TKeyType, TDataType> next_node = it.next();
            if(next_node.key.compareTo(key) == 0){
                it.remove();
                next_node = new Node<TKeyType, TDataType>(key, data);
                table[numb].add(next_node);
                return;
            }
        }

        Node<TKeyType, TDataType> node = new Node<TKeyType, TDataType>(key, data);
        table[numb].add(node);
        size_elements++;

        if(alpha_max <= (size_elements/(double)size_list)){
            func_resize(2*size_list+1);
        }
    }

    public void delete_by_key(TKeyType key){
        int numb = key.hashCode()%size_list;

        Iterator<Node<TKeyType, TDataType>> it = table[numb].iterator();
        while (it.hasNext()){
            if(it.next().key.compareTo(key) == 0){
                it.remove();
                size_elements--;
                return;
            }
        }
    }

    public TDataType value_by_key(TKeyType key){
        int numb = key.hashCode()%size_list;

        Iterator<Node<TKeyType, TDataType>> it = table[numb].iterator();
        while (it.hasNext()){
            Node<TKeyType, TDataType> next_node = it.next();
            if(next_node.key.compareTo(key) == 0)
                return next_node.data;
        }
        return (TDataType)null;
    }

    void print(){
        for(int i=0; i<size_list; i++){
            System.out.print("["+i+"]:\t");
            Iterator<Node<TKeyType, TDataType>> it = table[i].iterator();
            while (it.hasNext()){
                Node<TKeyType, TDataType> node = it.next();
                System.out.print( "->  (" + node.key + ", " + node.data + ")  ");
            }
            System.out.println();
        }
    }
}