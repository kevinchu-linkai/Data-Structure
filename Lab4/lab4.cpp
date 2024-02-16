//============================================================================
// Name         : lab4.cpp
// Author       :
// Version      : 1.0
// Date Created :
// Date Modified:
// Copyright    : All rights are reserved
// Description  : Doubly LinkedList implementation in C++
//============================================================================
#include<iostream>
#include<string>
#include<sstream>
#include<iomanip>
#include<exception>
using namespace std;

class Node
{
    private:
        string elem; //data element (type string in this case)
        Node* next; //Link (pointer) to the next Node
        Node* prev; //Link (pointer) to the previous Node
        friend class DoublyLinkedList;
        
    public:
        Node(): next(NULL), prev(NULL)
        {}
        Node(string elem) : elem(elem), next(NULL), prev(NULL)
        {}
};
//==============================================================
class DoublyLinkedList
{
    private:
        Node* head;     // pointer to the head of List
        Node* tail;     // pointer to the tail of List
    public:
        DoublyLinkedList (); // empty list constructor
        ~DoublyLinkedList (); // destructor to clean up all nodes
        bool empty() const; // is list empty?
        const string& front() const; // get the value (element) from front Node of list
        const string& back() const;  // get the value (element) from last Node of the List
        void addBefore(Node *ptr, const string& elem);     //add a new node before ptr
        void addFront(const string& elem); // add a new node to the front of list
        void addBack(const string & elem); //add a new node to the back of the list
        void removeFront(); // remove front node from list
        void removeBack();  // remove last node from list
        void reverseList();    // reverse the list
        bool isPalindrome(); //check if the List is Palindrome or not
        void display() const;    // display all element of the list
};
//===================================
void listCommands()
{
    cout<<"List of available Commands:"<<endl
        <<"display            : Display the Doubly Linkled List"<<endl
        <<"front              : Display the first element of the List"<<endl
        <<"back               : Display the last element of the List"<<endl
        <<"addFront <elem>    : Add a new Node at the begining of the List"<<endl
        <<"addBack  <elem>    : Add a new Node at the end of the List"<<endl
        <<"removeFront        : Remove the first Node of the Linked List"<<endl
        <<"removeBack         : Remove the last  Node of the Linked List"<<endl
        <<"isempty            : Check if the List is empty?"<<endl
        <<"reverse            : Reverse the Linked List"<<endl
        <<"isPalindrome       : Check if the List is Palindrome or not?"<<endl
        <<"help               : Display the list of available commands"<<endl
        <<"exit               : Exit the Program"<<endl;
}
//===================================
int main()
{
    DoublyLinkedList myList;
    listCommands();
    string user_input;
    string command;
    string parameter;

    do
    {
        cout<<">";
        getline(cin,user_input);

        // parse userinput into command and parameter(s)
        stringstream sstr(user_input);
        getline(sstr,command,' ');
        getline(sstr,parameter);
        
        try
        {
            if(command=="display")                 myList.display();
            else if(command=="front")            cout<<"Front = "<<myList.front()<<endl;
            else if(command=="back")            cout<<"Back = "<<myList.back()<<endl;
            else if(command=="addFront")        static_cast<void>(myList.addFront(parameter)),myList.display();
            else if(command=="addBack")             static_cast<void>(myList.addBack(parameter)),myList.display();
            else if(command=="removeFront")        static_cast<void>(myList.removeFront()),myList.display();
            else if(command=="removeBack")        static_cast<void>(myList.removeBack()),myList.display();
            else if(command=="isempty")            cout<<"List is "<<(myList.empty()? "Empty":"Not Empty")<<endl;
            else if(command=="reverse")            static_cast<void>(myList.reverseList()),myList.display();
            else if(command=="isPalindrome")    cout<<"List is "<<(myList.isPalindrome()? "Palindrome":"Not Palindrome")<<endl;
            else if(command == "help")            listCommands();
            else if(command == "exit")            break;
            else                                 cout<<"Invalid Commad !!"<<endl;
        }
        catch(exception &e)
        {
            cout<<"Exception: "<<e.what()<<endl;
        }

    }while(command!="exit" and command!="quit");

    return EXIT_SUCCESS;
}
//============================================================
DoublyLinkedList::DoublyLinkedList ()
{
    head = new Node;
    tail = new Node;
    head -> next = tail;
    tail -> prev = head;
}
//============================================================
DoublyLinkedList::~DoublyLinkedList () // destructor to clean up all nodes
{
    while(!empty()){
        removeFront();
    }
}
//============================================================
bool DoublyLinkedList::empty() const // is list empty?
{
    return head -> next == tail;
}
//============================================================
const string& DoublyLinkedList::front() const // get front element
{
    return head -> next -> elem;
}
//============================================================
const string& DoublyLinkedList::back() const // get front element
{
    return tail -> prev -> elem;
}
//============================================================
void DoublyLinkedList::addBefore(Node *ptr, const string& elem)
{
    Node* u = new Node;
    u -> elem = elem;
    u -> next = ptr;
    u -> prev = ptr -> prev;
    ptr -> prev -> next = u;
    ptr -> prev = u;
}
//============================================================
void DoublyLinkedList::addFront(const string& elem) // add to front of list
{
    addBefore(head -> next, elem);
}
//============================================================
void DoublyLinkedList::addBack(const string& elem) // add to Back of the list
{
    addBefore(tail -> prev -> next, elem);
}
//============================================================
void DoublyLinkedList::removeFront() // remove front item from list
{
    Node* v = head -> next;
    head -> next = v -> next;
    v -> next -> prev = v -> prev;
    delete v;
}
//============================================================
void DoublyLinkedList::removeBack() // remove last item from list
{
    Node* v = tail -> prev;
    tail -> prev = v -> prev;
    v -> prev -> next = v -> next;
    delete v;
}
//============================================================
void DoublyLinkedList::display() const
{
    Node *curr=head;
    while(curr!=NULL)
    {
        cout<<"+------";
        curr=curr->next;
    }
    cout<<"+"<<endl<<"|";
    curr=head;
    while(curr!=NULL)
    {
        if (curr == head)        cout<<" Head |";
        else if(curr == tail)    cout<<" Tail |";
        else                     cout<<setw(5)<<curr->elem<<" |";
    
        curr=curr->next;
    }
    curr=head;
    cout<<endl;
    while(curr!=NULL)
    {
        cout<<"+------";
        curr=curr->next;
    }
    cout<<"+"<<endl;
}
//============================================================
void DoublyLinkedList::reverseList()
{
    DoublyLinkedList Temp;
    while(!empty()){
        string s = front();
        Temp.addFront(s);
        removeFront();
    }
    while(!Temp.empty()){
        string s = Temp.front();
        addBack(s);
        Temp.removeFront();
    }
}
//============================================================
bool DoublyLinkedList::isPalindrome()
{
    bool state = true;
    DoublyLinkedList Temp1, Temp2;
    while(!empty()) {
        string s = front();
        Temp1.addBack(s);
        Temp2.addFront(s);
        removeFront();
    }
    Node* cursor1 = Temp1.head;
    Node* cursor2 = Temp2.head;
    
    for (int i = 0; state == true && cursor1 -> next != Temp1.tail; i++) {
        if (cursor1 -> next -> elem != cursor2 -> next -> elem) {
            state = false;
        }
        cursor1 = cursor1 -> next;
        cursor2 = cursor2 -> next;
    }
    while(!Temp1.empty()){
        string s = Temp1.front();
        addBack(s);
        Temp1.removeFront();
    }
    return state;
}
