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
	node(const valtype &c, const node<valtype> *n);
	~node() {}
	const node<valtype>& operator=(const node<valtype> &n);
	const bool operator==(const node<valtype> &n) const;
	friend ostream & operator<<(ostream &out, const node<valtype> &n)
	{
		out << n.data;
		return out;
	}
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
node<valtype>::node(const valtype &c, const node<valtype> *n)
{
	data = c;
	next = n;
};

template<class valtype>
const node<valtype>& node<valtype>::operator=(const node<valtype> &n)
{
	data = n.data;
	next = n.next;
	return *this;
};

template<class valtype>
inline const bool node<valtype>::operator==(const node<valtype>& n) const
{
	if ((data == n.data) && (next == n.next))
		return true;
	else
		return false;
};

#endif