#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cctype>
#include"flightticket.h"
#include"flighthashtable.h"

using namespace std;

// different array size used according to the number of elements in the file.
// Flight-ticket1k.csv - 990*1.25 = 1237.5 -> 1249
// Flight-ticket10k.csv - 9922*1.25 = 12402.5 ->12409
// Flight-ticket100k.csv – 99182*1.25 = 123977.5 ->123979

FlightHASHTABLE::FlightHASHTABLE()
{
	buckets = new MyList<HashNode>[1249]; //predefining the array size according to 1k file 
	this->capacity = 1249;
	this->size = 0;   
	this->collisions = 0;
}
FlightHASHTABLE::FlightHASHTABLE(int capacity)
{
	buckets = new MyList<HashNode>[capacity];	 
	this->capacity = capacity;
	this->size = 0;
	this->collisions = 0;
}
FlightHASHTABLE::~FlightHASHTABLE()
{
	delete [] buckets;
}
unsigned long FlightHASHTABLE::hashCode_1(string key)
{
	string hashKey = key;
	unsigned int sum = 0;
	unsigned int coeff = 53;
	int myHash = 0;

	//summing the ascii code and multiply with the coeff raised to the position
	for(int i = 0; i<hashKey.length(); i++)
	{
		myHash = (unsigned int)hashKey[i];
		sum += myHash*coeff^i;
	}
	return sum % this->capacity; //returning the index 
} 		 
unsigned long FlightHASHTABLE::hashCode_2(string key)
{
	unsigned int myHash = 0;
	unsigned int div = 33;
	unsigned int coeff = 97;

	//This function involves a series of operations
	//first cycle-shift the myHash by 19 bits then minus myHash from it
	//finally multiplying and dividing by prime numbers
    for (int i = 0; i < key.length(); i++)
    {
        myHash = coeff*(((myHash << 19) - myHash)/div);
        myHash += (unsigned int) key[i]; 
    }

    return myHash % this->capacity;	//returning the index 
} 		 
unsigned long FlightHASHTABLE::hashCode_3(string key)
{
	unsigned int myHash = 0;

	//This function completely uses bit wise operations
	//using the left cycle-shift, right cycle-sift and bitwise or
	for (int i = 0; i < key.length(); i++) 
	{
		myHash = (myHash << 5) | (myHash >> 27);
		myHash += (unsigned int) key[i]; 
	}
	return myHash % this->capacity;	//returning the index 
} 		 
int FlightHASHTABLE::importCSV(string path)
{
	int check = 0;
	string delim;
	string Cname, flightNo, origin, dest, stopOver, price, Tdeparture, Tarrival, date;
	//string corrected_date;

	int flight;
	ifstream TicketInfo(path, ios::in);//declares an ifstream object
	
    if (TicketInfo.is_open())//opens the file
    {
        string line;
         
        getline(TicketInfo, line);  //skip first line
        while( getline(TicketInfo, line) )//till last line
        { 
            stringstream s(line);
            //gets the word till ',' here comma is taken as the delimiter
            getline(s,Cname,','), getline(s,flightNo,','), getline(s,origin,','), getline(s,dest,','), getline(s,stopOver,','),
            getline(s,price,','), getline(s,Tdeparture,','), getline(s,Tarrival,','), getline(s,date); //getline(s, delim, ' ');
            date.resize(6);

            flight = stoi(flightNo);//converts string to integer
            Flight_Ticket ticket(Cname, flight, origin, dest, stopOver, price, Tdeparture, Tarrival, date);
            cout<< check+1 <<". " ; ticket.print();
            
            add(&ticket);
            check++; //counts the number of elements imported
        }
	}
	if(check == 0) return -1; 
	return (check);
}
int FlightHASHTABLE::exportCSV(string path)
{
	int check = 0;

	Node<HashNode>* curr; //declaring a node to iterate over the list
	ofstream fout(path, ios::app); //declaring a ofstream file fout
	if(fout)
	{
		for(int i = 0; i<capacity ; i++)
		{
			curr = buckets[i].getHead()->getNext();//declaring a node to iterate over the list

			while(curr->getNext() != NULL)//iterates till the end of the list 
		    {
		    	Flight_Ticket FT = curr->getElem().getTicket();
		        fout << FT.getCompanyName() <<", "<< FT.getFlightNumber() <<", "<< FT.getOrigin() <<", "<< FT.getDestination() <<", "<< FT.getStopOver() 
		        <<", " << FT.getPrice() <<", "<< FT.getTimeDep() <<", " << FT.getTimeArrival() <<", " << FT.getDate() <<endl;
		        
		        curr = curr->getNext();
		        check++; //counts the number of elements exported
		    }
		}
		fout.close();
	}
	else
	{
		perror("Error::");//for printing error
		return -1;
	}
	return (check);
}	
int FlightHASHTABLE::count_collisions()
{
	cout << "Total Number of Collisions is " << collisions << endl;
	return this->collisions;
}	
int FlightHASHTABLE::add(Flight_Ticket* data)
{
	//getting the company name and the flight number
	string compName = data->getCompanyName();
	int flightNo = data->getFlightNumber();

	//converting all the upper case characters to lower case 
	for (int i = 0; i < compName.length(); i++) { compName[i] = tolower(compName[i]); }
	string flight = to_string(flightNo);
	string key = compName + flight; //getting the key

	int code = hashCode_3(key);
	while(code>capacity) { code %= capacity; }
		
	HashNode temp(key, *data);
	buckets[code].addBack(temp); //pushing back the element to the list

	Node<HashNode>* curr = buckets[code].getHead()->getNext();//declaring a node to iterate over the list
	while(curr->getNext() != NULL)//iterates till the end of the list 
    {
        if (curr->getElem().getKey() == key)
        {
        	curr = curr->getNext();
        	continue;
        }
        else
        {
        	collisions++;
        	curr = curr->getNext();
        }
    }
	// if(buckets[code].getSize() > 1)  
	// {
	// 	collisions ++;//to count the number collisions
	// }
	size++;

	return 0;
}
void FlightHASHTABLE::removeRecord (string companyName, int flightNumber)
{
	string compName = companyName;
	int flightNo = flightNumber;

	for (int i = 0; i < compName.length(); i++) { compName[i] = tolower(compName[i]); }
	string flight = to_string(flightNo);
	string key = compName + flight; //getting the key

	// get the hash code of key
	int code = hashCode_3(key);
	while(code>capacity) { code %= capacity; }

	int num = 0;
    Node<HashNode>* curr = buckets[code].getHead()->getNext();//declaring a node to iterate over the list
	int BucketSize = buckets[code].getSize();

	Flight_Ticket* arr = new Flight_Ticket[BucketSize]; //temporary array

    while(curr->getNext() != NULL)//iterates till the end of the list 
    {
        if (curr->getElem().getKey() == key)
        {   
            arr[num] = curr->getElem().getTicket();
            buckets[code].remove(curr);//deletes the class using the node 
            num++;
        }
        curr = curr->getNext();
    }
    if(num == 0) { cout<<"Not Found!\n"; return;}

    cout << num << " Records Found: \n";
    for(int i = 0; i<num; i++)
    {
    	cout << i+1 <<". ";
    	arr[i].print(); //prints the information found
    }

    int todel;
    cout << "Please select the record you want to delete: "; cin >> todel; 
    for(int i = todel-1; i<num-1; i++)
       	arr[i] = arr[i+1]; //deletes the element from the array

    for(int i = 0; i<num-1; i++)
       	add(&arr[i]); //add back all the elements
    
    size--;
	return;
}	
void FlightHASHTABLE::find(string companyName, int flightNumber)	
{
	string compName = companyName;
	int flightNo = flightNumber;

	for (int i = 0; i < compName.length(); i++) { compName[i] = tolower(compName[i]); }
	string flight = to_string(flightNo);
	string key = compName + flight; //get the key
	
	// get the hash code of key
	int code = hashCode_3(key);
	while(code>capacity) { code %= capacity; }

	int num = 1;
	Node<HashNode>* curr = buckets[code].getHead()->getNext();//declaring a node to iterate over the list
 
    cout<<"The following are the records found: \n";
    while(curr->getNext() != NULL)//iterates till the end of the list 
    {
        if (curr->getElem().getKey() == key)
        {   
        	cout << "   " << num;
        	cout << "\tCompany Name: " << curr->getElem().getTicket().getCompanyName() << endl;
			cout << "\tFlight Number: " << curr->getElem().getTicket().getFlightNumber() << endl;
			cout << "\tCountry of Origin: " << curr->getElem().getTicket().getOrigin() << endl;
			cout << "\tCountry of Destination: " << curr->getElem().getTicket().getDestination() << endl;
			cout << "\tStopover: " << curr->getElem().getTicket().getStopOver() << endl;
			cout << "\tPrice: " << curr->getElem().getTicket().getPrice() << endl;
			cout << "\tTime of Departure: " << curr->getElem().getTicket().getTimeDep() << endl;
			cout << "\tTime of Arrival: " << curr->getElem().getTicket().getTimeArrival() << endl;
			cout << "\tDate: " << curr->getElem().getTicket().getDate() << endl;
			num++;
	    }
        curr = curr->getNext();
    }
	if(num == 1) {cout<<"Not Found!\n";}
	return;
}
void FlightHASHTABLE::allinday(string date)
{
	int num = 1;
	Node<HashNode>* curr;
	cout << "Records Found: \n";
	for(int i = 0; i<capacity ; i++)//this loop runs through all the elements in the hash array
	{
		curr = buckets[i].getHead()->getNext();//declaring a node to iterate over the list

		while(curr->getNext() != NULL)//iterates till the end of the list 
	    {  
	        if (curr->getElem().getTicket().getDate() == date)
	        { 
	        	cout << num << ". ";
	        	curr->getElem().getTicket().print();
	        	num++;
	        }
	        curr = curr->getNext();
	    }
	}

	if(num == 1) {cout<<"Not Found!\n";}
	return;
}
void FlightHASHTABLE::printASC(string companyName, int flightNumber)
{
	string compName = companyName;
	int flightNo = flightNumber;

	for (int i = 0; i < compName.length(); i++) { compName[i] = tolower(compName[i]); }
	string flight = to_string(flightNo);
	string key = compName + flight; //get the key

	// get the hash code of key
	int code = hashCode_3(key);
	while(code>capacity) { code %= capacity; }

	Node<HashNode>* curr = buckets[code].getHead()->getNext();//declaring a node to iterate over the list
	int BucketSize = buckets[code].getSize();

	Flight_Ticket* arr = new Flight_Ticket[BucketSize];
	int num = 0;
	while(curr->getNext() != NULL)//iterates till the end of the list 
    {
        if (curr->getElem().getKey() == key)
        {   
        	arr[num] = curr->getElem().getTicket();
        	num++;
        }
        curr = curr->getNext();
    }
    if(num == 0) {cout<<"Not Found!\n"; return;}

	int m;
    Flight_Ticket temp; //creating a temporary array 

	//sorting the array according to the country of Destination
    for (int k = 0; k < num - 1; k++) 
    {
        m = k;
        for (int j = k + 1; j < num; j++)
        {
            if (arr[j].getDestination() < arr[m].getDestination())
                m = j;
        }            
        //swaping the words
        temp = arr[m];
        arr[m] = arr[k];
        arr[k] = temp;
    }

	cout << "Records Found: \n";
	for (int i = 0; i < num; i++)
 	{
 		cout << i+1 <<". ";
 		arr[i].print(); //printing the sorted array of flight tickets
 	}

	return;
}