#ifndef __AISD_LIST__
#define __AISD_LIST__

#pragma once
#include "node.h"

template <class valtype>
class list
{
	node<valtype> *head;
	node<valtype> *tail;
	node<valtype> *current;
public:
	list();
	list(const list<valtype> &l);
	~list();
	void gotohead();
	void gotonext();
	bool currhead() const;
	void clean();
	void del(node<valtype> *n);
	void insert_to_tail(const valtype &d);
	void insertup(const valtype &d);
	valtype& getcurdata() const;
	node<valtype>* search(const valtype &d);
	const list<valtype>& operator=(const list<valtype> &l);
	friend ostream & operator<<(ostream &out, const list<valtype> &l)
	{
		node<valtype>* t = l.head->next;
		if (t == l.head)
			out << "0";
		while (t != l.head)
		{
			out << t->data << " ";
			t = t->next;
		}
		return out;
	}
};

template<class valtype>
list<valtype>::list()
{
	head = new node<valtype>();
	tail = head;
	head->next = head;
};

template<class valtype>
list<valtype>::list(const list<valtype>& l)
{
	head = new node<valtype>();
	node<valtype>* k = head;
	node<valtype>* kk = l.head->next;
	while (kk != l.head)
	{
		k->next = new node<valtype>(kk->data);
		tail = k->next;
		k = k->next;
		kk = kk->next;
	}
	tail->next = head;
};

template<class valtype>
list<valtype>::~list()
{
	clean();
	delete head;
};

template<class valtype>
void list<valtype>::gotohead() 
{
	current = head;
};

template<class valtype>
void list<valtype>::gotonext() 
{
	current = current->next;
};

template<class valtype>
bool list<valtype>::currhead() const
{
	return (current == head);
};

template<class valtype>
void list<valtype>::clean()
{
	node<valtype>* k = head->next;
	while (k != head)
	{
		node<valtype>* kk = k->next;
		delete k;
		k = kk;
	}
	head->next=head;
	tail = head;
};

template<class valtype>
void list<valtype>::del(node<valtype> *n)
{
	node<valtype> *k = head;
	while (k->next != n)
		k = k->next;
	k->next = n->next;
	delete n;
};

template<class valtype>
void list<valtype>::insert_to_tail(const valtype & d)
{
	node<valtype>* k = new node<valtype>(d);
	tail->next = k;
	tail = k;
	tail->next = head;
};

template<class valtype>
void list<valtype>::insertup(const valtype & d)
{
	node<valtype>* k = head->next;
	node<valtype>* kk = head;
	while ((k != head) && (k->data > d))
	{
		kk = k;
		k = k->next;
	}
	node<valtype>* kkk = new node<valtype>(d);
	kkk->next = k;
	kk->next = kkk;
	if (k == head)
		tail = kkk;
};

template<class valtype>
valtype & list<valtype>::getcurdata() const
{
	return current->data;
};

template<class valtype>
node<valtype>* list<valtype>::search(const valtype & d)
{
	node<valtype> *k = head->next;
	while ((k != head) && (k->data != d))
		k = k->next;
	if (k != head)
		return k;
	else
		return NULL;
};

template<class valtype>
const list<valtype>& list<valtype>::operator=(const list<valtype>& l)
{
	clean();
	head = new node<valtype>();
	node<valtype>* k = head;
	node<valtype>* kk = l.head->next;
	tail = head;
	while (kk != l.head)
	{
		k->next = new node<valtype>(kk->data);
		tail = k->next;
		k = k->next;
		kk = kk->next;
	}
	tail->next = head;
	return *this;
};

#endif