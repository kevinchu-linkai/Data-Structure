#ifndef _HEADER_H   //include headers
#define _HEADER_H

#include<iostream>
#include<string>
#include<sstream>
#include<iomanip>
#include<exception>
int STATE = 0; //to control login state
using namespace std;

//the template of nodes
template <typename T> class Node
{
    private:

    public:
        T elem; //data element (type string in this case)
        Node* next; //Link (pointer) to the next Node
        Node* prev; //Link (pointer) to the previous Node
        template <typename U> friend class DoublyLinkedList;
        template <typename V> friend V Login();
        friend void viewClassesWithVacancies();
        friend class FitnessClass;
        friend class Admin;
        friend class Member;
        Node(): elem(), next(NULL), prev(NULL)
        {}
        Node(T elem) : elem(elem), next(NULL), prev(NULL)
        {}
};
//==============================================================
//the template of linked list
template <typename T> class DoublyLinkedList
{
    private:
        
    public:
        Node<T>* head;     // pointer to the head of List
        Node<T>* tail;     // pointer to the tail of List
        DoublyLinkedList (); // empty list constructor
        ~DoublyLinkedList (); // destructor to clean up all nodes
        bool empty() const; // is list empty?
        const T& front() const; // get the value (element) from front Node of list
        T& back();  // get the value (element) from last Node of the List
        void addBefore(Node<T> *ptr, const T& elem);     //add a new node before ptr
        void addFront(const T& elem); // add a new node to the front of list
        void addBack(const T& elem); //add a new node to the back of the list
        void removeFront(); // remove front node from list
        void removeBack();  // remove last node from list
        void remove(Node<T>* v);
        friend void viewClassesWithVacancies();
        friend class FitnessClass;
        friend class Admin;
        friend class Member;
        template <typename U> friend U Login();
        //void display() const;    // display all element of the list
};
//============================================================
template <typename T> DoublyLinkedList<T>::DoublyLinkedList ()
{
    head = new Node<T>;
    tail = new Node<T>;
    head -> next = tail;
    tail -> prev = head;
}
//============================================================
template <typename T> DoublyLinkedList<T>::~DoublyLinkedList () // destructor to clean up all nodes
{
    while(!empty()){
        removeFront();
    }
}
//============================================================
template <typename T> bool DoublyLinkedList<T>::empty() const // is list empty?
{
    return head -> next == tail;
}
//============================================================
template <typename T> const T& DoublyLinkedList<T>::front() const // get front element
{
    return head -> next -> elem;
}
//============================================================
template <typename T> T& DoublyLinkedList<T>::back() // get front element
{
    return tail -> prev -> elem;
}
//============================================================
template <typename T> void DoublyLinkedList<T>::addBefore(Node<T> *ptr, const T& elem)
{
    Node<T>* u = new Node<T>;
    u -> elem = elem;
    u -> next = ptr;
    u -> prev = ptr -> prev;
    ptr -> prev -> next = u;
    ptr -> prev = u;
}
//============================================================
template <typename T> void DoublyLinkedList<T>::addFront(const T& elem) // add to front of list
{
    addBefore(head -> next, elem);
}
//============================================================
template <typename T> void DoublyLinkedList<T>::addBack(const T& elem) // add to Back of the list
{
    addBefore(tail -> prev -> next, elem);
}
//============================================================
template <typename T> void DoublyLinkedList<T>::removeFront() // remove front item from list
{
    Node<T>* v = head -> next;
    head -> next = v -> next;
    v -> next -> prev = v -> prev;
    delete v;
}
//============================================================
template <typename T> void DoublyLinkedList<T>::removeBack() // remove last item from list
{
    Node<T>* v = tail -> prev;
    tail -> prev = v -> prev;
    v -> prev -> next = v -> next;
    delete v;
}
//============================================================
template <typename T> void DoublyLinkedList<T>::remove(Node<T>* v) {
    Node<T>* u = v -> prev;
    Node<T>* w = v -> next;
    u -> next = w;
    w -> prev = u;
    delete v;
}
//========================================================================================================
//=========================display function to debug============================================
//========================================================================================================
//template <typename T> void DoublyLinkedList<T>::display() const
//{
//    Node<T> *curr=head;
//    while(curr!=NULL)
//    {
//        cout<<"+------";
//        curr=curr->next;
//    }
//    cout<<"+"<<endl<<"|";
//    curr=head;
//    while(curr!=NULL)
//    {
//        if (curr == head)        cout<<" Head |";
//        else if(curr == tail)    cout<<" Tail |";
//        else                     cout<<setw(5)<< curr -> elem.ID <<" |";
//
//        curr=curr->next;
//    }
//    curr=head;
//    cout<<endl;
//    while(curr!=NULL)
//    {
//        cout<<"+------";
//        curr=curr->next;
//    }
//    cout<<"+"<<endl;
//}

//set a class of linked stack
class LinkedStack{
public :
    LinkedStack();
    int size() const ;
    bool empty() const ;
    const int& top() const;
    void push(const int& m);
    void pop();
private:
    DoublyLinkedList<int> S; // linked list
    int n; // number of elements in stack
};
//============================================================
LinkedStack::LinkedStack(): S(), n(0) { } // constructor, initializes S and sets n=0
int LinkedStack::size() const {return n; }
bool LinkedStack::empty() const { return n == 0;}
const int& LinkedStack::top() const { // return top of stack
    if (empty())
    {cout << "empty stack!" << endl;}
    return S.front();
}
void LinkedStack::push(const int& e) // push “e” onto stack
{
    ++n;
    S.addFront(e);
}
void LinkedStack::pop() // pop the stack
{
    if (!empty()){--n;}
    S.removeFront();
}
//============================================================
//member class declarition
class Member{
    private://set the private variables of member
        
    public://set the constructor, public methods and friend elements
        int ID;
        string FirstName;
        string LastName;
        string UserName;
        string Password;
        LinkedStack BookingList;
        Member();
        friend class Admin;
        friend class FitnessClass;
        template <typename U> friend class DoublyLinkedList;
        //template <typename U> friend U Login(string, const DoublyLinkedList<U>);
        friend Member memberlogin(string);
        void viewBookingList();
        void listCommands();
        void bookAClass(int i);
        void cancelBooking(int i);
        int getID();
};

//set a function to get member ID
int Member::getID(){
    return ID;
}

//fitnessclasses class declarition
class FitnessClass{
    private://set the private variables of fitness class
        
    public://set the constructor, public methods and friend elements
        int ID;
        string ClassName;
        string ClassDate;
        string ClassTime;
        int MaxiumCapacity;
        int RoomNumber;
        LinkedStack ListOfMember;
        FitnessClass();
        template <typename U> friend class DoublyLinkedList;
        friend class Admin;
        friend class Member;
        friend int searchIndex_class(int,DoublyLinkedList<FitnessClass>);
        friend void viewClassesWithVacancies();
};

//admin class declarition
class Admin{
    private://set the private variables of admin
        
    public://set the constructor, public methods and friend elements
        int ID;
        string FirstName;
        string LastName;
        string UserName;
        string Password;
        Admin();
        friend class Member;
        friend class FitnessClass;
        template <typename U> friend class DoublyLinkedList;
        //template <typename V> friend V Login(string, const DoublyLinkedList<V>);
        friend Admin adminlogin(string U);
        void changeClassCapacity();
        void listCommands();
        void splitClass();
        void viewMemberList();
        void registerMember();
        void registerAdmin();
        void addFitnessClass();
        void deleteFitnessClass();
        void updateClassDetails();
};

//constructor for admin
Admin::Admin(){
    ID = 0;
    FirstName = "";
    LastName = "";
    UserName = "";
    Password = "";
}
//constructor for member
Member::Member(){
    ID = 0;
    FirstName = "";
    LastName = "";
    UserName = "";
    Password = "";
}
//constructor for fitness class
FitnessClass::FitnessClass(){
    ClassName = "";
    ClassDate = "";
    ClassTime = "";
}

//set a function listing out commands for admin
void Admin::listCommands()
{
    cout<<"List of available Commands for Admins:" << endl
        <<"1) Register a new admin" << endl
        <<"2) Register a new member" << endl
        <<"3) Add a new fitness class" << endl
        <<"4) Delete a fitness class" << endl
        <<"5) Update the details of a fitness class" << endl
        <<"6) Update the capacity of a fitness class" << endl
        <<"7) Split a fitness class" << endl
        <<"8) Display the classes with vacancies" << endl
        <<"9) View mamber list" << endl
        <<"10) Log out" << endl
        <<"11) Quit the program" << endl << endl
        <<"Enter the number of the required action: [1-11] "<< endl;
}

//set a function listing out commands for member
void Member::listCommands()
{
    cout<<"List of available Commands for Members:" << endl
        <<"1) Display the classes with vacancies" << endl
        <<"2) Book a class" << endl
        <<"3) Cancel a class" << endl
        <<"4) View book list" << endl
        <<"5) Log out" << endl
        <<"6) Quit the program" << endl
        <<"Enter the number of the required action: [1-6] " << endl;
}

#endif
