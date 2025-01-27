import java.util.Scanner;

public class test_binary_three {
    public static int add_k(BinaryTree<Integer, String> three, String data) {
        long k=0x0;
        for(int i=0; i<data.length(); i++){
            k = k<<8;
            k+=(byte)data.charAt(i);
        }
        return (int)k;
    }

    public static void filling(BinaryTree<Integer, String> three) {
        System.out.println("Input data. Press q to exit.");
        Scanner str = new Scanner(System.in);
        String data = str.nextLine();
        while(data.compareTo("q")!=0){
            three.insert(add_k(three, data), data);
            data = str.nextLine();
        }
    }

    public static void run() {
        BinaryTree<Integer, String> three = new BinaryTree<>();

        filling(three);

        three.PrintTree();

        System.out.print ("""
                Press:
                    1 - add an element
                    2 - search max element
                    3 - show the tree
                    4 - exit
                    0 - print this message
                    """);

        Scanner sc_int = new Scanner(System.in);
        Scanner sc_str = new Scanner(System.in);
        int ch = sc_int.nextInt();
        while (ch!=4) {
            switch (ch) {
                case 1:
                    System.out.println("Input data.");
                    String data = sc_str.nextLine();
                    three.insert(add_k(three, data), data);
                    break;
                case 2:
                    System.out.println("Input data.");
                    three.search(add_k(three, sc_str.nextLine()));
                    break;
                case 3:
                    three.PrintTree();
                    break;
                case 0:
                    
                default:
                    System.out.print ("""
                    Press:
                        1 - add an element
                        2 - search for an element
                        3 - delete all elements
                        4 - show the tree
                        5 - size of tree
                        6 - depth of tree
                        7 - exit
                        0 - print this message
                        """);
                    break;
            }
            System.out.println("");
            ch = sc_int.nextInt();
        }
    }

    public static void main(String[] args) {
        run();
    }
    
}