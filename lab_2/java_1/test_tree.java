import java.util.Random;
import java.util.Scanner;

public class test_tree{ 
    public static void main(String[] args) {
        rb_tree<Integer, Integer> tree = new rb_tree<>();
        Random random = new Random();

        System.out.println("Check empty: " + tree.empty());
        int number = 24;
        
        for(int i=0; i<number; i++){
            int buf = 1 + random.nextInt(number*4);
            tree.push(buf, buf);
        }

        System.out.println("The number of elements is: "+ number);
        System.out.println("Check empty: " + tree.empty());
        System.out.println("\nСhecking the total height of a tree: h = " + tree.height_three() + "; h <= " + (2*Math.log(number+1)/Math.log(2)) + "\n\n");
        tree.print_tree();

        System.out.println("\n\n");
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter a key to search for a value in the tree");
        number = sc.nextInt();
        System.out.print("You value: ");
        tree.search(number);

        tree.delete();
        System.out.println("Check delete all: " + tree.empty());        
    }
}