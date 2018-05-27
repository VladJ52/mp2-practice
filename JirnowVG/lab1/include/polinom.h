#pragma once
#include "monom.h"
class polinom
{
	list<monom> pol;
public:
	polinom() {}
	polinom(const polinom &p);
	polinom(const string &s);
	~polinom() {}
	const polinom& operator=(const polinom &p);
	polinom operator+(const polinom &p) const;
	polinom operator*(const polinom &p) const;
	polinom operator*(const double a) const;
	friend polinom operator*(const double d, const polinom &p) { return (p*d); }
	bool operator==(const polinom &p) const;
	bool operator!=(const polinom &p) const;
	friend ostream & operator<<(ostream &out, const polinom &p);
};
