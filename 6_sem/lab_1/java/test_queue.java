public class test_queue {

    public static void main(String[] args) {
        priority_queue<Integer> heap = new priority_queue<>();

        System.out.println("Check for emptiness: " + heap.empty());
        System.out.println( "\nFilling: ");
        for (int i = 0; i < 15; i++){
            heap.push((int)(-50 + Math.random()*100));
        }
        heap.print_heap();
        System.out.println("Check for emptiness: " + heap.empty());
        System.out.println( "Length check: " + heap.size_heap());
        System.out.println( "Max element: " + heap.get_max());

        System.out.println("\nDelete element: ");
        heap.pop();
        heap.print_heap();
        System.out.println( "Length check: " + heap.size_heap());
        System.out.println( "Max element: " + heap.get_max());
    }
}