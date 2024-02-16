//============================================================================
// Name         : lab11.cpp
// Author       : Khalid Mengal
// Version      : 1.0
// Date Created : 25-04-2020
// Date Modified: 18-11-2021
// Copyright    : All rights are reserved
// Description  : HashTable Implmentation using C++
//============================================================================

#include<iostream>
#include<fstream>
#include<sstream>
#include<math.h>
#include<string>
#include<list>

using namespace std;
class HashNode
{
    private:
        string key;
        string value;
    public:
        HashNode(string key, string value)
        {
            this->key = key;
            this->value = value;
        }
        friend class HashTable;

};

class HashTable
{
    private:
        //HashNode **nodeArray;            // Array of Pointers to Hash Nodes
        //Comment out the line above and uncomment line below for Task 3
        list<HashNode> *buckets;        // Array of lists of type Hash Nodes
        int size;                        //Current Size of HashTable
        int capacity;                    // Total Capacity of HashTable
        int probes;                    // Total Number of probes
    public:
        HashTable(int capacity);
        unsigned long hashCode(string key);
        void insert(string key, string value);
        string search(string key);
        void erase(string key); //uncomment it for Task3
        int getSize();
        int getProbes();
        ~HashTable();

};
HashTable::HashTable(int capacity)
{
//    nodeArray = new HashNode*[capacity];            // Array of Pointers to Hash Nodes
//    for(int i=0; i<capacity; i++)
//        nodeArray[i] = nullptr;
    //Comment out the line above and uncomment line below for Task 3
    buckets = new list<HashNode>[capacity];
    this->capacity = capacity;
    this->size = 0;
    this->probes = 0;
}

unsigned long HashTable::hashCode(string key)
{
    unsigned long h = 0;
    for (int i = 0; i < key.length(); i++) {
        h = long((h + pow(97,key.length()-i-1)*key[i])) % capacity;
    }
    return long(h) ;
}
//================================================
void HashTable::insert(string key, string value)
{
    int index = hashCode(key) % capacity;
    HashNode temp(key,value);
    buckets[index].push_back(temp);
    size++;
    for (list<HashNode>::iterator p = buckets[index].begin();
         p != buckets[index].end(); p++) {
        probes++;
        if (p->key == key) {
            return;
        }
    }
}
//===================================================
string HashTable::search(string key)
{
    int index = hashCode(key) % capacity;
    for (list<HashNode>::iterator p = buckets[index].begin();
         p != buckets[index].end(); p++) {
        if (p->key == key) {
            return p->value;
        }
    }
    return "Not found!";
}
//=====================================================
void HashTable::erase(string key)
{
    int index = hashCode(key) % capacity;
    for (list<HashNode>::iterator p = buckets[index].begin();
         p != buckets[index].end(); p++) {
        if (p->key == key) {
            buckets[index].erase(p);
        }
    }
    return;
}
//=====================================================
int HashTable::getSize()
{
    return this->size;
}
//======================================================
int HashTable::getProbes()
{
    return this->probes;
}
//======================================================
HashTable::~HashTable()
{
    for (int i = 0; i < capacity; i++) {
        buckets[i].clear();
    }
    delete [] buckets;
}

//======================================================
int main(void)
{
    ifstream fin;
    fin.open("zipcodes.csv");
    if(!fin){
        cout<<"Can not open the file <zipcodes.txt>...!"<<endl;
        exit(-1);
    }

    string line;
    HashTable myHashTable(24851);// Prime number bigger than >24850 (19880*1.25);
    getline(fin,line);  //skip first line
    while(!fin.eof())
    {
        string key, value;
        getline(fin,key,',');
        getline(fin,value);
        cout<<key<<":"<<value<<endl;
        myHashTable.insert(key,value);

    }
    fin.close();
    cout<<"==================================================="<<endl;
    cout<<"Hash Table size = "<<myHashTable.getSize()<<endl;
    cout<<"Total Number of probes = "<<myHashTable.getProbes()<<endl;
    cout<<"Avg. Number of probes Per Entry = "<<float(myHashTable.getProbes())/myHashTable.getSize()<<endl;
    cout<<"==================================================="<<endl;

    string user_input, command, argument1, argument2;

    while(true)
    {
    
        cout<<">";
        getline(cin,user_input);

        stringstream sstr(user_input);
        getline(sstr,command,' ');
        getline(sstr,argument1,',');
        getline(sstr,argument2);

            if(command == "search") cout<<"Zip code for "<<argument1<<" is: "<<myHashTable.search(argument1)<<endl;
        else if(command == "insert") {myHashTable.insert(argument1,argument2);}
        //Uncomment following line for the Task 3
        else if(command == "erase")      myHashTable.erase(argument1);
        else if(command == "help")      cout<<"Commands available \ninsert <key,value>\nsearch <key>\nerase <key>"<<endl;
        else if(command == "exit")      break;
        else cout<<"Invalid command !!!"<<endl;
    }
    return 0;
}
