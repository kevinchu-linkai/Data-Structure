//
//  contact.cpp
//  ass3
//
//  Created by 朱麟凱 on 2022/4/5.
//

#include "contact.h"

Contact::Contact(){
    fname = "";
    lname = "";
    email = "";
    primaryPhone = "";
    city = "";
    country = "";
    isFav = false;
}
Contact::Contact(string fname, string lname, string email, string primaryPhone, string city, string country, bool isFav){
    this->fname = fname;
    this->lname = lname;
    this->email = email;
    this->primaryPhone = primaryPhone;
    this->city = city;
    this->country = country;
    this->isFav = isFav;
}
Contact::~Contact(){
    fname = "";
    lname = "";
    email = "";
    primaryPhone = "";
    city = "";
    country = "";
    isFav = false;
}
