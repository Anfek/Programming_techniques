//import java.util.Random;
import java.util.Scanner;

public class test_hash_map{
    public static void main(String[] args) {
        Hash_Map<String> table = new Hash_Map<>();
        
        Scanner sc_string = new Scanner(System.in);
        int number = 10;
        
        System.out.println("Enter 10 lines: ");
        for(int i=0; i<number; i++){
            String buf = sc_string.nextLine();
            table.push(buf);
        }
        System.out.println();
        System.out.println("Your hash map: ");
        table.print();
    }
}