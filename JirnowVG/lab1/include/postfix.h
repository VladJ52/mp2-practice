#pragma once
#include "list.h"
#include "node.h"

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
	monom operator*(const monom &m) const;
	friend ostream & operator<<(ostream &out, const monom &m);
};

class polinom
{
	list<monom> pol;
public:
	polinom() {}
	polinom(const polinom &p);
	polinom(const string &s);
	~polinom() {}
	const polinom& operator=(const polinom &p);
	polinom operator+(polinom &p);
	polinom operator*(polinom &p);
	polinom operator*(const double a);
	//friend polinom operator*(const double d, const polinom &p);
	bool operator==(polinom &p);
	bool operator!=(polinom &p);
	friend ostream & operator<<(ostream &out, const polinom &p);
};

double rankn(const double a, const int i);
double convertn(const string &s);