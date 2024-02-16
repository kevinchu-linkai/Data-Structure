//============================================================================
// Name         : lab6_Queue.cpp
// Author       : Khalid Mengal
// Version      : 1.0
// Date Created : 7-10-2021
// Date Modified: 7-10-2021
// Copyright    : All rights are reserved
// Description  : Queue implementation using internal Array
//============================================================================

#include<iostream>
#include<iomanip> //for setw() manipulator
#include<exception>
#include<unistd.h>
#include<sstream>
#include<string>
#include<time.h>
#ifdef _WIN32
    #define clear_screen "cls"
#else
    #define clear_screen "clear"
#endif
#define SIZE 5
#define TOP 0
#define LEFT 1
#define BOTTOM 2
#define RIGHT 3
#define MAX_CARS 200
int current_signal = 0;
int state;
int SPEED=1; //1=slowest
using namespace std;
//===================================================
class QueueEmpty: public exception
{
    public:
        virtual const char* what() const throw()
        {
            return "Queue is Empty";
        }
};
//=================================================
class QueueFull: public exception
{
public:
    virtual const char* what() const throw()
    {
        return "Queue is Full";
    }
};
//=================================================

template <typename T>
class Queue
{
    private:
        T *array;
        int N;    //Array Size (Capacity)
        int r;    //index where a new element will be added
    public:
        Queue(int N); // N is the Capacity of Queue
        ~Queue();
        void enqueue(T)throw();
        T dequeue()throw();
        bool isEmpty();
        bool isFull();
        friend void display();
};

template <typename T> Queue <T>::Queue(int N):N(SIZE),array(new T[N]), r(0){} // N is the Capacity of Queue
template <typename T> Queue <T>::~Queue(){delete[] array;}
template <typename T> void Queue <T>::enqueue(T e) throw(){
    if(isFull()){throw QueueFull();}
    array[r]=e; r++;
}
template <typename T> T Queue <T>::dequeue() throw(){
    if(isEmpty()){throw QueueEmpty();}
    T temp = array[0];
    for(int i = 0; i < N-1; i++){
        array[i] = array[i+1];
    }
    r--;
    return temp;
}
template <typename T> bool Queue <T>::isEmpty(){return r == 0;}
template <typename T> bool Queue <T>::isFull(){return r == N-1;}

//===========================================
class Car
{
    private:
        time_t arrival_time;
    public:
        Car()
        {}
        Car(time_t time_stamp): arrival_time(time_stamp)
        {}
        time_t get_arrival_time()
        {
            return arrival_time;
        }
};
//===========================================
void display();
//===========================================
Queue<Car> left_queue(SIZE);
Queue<Car> right_queue(SIZE);
Queue<Car> top_queue(SIZE);
Queue<Car> bottom_queue(SIZE);
//==========================================
int main()
{
    srand(time_t(NULL));
    int cars=0;
    time_t signal_timer = time(NULL);
    double waiting_time=0;
    
    while(cars<MAX_CARS)
    {
        try {
            state = rand()%4;
            time_t current = time(NULL);
            Car c(time(NULL));
            if (current * 100 % 50 == 0) {
                if(state == TOP && !top_queue.isFull()) {
                    top_queue.enqueue(c);
                }
                else if(state == LEFT && !left_queue.isFull()){
                    left_queue.enqueue(c);
                }
                else if(state == BOTTOM && !bottom_queue.isFull()){
                    bottom_queue.enqueue(c);
                }
                else if(state == RIGHT && !right_queue.isFull()){
                    right_queue.enqueue(c);
                }
            }
            
            current_signal++;
            if (signal_timer * 2000 % 1000 == 0){
                current_signal = current_signal % 4;
                if(current_signal == TOP && !top_queue.isEmpty()) {
                    waiting_time += time(NULL) - top_queue.dequeue().get_arrival_time();
                    cars++;
                }
                else if(current_signal == LEFT && !left_queue.isEmpty()){
                    waiting_time += time(NULL) - left_queue.dequeue().get_arrival_time();
                    cars++;
                }
                else if(current_signal == BOTTOM && !bottom_queue.isEmpty()){
                    waiting_time += time(NULL) - bottom_queue.dequeue().get_arrival_time();
                    cars++;
                }
                else if(current_signal == RIGHT && !right_queue.isEmpty()){
                    waiting_time += time(NULL) - right_queue.dequeue().get_arrival_time();
                    cars++;
                }
            }

            system(clear_screen);
            display();
            cout<<"Total cars passed through the junction:"<<cars<<endl;
            cout<<"Avg. waiting time for a car: "<<setprecision(3)<<(float(waiting_time)/cars)*SPEED<<" seconds"<<endl;
            usleep(200000/SPEED);
        }
        catch (QueueFull &e) {
            cout<<"Exception: "<<e.what()<<endl;
        }catch (QueueEmpty &e) {
            cout<<"Exception: "<<e.what()<<endl;
        }
        
        
    }
    return EXIT_SUCCESS;
}
//========================================================
void display()
{
    string spaces;
    for(int j=0; j<=SIZE; j++)
        spaces+="     ";
    cout<<spaces<<"╔════╗"<<endl;
    for(int i=0; i<SIZE; i++)
    {
          cout<<spaces<<"║";
          if(i>=top_queue.N-top_queue.r)
              cout<<setw(4)<<" ▒▒ ";
          else
              cout<<"    ";
          cout<<"║"<<endl;
          cout<<spaces<<"╠════╣"<<endl;;
    }

    cout<<spaces<<"║";
    if(current_signal==TOP)
        cout<<"\033[1;32m"<<" ■■ "<<"\033[0m";
    else
        cout<<"\033[1;31m"<<" ■■ "<<"\033[0m";
    cout<<"║"<<endl;

    cout<<"╔════";
    for(int i=0; i<SIZE; i++)
        cout<<"╦════";
    cout<<"╝    ╚";
    for(int i=0; i<SIZE; i++)
        cout<<"════╦";

    cout<<"════╗"<<endl;


    for(int i=0; i<SIZE; i++)
    {
        cout<<"║";
        if(i>=left_queue.N-left_queue.r)
                  cout<<setw(4)<<" ▒▒ ";
        else
            cout<<"    ";
    }
    cout<<"║";

    if(current_signal==LEFT)
        cout<<"\033[1;32m"<<" █ "<<"\033[0m";
    else
        cout<<"\033[1;31m"<<" █ "<<"\033[0m";
    cout<<"      ";

    if(current_signal==RIGHT)
        cout<<"\033[1;32m"<<"   █ "<<"\033[0m";
    else
        cout<<"\033[1;31m"<<"   █ "<<"\033[0m";
    //cout<<"      ";

    for(int i=0; i<SIZE; i++)
    {
        cout<<"║";
        if(i < right_queue.r )
            cout<<setw(4)<<" ▒▒ ";
        else
            cout<<"    ";
    }
    cout<<"║"<<endl;

    cout<<"╚════";
    for(int i=0; i<SIZE; i++)
        cout<<"╩════";
    cout<<"╗    ╔";
    for(int i=0; i<SIZE; i++)
        cout<<"════╩";
    cout<<"════╝"<<endl;

     cout<<spaces<<"║";

     if(current_signal==BOTTOM)
        cout<<"\033[1;32m"<<" ▄▄ "<<"\033[0m";
    else
        cout<<"\033[1;31m"<<" ▄▄ "<<"\033[0m";
    cout<<"║"<<endl;

    for(int i=0; i<SIZE; i++)
    {
          cout<<spaces<<"╠════╣"<<endl;
          cout<<spaces;
                  cout<<"║";
        if(i < bottom_queue.r )
            cout<<setw(4)<<" ▒▒ ║"<<endl;
        else
            cout<<"    ║"<<endl;
    }
    cout<<spaces<<"╚════╝"<<endl;
    cout<<endl;
}
//===============================================
//complete the missing functions/methods

