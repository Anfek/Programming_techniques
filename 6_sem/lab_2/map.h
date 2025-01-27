#include <cstddef>
#include <iostream>

template<typename T>
struct Node{ // T = struct pair {TKeyType first; TDataType second;};
    T data;
    int balance;
    struct Node<T> *parent, *child_left, *child_right;
};


template<typename T>
class comparator { //функтор comparator
    public:
    int operator()(const T& arg1, const T& arg2) const{
        if(arg1 < arg2)
            return -1;
        else if(arg1 == arg2)
            return 0;
        else
            return 1;
    }
};


template<typename TKeyType, typename TDataType, class Type_Comparator = comparator<TKeyType>>
class Map{
    using Type_Node = Node<std::pair<TKeyType, TDataType>>;
    Type_Comparator compr;

    Type_Node *head; //указатель на узел, являющийся корнем дерева
public:
    Map(){ //конструктор
        head = new Type_Node();
        head = NULL;
        //(head->data).first = ...
    }
private:
    void delete_all(Type_Node *node){
        if(node->child_right != NULL)
            delete_all(node->child_right);

        if(node->child_left != NULL)
            delete_all(node->child_left);
            
        delete node;
    }
    
public:

    ~Map(){ //деструктор
        delete_all(head);
    }
    
    Map(const Map &another_map){ //конструктор копирования
        head = new Type_Node();
        *head = *another_map.head;
    }

    Map & operator=(const Map &another_map){ //копирующий оператор присваивания
        if (&another_map != this){
            delete head;
            
            head = new Type_Node();
            *head = *another_map.head;
        }
    
        return *this;
    }

    Type_Node* get_begin(){
        return head;
    }

    bool empty() { // проверка на пустоту
        if(head == NULL)
            return true;
        else
            return false;
    }

    void deleting_all_elements(){ //удаление всех элементов
        delete_all(head);
        head = NULL;
    }

    
    class Iterator {
        Type_Node *current_node;
        Type_Node *current_head;

    public:
        Iterator(Type_Node* node){
            current_node = node;
            current_head = node;
        }

    private:
        Type_Node* func_begin(Type_Node *node){
            if(node->child_left != NULL){
                return(func_begin(node->child_left));
            }
            else{
                return node;
            }
        }

        Type_Node* func_end(Type_Node *node){
            if(node->child_right != NULL){
                return(func_end(node->child_right));
            }
            else{
                return node;
            }
        }

    public:
        Type_Node* begin(){
            return current_node = func_begin(current_head);
        }

        Type_Node* end(){
            return current_node = func_end(current_head);
        }

        TKeyType& operator*(){ // получение значения
            return current_node->data.first;
        }

        TKeyType* operator->(){ // получение указателя
            return &current_node->data.first;
        }

        void operator++(){            
            Type_Node *node;
            if(current_node->child_right == NULL && current_node->parent != NULL){
                node = current_node->parent;
            }
            else if (current_node->child_right != NULL){
                node = func_begin(current_node->child_right);
            }

            while(node->data.first <= current_node->data.first){
                node = node->parent;
            }
            current_node = node;      
        }

        void operator--(){
            Type_Node *node;
            if(current_node->child_left == NULL && current_node->parent != NULL){
                node = current_node->parent;
            }
            else if (current_node->child_left != NULL){
                node = func_end(current_node->child_left);
            }

            while(node->data.first >= current_node->data.first){
                node = node->parent;
            }
            current_node = node;
        }
        
    };


private:   
    int return_max(int a, int b){
        if(a>b)
            return a;
        else
            return b;
    }

    int height(Type_Node *node){
        int h_left=0, h_right=0;
        if(node == NULL)
            return 0;
        
        if(node->child_left != NULL){
            h_left = height(node->child_left);
        }
        
        if(node->child_right != NULL){
            h_right = height(node->child_right);
        }
        
        return return_max(h_left, h_right)+1;
    }
    
    void PCB(Type_Node *N, Type_Node *P, Type_Node *CL, Type_Node *CR){// parent children and balanse
        N->parent = P;
        N->child_left = CL;
        N->child_right = CR;
        
        N->balance = 0;
        if(CL!=NULL)
            CL->parent = N;

        if(CR!=NULL)
            CR->parent = N;
     }

    void PCB_and_rotation (Type_Node *old_parent, Type_Node *new_node, Type_Node *CL, Type_Node *CR){ //parent_1_refers_to_2
        if (old_parent == NULL){ 
            head = new_node;
        }
        else if(old_parent->child_left == CL || old_parent->child_left == CR){
            old_parent->child_left = new_node;
        }
        else {//if(A->parent->child_right == A)
            old_parent->child_right = new_node;
        }
        
        PCB(new_node, old_parent, CL, CR);
    }

    void left_rotation(Type_Node *A, Type_Node *L, Type_Node *B, Type_Node *C, Type_Node *R){// простое левое вращение
        Type_Node *par; //нужен из-за изменяющегося баланса A
        par = A->parent;
        //разбираемся с A, L, C
        PCB(A, B, L, C);

        //разбираемся с B, A, R
        PCB_and_rotation(par, B, A, R); //родитель A ссылается на B
    }

    void right_rotation(Type_Node *A, Type_Node *B, Type_Node *R, Type_Node *L, Type_Node *C){// простое правое вращение
        Type_Node *par; //нужен из-за изменяющегося баланса A
        par = A->parent;
        //разбираемся с A, C, R
        PCB(A, B, C, R);
        
        //разбираемся с B, L, A
        PCB_and_rotation(par, B, L, A);
    }

    void big_left_rotation(Type_Node *A, Type_Node *L, Type_Node *B, Type_Node *C, Type_Node *R, Type_Node *CL, Type_Node *CR){
        Type_Node *par; //нужен из-за изменяющегося баланса A
        par = A->parent;
        //разбираемся с A, L, CL
        PCB(A, C, L, CL);

        //разбираемся с B, CR, R
        PCB(B, C, CR, R);

        if(C->balance < 0){
            B->balance = 1;
        }
        else if(C->balance > 0){
            A->balance = -1;
        }

        //разбираемся с C, A, B
        PCB_and_rotation(par, C, A, B);
    }

    void big_right_rotation(Type_Node *A, Type_Node *B, Type_Node *R, Type_Node *L, Type_Node *C, Type_Node *CL, Type_Node *CR){
        Type_Node *par; //нужен из-за изменяющегося баланса A
        par = A->parent;
        //разбираемся с B, L, CL
        PCB(B, C, L, CL);

        //разбираемся с A, CR, R
        PCB(A, C, CR, R);

        if(C->balance < 0){
            A->balance = 1;
        }
        else if(C->balance > 0){
            B->balance = -1;
        }
        
        //разбираемся с C, B, A
        PCB_and_rotation(par, C, B, A);
    }

    bool balancing(Type_Node *node){ 
        if(node->balance <= -2){ //перевешивает левое поддерево
            if(node->child_left->balance < 0){  //перевешивает край (левая часть левой части) - простое правое вращение
                //std::cout << "right rotation " << std::endl;
                right_rotation(node, (node->child_left), (node->child_right), (node->child_left->child_left), (node->child_left->child_right));
            }
            else{ //перевешивает центр  (правая часть левой части) - большое правое вращение
                //std::cout << "big right rotation " << std::endl;
                big_right_rotation(node, (node->child_left), (node->child_right), (node->child_left->child_left), (node->child_left->child_right), (node->child_left->child_right->child_left), (node->child_left->child_right->child_right));
            }
            //std::cout << "done" << std::endl;
            return true;
        }
        else if (node->balance >= 2){ //перевешивает правое поддерево
            if(node->child_right->balance > 0){ //перевешивает край (правая часть правой части) - простое левое вращение
                //std::cout << "left rotation " << std::endl;
                left_rotation(node, (node->child_left), (node->child_right), (node->child_right->child_left), (node->child_right->child_right));
            }
            else{ //перевешивает центр (левая часть правой части) - большое левое вращение
                //std::cout << "big left rotation " << std::endl;
                big_left_rotation(node, (node->child_left), (node->child_right), (node->child_right->child_left), (node->child_right->child_right), (node->child_right->child_left->child_left), (node->child_right->child_left->child_right)); 
            }
            //std::cout << "done" << std::endl;
            return true;
        }
        return false;
    }

    int add(Type_Node *new_node, Type_Node *node){
        int c = compr((new_node->data).first, (node->data).first);
        if(c < 0){ //если новое значение меньше текущего
            if(node->child_left!=NULL){ //и текущий левый потомок не пустой
                int ret = add(new_node, node->child_left); //сравниваем текущий левый потомок
                if(ret == 2){ // если мы перезаписали значение, то выходим без изменений
                    return 2;
                }
                else if(node->child_left->balance == 0 || ret == 0){ // если мы дошли до узла с балансом равным нулю (или сделали это ранее), то выходим без дальнейших изменений
                    return 0;
                }
                else{ // в случае return 1
                    node->balance--;
                }
            }
            else{ //если левый потомок пуст записываем туда значение
                new_node->parent = node;
                node->child_left = new_node;
                node->balance--;
                return 1;
            }
        }
        else if(c == 0){// в случае совпадения ключей перезаписываем значение
            (node->data).second = (new_node->data).second;
            return 2;
        }
        else{ // если ключ больше текущего (тоже самое что и с левым)
            if(node->child_right!=NULL){
                int ret = add(new_node, node->child_right);
                if(ret == 2){
                    return 2;
                }
                else if(node->child_right->balance == 0 || ret == 0){
                    return 0;
                }
                else{
                    node->balance++;
                }
            }
            else{
                new_node->parent = node;
                node->child_right = new_node;
                node->balance++;
                return 1;
            }
        }   

        if(balancing(node))
            return 0; // в случае изменения баланса
        else
            return 1; // если баланс в норме
    }

public:
    TDataType operator[](TKeyType &key){
        Type_Node* node;
        node = head;
        while (node!=NULL && node->data.first != key){
            int buf = compr(node->data.first, key);
            if(buf > 0){
                node = node->child_left;
            }
            else if (buf < 0){
                node = node->child_right;
            }
        }
        if(node != NULL)
            return node->data.second;
        else
            return (TDataType)NULL;
    }


    void push(const TKeyType& key, const TDataType& data){ //добавление пары ключ-значение
        Type_Node *new_node;
        new_node = new Type_Node();
        new_node->data.first = key;
        new_node->data.second = data;
        new_node->balance = 0;
        new_node->parent = NULL;
        new_node->child_left = NULL;
        new_node->child_right = NULL;

        if(empty()){
            head = new_node;
        }
        else{
            add(new_node, head); //с оперсантами не работает
        }
    }
    
    int height_three(){
        return height(head);
    }
private:
    void print(Type_Node *node, int lvl){ // вызывается без оперсанта
        if(node->child_right != NULL)
            print((node->child_right), lvl+1);

        if (lvl != 0) {;
            for (int i = 0; i < lvl*3; i++){
                std::cout << ' ';
            }
        }

        std::cout << node->data.second << '(' << node->balance << ')' << std::endl;

        if(node->child_left != NULL)
            print((node->child_left), lvl+1);
    }

public:
    void print_map(){
        if(!empty())
            print(head, 0);
        else
            std::cout << "Unfortunately the tree is empty :(" <<std::endl;
    }
};


