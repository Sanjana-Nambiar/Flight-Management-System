//=================================================================================
// Name          : DS Assignment#4 
// Author        : Sanjana Nambiar
// Version       : 1.0
// Date Created  : Apr-17-2022
// Date Modified : May-08-2022
// Description   : Flight-Ticket Management System using HASH TABLE in C++
//=================================================================================
#include<iostream>
#include<cstdlib>
#include<fstream>
#include<sstream>
#include<string>
#include<chrono>
#include"flightticket.h"
#include"flighthashtable.h"
#include"mylist.h"

//==========================================================
void listCommands()
{
	cout<<"----------------------------------"<<endl;
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
//==========================================================
int main(void)
{
	FlightHASHTABLE myFlightHASHTABLE;
	listCommands();
	cout << endl;
	string user_input;
	string command;
	string key;
	cout<<">";

	while(true)
	{
		getline(cin,user_input,'\n');

		// divide the user input into command and parameter(s)
		stringstream sstr(user_input);
		getline(sstr,command,' ');
		getline(sstr,key);

		if( command =="import") //for importing
		{ 
			int count = myFlightHASHTABLE.importCSV(key); 
			cout <<"Total "<<count<<" number of contacts has been imported\n";
		}
		else if( command =="export") //for exporting
		{ 
			int count = myFlightHASHTABLE.exportCSV(key); 
			cout <<"Total "<<count<<" number of contacts has been exported\n";
		}
		else if( command == "count_collisions"){ myFlightHASHTABLE.count_collisions(); } //for printing the number of collision
		else if( command == "add") // for adding new flight ticket
		{
			string Cname, flightNo, origin, dest, stopOver, price, Tdeparture, Tarrival, date;

			//getting the information of the new flight-ticket from the user
			cout << "Please enter the details of the Flight Ticket:\n";
			cout << "Company Name: "; getline(cin, Cname);
			cout << "Flight Number: "; getline(cin,flightNo); int flight = stoi(flightNo);
			cout << "Country of Origin: "; getline(cin, origin);
			cout << "Country of Destination "; getline(cin, dest);
			cout << "stopOver: "; getline(cin, stopOver);
			cout << "Price: "; getline(cin, price);
			cout << "Time of Departure: "; getline(cin,Tdeparture);
			cout << "Time of Arrival: "; getline(cin,Tarrival);
			cout << "Date: "; getline(cin,date);
		 
			Flight_Ticket ticket(Cname, flight, origin, dest, stopOver, price, Tdeparture, Tarrival, date);
			myFlightHASHTABLE.add(&ticket);
			cout << "Flight-ticket has been successfully added!\n";
		}
		else if( command == "delete") //for deleting a flight ticket
		{ 
			string Cname, flightNo;
			stringstream s(key);
			//dividing the key into company name and flight no.
			getline(s,Cname,','), getline(s,flightNo);

			int flight = stoi(flightNo);
			myFlightHASHTABLE.removeRecord(Cname, flight); 
			cout << "The flight-ticket has been successfully deleted!" << endl; 
		}
		else if( command =="find") //for finding a flight ticket
		{
			//using the library chrono to get the system time, to get the time taken
			std::chrono::time_point<std::chrono::system_clock> start, end;

			string Cname, flightNo;
			stringstream s(key);
			//dividing the key into company name and flight no.
			getline(s,Cname,','), getline(s,flightNo);

			int flight = stoi(flightNo);
			start = std::chrono::system_clock::now(); //getting the start time
			myFlightHASHTABLE.find(Cname, flight);
			end = std::chrono::system_clock::now(); //getting the end time 
			
			std::chrono::duration<double> diff = end - start; //getting the difference
			cout << "Time Taken: " << diff.count() << " secs \n";
		}	
		else if( command =="allinday")  //prints all the tickets in a particular date
		{ 
			myFlightHASHTABLE.allinday(key);
		}
		else if( command =="printASC") //prinst the data ascending order according to the destination country
		{ 
			string Cname, flightNo;
			stringstream s(key);
			//dividing the key into company name and flight no.
			getline(s,Cname,','), getline(s,flightNo);

			int flight = stoi(flightNo);
			myFlightHASHTABLE.printASC(Cname, flight);  
		}
		else if( command =="help") {listCommands(); }
		else if( command =="exit") {exit(-1);}
		else if( command == "") {continue;}
		else {cout <<"Invalid command !!!"<< endl; }
		cout << endl;
		cout << ">";
	}
		return 0;
}

