#include "polinom.h"

monom::monom(const double a, const unsigned int b)
{
	coeff = a;
	xyz = b;
}

monom::monom(const monom &m)
{
	coeff = m.coeff;
	xyz = m.xyz;
}

monom::monom(const string & s)
{
	string c = s + ' ';
	string str;
	xyz = 0;
	bool flag = true;
	int i, j = 1;
	if (c[0] == '-')
	{
		j = -1;
		c.erase(0, 1);
	}
	int len = c.length();
	for (i = 0; flag; i++)
	{
		if (((c[i] >= '0') && (c[i] <= '9')) || (c[i] == '.'))
			str = str + c[i];
		else
		{
			flag = false;
			if (str != "")
				coeff = j*atof(str.c_str());
			else
				coeff = j;
		}
	}
	for (int k = i - 1; k < len; k++)
	{
		if (c[k] == 'x')
		{
			if ((c[k + 1] >= '0') && (c[k + 1] <= '9'))
			{
				xyz += 100 * (c[k + 1] - '0');
				k++;
			}
			else
				xyz += 100;
		}
		else
			if (c[k] == 'y')
			{
				if ((c[k + 1] >= '0') && (c[k + 1] <= '9'))
				{
					xyz += 10 * (c[k + 1] - '0');
					k++;
				}
				else
					xyz += 10;
			}
			else
				if (c[k] == 'z')
					if ((c[k + 1] >= '0') && (c[k + 1] <= '9'))
					{
						xyz += (c[k + 1] - '0');
						k++;
					}
					else
						xyz += 1;
	}
}

const monom & monom::operator=(const monom & m)
{
	coeff = m.coeff;
	xyz = m.xyz;
	return *this;
}

bool monom::operator==(const monom & m) const
{
	return (xyz == m.xyz);
}

bool monom::operator!=(const monom & m) const
{
	return (xyz != m.xyz);
}

bool monom::operator<(const monom & m) const
{
	return (xyz < m.xyz);
}

bool monom::operator>(const monom & m) const
{
	return (xyz > m.xyz);
}

monom monom::operator*(const double d) const
{
	monom m(coeff*d, xyz);
	return m;
}

monom monom::operator*(const monom & m) const
{
	if (xyz + m.xyz > 999)
		throw "Error <can't multiply>";
	else
	{
		monom mon(coeff * m.coeff, xyz + m.xyz);
		return mon;
	}
}


polinom::polinom(const polinom &p)
{
	pol = p.pol;
}

polinom::polinom(const string &s)
{
	string c = s + '+';
	string mon;
	bool min = false;
	int len = c.length();
	for (int i = 0; i < len; i++)
	{
		if ((c[i] != '+') && (c[i] != '-'))
			mon = mon + c[i];
		else
		{
			if (mon != "")
			{
				if (min)
					mon = '-' + mon;
				monom m(mon);
				mon = "";
				node<monom>* k = pol.search(m);
				if (k == NULL)
					pol.insertup(m);
				else
					k->data.coeff += m.coeff;
			}
			if (c[i] == '-')
				min = true;
			else
				min = false;
		}
	}
}

const polinom & polinom::operator=(const polinom & p)
{
	pol = p.pol;
	return *this;
}

polinom polinom::operator+(const polinom & p) const
{
	list<monom> currpol = pol;
	list<monom> thispol = p.pol;
	currpol.gotohead();
	thispol.gotohead();
	currpol.gotonext();
	thispol.gotonext();
	polinom pp;
	while ((!currpol.currhead()) && (!thispol.currhead()))
	{
		if (currpol.getcurdata() > thispol.getcurdata())
		{
			pp.pol.insert_to_tail(currpol.getcurdata());
			currpol.gotonext();
		}
		else
		{
			if (currpol.getcurdata() < thispol.getcurdata())
			{
				pp.pol.insert_to_tail(thispol.getcurdata());
				thispol.gotonext();
			}
			else
			{
				monom m(currpol.getcurdata().coeff + thispol.getcurdata().coeff, currpol.getcurdata().xyz);
				if (m.coeff != 0.0)
					pp.pol.insert_to_tail(m);
				currpol.gotonext();
				thispol.gotonext();
			}
		}
	}
	while (!currpol.currhead())
	{
		pp.pol.insert_to_tail(currpol.getcurdata());
		currpol.gotonext();
	}
	while (!thispol.currhead())
	{
		pp.pol.insert_to_tail(thispol.getcurdata());
		thispol.gotonext();
	}
	return pp;
}

polinom polinom::operator*(const polinom& p) const
{
	list<monom> currpol=pol;
	list<monom> thispol = p.pol;
	currpol.gotohead();
	thispol.gotohead();
	currpol.gotonext();
	thispol.gotonext();
	polinom pp;
	while (!currpol.currhead())
	{
		while (!thispol.currhead())
		{
			monom m(currpol.getcurdata() * thispol.getcurdata());
			if (m.coeff != 0.0)
			{
				node<monom>* k = pp.pol.search(m);
				if (k == NULL)
					pp.pol.insertup(m);
				else
				{
					k->data.coeff += m.coeff;
					if (k->data.coeff == 0.0)
						pp.pol.del(k);
				}
			}
			thispol.gotonext();
		}
		currpol.gotonext();
		thispol.gotohead();
		thispol.gotonext();
	}
	return pp;
}

polinom polinom::operator*(const double a) const
{
	list<monom> currpol = pol;
	polinom p;
	if (a != 0)
	{
		currpol.gotohead();
		currpol.gotonext();
		while (!currpol.currhead())
		{
			p.pol.insert_to_tail(currpol.getcurdata()*a);
			currpol.gotonext();
		}
	}
	return p;
}

bool polinom::operator==(const polinom &p) const
{
	if (this != &p)
	{
		bool flag = true;
		polinom copypolinom(*this), copyp(p);
		copypolinom.pol.gotohead();
		copypolinom.pol.gotonext();
		copyp.pol.gotohead();
		copyp.pol.gotonext();
		while ((flag) && (!copypolinom.pol.currhead()) && (!copyp.pol.currhead()))
		{
			monom a = copypolinom.pol.getcurdata();
			monom b = copyp.pol.getcurdata();
			if (a == b)
			{
				if (a.coeff != b.coeff)
					flag = false;
			}
			else
				flag = false;
			copypolinom.pol.gotonext();
			copyp.pol.gotonext();
		}
		if ((!copypolinom.pol.currhead()) || (!copyp.pol.currhead()))
			flag = false;
		return flag;
	}
	else
		return true;
}

bool polinom::operator!=(const polinom &p) const
{
	return !(*this == p);
}

ostream & operator<<(ostream & out, const monom & m)
{
	out << m.coeff << "*x" << m.xyz / 100 << "*y" << (m.xyz / 10) % 10 << "*z" << m.xyz % 10;
	return out;
}

ostream & operator<<(ostream & out, const polinom & p)
{
	out << p.pol;
	return out;
}
