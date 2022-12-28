#ifndef MYLIST_H
#define MYLIST_H

#include<iostream>
using namespace std;

//================================ MyList ===========================
template <typename T> 
class Node
{
	private:
		T elem; //data element 
		Node* next; //Link (pointer) to the next Node
		Node* prev; //Link (pointer) to the previous Node
		template <typename T2> friend class MyList;
		
	public:
		Node(): next(NULL), prev(NULL) {}
		Node(T elem) : elem(elem),next(NULL), prev(NULL) {}
		Node<T>* getPrev() {return(prev);}
		Node<T>* getNext() {return(next);}
		T& getElem() {return(elem);}
};
//==============================================================
template <typename T> 
class MyList
{
	private:
		Node<T>* head; 	// pointer to the head of List
		Node<T>* tail; 	// pointer to the tail of List
		int size;
	public:
		MyList (); // empty list constructor
		~MyList (); // destructor to clean up all nodes
		bool empty() const; // is list empty?
		int getSize();
		Node<T>* getHead() {return(head);}
		Node<T>* getTail() {return(tail);}
		const T& front() const; // get the value (element) from front Node<T> of list
		const T& back() const;  // get the value (element) from last Node<T> of the List 
		void addBefore(Node<T> *ptr, const T& elem);	 //add a new node before ptr
		void addFront(const T& elem); // add a new node to the front of list
		void addBack(const T & elem); //add a new node to the back of the list
		void remove(Node<T>* ptr);
		void removeFront(); // remove front node from list
		void removeBack();  // remove last node from list
};

#endif