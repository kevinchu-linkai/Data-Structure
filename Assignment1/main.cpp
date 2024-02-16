//============================================================================
// Name         :Assignment1
// Author       :
// Version      : 1.0
// Date Created :
// Date Modified:
// Copyright    : All rights are reserved
// Description  : Singly Linked-List implementation in C++
//============================================================================
#include<iostream>
#include<string>
#include<fstream>
#include <ctype.h>
#include<exception>
#include<sstream>
#include<cstdlib>
using namespace std;

//set the size of arrays
const int SIZE = 100;
//set a class of admins
class Admin{
    private://set the private variables of admin
        int ID;
        string FirstName;
        string LastName;
        string UserName;
        string Password;
    public://set the constructor, public methods and friend elements
        Admin(int i, string F, string L, string U, string P);
        friend class Member;
        friend class FitnessClass;
        int login(string U,Admin *x[]);
        friend int Adminlogin(string U, Admin*[]);
        void listCommands();
        void registerMember();
        void registerAdmin();
        void addFitnessClass();
        void deleteFitnessClass();
        void updateClassDetails();
};

class Member{
    private://set the private variables of member
        int ID;
        string FirstName;
        string LastName;
        string UserName;
        string Password;
    public://set the constructor, public methods and friend elements
        Member(int i, string F, string L, string U, string P);
        friend class Admin;
        friend class FitnessClass;
        friend int Memberlogin(string, Member*[]);
        int getID(int i);
        void listCommands();
        void bookAClass(int i);
        void cancelBooking(int i);
};

class FitnessClass{
    private://set the private variables of fitness class
        int ID;
        string ClassName;
        string ClassDate;
        string ClassTime;
        int MaxiumCapacity;
        int RoomNumber;
        int ListOfMembers[SIZE];
    public://set the constructor, public methods and friend elements
        FitnessClass();
        friend class Admin;
        friend class Member;
        friend int searchIndex_class(int,FitnessClass* []);
        friend void viewClassesWithVacancies();
};

//set a function for checking if the member list is full
int ifFull(int i, int x[]){
    for (int j = 0; j < i; j++) {
        if (x[j] == 0) {
            return j;
        }
    }
    return 101;
}

//set a finction for searching the assigned class by ID
int searchIndex_class(int i, FitnessClass* x[]){
    for (int j = 0; j < SIZE; j++) {
        if (i == x[j] -> ID) {
            return j;
        }
    }
    return 101;
};

//set arrays to store classes pointers
Admin* admins[SIZE];
Member* members[SIZE];
FitnessClass* classes[SIZE];

//set a function for to display all the classes with vacancies
void viewClassesWithVacancies(){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; classes[i] != NULL && j < classes[i] -> MaxiumCapacity; j++) {
            if (classes[i] -> ListOfMembers[j] == 0) {
                cout << "This class is now open" << endl
                << "Class ID: " << classes[i] -> ID << endl
                << "Class Name: " << classes[i] -> ClassName << endl
                << "Class Date: " << classes[i] -> ClassDate << endl
                << "Class Time: " << classes[i] -> ClassTime << endl
                << "Class Room: " << classes[i] -> RoomNumber << endl << endl;
                break;
            }
        }
    }
}

int main(){
    string category;
    string username;
    string password;
    int state;
    int command;
    
    //fill the arrays with pointers pointing to NULL
    for(int i = 0; i < SIZE; i++){
        admins[i] = NULL;
        members[i] = NULL;
        classes[i] = NULL;
    }

    //set up admin1
    Admin admin1(1,"admin","admin","admin1","admin1");
    admins[0] = &admin1;
    
    //start the program and keep it running till quit program
    while(true){
        cout << "Welcome to the fitness management system!" << endl;
        cout << "Please enter the category of your account before login : [ admin / member ]" << endl;
        cin >> category; cout << endl;
        
        //when login as an admin
        if (category == "admin") {
            cout << "Please enter your username: " << endl;
            cin >> username; cout << endl;
            state = Adminlogin(username, admins);
            if (state != 101) {
                admins[state] -> listCommands();
                //user input command
                cin >> command; cout << endl;
                if(command == 1){admins[state] -> registerAdmin();}
                else if(command == 2){admins[state] -> registerMember();}
                else if(command == 3){admins[state] -> addFitnessClass();}
                else if(command == 4){admins[state] -> deleteFitnessClass();}
                else if(command == 5){admins[state] -> updateClassDetails();}
                else if(command == 6){viewClassesWithVacancies();}
                else if(command == 7){cout << "Program ended!" << endl; break;}
                else{cout << "No such command!" << endl;}
            }
        }
        
        //when login as a member
        else if (category == "member"){
            cout << "Please enter your username: " << endl;
            cin >> username; cout << endl;
            state = Memberlogin(username, members);
            if (state != 101) {
                members[state] -> listCommands();
                //user input command
                cin >> command; cout << endl;
                if(command == 1){viewClassesWithVacancies();}
                else if(command == 2){members[state] -> bookAClass(members[state] -> getID(state));}
                else if(command == 3){members[state] -> cancelBooking(members[state] -> getID(state));}
                else if(command == 4){cout << "Program ended!" << endl; break;}
                else{cout << "No such command!" << endl;}
            }
            else{cout << "This member does not exist!" << endl;}
        }
        
        //when wrong input category
        else{
            cout << "No such category! Please enter the category of your account before login : [ admin / member ]" << endl;
        }
    }
    return 0;
}

//constructor for admin
Admin::Admin(int i, string F, string L, string U, string P){
    ID = i;
    FirstName = F;
    LastName = L;
    UserName = U;
    Password = P;
}
//constructor for member
Member::Member(int i, string F, string L, string U, string P){
    ID = i;
    FirstName = F;
    LastName = L;
    UserName = U;
    Password = P;
}
//constructor for fitness class
FitnessClass::FitnessClass(){
    string ClassName = "";
    string ClassDate = "";
    string ClassTime = "";
    for (int i = 0; i < SIZE; i++) {
        ListOfMembers[i] = 0;
    }
}

//set a function for admin login
int Adminlogin(string U, Admin*x[]){
    string P;
    for (int i = 0; i < SIZE; i++) {
        if(U == x[i]-> UserName){
            cout << "Enter your password: " << endl;
            cin >> P; cout << endl;
            if(P == x[i] -> Password){
                cout << "You have login successfully!" << endl;
                return i;
            }
            else{
                cout << "Wrong password!" << endl;
                return 101;
            }
        }
    }
    return 101;
}

//set a function for member login
int Memberlogin(string U, Member*x[]){
    string P;
    for (int i = 0; i < SIZE; i++) {
        if(U == x[i]-> UserName){
            cout << "Enter your password: " << endl;
            cin >> P; cout << endl;
            if(P == x[i] -> Password){
                cout << "You have login successfully!" << endl;
                return i;
            }
            else{
                cout << "Wrong password!" << endl;
                return 101;
            }
        }
    }
    return 101;
}

//set a function for admin to register a new member
void Admin::registerMember(){
    int ID = 0;
    string F;
    string L;
    string U;
    string P;
    for(int i = 0; i < SIZE; i++){
        if (members[i] == NULL) {
            
            members[i] = new Member(ID,F,L,U,P);
            
            members[i] -> ID = rand()%10000+1000;
            
            cout << "Please enter the first name of the member:" << endl;
            cin >> F; cout << endl; members[i] -> FirstName = F;
            
            cout << "Please enter the last name of the member:" << endl;
            cin >> L; cout << endl; members[i] -> LastName = L;
            
            U = members[i] -> FirstName;
            U[0] = U[0] - 'Z' + 'z'; U = U + to_string(members[i] -> ID);
            members[i] -> UserName = U;
            
            P = members[i] -> LastName;
            P[0] = P[0] - 'Z' + 'z'; P = P + to_string(rand()%10000+1000);
            members[i] -> Password = P;
            
            cout << "Your username is: " << members[i] -> UserName << endl
            << "Your password is: " << members[i] -> Password << endl;
            return;
        }
    }
}

//set a function for admin to register a new admin
void Admin::registerAdmin(){
    int ID = 0;
    string F;
    string L;
    string U;
    string P;
    for(int i = 0; i < SIZE; i++){
        if (admins[i] == NULL) {
            
            admins[i] = new Admin(ID,F,L,U,P);
            
            admins[i] -> ID = rand()%10000+1000;
            
            cout << "Please enter the first name of the admin:" << endl;
            cin >> F; cout << endl; admins[i] -> FirstName = F;
            
            cout << "Please enter the last name of the admin:" << endl;
            cin >> L; cout << endl; admins[i] -> LastName = L;
            
            U = admins[i] -> FirstName;
            U[0] = U[0] - 'Z' + 'z'; U = U + to_string(admins[i] -> ID);
            admins[i] -> UserName = U;
            
            P = admins[i] -> LastName;
            P[0] = P[0] - 'Z' + 'z';; P = P + to_string(rand()%10000+1000);
            admins[i] -> Password = P;
            
            cout << "Your username is: " << admins[i] -> UserName << endl
            << "Your password is: " << admins[i] -> Password << endl;
            
            return;
        }
    }
}

//set a function for admin to add a new fitness class
void Admin::addFitnessClass(){
    string ID;
    string Capacity;
    string RoomNum;
    string Name;
    string Date;
    string Time;
    
    for(int i = 0; i < SIZE; i++){
        if (classes[i] == NULL) {
            
            classes[i] = new FitnessClass;
            for (int j = 0; j < SIZE; j++) {
                classes[i] -> ListOfMembers[j] = 0;
            }
            
            cout << "Please enter the Class ID:" << endl;
            cin >> ID; cout << endl; classes[i] -> ID = stoi(ID);
            
            cout << "Please enter the name of the class:" << endl;
            cin >> Name; cout << endl; classes[i] -> ClassName = Name;
            
            cout << "Please enter the maxium capacity of the class:" << endl;
            cin >> Capacity; cout << endl; classes[i] -> MaxiumCapacity = stoi(Capacity);
            
            cout << "Please enter the room number of the class:" << endl;
            cin >> RoomNum; cout << endl; classes[i] -> RoomNumber = stoi(RoomNum);
            
            cout << "Please enter the date of the class:" << endl;
            cin >> Date; cout << endl; classes[i] -> ClassDate = Date;
            
            cout << "Please enter the time of the class:" << endl;
            cin >> Time; cout << endl; classes[i] -> ClassTime = Time;
            
            return;
        }
    }
}

//set a function for admin to delete a fitness class
void Admin::deleteFitnessClass(){
    int ID;
    int index;

    cout << "Please enter the ID of the class you want to delete:" << endl;
    cin >> ID; cout << endl;
    index = searchIndex_class(ID, classes);
    if(index == 101){
        cout << "There is no exising class ID: " << ID << endl;
        return;
    }
    delete classes[index];
    for (int i = index; i < SIZE ; i++) {
        classes[i] = classes[i+1];
        classes[i+1] = NULL;
    }
    return;
}

//set a function for admin to update a fitness class
void Admin::updateClassDetails(){
    int ID;
    int index;
    string info;

    cout << "Please enter the ID of the class you want to update:" << endl;
    cin >> ID; cout << endl;
    index = searchIndex_class(ID, classes);
    cout << "Please enter the info of the class you want to update:" << endl;
    cin >> info; cout << endl;
    
    if (info == "Name") {
        cout << "Please enter the new name of the class:" << endl;
        cin >> info; cout << endl;
        classes[index] -> ClassName = info;
    }
    else if (info == "Capacity") {
        cout << "Please enter the new capacity of the class:" << endl;
        cin >> info; cout << endl;
        classes[index] -> MaxiumCapacity = stoi(info);
    }
    else if (info == "Room") {
        cout << "Please enter the new room of the class:" << endl;
        cin >> info; cout << endl;
        classes[index] -> RoomNumber = stoi(info);
    }
    else if (info == "Date") {
        cout << "Please enter the new date of the class:" << endl;
        cin >> info; cout << endl;
        classes[index] -> ClassDate = info;
    }
    else if (info == "Time") {
        cout << "Please enter the new time of the class:" << endl;
        cin >> info; cout << endl;
        classes[index] -> ClassTime = info;
    }
    else{
        cout << "There is no such info:" << endl;
    }
}

//set a function for member to book a class
void Member::bookAClass(int i){
    int ID;
    int index;
    int state;

    cout << "Please enter the ID of the class you want to book:" << endl;
    cin >> ID; cout << endl;
    index = searchIndex_class(ID, classes);
    state = ifFull(classes[index] -> MaxiumCapacity, classes[index] -> ListOfMembers);
    if (state != 101) {
        classes[index] -> ListOfMembers[state] = i;
        cout << "The class now has ";
        for (int j = 0; j < classes[index] -> MaxiumCapacity ; j++) {
            if (classes[index] -> ListOfMembers[1] == 0) {
                cout << "The 1 on 1 session is taken! " << endl;
                break;
            }
            else if (classes[index] -> ListOfMembers[j] == 0) {
            cout << j << " out of " << classes[index] -> MaxiumCapacity << " places booked!" << endl;
                break;
            }
        }
    }
    else{ cout << "There is no exising class ID: " << ID << endl;}
}

//set a function for member to cancel a class
void Member::cancelBooking(int i){
    int ID;
    int index;

    cout << "Please enter the ID of the class you want to cancel:" << endl;
    cin >> ID; cout << endl;
    index = searchIndex_class(ID, classes);
    if (index != 101) {
        for (int j = 0; j < classes[index] -> MaxiumCapacity; j++) {
            if (classes[index] -> ListOfMembers[j] == i) {
                for (int k = j; k < classes[index] -> MaxiumCapacity; k++) {
                    classes[index] -> ListOfMembers[k] = classes[index] -> ListOfMembers[k+1];
                    classes[index] -> ListOfMembers[k+1] = 0;
                }
                cout << "The class now has ";
                for (int j = 0; j < classes[index] -> MaxiumCapacity ; j++) {
                    if (classes[index] -> ListOfMembers[j] == 0) {
                        cout << j << " out of " << classes[index] -> MaxiumCapacity << " places booked!" << endl;
                        break;
                    }
                }
                return;
            }
        }
    }
    else{ cout << "There is no exising class ID: " << ID << endl;}
    
}

//set a function to get member ID
int Member::getID(int i){
    return members[i] -> ID;
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
        <<"6) Display the classes with vacancies" << endl
        <<"7) Quit the program" << endl << endl
        <<"Enter the number of the required action: [1-7] "<< endl;
}

//set a function listing out commands for member
void Member::listCommands()
{
    cout<<"List of available Commands for Members:" << endl
        <<"1) Display the classes with vacancies" << endl
        <<"2) Book a class" << endl
        <<"3) Cancel a class" << endl
        <<"4) Quit the program" << endl
        <<"Enter the number of the required action: [1-4] " << endl;
}
