#ifndef FlightHASHTABLE_H
#define FlightHASHTABLE_H

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include "flightticket.h"
#include "mylist.h"

using namespace std;

class HashNode
{
	private:
		string key; // key = companyName+flightNumber
		Flight_Ticket value;
	public: 
		HashNode() { this->key = " "; }
		HashNode(string key, Flight_Ticket value)
		{
			this->key = key;
			this->value = value;
		}
		string getKey() { return(key); }
		Flight_Ticket& getTicket() { return(value); }
		friend class FlightHASHTABLE;
};

//=============================================================================
class FlightHASHTABLE
{
	private:
		MyList<HashNode> *buckets;	    //List of Buckets, Please create your own List Class called MyList
		int size;					    //Current Size of HashTable
		int capacity;				    // Total Capacity of HashTable
		int collisions;					// Total Number of Collisions
		
	public:
		FlightHASHTABLE();						//constructor
		FlightHASHTABLE(int capacity);			//non-default constructor
		~FlightHASHTABLE();						//destructor
		unsigned long hashCode_1(string key); 	//implement and test different hash functions 
		unsigned long hashCode_2(string key); 
		unsigned long hashCode_3(string key); 
		int importCSV(string path); 			//Load all the flight-tickets from the CSV file to the HashTable
		int exportCSV(string path); 			//Export all the flight-tickets from the HashTable to a CSV file in an ascending order		
		int count_collisions();					//return the number of collisions on the HashTable
		int add(Flight_Ticket* data);			//add new flight to the HashTable
		void removeRecord (string companyName, int flightNumber);	//Delete a record with key from the hashtable
		void find(string companyName, int flightNumber);		    //Find and Display records with same key entered 
		void allinday(string date);  				              	//Find and Display records with same day entered
		void printASC(string companyName, int flightNumber);  		//display the collisions for the entered key in an ascending order 
};

#endif
