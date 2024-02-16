//
//  contactbst.cpp
//  ass3
//
//  Created by 朱麟凱 on 2022/4/5.
//

#include "contactbst.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Node::Node(string key, MyVector<Contact>* contactVector)
{
   this->key = key;
   this->contactVector = contactVector;
   this->left = nullptr;
   this->right = nullptr;
}
Node::~Node()
{
   cout<<"deleted.."<<this->key<<endl;
}

ContactBST::ContactBST(){
    root = nullptr;
};                                    //constructor
ContactBST::~ContactBST(){
    while(root)
           root = del(root,root->key);
};                                    //destructor
Node* ContactBST::getRoot(){return root;};                        //returns the root of the Tree
Node* ContactBST::findMin(Node *ptr){
    if(ptr->left == nullptr){
        return ptr;
    }
    return findMin(ptr->left);
};
Node* ContactBST::add(Node* ptr,string key, Contact* data){
    
    if(ptr == nullptr) {
        MyVector<Contact>* contactVector = new MyVector<Contact>;
        contactVector->push_back(*data);
        ptr = new Node(key, contactVector);
        return ptr;
    }
    if(key < ptr->key){
        ptr->left = add(ptr->left, key, data);
    }
    else if(key > ptr->key){
        ptr->right = add(ptr->right, key, data);
    }
    else{
        ptr = ptr;
        ptr->contactVector->push_back(*data);
    }
    return ptr;
};    //add key into tree/subtree with root ptr

Node* ContactBST::update(Node* ptr, string key){
    Node* temp = search(ptr, key);
    string input;
    for (int i = 0; i < temp->contactVector->size(); i++) {
     cout << i+1 << ". " << temp->key << ", "
     << temp->contactVector->at(i).email << ", "
     << temp->contactVector->at(i).primaryPhone << ", "
     << temp->contactVector->at(i).city << ", "
     << temp->contactVector->at(i).country << endl << endl;
    }
    cout << "Which contact you want to update?" << endl;
    cin >> input; cout << endl;
    int ans = stoi(input);
	Contact now = temp->contactVector->at(ans-1);
	while(true){
		cout << "What do you want to update? 1)First name 2)Last name 3) Email 4)Phone# 5)City 6)Country: ";
		cin >> input;
		if(input == "1"){
			cout << "Please enter new first name:";
			cin >> input;
			now.fname = input;
		}
		else if(input == "2"){
			cout << "Please enter new last name:";
			cin >> input;
			now.lname = input;
		}
		else if(input == "3"){
			cout << "Please enter new email:";
			cin >> input;
			now.email = input;
		}
		else if(input == "4"){
			cout << "Please enter new phone#:";
			cin >> input;
			now.primaryPhone = input;
		}
		else if(input== "5"){
			cout << "Please enter new city:";
			cin >> input;
			now.city = input;
		}
		else if(input == "6"){
			cout << "Please enter new country:";
			cin >> input;
			now.country = input;
		}
		else{cout << "Invalid input!" << endl;}
        char in;
        bool state = false;
        while (state == false){
            cout << "Do you want to change more field? [Y/N]: "; cin >> in;
	    	if (in == 'N' || in == 'n') {
                state = true;
            }
            else if(in == 'Y' || in == 'y'){
                state = true;
                cout << endl;
            }
            else{
                cout << "The answer should be only Y/N" << endl;
            }
        }   
        if (in == 'N' || in == 'n'){
            break;
        }
        
	}
	if(now.fname+" "+now.lname != key)
	{
		insert_helper(now.fname+" "+now.lname,&now);
		if(temp->contactVector->size() > 1){
			temp->contactVector->erase(ans-1);
		}
		else{
			remove_helper(key);
		}
	}
	fflush(stdin);
	return temp;
}; //Edit the node with key

Node* ContactBST::del(Node* ptr,string key){
    if(ptr == nullptr){
        cout << "The contact does not exist!" << endl;
    }
    if(key < ptr->key){
        ptr->left = del(ptr->left, key);
    }
    else if(key > ptr->key){
        ptr->right = del(ptr->right, key);
    }
    else{
        Node* temp = ptr;
        string input;
        if (ptr->contactVector->size()!=1) {
            for (int i = 0; i < temp->contactVector->size(); i++) {
                cout << i+1 << ". " << temp->key << ", "
                << temp->contactVector->at(i).email << ", "
                << temp->contactVector->at(i).primaryPhone << ", "
                << temp->contactVector->at(i).city << ", "
                << temp->contactVector->at(i).country << endl << endl;
            }
            cout << "Which contact you want to delete?" << endl;
            cin >> input; cout << endl;
            int ans = stoi(input);
            temp->contactVector->erase(ans-1);
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
                ptr->right = del(ptr->right, temp->key);
            }
        }
    }
    return ptr;//Remove a node with key from the tree/subtree with root
};        //Delete a node with key from the tree/subtree with root

Node* ContactBST::search(Node* ptr,string key){
    if(ptr != nullptr){
        if(ptr->key > key){
            return search(ptr->left, key);
        }
        else if(ptr->key < key){
            return search(ptr->right, key);
        }
        if(ptr->key == key){
            cout << ptr->contactVector->size() << "record(s) found: " << endl;
            for (int i = 0; i < ptr->contactVector->size(); i++)
            {
                cout << i+1 << ". " << "Name: " << ptr->key << endl
                <<  "Email: " << ptr->contactVector->at(i).email << endl
                <<  "Phone#: " << ptr->contactVector->at(i).primaryPhone << endl
                <<  "City: " << ptr->contactVector->at(i).city << endl
                <<  "Country: " << ptr->contactVector->at(i).country << endl << endl;
            }
            
            return ptr;
        }
    }
    return nullptr;
};  //Find and returns the node with key

bool ContactBST::markFav(Node* ptr, string key){
    Node* temp = search(ptr, key);
    string input;
    for (int i = 0; i < temp->contactVector->size(); i++) {
        cout << i+1 << ". " << temp->key << ", "
        << temp->contactVector->at(i).email << ", "
        << temp->contactVector->at(i).primaryPhone << ", "
        << temp->contactVector->at(i).city << ", "
        << temp->contactVector->at(i).country << endl << endl;
    }
    cout << "Which contact you want to mark as a favorite?" << endl;
    cin >> input; cout << endl;
    int ans = stoi(input);
    temp->contactVector->at(ans-1).isFav = true;
    return true;
};  //Mark a contact as favorite

bool ContactBST::unmarkFav(Node* ptr, string key){
    Node* temp = search(ptr, key);
    string input;
    for (int i = 0; i < temp->contactVector->size(); i++) {
        cout << key << ", "
        << temp->contactVector->at(i).email << ", "
        << temp->contactVector->at(i).primaryPhone << ", "
        << temp->contactVector->at(i).city << ", "
        << temp->contactVector->at(i).country << endl << endl;
    }
    cout << "Which contact you want to unmark as a favorite?" << endl;
    cin >> input; cout << endl;
    int ans = stoi(input);
    temp->contactVector->at(ans-1).isFav = false;
    return true;
};  //Unmark a contact as favorite

void ContactBST::printASC(Node* ptr){
    if(ptr == nullptr){
       return;
    }
    printASC(ptr->left);
    for (int i = 0; i < ptr->contactVector->size(); i++) {
        cout << ptr->key << ", "
        << ptr->contactVector->at(i).email << ", "
        << ptr->contactVector->at(i).primaryPhone << ", "
        << ptr->contactVector->at(i).city << ", "
        << ptr->contactVector->at(i).country << endl << endl;
    }
    printASC(ptr->right);
};            //Print the data at nodes in an ascending order

void ContactBST::printDES(Node* ptr){
    if(ptr == nullptr){
       return;
    }
    printDES(ptr->right);
    for (int i = 0; i < ptr->contactVector->size(); i++) {
        cout << ptr->key << ", "
        << ptr->contactVector->at(i).email << ", "
        << ptr->contactVector->at(i).primaryPhone << ", "
        << ptr->contactVector->at(i).city << ", "
        << ptr->contactVector->at(i).country << endl << endl;
    }
    printDES(ptr->left);
}; //Print the data at nodes in a descending order

void ContactBST::printFav(Node* ptr){
    if(ptr == nullptr){
       return;
    }
    printFav(ptr->left);
    for (int i = 0; i < ptr->contactVector->size(); i++) {
        if (ptr->contactVector->at(i).isFav == true)
        {
            cout << ptr->key << ", "
            << ptr->contactVector->at(i).email << ", "
            << ptr->contactVector->at(i).primaryPhone << ", "
            << ptr->contactVector->at(i).city << ", "
            << ptr->contactVector->at(i).country << endl << endl;
        }
    }
    printFav(ptr->right);
};           //Print the favorite data at nodes in an ascending order

int ContactBST::importCSV(Node* ptr, string path){
    ifstream fin(path);
    string line;
	bool is_fav;
    int cnt = 0;
	if(!fin.good()){
        return -1;
    }
    while(getline(fin,line)){
        stringstream sstr(line);
        Contact* data = new Contact;
        int i = 0;
		while(i<7){
			string elem;
			getline(sstr, elem,',');
            if(i == 0){
                data->fname = elem;
		    }
		    else if(i == 1){
                data->lname = elem;
		    }
		    else if(i == 2){
                data->email = elem;
		    }
		    else if(i == 3){
                data->primaryPhone = elem;
		    }
		    else if(i== 4){
                data->city = elem;
		    }
		    else if(i == 5){
                data->country = elem;
		    }
            else{
                if (elem == "1"){
                 is_fav = true;
                }
                else{
                 is_fav = false;
                }
            }
            i++;
		}
        Contact* temp = data;
		insert_helper(temp->fname+" "+temp->lname, temp);
        cnt++;
    }
    fin.close();
    return cnt;
}; //Load all the contacts from the CSV file to the BST

void ContactBST::export_helper(Node* ptr, MyVector<Contact>* temp){
    if(ptr == nullptr){
       return;
    }
    export_helper(ptr->left, temp);
    for (int i = 0; i < ptr->contactVector->size(); i++) {
        temp->push_back(ptr->contactVector->at(i));
    }
    export_helper(ptr->right, temp);
}
//helper to export file

int ContactBST::exportCSV(Node* ptr, string path){
    ofstream fout(path);
    MyVector<Contact>* temp = new MyVector<Contact>(30);
    if (!fout.good())
	{
		return -1;
	}
    export_helper(root, temp);
    for (int i = 0; i < temp->size(); i++)
    {
       fout << temp->at(i).fname << ","
        << temp->at(i).lname << ","
        << temp->at(i).email << ","
        << temp->at(i).primaryPhone << ","
        << temp->at(i).city << ","
        << temp->at(i).country << ","
        << temp->at(i).isFav << endl;
    }
    fout.close();
    int cnt = temp->size();
    delete temp;
    return cnt;
}; //Export all the contacts from the BST to a CSV file in an ascending order
void ContactBST::insert_helper(string key, Contact* data){
    root = add(root, key, data);
};                //Helper method for insert method
void ContactBST::remove_helper(string key){
    root = del(root, key);
};                                //Helper method for remove method
