
//=================================================================================
// Name         : DS Assignment#4 
// Author       : 
// Version      : 1.0
// Date Created : Apr-17-2022
// Date Modified: 
// Description  : Starter Code for Flight-Ticket Management System using HASH TABLE in C++
//=================================================================================
#include<iostream>
#include<cstdlib>
#include<sstream>
#include<fstream>

#include "flighthashtable.h"

//==========================================================
void listCommands()
{
	cout<<"\n----------------------------------"<<endl;
	cout<<"import <path>      	:Import flight-tickets from a CSV file"<<endl
		<<"export <path>      	:Export flight-tickets to a CSV file"<<endl
		<<"count_collisions   	:Print number of collisions"<<endl
		<<"add                	:Add a new flight-ticket"<<endl
		<<"delete <key>       	:Delete a flight-ticket"<<endl
		<<"find <key>         	:Find a flight-ticket's details"<<endl
		<<"allinday <date>    	:Display all flight-tickets in a day"<<endl
		<<"printASC <key>     	:Print flight-tickets in ascending order"<<endl
		<<"exit               	:Exit the program"<<endl;
}

string input_checker(string input){
    for(int i = 0; i < input.length(); i++){
        if(isupper(int(input[i]))){
            input[i] = tolower(int(input[i]));
        }
    }
    return input;
}

string date_checker(string input){
    if(input.length() == 5){
        for(int i = 2; i < input.length(); i++){
            input[i] = tolower(int(input[i]));
        }
        input[2] = toupper(int(input[2]));
    }
    else{
        for(int i = 1; i < input.length(); i++){
            input[i] = tolower(int(input[i]));
        }
        input[1] = toupper(int(input[1]));
    }
    return input;
}
//==========================================================
int main(void)
{
	FlightHASHTABLE myFlightHASHTABLE(126683);
    string user_input;
    string command;
    string CN;
    string FN;
    string key;
	while(true)
	{
        listCommands();
        cout<<">";
        getline(cin,user_input);
        
        // parse userinput into command and parameter(s)
        stringstream sstr(user_input);
        getline(sstr,command,' ');
        getline(sstr,CN,',');
        getline(sstr,FN);
        if( command =="find"){
            cout << CN << endl;
            myFlightHASHTABLE.find(CN, stoi(FN));
            fflush(stdin);
        }
        //call add function when the command is add
        else if( command =="add" or command =="a"){
            fflush(stdin);
            string companyName;
            cout << "Please enter the details of the contact:" << endl
            << "Company Name: "; cin >> companyName;

            string flightNumber;
            while(true){
                cout << "Flight Number: "; cin >> flightNumber;
                int i = 0;
                for(i = 0; i < flightNumber.length(); i++){
                    if(isdigit(flightNumber[i]) == false){
                        cout << "Flight Number can only be composed of numbers, please enter another input:"
                        << endl;
                        break;
                    }
                }
                if(i == flightNumber.length()){
                    break;
                }
            }
            
            string country_of_origin;
            cout << "Country of Origin: "; cin >> country_of_origin;

            string country_of_destination;
            cout << "Country of Destination: "; cin >> country_of_destination;

            string stopOver;
            cout << "Stopover: "; cin >> stopOver;

            string price;
            cout << "Price: "; cin >> price;

            string time_of_departure;
            cout << "Time of Departure: "; cin >> time_of_departure;

            string time_of_arrival;
            cout << "Time of Arrival: "; cin >> time_of_arrival;

            string date;
            cout << "Date: "; cin >> date;
            
            Flight_Ticket* data = new Flight_Ticket(companyName, stoi(flightNumber), country_of_origin, country_of_destination, stopOver, price, time_of_departure, time_of_arrival, date);
            int state = myFlightHASHTABLE.add(data);
            if(state == 1){
                cout << "Flight " << data->getCN() << " " << data->getFN()
                << " has been added successfully!" << endl;
            }
            fflush(stdin);
        }
        //call delete function when the command is delete
        else if( command =="delete"){
            myFlightHASHTABLE.removeRecord(CN, stoi(FN));
            fflush(stdin);
        }
        //call allinday function when the command is allinday
        else if( command =="allinday"){
            CN = date_checker(CN);
            myFlightHASHTABLE.allinday(CN);
            fflush(stdin);
        }
        //call count collision function when the command is count_collisions
        else if( command =="count_collisions" or command == "c"){
            cout << "There are " << myFlightHASHTABLE.count_collisions() << " collisions!" << endl;
        }
        //call printASC function when the command is printASC
        else if( command =="printASC"){
            CN = input_checker(CN);
            myFlightHASHTABLE.printASC(CN, stoi(FN));
            fflush(stdin);
        }
        //call import function when the command is import
        else if( command =="import"){
            int state = 0;
            state = myFlightHASHTABLE.importCSV(CN);
            if (state == -1)
            {
                cout << "Fail to import the file!" << endl;
            }
            else{
                cout << state << " flight tickets imported!" << endl;
            }
        }
        //call export function when the command is export
        else if( command =="export"){
            int state = 0;
            state = myFlightHASHTABLE.exportCSV(CN);
            if (state == -1)
            {
                cout << "Fail to export the file!" << endl;
            }
            else{
                cout << state << " flight tickets exported!" << endl;
            }
        }
        //call exit function when the command is exit
        else if( command =="exit"){
            break;
        }
        //call listCommands function when the command is help
        else if( command == "help") listCommands();
        else {
            cout<<"Invalid command !!!"<<endl;
        }
        fflush(stdin);
    }
	return 0;
}
