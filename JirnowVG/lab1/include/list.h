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
	bool currhead();
	void clean();
	void insert_to_head(const valtype &d);
	void insert_to_tail(const valtype &d);
	void insertup(const valtype &d);
	valtype& getcurdata();
	node<valtype>* search(const valtype &d);
	const list<valtype>& operator=(const list<valtype> &l);
	friend ostream & operator<<(ostream &out, const list<valtype> &l)
	{
		node<valtype>* t = l.head->next;
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
bool list<valtype>::currhead()
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
	delete head;
	head = NULL;
	tail = NULL;
};

template<class valtype>
void list<valtype>::insert_to_head(const valtype & d)
{
	node<valtype>* k = new node<valtype>(d);
	k->next = head->next;
	head->next = k;

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
valtype & list<valtype>::getcurdata()
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