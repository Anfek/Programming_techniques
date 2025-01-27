import java.util.Arrays;

public class effective_sort{
    public static <T extends Comparable<T>> void qsort(T a[]) {
           qsort(a,0,a.length-1);
    }

    public static <T extends Comparable<T>> void qsort(T a[], int sleft, int sright) {
        if (sleft < sright)
        {
            //make partition
            T pivot = a[(sleft + sright) / 2];
            int left = sleft;
            int right = sright;

            while (left <= right) {

                while (a[left].compareTo(pivot) < 0) {
                    left++;
                }
                while (a[right].compareTo(pivot) > 0) {
                    right--;
                }


                if (left <= right) {
                    T t = a[left];
                    a[left] = a[right];
                    a[right] = t;
                    left++;
                    right--;

                }
            }

            qsort(a, sleft, left-1);
            qsort(a, left, sright);
        }
    }

    public static <T extends Comparable<T>> void heap_sort(T arr[]) {
        heap_sort_range(arr, 0, arr.length);
    }

    public static <T extends Comparable<T>> void heap_sort_range(T arr[], int left, int right){
        int n= right-1;
        for (int i = n/2; i >=left; i--)
            heap_rebalance(arr, i, n);
        for (int i = n; i >= left; i--){
            //swap
            T t = arr[left];
            arr[left] = arr[n];
            arr[n] = t;
            n--;
            heap_rebalance(arr, 0, n);
        }
    }

    private static <T extends Comparable<T>> void heap_rebalance(T arr[], int pos, int size){
        int a = 2*pos+1;
        int b = 2*pos+2;
        int largest_el = pos;

        if (a <= size)
            if (arr[a].compareTo(arr[largest_el]) > 0){
                largest_el = a;
            }
        if (b <= size)
            if ( arr[b].compareTo(arr[largest_el]) > 0){
                largest_el = b;
            }

        if (largest_el != pos) {
            //swap
            T t = arr[pos];
            arr[pos] = arr[largest_el];
            arr[largest_el] = t;

            heap_rebalance(arr, largest_el, size);
        }
    }


    public static Integer[] merge_sort(Integer[] arr){
        if (arr.length < 2)
            return arr;
        int mid = arr.length / 2;
        //переписать все из T[] к Integer[]
        //когда берешь индекс - приводишь к T
        Integer[] arr_left = new Integer[mid]; //Arrays.copyOfRange(arr, 0, mid);
        System.arraycopy(arr,0,arr_left,0, mid );
        Integer[] arr_right =  new Integer[arr.length - mid]; // Arrays.copyOfRange(arr,  mid, arr.length);
        System.arraycopy(arr,mid,arr_right,0, arr.length - mid );
        return merge_op(merge_sort(arr_left), merge_sort(arr_right));
    }

    private static Integer[] merge_op(Integer[] arr1, Integer[] arr2){
        Integer[] buf = new Integer[arr1.length+arr2.length];

        int i_up = 0;
        int i_down = 0;

        for (int i =0; i < buf.length; i++){
            if (i_up == arr1.length){
                buf[i] = arr2[i_down++];
            } else if (i_down == arr2.length) {
                buf[i] = arr1[i_up++];
            } else {
                if ( arr1[i_up].compareTo(arr2[i_down]) < 0) {
                    buf[i] = arr1[i_up++];
                } else {
                    buf[i] = arr2[i_down++];
                }
            }
        }
        return buf;
    }

    private static int getFactorial(int f) {
        int result = 1;
        for (int i = 1; i <= f; i++) {
           result = result * i;
        }
        return result;
    }

    private static Integer[] prime_numbers(Integer[] arr) {
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
            Integer[] arr_prime = new Integer[size_prime];
        if (size_prime!=0){
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
        } 
        return arr_prime;    
    }

    private Integer[] odd_numbers(Integer[] arr){
        int len = 0;
        for (int i = 0; i < arr.length; i++) {
            if(arr[i]%2 != 0)
                len++;
        }
        Integer[] odd = new Integer[len];
        for (int i = 0, j = 0; i < arr.length; i++) {
            if(arr[i]%2 != 0){
                odd[j] = arr[i];
                j++;
            }
        }
        return odd;
    }

    private Integer[] even_numbers(Integer[] arr){
        int len = 0;
        for (int i = 0; i < arr.length; i++) {
            if(arr[i]%2 == 0)
                len++;
        }
        Integer[] even = new Integer[len];
        for (int i = 0, j = 0; i < arr.length; i++) {
            if(arr[i]%2 == 0){
                even[j] = arr[i];
                j++;
            }
        }
        return even;
    }

    public void subsequence_sort(Integer[] arr){
        Integer[] oddArray = odd_numbers(arr);
        Integer[] evenArray = even_numbers(arr);
        Integer[] primeArray = prime_numbers(arr);

        System.out.println("odd numbers:\n" + Arrays.toString(merge_sort(oddArray)));
        heap_sort(evenArray);
        System.out.println("even numbers:\n" + Arrays.toString(evenArray));
        qsort(primeArray);
        System.out.println("prime numbers:\n" + Arrays.toString(primeArray));
    }
}
