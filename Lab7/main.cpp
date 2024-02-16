//============================================================================
// Name         : MyVector.cpp
// Author       : Khalid Mengal
// Version      : 1.0
// Date Created : 16-03-2019
// Date Modified: 21-10-2021
// Copyright    : All rights are reserved
// Description  : Vector implmentation in C++
//============================================================================
#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<stdexcept>
#include<sstream>

using namespace std;
template <typename T>
class MyVector
{
    private:
        T *data;                        //pointer to int(array) to store elements
        int v_size;                        //current size of vector (number of elements in vector)
        int v_capacity;                    //capacity of vector
    public:
        MyVector();                        //No argument constructor
        MyVector(int cap);                //One Argument Constructor
        ~MyVector();                    //Destructor
        void push_back(T element);        //Add an element at the end of vector
        void insert(int index, T element); //Add an element at the index
        void erase(int index);            //Removes an element from the index
        T& at(int index);                 //return reference of the element at index
        const T& front();                //Returns reference of the first element in the vector
        const T& back();                //Returns reference of the Last element in the vector
        int size() const;                //Return current size of vector
        int capacity() const;            //Return capacity of vector
        bool empty() const;             //Rturn true if the vector is empty, False otherwise
        void shrink_to_fit();            //Reduce vector capacity to fit its size
        void display();
};

void listCommands()
{
    cout<<"List of available Commands:"<<endl
        <<"display                  : Display the Vector"<<endl
        <<"push_back <element>      : Add an element to the end of the vector"<<endl
        <<"insert <index element>   : Insert an element at location index"<<endl
        <<"erase <index>           : Remove the element from index"<<endl
        <<"at <index>               : Returns a reference to an element at a specified location"<<endl
        <<"front                    : Return the (reference of) front element"<<endl
        <<"back                     : Returns a reference to the last element of the vector"<<endl
        <<"size                     : Returns the number of elements in the vector"<<endl
        <<"capacity                 : Returns the capacity of vector"<<endl
        <<"empty                    : Tests if the vector container is empty"<<endl
        <<"shrink                   : Reduce vector capacity to fit its size (shrink_to_fit)"<<endl
        <<"exit/quit                : Exit the Program"<<endl;
}
//=======================================
int main()
{
    MyVector<int> myVector;
    listCommands();
    string user_input;
    string command;
    string parameter1;
    string parameter2;

    do
    {
        cout<<">";
        getline(cin,user_input);

        // parse userinput into command and parameter(s)
        stringstream sstr(user_input);
        getline(sstr,command,' ');
        getline(sstr,parameter1,' ');
        getline(sstr,parameter2);

        try
        {
            if(command=="display" or command=="d")                                 myVector.display();
            else if(command=="push_back" or command=="p" )        static_cast<void>(myVector.push_back(stoi(parameter1))),myVector.display();
            else if(command=="insert" or command=="i")            static_cast<void>(myVector.insert(stoi(parameter1),stoi(parameter2))),myVector.display();
            else if(command=="erase" or command=="e")            static_cast<void>(myVector.erase(stoi(parameter1))),myVector.display();
            else if(command=="at" or command=="a")                cout<<myVector.at(stoi(parameter1))<<endl;
            else if(command=="front" or command=="f")            cout<<myVector.front()<<endl;
            else if(command=="back" or command=="b")            cout<<myVector.back()<<endl;
            else if(command=="size" or command=="s")            cout<<myVector.size()<<endl;
            else if(command=="capacity" or command=="c")        cout<<myVector.capacity()<<endl;
            else if(command=="empty" or command=="e")            cout<<boolalpha<<myVector.empty()<<endl;
            else if(command=="shrink")                          static_cast<void>(myVector.shrink_to_fit()),myVector.display();
            else if(command == "help" or command=="?")            listCommands();
            else if(command == "exit" or command=="quit")            break;
            else                                 cout<<"Invalid Commad !!"<<endl;
        }
        catch(exception &e)
        {
            cout<<"Exception: "<<e.what()<<endl;
        }

    }while(command!="exit" and command!="quit");

    return EXIT_SUCCESS;
}

template <typename T> MyVector<T>::MyVector(){
    v_size = 0;
    v_capacity = 0;
    data = new T[0];
};                        //No argument constructor
template <typename T> MyVector<T>::MyVector(int cap){
    v_size = 0;
    v_capacity = cap;
    data = new T[cap];
};                //One Argument Constructor
template <typename T> MyVector<T>::~MyVector(){
    delete []data;
};                    //Destructor
template <typename T> void MyVector<T>::push_back(T element){
    v_size ++;
    if (v_size >= v_capacity) {
        v_capacity *= 2;
        if (v_capacity == 0) {
            v_capacity = 1;
        }
        T* temp = new T[v_capacity];
        for (int i = 0; i < v_size; i++) {
            temp[i] = data[i];
        }
        data = temp;
        delete[] temp;
    }
    data[v_size - 1] = element;
};        //Add an element at the end of vector
template <typename T> void MyVector<T>::insert(int index, T element){
    if (index >= v_size - 1) {
        cout << "out of range" << endl;
        return;
    }
    else{
        v_size++;
        for (int i = v_size - 1; i > index; i--) {
            data[i] = data[i - 1];
        }
        data[index] = element;
    }
}; //Add an element at the index
template <typename T> void MyVector<T>::erase(int index){
    if (index > v_size - 1) {
        cout << "out of range" << endl;
        return;
    }
    else{
        for (int i = index; i < v_size; i++) {
            data[i] = data[i + 1];
        }
        v_size--;
    }
};            //Removes an element from the index
template <typename T> T& MyVector<T>::at(int index){
    return data[index];
};                 //return reference of the element at index
template <typename T> const T& MyVector<T>::front(){
    return data[0];
};                //Returns reference of the first element in the vector
template <typename T> const T& MyVector<T>::back(){
    return data[v_size - 1];
};                //Returns reference of the Last element in the vector
template <typename T> int MyVector<T>::size() const{
    return v_size;
};                //Return current size of vector
template <typename T> int MyVector<T>::capacity() const{
    return v_capacity;
};            //Return capacity of vectortemplate <typename T>
template <typename T> bool MyVector<T>::empty() const{
    return v_size == 0;
};             //Rturn true if the vector is empty, False otherwise
template <typename T> void MyVector<T>::shrink_to_fit(){
    if (v_capacity > v_size) {
        v_capacity = v_size;
        T* temp = new T[v_capacity];
        for (int i = 0; i < v_size; i++) {
            temp[i] = data[i];
        }
        data = temp;
        delete[] temp;
    }
};            //Reduce vector capacity to fit its size

#ifndef _WIN32
//======================================
template <typename T>
void MyVector<T>::display()
{
    cout<<"╔════";
    for(int i=0; i<v_capacity-1; i++)
        cout<<"╦════";
    cout<<"╗ size = "<<v_size<<endl;
    
    for(int i=0; i<v_capacity; i++)
    {
        if(i<v_size)
            cout<<"║"<<setw(4)<<data[i];
        else
            cout<<"║"<<setw(4)<<" ";
    }
    if(v_size==0) cout<<"║    ";
    cout<<"║"<<endl<<"╚════";
    for(int i=0; i<v_capacity-1; i++)
        cout<<"╩════";
    cout<<"╝ capacity = "<<v_capacity<<endl;
}
//======================================
#else
template <typename T>
void MyVector<T>::display()
{
    cout<<"+";
    for(int i=0; i<v_capacity; i++)
        cout<<"---+";
    cout<<" size = "<<v_size<<endl;
    
    for(int i=0; i<v_capacity; i++)
    {
        if(i<v_size)
            cout<<"|"<<setw(3)<<data[i];
        else
            cout<<"|"<<"   ";
    }
    cout<<"|"<<endl<<"+";
    for(int i=0; i<v_capacity; i++)
        cout<<"---+";
    cout<<" capacity = "<<v_capacity<<endl;
}
#endif
