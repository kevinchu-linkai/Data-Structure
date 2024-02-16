//
//  myvector.cpp
//  ass3
//
//  Created by 朱麟凱 on 2022/4/5.
//

#include "myvector.h"

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
};
