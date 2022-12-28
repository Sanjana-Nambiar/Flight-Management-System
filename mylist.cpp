#include<iostream>
#include<algorithm>
#include"flighthashtable.h"
#include"mylist.h"
using namespace std;

//===========================================================
template <typename T>
MyList<T>::MyList ()
{
	this->head = new Node<T>();
	this->tail = new Node<T>();
	this->head->next = tail;
	this->tail->prev = head;
	this->size = 0;
}
template <typename T>
MyList<T>::~MyList () // destructor to clean up all nodes
{
	while(!empty())
		removeFront();
	delete head;
    delete tail;
}
template <typename T>
bool MyList<T>::empty() const // is list empty?
{
	return this->head->next == tail;
}
template <typename T> 
int MyList<T>::getSize()
{
    return size;
}
template <typename T>
const T& MyList<T>::front() const // get front element
{
	if(!empty())
		return this->head->next->elem;
	else
		throw runtime_error("List is Empty");
}
template <typename T>
const T& MyList<T>::back() const // get front element
{
	if(!empty())
		return this->tail->prev->elem;
	else
		throw runtime_error("List is Empty");
}
template <typename T>
void MyList<T>::addBefore(Node<T> *ptr, const T& elem)
{
	Node<T> *tmp = new Node<T>(elem);
	tmp->next = ptr;
	tmp->prev = ptr->prev;
	ptr->prev->next = tmp;
	ptr->prev = tmp;
	size++;
}
template <typename T>
void MyList<T>::addFront(const T& elem) // add to front of list
{
	addBefore(this->head->next, elem);
}
template <typename T>
void MyList<T>::addBack(const T& elem) // add to Back of the list
{
	addBefore(this->tail, elem);
}
template <typename T> 
void MyList<T>::remove(Node<T>* ptr) 
{
	if(!empty())
	{
		Node<T>* tmp1 = ptr->prev;
	    Node<T>* tmp2 = ptr->next;
	    tmp1->next = tmp2;
	    tmp2->prev = tmp1;
	    delete ptr;
	    size--;
	}
	else
		throw runtime_error("List is Empty");   
}
template <typename T>
void MyList<T>::removeFront() // remove front item from list
{
	remove(head->next);
}
template <typename T>
void MyList<T>::removeBack() // remove last item from list
{
	remove(tail->prev);
}
//============================================================
 
template class MyList<HashNode>;