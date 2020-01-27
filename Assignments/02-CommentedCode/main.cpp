///////////////////////////////////////////////////////////////////////////////
//                   
// Author:           Jeff Reeve
// Email:            Reeve.jeff@yahoo.com
// Label:            02-CommentedCode
// Title:            Commenting c++ code
// Course:           2143-OOP
// Semester:         Spring 2020
//
// Description:
//       Program with a basic linked list and overloaded operators.
//
// Usage:
//       
//
// Files:            
/////////////////////////////////////////////////////////////////////////////////

#include <iostream>

using namespace std;

int A[100];

/**
 * Node
 * 
 * Description:
 *      Node to hold items to go in a list
 * 
 * Public Methods:
 *      - node()
 *      - node(int n)
 *      
 */
struct Node
{
    int x;
    Node *next;
    //default constructor
    Node()
    {
        x = -1;
        next = NULL;
    }
    //constructor with specified number
    Node(int n)
    {
        x = n;
        next = NULL;
    }
};

/**
 * List
 * 
 * Description:
 *      Class holds a linked list and related methods
 * 
 * Public Methods:
 *      - void push
 *      - void insert
 *      - void printTail
 *      - void print
 *      - int pop
 *      - int operator+
 *      - int operator[]
 * 
 * Private Methods:
 *      NONE
 * 
 * Usage: 
 * 
 *      list List1
 *      list1.push(4);
 *      list1.print():
 *      
 */
class List
{
  private:
    //head and tail pointer to dictate the beginning and end of the list
    Node *Head;
    Node *Tail;
    int Size;

  public:
    //default constructer
    List()
    {
        Head = Tail = NULL;
        Size = 0;
    }

    /**
     * Public : Push
     * 
     * Description:
     *      add a integer to the end of the list
     * 
     * Params:
     *      - int val
     *      value to be added to the list
     * 
     * Returns:
     *      - NONE
     */
    void Push(int val)
    {
        // allocate new memory and init node
        Node *Temp = new Node(val);
        
        //checks if list is empty
        if (!Head && !Tail)
        {
            Head = Tail = Temp;
        }
        else
        {
            //adds new node at the end of the list and sets that to be the last item
            Tail->next = Temp;
            Tail = Temp;
        }
        Size++;
    }
    
    /**
     * Public : Insert
     * 
     * Description:
     *      add a integer to a specified point in the list
     * 
     * Params:
     *      - int val
     *      value to be added to the list
     * 
     * Returns:
     *      - NONE
     */
    void Insert(int val)
    {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        // figure out where it goes in the list
       
        Temp->next = Head;
        Head = Temp;
        if (!Tail)
        {
            Tail = Head;
        }
        Size++;
    }

    /**
     * Public : PrintTail
     * 
     * Description:
     *      Print value in last item of list
     * 
     * Params:
     *      - NONE
     * 
     * Returns:
     *      - NONE
     */
    void PrintTail()
    {
        cout << Tail->x << endl;
    }

    /**
     * Public : Print
     * 
     * Description:
     *      returns string of list to be printed
     * 
     * Params:
     *      - NONE
     * 
     * Returns:
     *      - string
     *          List of all items in list
     */
    string Print()
    {
        Node *Temp = Head;
        string list;

        //loops through each item in a list and adds them to a string
        while (Temp != NULL)
        {
            list += to_string(Temp->x) + "->";
            Temp = Temp->next;
        }

        return list;
    }

    /**
     * Public : Pop
     * 
     * Description:
     *      return the last item in the list
     * 
     * Params:
     *      - NONE
     * 
     * Returns:
     *      - int
     *          last number in the list
     */ 
    int Pop()
    {
        Size--;
        return 0; //
    }
    
    /**
     * Public : operator+
     * 
     * Description:
     *      combines two lists
     * 
     * Params:
     *      - const list &Rhs
     *      
     * 
     * Returns:
     *      - List
     *          a new list with two lists combined
     */
    List operator+(const List &Rhs)
    {
        // Create a new list that will contain both when done
        List NewList;

        // Get a reference to beginning of local list
        Node *Temp = Head;

        // Loop through local list and Push values onto new list
        while (Temp != NULL)
        {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Get a reference to head of Rhs
        Temp = Rhs.Head;

        // Same as above, loop and push
        while (Temp != NULL)
        {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Return new concatenated version of lists
        return NewList;
    }
    
    /**
     * Public : operator[]
     * 
     * Description:
     *      Implementation of [] operator.  This function returns an
     *      int value as if the list were an array.
     * 
     * Params:
     *      - int index
     *          index in list to get number
     * 
     * Returns:
     *      - int
     *          value as specified index
     */
    int operator[](int index)
    {
        Node *Temp = Head;
        
        //ensures the index is within lists bounderies
        if (index >= Size)
        {
            cout << "Index out of bounds, exiting";
            exit(0);
        }
        else
        {
            // loops through untill at the specified index
            for (int i = 0; i < index; i++)
            {
                Temp = Temp->next;
            }
            return Temp->x;
        }
    }

    /**
     * Public : &operator<<
     * 
     * Description:
     *      
     * 
     * Params:
     *      - ofstream &os, List L
     *      
     * 
     * Returns:
     *      - friend
     */
    friend ostream &operator<<(ostream &os, List L)
    {
        os << L.Print();
        return os;
    }
};

int main(int argc, char **argv)
{
    List L1;
    List L2;

    // loop to put 25 numbers in L1
    for (int i = 0; i < 25; i++)
    {
        L1.Push(i);
    }

    // loop to put 50 numbers in L1
    for (int i = 50; i < 100; i++)
    {
        L2.Push(i);
    }

    //cout << L1 << endl;
    L1.PrintTail(); // prints last number in each list
    L2.PrintTail();

    //makes a third list and adds L1 and L2
    List L3 = L1 + L2;
    cout << L3 << endl;

    //prints the fifth index in L3
    cout << L3[5] << endl;
    return 0;
}
