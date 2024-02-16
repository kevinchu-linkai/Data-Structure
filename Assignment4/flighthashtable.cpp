#include "flighthashtable.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <math.h>
#include <string>
using namespace std;

FlightHASHTABLE::FlightHASHTABLE(int capacity){
    this->buckets = new MyList<HashNode>[capacity];
    this->capacity = capacity;
    this->size = 0;
    this->collision = 0;
}                        //constructor

FlightHASHTABLE::~FlightHASHTABLE(){
    delete [] buckets;
}                        //destructor

long FlightHASHTABLE::hashCode(string key){
//    //hash function 1:
//    //1k.file 1012 collisions
//    //10k.file 102679 collisions
//    //100k.file 10379641 collisions
//    unsigned long h = 0;
//    for (int i = 0; i < key.length(); i++) {
//        h = long(h + key[i]) % capacity;
//    }
//    return long(h) ;
//
//    //hash function 2:
//    //1k.file 613 collisions
//    //10k.file 55156 collisions
//    //100k.file 5469478 collisions
//    unsigned long h = 0;
//    for (int i = 0; i < key.length(); i++) {
//        h = long((h + pow(97,key.length()-i-1)*key[i])) % capacity;
//    }
//    return long(h) ;
    
    //hash function 3:
    //1k.file 0 collisions (7,57)
    //10k.file 105 collisions (7,57)
    //100k.file 8189 collisions (7,57)
    unsigned long h = 0;
    for (int i = 0; i < key.length(); i++) {
        char temp;
        if(isupper(int(key[i]))){
            temp = tolower(int(key[i]));
        }
        else{
            temp = key[i];
        }
        h = (h << 7) | (h >> 57); h = (h + long(temp)) % capacity;
    }
    return long(h);
}                         //implement and test different hash functions

int FlightHASHTABLE::importCSV(string path){
    ifstream fin(path);
    string line;
    int cnt = 0;
    if(!fin.good()){
        return -1;
    }
    getline(fin,line);
    while(fin.peek() != EOF){
        getline(fin,line);
        string companyName;
        string flightNumber;
        string country_of_origin;
        string country_of_destination;
        string stopOver;
        string price;
        string time_of_departure;
        string time_of_arrival;
        string date = "";
        for(int k = 0; k < line.size(); k++){
            if(line[k] == ',' && line[k+1] == ' '){
                line[k] = '-'; line[k+1] = '-';
            }
        }
        stringstream sstr(line);
        int i = 0;
        while(i<9){
            string elem;
            getline(sstr, elem,',');
            for(int j = 0; j < elem.length(); j++){
                if (elem[j] == '-' && elem[j+1] == '-') {
                    elem[j] = ',';
                    elem[j+1] = ' ';
                    break;
                }
            }
            if(i == 0){
                companyName = elem;
            }
            else if(i == 1){
                flightNumber = elem;
            }
            else if(i == 2){
                country_of_origin = elem;
            }
            else if(i == 3){
                country_of_destination = elem;
            }
            else if(i== 4){
                stopOver = elem;
            }
            else if(i == 5){
                price = elem;
            }
            else if(i == 6){
                time_of_departure = elem;
            }
            else if(i == 7){
                time_of_arrival = elem;
            }
            else if(i == 8){
                if(elem.length() == 6){
                    for(int k = 0; k < 5; k++){
                        date = date + elem[k];
                    }
                }
                else{
                    for(int k = 0; k < 4; k++){
                        date = date + elem[k];
                    }
                }
            }
            i++;
        }
        Flight_Ticket* temp = new Flight_Ticket(companyName, stoi(flightNumber), country_of_origin, country_of_destination, stopOver, price, time_of_departure, time_of_arrival, date);
        cnt = cnt + add(temp);
    }
    fin.close();
    return cnt;
}             //Load all the flight-tickets from the CSV file to the HashTable

int FlightHASHTABLE::exportCSV(string path){
    ofstream fout(path);
    int cnt = 0;
    if (!fout.good())
    {
        return -1;
    }
    for(int i = 0; i < capacity; i++){
        for (MyList<HashNode>::iterator p = buckets[i].begin();
             p != buckets[i].end(); ++p){
            HashNode temp = *p;
            fout << temp.value.getCN() << ",";
            fout << temp.value.getFN() << ",";
            fout << temp.value.getCO() << ",";
            fout << temp.value.getCD() << ",";
            fout << temp.value.getSO() << ",";
            fout << temp.value.getP() << ",";
            fout << temp.value.getTD() << ",";
            fout << temp.value.getTA() << ",";
            fout << temp.value.getDate() << endl;
            cnt++;
        }
    }
    fout.close();
    return cnt;
}             //Export all the flight-tickets from the HashTable to a CSV file in an ascending order

int FlightHASHTABLE::count_collisions(){
    return collision;
}                    //return the number of collisions on the HashTable

int FlightHASHTABLE::add(Flight_Ticket* data){
    string key = data->getKey();
    long index = hashCode(key);
    HashNode newElem(key,*data);
    if(!buckets[index].empty()){
        for (MyList<HashNode>::iterator p = buckets[index].begin();
             p != buckets[index].end(); ++p){
            HashNode temp = *p;
            if (temp.getValue().getKey() != key){
                collision++;
            }
            else{
                if(temp.getValue().getCO() == newElem.getValue().getCO() &&
                   temp.getValue().getCD() == newElem.getValue().getCD() &&
                   temp.getValue().getTA() == newElem.getValue().getTA() &&
                   temp.getValue().getTD() == newElem.getValue().getTD() &&
                   temp.getValue().getSO() == newElem.getValue().getSO() &&
                   temp.getValue().getDate() == newElem.getValue().getDate() &&
                   temp.getValue().getP() == newElem.getValue().getP()
                   )
                {
                    cout << "The ticket already exists!" << endl;
                    return -1;
                }
            }
        }
        if(buckets[index].back().value.getCD() <= newElem.getValue().getCD()){
            buckets[index].addBack(newElem);
            size++;
            return 1;
        }
        for (MyList<HashNode>::iterator p = buckets[index].begin();
             p != buckets[index].end(); ++p){
            HashNode temp1 = *p;
            HashNode temp2 = p.get()->getNext()->getElem();
            if (newElem.getValue().getCD() > temp1.getValue().getCD() && newElem.getValue().getCD() <= temp2.getValue().getCD()){
                buckets[index].addAfter(p.get(), newElem);
                size++;
                return 1;
            }
            if(p == buckets[index].begin() && newElem.getValue().getCD() <= temp1.getValue().getCD()){
                buckets[index].addBefore(p.get(), newElem);
                return 1;
            }
        }
    }
    else{
        buckets[index].addBack(newElem);
        size++;
        return 1;
    }
    return -1;
}            //add new flight to the HashTable

void FlightHASHTABLE::removeRecord (string companyName, int flightNumber){
    string key = companyName + to_string(flightNumber);
    int index = hashCode(key) % capacity;
    int cnt = 0;
    for (MyList<HashNode>::iterator p = buckets[index].begin();
         p != buckets[index].end(); ++p){
        HashNode temp = *p;
        if (key_in_lower(temp.getValue().getKey()) == key_in_lower(key)){
            cnt++;
        }
    }
    if(cnt == 0){
        cout << "Not found!" << endl;
        return;
    }
    cout << cnt << " records found: " << endl;
    printASC(companyName, flightNumber);
    cout << endl << "Which record you want to delete: " ;
    string num; cin >> num;
    cnt = 0;
    for (MyList<HashNode>::iterator p = buckets[index].begin();
         p != buckets[index].end(); ++p){
        HashNode temp = *p;
        if (key_in_lower(temp.getValue().getKey()) == key_in_lower(key)){
            cnt++;
            if(cnt == stoi(num)){
                buckets[index].remove(p);
            }
        }
    }
    return;
}    //Delete a record with key from the hashtable

void FlightHASHTABLE::find(string companyName, int flightNumber){
    string key = companyName + to_string(flightNumber);
    int index = hashCode(key) % capacity;
    int cnt = 0;
    int num = 1;
    for (MyList<HashNode>::iterator p = buckets[index].begin();
         p != buckets[index].end(); ++p){
        HashNode temp = *p;
        if (key_in_lower(temp.getValue().getKey()) == key_in_lower(key)){
            cnt++;
        }
    }
    if(cnt == 0){
        cout << "Not found!" << endl;
        return;
    }
    cout << cnt << " records found: " << endl;
    
    for (MyList<HashNode>::iterator p = buckets[index].begin();
         p != buckets[index].end(); ++p){
        HashNode temp = *p;
        if (key_in_lower(temp.getValue().getKey()) == key_in_lower(key)){
            cout << num << ". ";
            cout << temp.value.getCN() << ", ";
            cout << temp.value.getFN() << ", ";
            cout << temp.value.getCO() << ", ";
            cout << temp.value.getCD() << ", ";
            cout << temp.value.getSO() << ", ";
            cout << temp.value.getP() << ", ";
            cout << temp.value.getTD() << ", ";
            cout << temp.value.getTA() << ", ";
            cout << temp.value.getDate() << endl;
            num++;
        }
    }
    return;
}        //Find and Display records with same key entered

void FlightHASHTABLE::allinday(string date){
    int num = 1;
    for(int i = 0; i < capacity; i++){
        for (MyList<HashNode>::iterator p = buckets[i].begin();
             p != buckets[i].end(); ++p){
            HashNode temp = *p;
            if(temp.value.getDate() == date){
                cout << num << ". ";
                cout << temp.value.getCN() << ",";
                cout << temp.value.getFN() << ",";
                cout << temp.value.getCO() << ",";
                cout << temp.value.getCD() << ",";
                cout << temp.value.getSO() << ",";
                cout << temp.value.getP() << ",";
                cout << temp.value.getTD() << ",";
                cout << temp.value.getTA() << ",";
                cout << temp.value.getDate() << endl;
                num++;
            }
        }
    }
}                      //Find and Display records with same day entered

void FlightHASHTABLE::printASC(string companyName, int flightNumber){
    string key = companyName + to_string(flightNumber);
    int index = hashCode(key) % capacity;
    int num = 1;
    for (MyList<HashNode>::iterator p = buckets[index].begin();
         p != buckets[index].end(); ++p){
        HashNode temp = *p;
        if (key_in_lower(temp.getValue().getKey()) == key_in_lower(key)){
            cout << num << ". ";
            cout << temp.value.getCN() << ", ";
            cout << temp.value.getFN() << ", ";
            cout << temp.value.getCO() << ", ";
            cout << temp.value.getCD() << ", ";
            cout << temp.value.getSO() << ", ";
            cout << temp.value.getP() << ", ";
            cout << temp.value.getTD() << ", ";
            cout << temp.value.getTA() << ", ";
            cout << temp.value.getDate() << endl;
            num++;
        }
    }
    return;
}          //display the collisions for the entered key in an ascending order

string FlightHASHTABLE::key_in_lower(string key){
        char temp[key.length()];
        for(int i = 0; i < key.length(); i++){
            if(isupper(int(key[i]))){
                temp[i] = tolower(int(key[i]));
            }
            else{
                temp[i] = int(key[i]);
            }
        }
    return temp;
}
// a method to change the input into lower cases to compare
