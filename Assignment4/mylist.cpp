#include "mylist.h"
#include <iostream>
#include <fstream>
#include <string>
//mylist class and methods defination
//===========================================================
template <typename T>
MyList<T>::MyList()
{
    this->head = new Node<T>();
    this->tail = new Node<T>();
    this->head->next = tail;
    this->tail->prev = head;
}
//============================================================
template <typename T>
MyList<T>::~MyList() // destructor to clean up all nodes
{
    while(!empty())
        removeFront();
}
//============================================================
template <typename T>
bool MyList<T>::empty() const // is list empty?
{
    return this->head->next == tail;
}
//============================================================
template <typename T>
const T& MyList<T>::front() const // get front element
{
    if(!empty())
        return this->head->next->elem;
    else
        throw runtime_error("List is Empty");
}
//============================================================
template <typename T>
T& MyList<T>::back() const// get back element
{
    if(!empty())
        return this->tail->prev->elem;
    else
        throw runtime_error("List is Empty");
}
//============================================================
template <typename T>
void MyList<T>::addBefore(Node<T> *ptr, const T& elem)
{
    Node<T> *tmp = new Node<T>(elem);
    tmp->next = ptr;
    tmp->prev = ptr->prev;
    ptr->prev->next = tmp;
    ptr->prev=tmp;
    size++;
}
//============================================================
template <typename T>
void MyList<T>::addAfter(Node<T> *ptr, const T& elem)
{
    Node<T> *tmp = new Node<T>(elem);
    tmp->prev = ptr;
    tmp->next = ptr->next;
    ptr->next->prev = tmp;
    ptr->next=tmp;
    size++;
}
//============================================================
template <typename T>
void MyList<T>::addFront(const T& elem) // add to front of list
{
    addBefore(this->head->next, elem);
}
//============================================================
template <typename T>
void MyList<T>::addBack(const T& elem) // add to Back of the list
{
    addBefore(this->tail, elem);
}
//============================================================
template <typename T>
void MyList<T>::removeFront() // remove front item from list
{
    if(!empty())
    {
        Node<T> *tmp = this->head->next;
        this->head->next = tmp->next;
        tmp->next->prev = head;
        delete tmp;
    }
    size--;
}
//============================================================
template <typename T>
void MyList<T>::removeBack() // remove last item from list
{
    if(!empty())
    {
        Node<T> *tmp = this->tail->prev;
        this->tail->prev = tmp->prev;
        tmp->prev->next = tail;
        delete tmp;
    }
    size--;
}
//============================================================
template <typename T>
void MyList<T>::remove(iterator other) // remove item from list
{
    if(!empty())
    {
        for (iterator p = begin(); p != end(); ++p){
            if (p == other){
                Node<T> *tmp = p.get();
                tmp->prev->next = tmp->next;
                tmp->next->prev = tmp->prev;
                delete tmp;
            }
        }
        size--;
    }
}
