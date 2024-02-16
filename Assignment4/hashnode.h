#ifndef hashnode_h
#define hashnode_h
#include "flightticket.h"
class HashNode
{
    private:
        string key; // key = companyName+flightNumber
        Flight_Ticket value;
    public:
        HashNode(string key, Flight_Ticket value)
        {
            this->key = key;
            this->value = value;
        }
        HashNode(){
            key = "";
            value = Flight_Ticket();
        }
        Flight_Ticket getValue(){
            return value;
        }
        friend class FlightHASHTABLE;
};

#endif /* hashnode_h */
