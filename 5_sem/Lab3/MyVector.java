@SuppressWarnings("unchecked")
public class MyVector<T>{
    private T[] arr;
    private int len;
    private int capacity;

    public MyVector(){
        this.arr = (T[])new Object[1];
        this.capacity = 1;
        this.len = 0;
    }
    public MyVector(int _capacity){
        this.arr = (T[])new Object[_capacity];
        this.capacity = _capacity;
        this.len = 0;
    }
    private MyVector(T[] _arr, int _len, int _cap){
        this.arr = _arr;
        this.len = _len;
        this.capacity = _cap;
    }
    public MyVector(MyVector<T> vec){
        this(vec.arr, vec.len, vec.capacity);
    }
    private void resize(){
        T[] new_arr = (T[])new Object[2*this.capacity + 10];
        for (int i = 0; i < this.capacity; i++){
            new_arr[i] = this.arr[i];
        }
        this.arr = new_arr;
        this.capacity = 2*this.capacity;
    }
    
    public int getCapacity(){
        return this.capacity;
    }
    public int getLen(){
        return this.len;
    }
    public T get(int index) throws Exception{
        if (index > this.len || index < 0){
            throw new Exception("Bad Index");
        }
        return this.arr[index];
    }


    public void push(T element){
        if (this.len == this.capacity){
            resize();
        }
        this.arr[len] = element;
        this.len++;
    }
    public T pop() throws Exception{
        if (this.len == 0){
            throw new Exception("Error: nothing to pop");
        }
        len--;
        return this.arr[len];
    }

    public void delete(int index) throws Exception{
        if (index > this.len || index < 0){
            throw new Exception("Bad Index");
        }

        for (int i = index; i < len-1; i++){
            this.arr[i] = arr[i+1];
        }
        len--;
    }

    public void insert(T element, int index) throws Exception{
        if (index > this.len || index < 0){
            throw new Exception("Bad Index");
        }

        if (this.len == this.capacity){
            resize();
        }

        len++;


        for (int i = len-1; i > index; i--){
            this.arr[i] = arr[i-1];
        }


        arr[index] = element;
    }


    public void clear(){
        this.arr = (T[])new Object[1];
        this.capacity = 1;
        this.len = 0;
    }

    public void printVector(){
        System.out.print("Vector: ");
        for(int i=0; i<this.len; i++)
            System.out.print("{" + this.arr[i] + "} ");
        System.out.println("");
    }

    @Override
    public String toString(){
        String res = " ";
        for (int i = 0; i < this.len; i++)
        {
            res+=(this.arr[i]+" ");
        }
        return res;
    }


}