import java.util.Arrays;

public class Simple_sort<T>{
    private T[] arr;
    private int[] age;
    private int len;
    private int capacity;

    public Simple_sort(){
        this.arr = (T[])new Object[1];
        this.age = new int[1];
        this.len = 0;
        this.capacity = 1;
    }

    public Simple_sort(T[] arr){
        this.arr = arr;
        this.age = new int[1];
        this.len = arr.length;
        this.capacity = arr.length;
    }

    public void clear(){
        this.arr = (T[])new Object[1];
        this.age = new int[1];
        this.len = 0;
        this.capacity = 1;
    }

    private void resize(){
        T[] new_arr = (T[])new Object[2*this.capacity + 10];
        int[] new_age = new int[2*this.capacity + 10];
        for (int i = 0; i < this.capacity; i++){
            new_arr[i] = this.arr[i];
            new_age[i] = this.age[i];
        }
        this.arr = new_arr;
        this.age = new_age;
        this.capacity = 2*this.capacity;
    }

    public int getlen(){
        return this.len;
    }

    public void add(int age){
        if (this.len == this.capacity){
            resize();
        }
        this.arr[len] = null;
        this.age[len] = age;
        this.len++;
    }

    public void add(T el){
        if (this.len == this.capacity){
            resize();
        }
        this.arr[len] = el;
        this.age[len] = 0;
        this.len++;
    }

    public void add(T el, int age){
        if (this.len == this.capacity){
            resize();
        }
        this.arr[len] = el;
        this.age[len] = age;
        this.len++;
    }

    public int sum(){
        int res = 0;
        for (int i = 0; i < this.len; i++) {
            res+=this.age[i];
        }
        return res;
    }

    public void printVec(){
        if(this.arr[0]==null){
            for(int i=0; i<this.len; i++)
                System.out.print("{" + this.age[i] + "} ");
        }
        else if(sum()==0){
            for(int i=0; i<this.len; i++)
                System.out.print("{" + this.arr[i] + "} ");
        }
        else{
            for(int i=0; i<this.len; i++)
                System.out.print("{" + this.arr[i] + ", " + this.age[i] + "} ");
        }
        
        System.out.println("");
    }


    public void sort_buble_range(){
        // Сортировка массива
        for(int i=0;i<this.len;i++){
            boolean sorted=true;
            for(int j=0;j<this.len-i-1;j++){
                if(this.arr[0]==null){
                    if(this.age[j]>this.age[j+1]){
                        int n = this.age[j];
                        this.age[j] = this.age[j+1];
                        this.age[j+1] = n;
                        sorted=false;
                    }
                }
                else{
                    if(((Comparable)this.arr[j]).compareTo(this.arr[j+1])>0){
                        T temp = this.arr[j];
                        this.arr[j] = this.arr[j+1];
                        this.arr[j+1] = temp;
    
                        int n = this.age[j];
                        this.age[j] = this.age[j+1];
                        this.age[j+1] = n;
                        sorted=false;
                    }
                }
            }
            if(sorted){
                break;
            }
        }
        printVec();
    }

    public void sort_buble_range(int[] arr){
        for(int i=0;i<arr.length;i++){
            boolean sorted=true;
            for(int j=0;j<arr.length-i-1;j++){
                if(((Comparable)arr[j]).compareTo(arr[j+1])>0){
                    int temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                    sorted=false;
                }
            }
            if(sorted){
                break;
            }
        }
        System.out.println(Arrays.toString(arr));
    }

    public void sort_insert_range(){
        for (int i = 0; i < this.len; i++){
            T value = this.arr[i];
            int val = this.age[i];
            int el = i - 1;
            for (; el>=0; el--) {
                //if (value < c[el])
                if (((Comparable)value).compareTo(this.arr[el]) < 0)
                {
                    this.arr[el + 1] = this.arr[el];
                    this.age[el + 1] = this.age[el];
                } else {
                    break;
                }
            }
            this.arr[el+1] = value;
            this.age[el+1] = val;
        }
        printVec();
    }

    public void sort_insert_range(int[] arr){
        for (int i = 0; i < arr.length; i++){
            int val = arr[i];
            int el = i - 1;
            for (; el>=0; el--) {
                //if (value < c[el])
                if (val<arr[el])
                {
                    arr[el + 1] = arr[el];
                } else {
                    break;
                }
            }
            arr[el+1] = val;
        }
        System.out.println(Arrays.toString(arr));
    }

    public void sort_selection_range(){
        for (int i = 0; i < this.len; i++){
            int minn = i;

            for (int j = i; j < this.len; j++){
                //if (c[j] < c[minn])
                if (((Comparable)this.arr[j]).compareTo(this.arr[minn]) < 0)
                {
                    minn = j;
                }
            }
            //swap
            T tmp = this.arr[i];
            this.arr[i] = this.arr[minn];
            this.arr[minn] = tmp;

            int t = this.age[i];
            this.age[i] = this.age[minn];
            this.age[minn] = t;
        }
        printVec();
    }

    public void sort_selection_range(int[] arr){
        for (int i = 0; i < arr.length; i++){
            int minn = i;

            for (int j = i; j < arr.length; j++){
                //if (c[j] < c[minn])
                if (arr[j]<arr[minn])
                {
                    minn = j;
                }
            }
            //swap
            int tmp = arr[i];
            arr[i] = arr[minn];
            arr[minn] = tmp;
        }
        System.out.println(Arrays.toString(arr));
    }

    public void sort_arr(){
        sort_buble_range();
        sort_insert_range();
        sort_selection_range();
    }

    public void sort_arr(int[] arr){
        sort_buble_range(arr);
        sort_insert_range(arr);
        sort_selection_range(arr);
    }

    private static int getFactorial(int f) {
        int result = 1;
        for (int i = 1; i <= f; i++) {
           result = result * i;
        }
        return result;
    }

    public void prime_numbers(int[] arr) {
        int size_prime = 0;
        for (int i = 0; i < arr.length; i++) {
            if (arr[i]>0 && arr[i]%2!=0) {
                if((getFactorial(arr[i]-1)+1)%arr[i]==0){ //Теорема Вильсона
                    size_prime++;
                }
                else if((getFactorial(arr[i]-2)-1)%arr[i]==0){ //Теорема Лейбница
                    size_prime++;
                }
                else if((arr[i]-1)%4==0){
                    if((Math.pow(getFactorial((arr[i]-1)/2), 2)+1)%arr[i]==0){ //Теорема Серпинского
                        size_prime++;
                    }
                }
            }
        }
        if (size_prime!=0){
            int[] arr_prime = new int[size_prime];
            for (int i = 0, j = 0; i < arr.length; i++) {
                if (arr[i]>0) {
                    if((getFactorial(arr[i]-1)+1)%arr[i]==0){ //Теорема Вильсона
                        arr_prime[j]=arr[i];
                        j++;
                    }
                    else if((getFactorial(arr[i]-2)-1)%arr[i]==0){ //Теорема Лейбница
                        arr_prime[j]=arr[i];
                        j++;
                    }
                    else if((arr[i]-1)%4==0){
                        if((Math.pow(getFactorial((arr[i]-1)/2), 2)+1)%arr[i]==0){ //Теорема Серпинского
                            arr_prime[j]=arr[i];
                        j++;
                        }
                    }
                }
            }
            System.out.println("Prime numbers");
            sort_buble_range(arr_prime);
        }     
    }

    public void even_and_odd_numbers(int[] arr) {
        int[] oddArray = Arrays.stream(arr).filter(x -> x % 2 != 0).sorted().toArray();
        int[] evenArray = Arrays.stream(arr).filter(x -> x % 2 == 0).sorted().toArray();
        evenArray = Arrays.stream(evenArray).filter(x -> x != 0).sorted().toArray();

            
        System.out.println("Odd numbers");
        System.out.println(Arrays.toString(oddArray));
        System.out.println("Even numbers");
        System.out.println(Arrays.toString(evenArray));
    }

    public void subsequence_sort(){
        if(this.arr[0]==null){
            even_and_odd_numbers(this.age);
            prime_numbers(this.age);
        }
        else{
            sort_arr();
        }
        System.out.println("");
    }

    
}
