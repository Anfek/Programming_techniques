import java.util.Random;
import java.util.Scanner;

public class test_tree{ 
    public static void main(String[] args) {
        rb_tree<Integer, Integer> tree = new rb_tree<>();
        Random random = new Random();

        System.out.println("Check empty: " + tree.empty());
        int number = 512;
        
        for(int i=1; i<512; i++){
            tree.push(i*2, i*2);
            System.out.println("Numbers: " + i + "\th1 = " + tree.h1() + "\th2 = " + tree.h2());
        }

        System.out.println("The number of elements is: "+ number);
        System.out.println("Check empty: " + tree.empty());
        System.out.println("\nСhecking the total height of a tree: h1 = " + tree.h1() + "\th2 = " + tree.h2() + "; h <= " + (2*Math.log(number+1)/Math.log(2)) + "\n\n");
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