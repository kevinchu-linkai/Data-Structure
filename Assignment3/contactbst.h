#ifndef ContactBST_H
#define ContactBST_H

#include <iostream>
#include <fstream>
#include <string>
#include "contact.h"
#include "myvector.h"  //create this header file where you define the vector class

using namespace std;
//template class MyVector<Contact>;

class Node
{
    private:
        string key;
        MyVector<Contact>* contactVector;
        Node* left;
        Node* right;
    public:
        Node(string key, MyVector<Contact>* contactVector);
        ~Node();
        string getKey() { return this->key;}
        MyVector<Contact>* getData() { return this->contactVector;}
        friend class ContactBST;
};

//=============================================================================
class ContactBST
{
    private:
        Node* root;
    public:
        ContactBST();                                    //constructor
        ~ContactBST();                                    //destructor
        Node* getRoot();                        //returns the root of the Tree
        Node* add(Node* ptr,string key, Contact* data);        //add key into tree/subtree with root ptr
        Node* update(Node* ptr, string key); //Edit the node with key
        Node* del(Node* ptr,string key);        //Delete a node with key from the tree/subtree with root
        Node* search(Node* ptr,string key);    //Find and returns the node with key
        Node* findMin(Node *ptr);
        bool markFav(Node* ptr, string key);  //Mark a contact as favorite
        bool unmarkFav(Node* ptr, string key);  //Unmark a contact as favorite
        void printASC(Node* ptr);            //Print the data at nodes in an ascending order
        void printDES(Node* ptr);            //Print the data at nodes in a descending order
        void printFav(Node* ptr);           //Print the favorite data at nodes in an ascending order
        int importCSV(Node* ptr, string path); //Load all the contacts from the CSV file to the BST
        int exportCSV(Node* ptr, string path); //Export all the contacts from the BST to a CSV file in an ascending order

    public:    //helper methods
        void insert_helper(string key, Contact* data);                //Helper method for insert method
        void remove_helper(string key);                                //Helper method for remove method
        void export_helper(Node* ptr, MyVector<Contact>* temp);
    private:
        void printTreeHelper(string* A, bool* B, Node* ptr, int n); //Helper method for PrintTree()
};

#endif
