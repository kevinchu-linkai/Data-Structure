//============================================================================
// Name         : Assignment2.cpp
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
#include<fstream>
#include<ostream>
#include"Header.h"//include my template

using namespace std;
DoublyLinkedList <Admin> Admins; //create an admin object of doubly linked list
DoublyLinkedList <Member> Members; //create a member object of doubly linked list
DoublyLinkedList <FitnessClass> FitnessClasses; //create a fitness classes object of doubly linked list
ifstream admins;
ifstream members;
ifstream fitnessclasses;
ofstream admin("Admins.txt", ios::out);
ofstream member("Members.txt", ios::out);
ofstream fitnessclass("FitnessClasses.txt", ios::out);
// the program for creating files when quitting
void quit(){
    
    if(admin.is_open()){
        //outputing admin list
        Node<Admin>* current1 = Admins.head -> next;
        while(current1!= Admins.tail){
            admin << current1 -> elem.ID << ",";
            admin << current1 -> elem.FirstName << ",";
            admin << current1 -> elem.LastName << ",";
            admin << current1 -> elem.UserName << ",";
            admin << current1 -> elem.Password << endl;
            current1 = current1 -> next;
        }
    }
    else{perror("Error");}
    
    if(member.is_open()){
        //outputting member list
        Node<Member>* current2 = Members.head -> next;
        while(current2 != Members.tail){
            member << current2 -> elem.ID << ",";
            member << current2 -> elem.FirstName << ",";
            member << current2 -> elem.LastName << ",";
            member << current2 -> elem.UserName << ",";
            member << current2 -> elem.Password << endl;
            current2 = current2 -> next;
        }
    }
    else{perror("Error");}
    
    if(fitnessclass.is_open()){
        //outputing fitnessclasses list
        Node<FitnessClass>* current3 = FitnessClasses.head -> next;
        while(current3 != FitnessClasses.tail){
            fitnessclass << current3 -> elem.ID << ",";
            fitnessclass << current3 -> elem.ClassName << ",";
            fitnessclass << current3 -> elem.ClassDate << ",";
            fitnessclass << current3 -> elem.ClassTime << ",";
            fitnessclass << current3 -> elem.MaxiumCapacity << ",";
            fitnessclass << current3 -> elem.RoomNumber << ",";
            while (current3 -> elem.ListOfMember.size() != 0) {
                fitnessclass << current3 -> elem.ListOfMember.top() << ",";
                current3 -> elem.ListOfMember.pop();
            }
            fitnessclass << endl;
            current3 = current3 -> next;
        }
    }
    else{perror("Error");}
    
    //close the files
    admin.close();
    member.close();
    fitnessclass.close();
}

//set a function for admin login
Admin adminLogin(string U){
    string P;
    Node<Admin>* current = Admins.head;
    while(current != Admins.tail){
        if(U == current -> elem.UserName){
            cout << "Enter your password: " << endl;
            cin >> P; cout << endl;
            if(P == current -> elem.Password){
                cout << "You have login successfully!" << endl;
                STATE = 1;
                return current -> elem;
                }
            else{
                cout << "Wrong password!" << endl;
                STATE = 0;
                return Admins.tail -> elem;
            }
        }
        current = current -> next;
    }
    STATE = 0;
    return Admins.tail -> elem;
}

//set a function for member login
Member memberLogin(string U){
    string P;
    Node<Member>* current = Members.head;
    while(current != Members.tail){ 
        if(U == current -> elem.UserName){
            cout << "Enter your password: " << endl;
            cin >> P; cout << endl;
            if(P == current -> elem.Password){
                cout << "You have login successfully!" << endl;
                STATE = 1;
                return current -> elem;
                }
            else{
                cout << "Wrong password!" << endl;
                STATE = 0;
                return Members.tail -> elem;
            }
        }
        current = current -> next;
    }
    STATE = 0;
    return Members.tail -> elem;
}

//set a function for to display all the classes with vacancies
void viewClassesWithVacancies(){
    Node<FitnessClass>* current = FitnessClasses.head -> next;
    while(current != NULL){
        if (current -> elem.ListOfMember.size() < current -> elem.MaxiumCapacity) {
            cout << "This class is now open" << endl
            << "Class ID: " << current -> elem.ID << endl
            << "Class Name: " << current -> elem.ClassName << endl
            << "Class Date: " << current -> elem.ClassDate << endl
            << "Class Time: " << current -> elem.ClassTime << endl
            << "Class Room: " << current -> elem.RoomNumber << endl << endl;
        }
        current = current -> next;
    }
}

int main(){
//THIS IS THE PART I FAIL TO LOAD THE FILE IN
    
//    while (!admins.eof()) {
//        string data;
//        string data_list[5];
//        Admin a;
//        int i = 0;
//        while (getline(admins, data, ',')) {
//            data_list[i] = data;
//            i++;
//        }
//        a.ID = stoi(data_list[0]);
//        a.FirstName = data_list[1];
//        a.LastName = data_list[2];
//        a.UserName = data_list[3];
//        a.Password = data_list[4];
//        Admins.addBack(a);
//    }
//    admins.close();
//
//    while (!members.eof()) {
//        string data;
//        string data_list[5];
//        Member a;
//        int i = 0;
//        while (getline(members, data, ',')) {
//            data_list[i] = data;
//            i++;
//        }
//        a.ID = stoi(data_list[0]);
//        a.FirstName = data_list[1];
//        a.LastName = data_list[2];
//        a.UserName = data_list[3];
//        a.Password = data_list[4];
//        Members.addBack(a);
//    }
//    members.close();
//
//    while (!fitnessclasses.eof()) {
//        string data;
//        string data_list[9];
//        FitnessClass a;
//        int i = 0;
//        while (getline(fitnessclasses, data, ',')) {
//            data_list[i] = data;
//            i++;
//        }
//        a.ID = stoi(data_list[0]);
//        a.ClassName = data_list[1];
//        a.ClassDate = data_list[2];
//        a.ClassTime = data_list[3];
//        a.MaxiumCapacity = stoi(data_list[4]);
//        a.RoomNumber = stoi(data_list[5]);
//        a.ListOfMember.push(stoi(data_list[6]));
//        a.ListOfMember.push(stoi(data_list[7]));
//        a.ListOfMember.push(stoi(data_list[8]));
//        FitnessClasses.addBack(a);
//    }
//    fitnessclasses.close();
    
    string category;
    string username;
    string password;
    int command;
    
    
    //since I failed to load the file in, I registered an admin in the beginning of the program
    Admin a;
    a.registerAdmin();
    //start the program and keep it running till quit program
    while(true){
        
        cout << "Welcome to the fitness management system!" << endl;
        cout << "Please enter the category of your account before login : [ admin / member ]" << endl;
        cin >> category; cout << endl;
           
        //when login as an admin
        if (category == "admin") {
            cout << "Please enter your username: " << endl;
            cin >> username; cout << endl;
            Admin user = adminLogin(username);
            //this shows if the admin exists or if the password is wrong
            if (STATE == 0) {
                cout << "This member does not exist!" << endl;
            }
            //successful login
            while(STATE == 1) {
                user.listCommands();
                //user input command
                //call different function according to the command
                cin >> command; cout << endl;
                if(command == 1){user.registerAdmin();}
                else if(command == 2){user.registerMember();}
                else if(command == 3){user.addFitnessClass();}
                else if(command == 4){user.deleteFitnessClass();}
                else if(command == 5){user.updateClassDetails();}
                else if(command == 6){user.changeClassCapacity();}
                else if(command == 7){user.splitClass();}
                else if(command == 8){viewClassesWithVacancies();}
                else if(command == 9){user.viewMemberList();}
                else if(command == 10){cout << "Logged out!" << endl; STATE = 0;}
                else if(command == 11){cout << "Quit program!" << endl; quit(); return EXIT_SUCCESS;}
                else{cout << "No such command!" << endl;}
            }
        }
           
        //when login as a member
        else if (category == "member"){
            cout << "Please enter your username: " << endl;
            cin >> username; cout << endl;
            Member user = memberLogin(username);
            //this shows if the member exists or if the password is wrong
            if (STATE == 0) {
                cout << "This member does not exist!" << endl;
            }
            //successful login
            while(STATE == 1) {
                user.listCommands();
                //user input command
                //call different function according to the command
                cin >> command; cout << endl;
                if(command == 1){viewClassesWithVacancies();}
                else if(command == 2){user.bookAClass(user.getID());}
                else if(command == 3){user.cancelBooking(user.getID());}
                else if(command == 4){user.viewBookingList();}
                else if(command == 5){cout << "Logged out!" << endl; STATE = 0;}
                else if(command == 6){cout << "Quit program!" << endl; quit(); return EXIT_SUCCESS;}
                else{cout << "No such command!" << endl;}
            }
        }
           
        //when wrong input category
        else{
            cout << "No such category! Please enter the category of your account before login : [ admin / member ]" << endl;
        }
    }
    return 0;
}

//set a function for member to book a class
void Member::bookAClass(int i){
    int ID;
    cout << "Please enter the ID of the class you want to book:" << endl;
    cin >> ID; cout << endl;
    Node<FitnessClass>* current = FitnessClasses.head;
    while(current != FitnessClasses.tail){
        if(current -> elem.ID == ID){
            if (current -> elem.ListOfMember.size() < current -> elem.MaxiumCapacity) {
                current -> elem.ListOfMember.push(i);
                BookingList.push(ID);
                return;
            }
        }
        current = current -> next;
    }
    cout << "No such class exists!" << endl;
    return;
}

//set a function for member to cancel a class
void Member::cancelBooking(int i){
    int ID;

    cout << "Please enter the ID of the class you want to cancel:" << endl;
    cin >> ID; cout << endl;
    Node<FitnessClass>* current = FitnessClasses.head;
    while(current != FitnessClasses.tail){
        if(current -> elem.ID == ID){
            LinkedStack S;
            int k = current -> elem.ListOfMember.size();
            for (int j = 0; j < k; j++) {
                if (current -> elem.ListOfMember.top() != i) {
                    S.push(current -> elem.ListOfMember.top());
                    S.pop();
                }
            }
            current -> elem.ListOfMember = S;
            LinkedStack T;
            int l = BookingList.size();
            for (int j = 0; j < l; j++) {
                if (BookingList.top() !=  ID) {
                    T.push(BookingList.top());
                    T.pop();
                }
            }
            BookingList = T;
        }
        current = current -> next;
    }
    cout << "No such class exists!" << endl;
    return;
}

//set a function for admin to register a new admin
void Admin::registerAdmin(){
    string F;
    string L;
    string U;
    string P;
    Admin a;
    Admins.addBack(a);
    
    Admins.back().ID = rand()%10000+1000;
    cout << "Please enter the first name of the registering admin:" << endl;
    cin >> F; cout << endl; Admins.back().FirstName = F;

    cout << "Please enter the last name of the reistering admin:" << endl;
    cin >> L; cout << endl; Admins.back().LastName = L;

    U = Admins.back().FirstName;
    if ('A' <= U[0] && U[0] <= 'Z') {
        U[0] = U[0] - 'Z' + 'z';
    }
    U = U + to_string(Admins.back().ID);
    Admins.back().UserName = U;

    P = Admins.back().LastName;
    if ('A' <= P[0] && P[0] <= 'Z') {
        P[0] = P[0] - 'Z' + 'z';
    }
    P = P + to_string(rand()%10000+1000);
    Admins.back().Password = P;

    cout << "Your username is: " << Admins.back().UserName << endl
    << "Your password is: " << Admins.back().Password << endl << endl;
    return;
}

//set a function for admin to register a new member
void Admin::registerMember(){
    string F;
    string L;
    string U;
    string P;
    Member m;
    Members.addBack(m);
    Members.back().ID = rand()%10000+1000;
    cout << "Please enter the first name of the registering member:" << endl;
    cin >> F; cout << endl; Members.back().FirstName = F;

    cout << "Please enter the last name of the registering member:" << endl;
    cin >> L; cout << endl; Members.back().LastName = L;

    U = Members.back().FirstName;
    if ('A' <= U[0] && U[0] <= 'Z') {
        U[0] = U[0] - 'Z' + 'z';
    }
    U = U + to_string(Members.back().ID);
    Members.back().UserName = U;

    P = Members.back().LastName;
    if ('A' <= P[0] && P[0] <= 'Z') {
        P[0] = P[0] - 'Z' + 'z';
    }
    P = P + to_string(rand()%10000+1000);
    Members.back().Password = P;

    cout << "Your username is: " << Members.back().UserName << endl
    << "Your password is: " << Members.back().Password << endl << endl;
    return;
}

//set a function for admin to add a new fitness class
void Admin::addFitnessClass(){
    string ID;
    string Capacity;
    string RoomNum;
    string Name;
    string Date;
    string Time;
    
    FitnessClass f;
    FitnessClasses.addBack(f);
            
    cout << "Please enter the Class ID:" << endl;
    cin >> ID; cout << endl; FitnessClasses.back().ID = stoi(ID);
            
    cout << "Please enter the name of the class:" << endl;
    cin >> Name; cout << endl; FitnessClasses.back().ClassName = Name;
            
    cout << "Please enter the maxium capacity (5-15) of the class:" << endl;
    cin >> Capacity;
    while(stoi(Capacity) > 15 || stoi(Capacity) < 5){
        Capacity = "10";
    }
    cout << endl; FitnessClasses.back().MaxiumCapacity = stoi(Capacity);
            
    cout << "Please enter the room number of the class:" << endl;
    cin >> RoomNum; cout << endl; FitnessClasses.back().RoomNumber = stoi(RoomNum);
            
    cout << "Please enter the date of the class:" << endl;
    cin >> Date; cout << endl; FitnessClasses.back().ClassDate = Date;
            
    cout << "Please enter the time of the class:" << endl;
    cin >> Time; cout << endl; FitnessClasses.back().ClassTime = Time;
            
    return;
}

//set a function for admin to delete a fitness class
void Admin::deleteFitnessClass(){
    int ID;

    cout << "Please enter the ID of the class you want to delete:" << endl;
    cin >> ID; cout << endl;
    Node<FitnessClass>* current = FitnessClasses.head -> next;
    while(current!= FitnessClasses.tail){
        if(current -> elem.ID == ID){
            FitnessClasses.remove(current);
            return;
        }
        current = current -> next;
    }
    cout << "No such class exists!" << endl;
    return;
}

//set a function for admin to update a fitness class
void Admin::updateClassDetails(){
    int ID;
    string info;

    cout << "Please enter the ID of the class you want to update:" << endl;
    cin >> ID; cout << endl;
    Node<FitnessClass>* current = FitnessClasses.head -> next;
    while(current!= FitnessClasses.tail){
        if(current -> elem.ID == ID){
            cout << "Please enter the info of the class you want to update:" << endl;
            cin >> info; cout << endl;
            if (info == "Name") {
                cout << "Please enter the new name of the class:" << endl;
                cin >> info; cout << endl;
                current -> elem.ClassName = info;
                return;
            }
            else if (info == "Room") {
                cout << "Please enter the new room of the class:" << endl;
                cin >> info; cout << endl;
                current -> elem.RoomNumber = stoi(info);
                return;
            }
            else if (info == "Date") {
                cout << "Please enter the new date of the class:" << endl;
                cin >> info; cout << endl;
                current -> elem.ClassDate = info;
                return;
            }
            else if (info == "Time") {
                cout << "Please enter the new time of the class:" << endl;
                cin >> info; cout << endl;
                current -> elem.ClassTime = info;
                return;
            }
            else{
                cout << "There is no such info:" << endl;
                return;
            }
        }
        current = current -> next;
    }
    cout << "No such class exists!" << endl;
    return;
}

//set a function for admin to update the capacity of a class
void Admin::changeClassCapacity(){
    int ID;
    string info;

    cout << "Please enter the ID of the class you want to update:" << endl;
    cin >> ID; cout << endl;
    Node<FitnessClass>* current = FitnessClasses.head -> next;
    while(current!= FitnessClasses.tail){
        if (current -> elem.ID == ID) {
            cout << "Please enter the new capacity of the class:" << endl;
            cin >> info; cout << endl;
            current -> elem.MaxiumCapacity = stoi(info);
            while (current -> elem.MaxiumCapacity < current -> elem.ListOfMember.size()){
                current -> elem.ListOfMember.pop();
            }
            return;
        }
        current = current -> next;
    }
    cout << "No such class exists!" << endl;
    return;
}

//set a function for admin to split a class into two
void Admin::splitClass(){
    int i;
    cout << "Please enter the ID of the class you want to split:" << endl;
    cin >> i; cout << endl;
    Node<FitnessClass>* current = FitnessClasses.head -> next;
    while(current!= FitnessClasses.tail){
        if (current -> elem.ID == i) {
            FitnessClass f;
            FitnessClasses.addBack(f);
            string ID;
            string Capacity;
            int RoomNum = current -> elem.RoomNumber;
            string Name = current -> elem.ClassName;
            string Date = current -> elem.ClassDate;
            string Time = current -> elem.ClassTime;
            
            FitnessClasses.back().ClassTime = Time;
            FitnessClasses.back().ClassName = Name;
            FitnessClasses.back().ClassDate = Date;
            FitnessClasses.back().RoomNumber = RoomNum;
            cout << "Please enter the new Class ID:" << endl;
            cin >> ID; cout << endl; FitnessClasses.back().ID = stoi(ID);
                        
            cout << "Please enter the maxium capacity (5-15) of the previous class:" << endl;
            cin >> Capacity;
            if(stoi(Capacity) > 15 || stoi(Capacity) < 5){
                Capacity = "10";
            }
            if (stoi(Capacity) < current -> elem.ListOfMember.size()) {
                for (int i = 0; i < (current -> elem.ListOfMember.size() - stoi(Capacity)); i++) {
                    FitnessClasses.back().ListOfMember.push(current -> elem.ListOfMember.top()) ;
                    current -> elem.ListOfMember.pop();
                }
            }
            cout << endl; current -> elem.MaxiumCapacity = stoi(Capacity);
            
            cout << "Please enter the maxium capacity (5-15) of the new class:" << endl;
            cin >> Capacity;
            if(stoi(Capacity) > 15 || stoi(Capacity) < 5){
                Capacity = "10";
            }
            cout << endl; FitnessClasses.back().MaxiumCapacity = stoi(Capacity);
        }
        current = current -> next;
    }
    return;
}

//set a function for the member to view their booking list
void Member::viewBookingList(){
    LinkedStack S;
    if (BookingList.size() == 0) {
        cout << "No class booked yet!" << endl;
        return;
    }
    while (BookingList.size() != 0) {
        int i = BookingList.top();
        S.push(i);
        BookingList.pop();
        Node<FitnessClass>* current = FitnessClasses.head -> next;
        while(current!= FitnessClasses.tail){
            if (current -> elem.ID == i) {
                cout << "Class ID:" << current -> elem.ID <<endl;
                cout << "Class name:" << current -> elem.ClassName << endl;
                cout << "Class date:" << current -> elem.ClassDate << endl;
                cout << "Class time:" << current -> elem.ClassTime << endl;
                cout << "Class room number:" << current -> elem.RoomNumber << endl << endl;
            }
            current = current -> next;
        }
    }
    BookingList = S;
    return;
}

//set a function for the admin to view the list of members
void Admin::viewMemberList(){
    Node<Member>* current = Members.head -> next;
    while(current!= Members.tail){
        cout << "Member ID:" << current -> elem.ID <<endl;
        cout << "Member First name:" << current -> elem.FirstName << endl;
        cout << "Member Last name:" << current -> elem.LastName << endl << endl;
        current = current -> next;
    }
}


