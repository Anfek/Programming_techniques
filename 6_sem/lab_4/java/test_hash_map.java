import java.util.Random;
import java.util.Scanner;

public class test_hash_map{
    public static void main(String[] args) {
        Hash_Map<Integer, String> table = new Hash_Map<>();

        Random random = new Random();
        int number = 20;
        
        for(int i=0; i<number; i++){
            int buf = 1 + random.nextInt(number*4);
            String buf1 = Integer.toString(buf);
            table.push(buf, buf1);
        }
        table.print();

        System.out.println("Maximum load factor = " + table.get_max_alhpa());
        System.out.println("Current load factor = " + table.get_alhpa());
        System.out.println("Current numbers of elements = " + table.get_size());
        System.out.println();

        int buf;
        System.out.print("Enter any key to start checks: ");
        Scanner sint = new Scanner(System.in);
        buf = sint.nextInt();
        System.out.println("Check operator[" + buf + "]: " + table.value_by_key(buf));
        System.out.println("Check delete by key: ");
        table.delete_by_key(buf);
        System.out.println();

        double ch;
        System.out.print("Enter any value to change the maximum load factor: ");
        Scanner sdouble = new Scanner(System.in);
        ch = sdouble.nextDouble();
        table.push_max_alpha(ch);
        System.out.print("Enter any value to change the current load factor: ");
        ch = sdouble.nextDouble();
        table.push_alpha(ch);
        System.out.println("MLF = " + table.get_max_alhpa() + "\tCLF = " + table.get_alhpa());
        System.out.println();
        table.print();
        System.out.println();

        System.out.print("Enter any value to change the current numbers of lists: ");
        buf = sint.nextInt();
        table.push_size_list(buf);
        System.out.println();

        System.out.println("MLF = " + table.get_max_alhpa() + "\tCLF = " + table.get_alhpa());
        System.out.println();
        table.print();
        System.out.println();
        
        System.out.println("Deletion check: ");
        table.delete_all();
        table.print();
    }
}