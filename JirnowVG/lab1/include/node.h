#ifndef __AISD_NODE__
#define __AISD_NODE__

#pragma once
#include <iostream>
#include <string>
using namespace std;

template <class valtype>
class node
{
public:
	valtype data;
	node <valtype> *next;
	node() { next = NULL; }
	node(const node<valtype> &n);
	node(const valtype &c);
	~node() {}
	const node<valtype>& operator=(const node<valtype> &n);
	bool operator==(const node<valtype> &n) const;
};

template<class valtype>
node<valtype>::node(const node<valtype>& n)
{
	data = n.data;
	next = n.next;
};

template<class valtype>
node<valtype>::node(const valtype &c)
{
	data = c;
	next = NULL;
};


template<class valtype>
const node<valtype>& node<valtype>::operator=(const node<valtype> &n)
{
	data = n.data;
	next = n.next;
	return *this;
};

template<class valtype>
inline bool node<valtype>::operator==(const node<valtype>& n) const
{
	if ((data == n.data) && (next == n.next))
		return true;
	else
		return false;
};

#endif