#ifndef FLIGHT_TICKET_H
#define FLIGHT_TICKET_H

#include<iostream>
using namespace std;

class Flight_Ticket
{
	private:
		string companyName;
		int flightNumber;
		string country_of_origin;
		string country_of_destination;
		string stopOver;
		string price;
		string time_of_departure;
		string time_of_arrival;
		string date;

	public:
		Flight_Ticket(); //default constructor
		//non default constructor
		Flight_Ticket(string companyName, int flightNumber, string country_of_origin, string country_of_destination, 
			string stopOver, string price, string time_of_departure, string time_of_arrival, string date);
		
		//getter functions 
		std::string getCompanyName();
		int getFlightNumber();
		std::string getOrigin();
		std::string getDestination();
		std::string getStopOver();
		std::string getPrice();
		std::string getTimeDep();
		std::string getTimeArrival();
		std::string getDate();
	
		//setter functions
		void setCompanyName(std::string companyName);
		void setFlightNumber(int flightNumber);
		void setOrigin(std::string country_of_origin);
		void setDestination(std::string country_of_destination);
		void setStopOver(std::string stopOver);
		void setPrice(std::string price);
		void setTimeDep(std::string time_of_departure);
		void setTimeArrival(std::string time_of_arrival);
		void setDate(std::string date);
	
		void print();//prints the flight informations	
};

#endif
