class myList_node<T>{
    private T data;
    private myList_node<T> nextNode;

    public myList_node(){}
    public myList_node(T _data, myList_node<T> _NextNode){
        data = _data;
        nextNode = _NextNode;
    }
    public myList_node(myList_node<T> node){
        this(node.getData(), node.getNextNode());
    }

    public T getData(){
        return data;
    }

    public myList_node<T> getNextNode(){
        return nextNode;
    }
    
    public void setNextNode(myList_node<T> node){
        nextNode = node;
    }
}


public class myList<T> { 
    private myList_node<T> first_element; 
    private myList_node<T> last_element; 
    private int list_length; 


    
    public myList(){};  

    public myList(myList_node<T> fe, myList_node<T> se, int len) {    
        list_length   = len;
        first_element = fe;
        last_element  = se;

        first_element.setNextNode(last_element);
    }
    
    public myList(myList<T> another_list){
        first_element = another_list.first_element;
        last_element = another_list.last_element;
        list_length = another_list.list_length;
    }
    

    
    public void addFirstNode(myList_node<T> node){
        node.setNextNode(first_element);
        first_element = node;
        list_length++;
    }

    
    public void addLastNode(myList_node<T> node){
        if (list_length == 1){
            first_element.setNextNode(node);
            last_element = node;
        }
        last_element.setNextNode(node);
        node.setNextNode(null);
        last_element = node;
        list_length++;
    }

    
    public void deleteFirstNode(){ 
        first_element = first_element.getNextNode();
        list_length--;
    }

    
    public void deleteByValue(T value) throws Exception{    
        myList_node<T> node = first_element;
        myList_node<T> lastNode = null;
        while (node != null){
            if (node.getData() == value){

                if (node == first_element){
                    first_element = node.getNextNode();
                    node.setNextNode(null);
                } else if (node == this.last_element){
                    lastNode.setNextNode(null);
                    last_element = lastNode;
                } else {
                    lastNode.setNextNode(node.getNextNode());
                    node.setNextNode(null); 
                }
                list_length--;
                return;
            }
            lastNode = node;
            node = node.getNextNode();
        }
        throw new Exception("No element found for delete.");
    }

    
    public int getLength(){ 
        return this.list_length;
    }


    public void printmyList() { 
        myList_node<T> curlink = first_element;
        System.out.print("List: ");
        while(curlink != null) {
            System.out.print("{" + curlink.getData() + "} ");
            curlink = curlink.getNextNode();
        }
        System.out.println("");
    }
    

    public void deleteList(){
        first_element = null;
        last_element = null;
        list_length = 0;
    }
}