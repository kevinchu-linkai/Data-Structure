#ifndef FLIGHT_TICKET_H
#define FLIGHT_TICKET_H

#include <iostream>
#include <sstream>

using namespace std;
//flight ticket class and methods declaration
class Flight_Ticket
{
    private:
        string companyName;
        int flightNumber;
        string stopOver;
        string price;
        string country_of_origin;
        string country_of_destination;
        string time_of_departure;
        string time_of_arrival;
        string date;

    public:
        Flight_Ticket();
        Flight_Ticket(string companyName, int flightNumber, string country_of_origin, string country_of_destination, string stopOver, string price, string time_of_departure, string time_of_arrival, string date);
        string getCN();
        string getFN();
        string getCO();
        string getCD();
        string getSO();
        string getP();
        string getTD();
        string getTA();
        string getKey();
        string getDate();
};

#endif
