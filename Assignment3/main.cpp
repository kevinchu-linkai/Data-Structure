
//=================================================================================
// Name         : DS Assignment#3
// Author       :
// Version      : 1.0
// Date Created : 03-20-2022
// Date Modified:
// Description  : Starter Code for Contact Management System using BST Tree in C++
// Copyright © 2022 Khalid Mengal and Mai Oudah. All rights reserved.
//=================================================================================
#include<iostream>
#include<cstdlib>
#include<sstream>
#include "contact.h"
#include "contactbst.h"

//==========================================================
void listCommands()
{
    cout<<"----------------------------------"<<endl;
    cout<<"import <path>      :Import contacts from a CSV file"<<endl
        <<"export <path>      :Export contacts to a CSV file"<<endl
        <<"add                :Add a new contact"<<endl
        <<"edit <key>         :Update a contact's details"<<endl
        <<"del <key>          :Delete a contact"<<endl
        <<"searchFor <key>    :Search for a contact"<<endl
        <<"markfv <key>       :Mark as favourite"<<endl
        <<"umarkfv <key>      :Unmark as favourite"<<endl
        <<"printASC           :Print contacts in ascending order"<<endl
        <<"printDES           :Print contacts in descending order"<<endl
        <<"printfv            :Print all favourite contacts"<<endl
        <<"help               :Display the available commands"<<endl
        <<"exit               :Exit the program"<<endl;
}
//==========================================================

// to be completed with all the necessary method definitions

//==========================================================
int main(void)
{
    ContactBST myContactBST;
    string user_input;
    string command;
    string key;
    while(true)
    {
        listCommands();
        cout<<">";
        getline(cin,user_input);
        // parse userinput into command and parameter(s)
        stringstream sstr(user_input);
        getline(sstr,command,' ');
        getline(sstr,key);
        
        Node* root = myContactBST.getRoot();    //get the root of the tree
        cout<<"----------------------------------"<<endl;
        if( command =="search"){
            myContactBST.search(root,key);
            fflush(stdin);
        }
        else if( command =="add" or command =="a"){
            fflush(stdin);
            string input;
            Contact* data = new Contact;
            cout << "Please enter the details of the contact:" << endl
            << "First name: "; cin >> input; data->fname = input;
            cout << "Last name: "; cin >> input; data->lname = input;
            cout << "Email: "; cin >> input; data->email = input;
            cout << "Phone#: "; cin >> input; data->primaryPhone = input;
            cout << "City: "; cin >> input; data->city = input;
            cout << "Country: "; cin >> input; data->country = input;
            char ans;
            bool fav = false;
            while (fav == false) {
                cout << "Do you want to add the contact in your favorite? [Y/N]: ";
                cin >> ans;
                if (ans == 'N' || ans == 'n') {
                    data->isFav = false;
                    fav = true;
                }
                else if(ans == 'Y' || ans == 'y'){
                    data->isFav = true;
                    fav = true;
                }
                else{
                    cout << "The answer should be only Y/N" << endl;
                }
            }
            key = data->fname + " " + data->lname;
            myContactBST.insert_helper(key,data);
            cout << "Contact " << key << " has been added successfully!" << endl;
            fflush(stdin);
        }
        else if( command =="del"){
            myContactBST.remove_helper(key);
        }
        else if( command =="edit"){
            myContactBST.update(root,key);
        }
        else if( command =="printASC"){
            myContactBST.printASC(root);
        }
         else if( command =="printDES"){
            myContactBST.printDES(root);
        }
         else if( command =="printfv"){
            myContactBST.printFav(root);
        }
        else if( command =="markfv"){
            myContactBST.markFav(root,key);
        }
        else if( command =="unmarkfv"){
            myContactBST.unmarkFav(root,key);
        }
        else if( command =="import"){
            int state = 0;
            state = myContactBST.importCSV(root,key);
            if (state == -1)
            {
                cout << "Fail to import the file!" << endl;
            }
            else{
                cout << state << " contact imported!" << endl;
            }
        }
        else if( command =="export"){
            int state = 0;
            state = myContactBST.exportCSV(root,key);
            if (state == -1)
            {
                cout << "Fail to export the file!" << endl;
            }
            else{
                cout << state << " contact exported!" << endl;
            }
        }

        else if( command =="exit") break;
        else if( command == "help") listCommands();
        else {
            cout<<"Invalid command !!!"<<endl;
        }
        fflush(stdin);
    }

    return 0;
}
