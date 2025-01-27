import java.util.Random;
import java.util.Scanner;

public class test {
    public static void main(String[] args) {
        Graph_a graph_a = new Graph_a();
        
        int arr[][] = {
            {0, 4, 5, 0, 0, 0, 1, 0},
            {4, 0, 0, 8, 0, 0, 0, 3},
            {5, 0, 0, 0, 6, 0, 0, 0},
            {0, 8, 0, 0, 0, 9, 0, 0},
            {0, 0, 6, 0, 0, 0, 7, 0},
            {0, 0, 0, 9, 0, 0, 0, 10},
            {1, 0, 0, 0, 7, 0, 0, 2},
            {0, 3, 0, 0, 0, 10, 2, 0}
        };

        for(int i=0; i<8; i++){
            for(int j=i; j<8; j++){
                if(arr[i][j] != 0){
                    graph_a.add(i, j, arr[i][j]);
                    graph_a.add(j, i, arr[j][i]);
                }
            }
        }

        graph_a.print_AL();             System.out.println();
        graph_a.print_AM();             System.out.println();

        graph_a.Kruskal_algorithm();
    }
}