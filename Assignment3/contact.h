#ifndef CONTACT_H
#define CONTACT_H

#include<iostream>
using namespace std;

class Contact
{
    protected:
        string fname;
        string lname;
        string email;
        string primaryPhone;
        string city;
        string country;
        bool isFav;

    public:
        Contact();
        ~Contact();
        Contact(string fname, string lname, string email, string primaryPhone, string city, string country, bool isFav);
        friend class ContactBST;
        friend int main(void);
};

#endif
