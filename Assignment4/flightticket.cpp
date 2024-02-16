#include "flightticket.h"
#include <iostream>
#include <sstream>

using namespace std;
//flight ticket class and methods defination
Flight_Ticket::Flight_Ticket()
{
    companyName = "";
    flightNumber = 0;
    country_of_origin = "";
    country_of_destination = "";
    stopOver = "";
    price = "";
    time_of_departure = "";
    time_of_arrival = "";
    date = "";
}

Flight_Ticket::Flight_Ticket(string CN, int FN, string CO, string CD, string SO, string P, string TD, string TA, string D)
{
    companyName = CN;
    flightNumber = FN;
    country_of_origin = CO;
    country_of_destination = CD;
    stopOver = SO;
    price = P;
    time_of_departure = TD;
    time_of_arrival = TA;
    date = D;
}

string Flight_Ticket::getCN(){return this->companyName;}
string Flight_Ticket::getFN(){return to_string(this->flightNumber);}
string Flight_Ticket::getCO(){return this->country_of_origin;}
string Flight_Ticket::getCD(){return this->country_of_destination;}
string Flight_Ticket::getSO(){return this->stopOver;}
string Flight_Ticket::getP(){return this->price;}
string Flight_Ticket::getTD(){return this->time_of_departure;}
string Flight_Ticket::getTA(){return this->time_of_arrival;}
string Flight_Ticket::getKey(){return getCN()+getFN();}
string Flight_Ticket::getDate(){return this->date;}
