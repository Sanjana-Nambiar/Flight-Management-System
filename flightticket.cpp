#include<iostream>
#include "flightticket.h"

using namespace std;

Flight_Ticket::Flight_Ticket() //default constructor
{
	this->companyName = " ";
	this->flightNumber = 0;
	this->country_of_origin = " ";
	this->country_of_destination = " ";
	this->stopOver = " ";
	this->price = " ";
	this->time_of_departure = " ";
	this->time_of_arrival = " ";
	this->date = " ";
}

//non-default constructor
Flight_Ticket::Flight_Ticket(string companyName, int flightNumber, string country_of_origin, string country_of_destination, 
			string stopOver, string price, string time_of_departure, string time_of_arrival, string date)
{
	this->companyName = companyName;
	this->flightNumber = flightNumber;
	this->country_of_origin = country_of_origin;
	this->country_of_destination = country_of_destination;
	this->stopOver = stopOver;
	this->price = price;
	this->time_of_departure = time_of_departure;
	this->time_of_arrival = time_of_arrival;
	this->date = date;
}
		
//getter functions 
string Flight_Ticket::getCompanyName() { return(companyName); }
int Flight_Ticket::getFlightNumber() { return(flightNumber); }
string Flight_Ticket::getOrigin() { return(country_of_origin); }
string Flight_Ticket::getDestination() { return(country_of_destination); }
string Flight_Ticket::getStopOver() { return(stopOver); }
string Flight_Ticket::getPrice() { return(price); }
string Flight_Ticket::getTimeDep() { return(time_of_departure);}
string Flight_Ticket::getTimeArrival() { return(time_of_arrival); }
string Flight_Ticket::getDate() { return(date); }

//setter functions
void Flight_Ticket::setCompanyName(string companyName) { this->companyName = companyName; }
void Flight_Ticket::setFlightNumber(int flightNumber) { this->flightNumber = flightNumber; }
void Flight_Ticket::setOrigin(string country_of_origin) { this->country_of_origin = country_of_origin; }
void Flight_Ticket::setDestination(string country_of_destination) {	this->country_of_destination = country_of_destination; }
void Flight_Ticket::setStopOver(string stopOver) { this->stopOver = stopOver; }
void Flight_Ticket::setPrice(string price) { this->price = price; }
void Flight_Ticket::setTimeDep(string time_of_departure) { this->time_of_departure = time_of_departure; }
void Flight_Ticket::setTimeArrival(string time_of_arrival) { this->time_of_arrival = time_of_arrival; }
void Flight_Ticket::setDate(string date) { this->date = date; }

void Flight_Ticket::print()//helps to print the contact informations
{
	cout << companyName << ", " << flightNumber << ", " << country_of_origin << ", " << country_of_destination << ", " << stopOver << ", "
	 << price << ", " << time_of_departure << ", " << time_of_arrival << ", " << date << endl;
}	