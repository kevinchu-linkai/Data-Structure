//============================================================================
// Name         : lab8.cpp
// Author       : Khalid Mengal
// Version      : 1.0
// Date Created : 04-11-2019
// Date Modified: 29-03-2020
// Description  : BST Tree implementation in C++
// Copyright © 2020 Khalid Mengal. All rights reserved.
//============================================================================
#include<iostream>
#include<sstream>
#include<cstdlib>

using namespace std;

class Node
{
   private:
       int key;
       Node* left;
       Node* right;
   public:
       Node(int key);
       ~Node();
       int getKey() { return this->key;}
       friend class BST;
};

Node::Node(int key)
{
   this->key = key;
   this->left = nullptr;
   this->right = nullptr;
}
Node::~Node()
{
   cout<<"deleted.."<<this->key<<endl;
}
//=============================================================================
class BST
{
   private:
       Node *root;
   public:
       BST();                                    //constructor
       ~BST();                                    //destructor
       Node* getRoot();                        //returns the root of the Tree
       int height(Node *ptr);                    //Find the height of a tree/subtree with root ptr
       Node* findMin(Node *ptr);                //Find and return the Node with minimum key value from a tree/subtree with root ptr
       Node* findMax(Node *ptr);                //Find and return the Node with Max key value from a tree/subtree with root ptr
       Node* findKey(Node *ptr,int key);        //Find and returns the node with key
       Node* insert(Node* ptr,int key);        //Insert key into tree/subtree with root ptr
       Node* remove(Node *ptr,int key);        //Remove a node with key from the tree/subtree with root
       void printInorder(Node* ptr);            //Traverse (inroder) and print the key of a tree/subtree with root ptr
       void printTree();                        //Print 2D Tree
   public:    //helper methods
       void insert_helper(int key);                //Helper method for insert method
       void remove_helper(int key);                //Helper method for remove method
   private:
       void printTreeHelper(int *A, bool *B, Node *ptr, int n); //Helper method for PrintTree()
};

//==========================================================
void listCommands()
{
   cout<<"----------------------------------"<<endl;
   cout<<"display            :Display the BST Tree"<<endl
       <<"height             :Find the hieght of the Tree"<<endl
       <<"min                :Find the node with minimum key in BST"<<endl
       <<"max                :Find the node with maximum key in BST"<<endl
       <<"find <key>         :Find a node with a given key value in BST"<<endl
       <<"insert <key>       :Insert a new node in BST"<<endl
       <<"remove <key>       :Remove the node from BST "<<endl
       <<"inorder            :Print the BST in Inorder"<<endl
       <<"help               :Display the available commands"<<endl
       <<"exit               :Exit the program"<<endl;
}
//==========================================================
void demo( BST &myBST)
{
   myBST.insert_helper(10);
   myBST.insert_helper(5);
   myBST.insert_helper(4);
   myBST.insert_helper(7);
   myBST.insert_helper(13);
   myBST.insert_helper(15);
   myBST.insert_helper(12);
   myBST.insert_helper(14);
   myBST.printTree();
}
//==========================================================
int main(void)
{
   BST myBST;
   listCommands();
   string user_input;
   string command;
   string key;

   while(true)
   {
       cout<<">";
       getline(cin,user_input);

       // parse userinput into command and parameter(s)
       stringstream sstr(user_input);
       getline(sstr,command,' ');
       getline(sstr,key);
       
       Node* root = myBST.getRoot();    //get the root of the tree
       cout<<"----------------------------------"<<endl;
       if( user_input =="display")    myBST.printTree();
       else if( command =="height")    cout<<"Height = "<<myBST.height(root)<<endl;
       else if( command =="min")
       {
           Node* min = myBST.findMin(root);
           cout<<"Min. key = "<<((min!=nullptr)? to_string(min->getKey()):" does not exist")<<endl;
       }
       else if( command =="max")
       {
           Node* max = myBST.findMax(root);
           cout<<"Max. key = "<<((max!=nullptr)? to_string(max->getKey()):" does not exist")<<endl;
       }
       else if( command =="find")    cout<<key<<(myBST.findKey(root,stoi(key))==nullptr ? " not found":" found")<<endl;
       else if( command =="insert" or command=="i")    { myBST.insert_helper(stoi(key)); myBST.printTree();}
       else if( command =="remove" or command=="r")    { myBST.remove_helper(stoi(key)); myBST.printTree();}
       else if( command =="inorder")    {myBST.printInorder(root); cout<<endl;}
       else if( command =="exit") break;
       else if( command == "demo") demo(myBST);
       else if( command == "help") listCommands();
       else if( command == "exit") break;
       else cout<<"Invalid command !!!"<<endl;

   }

   return 0;
}
//=====================================================================

BST::BST()
{
   this->root=nullptr;
}
BST::~BST()
{
   //Keep removing the root of the tree untill it becomes empty
   while(root)
       root=remove(root,root->key);
}
//Helper method for insert method
void BST::insert_helper(int key)
{
   root = insert(root,key);
}
//=================================================
//Helper method for remove
void BST::remove_helper(int key)
{
   root = remove(root, key);
}
//==================================================================
//  This method prints a Binary Tree in 2D format
//  Created by Saurabh Ray
//  Copyright © 2020 Saurabh Ray. All rights reserved.

void BST::printTree(){
  char *space = (char *) "  ";
  int d = height(this->getRoot());
  int n = (1<<(d+1))- 1; // n = 2^(d+1)-1

  int *A = new int[n];
  bool *B = new bool[n];
  for(int i=0; i<n; ++i)
        B[i]=false;

  printTreeHelper(A,B,root,n);

  cout<<"\nTree:"<<endl;
  for(int t=(n+1)/2; t>0; t=t/2){
       for(int j=0; j<n; j++){
           if( ((j+1)%t == 0) && B[j]){
               cout<<A[j];
               B[j] = false;
           }
           else{
               cout<<space;
           }
       }
       cout<<endl;
  }
  cout<<endl;
  delete [] A;
  delete [] B;
}

void BST::printTreeHelper(int *A,bool *B, Node *ptr, int n){
   if(ptr!=nullptr){
       int mid = (n-1)/2;
       A[mid] = ptr->key;
       B[mid] = true;
       printTreeHelper(A,B,ptr->left,mid);
       printTreeHelper(A+(mid+1),B+(mid+1), ptr->right, mid);
   }
}

Node* BST::getRoot(){return root;}                        //returns the root of the Tree
int BST::height(Node *ptr){
    if(ptr == nullptr){
        return 0;
    }
    int L = height(ptr->left);
    int R = height(ptr->right);
    if(L > R){
        return L + 1;
    }
    return R + 1;
}                    //Find the height of a tree/subtree with root ptr
Node* BST::findMin(Node *ptr){
    if(ptr->left == nullptr){
        return ptr;
    }
    return findMin(ptr->left);
}                //Find and return the Node with minimum key value from a tree/subtree with root ptr
Node* BST::findMax(Node *ptr){
    if(ptr->right == nullptr){
        return ptr;
    }
    return findMin(ptr->right);
}                //Find and return the Node with Max key value from a tree/subtree with root ptr
Node* BST::findKey(Node *ptr,int key){
    if(ptr != nullptr){
        if(ptr->key > key){
            return findKey(ptr->left, key);
        }
        else if(ptr->key < key){
            return findKey(ptr->right, key);
        }
        if(ptr->key == key){
            return ptr;
        }
    }
    return nullptr;
}        //Find and returns the node with key
Node* BST::insert(Node* ptr,int key){
    if(ptr == nullptr) {
        return new Node(key);
    }
    if(key < ptr->key){
        ptr->left = insert(ptr->left, key);
    }
    else if(key > ptr->key){
        ptr->right = insert(ptr->right, key);
    }
    else{
        ptr = ptr;
        cout << "The key exists!" << endl;
    }
    return ptr;
}        //Insert key into tree/subtree with root ptr
Node* BST::remove(Node *ptr,int key){
    if(ptr == nullptr){
        ptr = ptr;
        cout << "The key does not exist!" << endl;
    }
    if(key < ptr->key){
        ptr->left = remove(ptr->left, key);
    }
    else if(key > ptr->key){
        ptr->right = remove(ptr->right, key);
    }
    else{
        if (ptr->left == nullptr && ptr->right == nullptr){
            ptr = nullptr;
        }
        else if (ptr->left == nullptr){
            Node* temp = ptr->right;
            delete ptr;
            return temp;
        }
        else if (ptr->right == nullptr){
            Node* temp = ptr->left;
            delete ptr;
            return temp;
        }
        else{
            Node* temp = findMin(ptr->right);
            ptr->key = temp->key;
            ptr->right = remove(ptr->right, temp->key);
        }
    }
    return ptr;//Remove a node with key from the tree/subtree with root
}
void BST::printInorder(Node* ptr){
    if(ptr == nullptr){
        return;
    }
    printInorder(ptr->left);
    cout << ptr->key << " ";
    printInorder(ptr->right);
}            //Traverse (inroder) and print the key of a tree/subtree with root ptr
