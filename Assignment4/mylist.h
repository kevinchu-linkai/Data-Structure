#include<iostream>
#include<algorithm>
using namespace std;
//mylist class and methods declaration
template <typename T>
class Node
{
    private:
        T elem; //data element
        Node* next; //Link (pointer) to the next Node
        Node* prev; //Link (pointer) to the previous Node
        template <typename T2> friend class MyList;
        
    public:
        Node(): elem(),next(NULL), prev(NULL)
        {}
        Node(T elem) : elem(elem),next(NULL), prev(NULL)
        {}
        T getElem(){
            return elem;
        }
        Node* getNext(){
            return next;
        }
};
//==============================================================
template <typename T>
class MyList
{
    private:
        Node<T>* head;     // pointer to the head of List
        Node<T>* tail;     // pointer to the tail of List
        int size;
    public:
        MyList(); // empty list constructor
        ~MyList(); // destructor to clean up all nodes
        bool empty() const; // is list empty?
        const T& front() const; // get the value (element) from front Node<T> of list
        T& back() const;  // get the value (element) from last Node<T> of the List
        void addBefore(Node<T> *ptr, const T& elem);     //add a new node before ptr
        void addFront(const T& elem); // add a new node to the front of list
        void addBack(const T & elem); //add a new node to the back of the list
        void addAfter(Node<T> *ptr, const T& elem);
        void removeFront(); // remove front node from list
        void removeBack();  // remove last node from list
        int getSize(){
            return size;
        }
        void reverseList();    // reverse the list
        bool isPalindrome(); //check if the List is Palindrome or not
        void display() const;    // display all element of the list
        //Iterator
        class iterator;   //Forwarding declarion of iterator class
        void remove(iterator other);
        iterator begin()
        {
            return iterator(head->next);
        }
        iterator end()
        {
            return iterator(tail);
        }
        //class iterator with the mylist class
        class iterator
        {
        private:
            Node<T>* ptr;
        public:
            using value_type = T;
            using pointer = T*;
            using reference = T&;
            using iterator_category = bidirectional_iterator_tag;
            using difference_type = ptrdiff_t;
        public:
            iterator(Node<T>* node){
                this->ptr = node;
            }
            T& operator*(){
                return ptr->elem;
            }
            iterator& operator++(){
                ptr = ptr->next;
                return *this;
            }
            iterator& operator--(){
                ptr = ptr->prev;
                return *this;
            }
            bool operator==(const iterator& other) const{
                return ptr == other.ptr;
            }
            bool operator!=(const iterator& other) const{
                return ptr != other.ptr;
            }
            Node<T>* get(){
                return ptr;
            }
        };
};
