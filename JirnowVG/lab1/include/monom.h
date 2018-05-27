#ifndef __AISD_MONOM__
#define __AISD_MONOM__

#pragma once
#include "list.h"
#include "node.h"

using namespace std;

class monom
{
public:
	double coeff;
	unsigned int xyz;
	monom(const double a = 0.0, const unsigned int b = 0);
	monom(const monom &m);
	monom(const string &s);
	~monom() {}
	const monom& operator=(const monom &m);
	bool operator==(const monom &m) const;
	bool operator!=(const monom &m) const;
	bool operator<(const monom &m) const;
	bool operator>(const monom &m) const;
	monom operator*(const double d) const;
	friend monom operator*(const double d, const monom &m) { return (m * d); }
	monom operator*(const monom &m) const;
	friend ostream & operator<<(ostream &out, const monom &m);
};

#endif
