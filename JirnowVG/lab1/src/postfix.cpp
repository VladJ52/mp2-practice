#include "postfix.h"

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
				coeff = j*convertn(str);
			else
				coeff = 1;
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

polinom polinom::operator+(polinom & p)
{
	pol.gotohead();
	p.pol.gotohead();
	pol.gotonext();
	p.pol.gotonext();
	polinom pp;
	while ((!pol.currhead()) && (!p.pol.currhead()))
	{
		if (pol.getcurdata() > p.pol.getcurdata())
		{
			pp.pol.insert_to_tail(pol.getcurdata());
			pol.gotonext();
		}
		else
		{
			if (pol.getcurdata() < p.pol.getcurdata())
			{
				pp.pol.insert_to_tail(p.pol.getcurdata());
				p.pol.gotonext();
			}
			else
			{
				monom m(pol.getcurdata().coeff + p.pol.getcurdata().coeff, pol.getcurdata().xyz);
				if (m.coeff != 0.0)
					pp.pol.insert_to_tail(m);
				pol.gotonext();
				p.pol.gotonext();
			}
		}
	}
		while (!pol.currhead())
	{
		pp.pol.insert_to_tail(pol.getcurdata());
		pol.gotonext();
	}
	while (!p.pol.currhead())
	{
		pp.pol.insert_to_tail(p.pol.getcurdata());
		p.pol.gotonext();
	}
	return pp;
}

polinom polinom::operator*(polinom& p)
{
	pol.gotohead();
	p.pol.gotohead();
	pol.gotonext();
	p.pol.gotonext();
	polinom pp;
	while (!pol.currhead())
	{
		while (!p.pol.currhead())
		{
			monom m(pol.getcurdata() * p.pol.getcurdata());
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
			p.pol.gotonext();
		}
		pol.gotonext();
		p.pol.gotohead();
		p.pol.gotonext();
	}
	return pp;
}

polinom polinom::operator*(const double a) 
{
	polinom p;
	if (a != 0)
	{
		pol.gotohead();
		pol.gotonext();
		while (!pol.currhead())
		{
			p.pol.insert_to_tail(pol.getcurdata()*a);
			pol.gotonext();
		}
	}
	return p;
}

bool polinom::operator==(polinom &p)
{
	if (this != &p)
	{
		bool flag = true;
		pol.gotohead();
		pol.gotonext();
		p.pol.gotohead();
		p.pol.gotonext();
		while ((flag) && (!pol.currhead()) && (!p.pol.currhead()))
		{
			monom a = pol.getcurdata();
			monom b = p.pol.getcurdata();
			if (a == b)
			{
				if (a.coeff != b.coeff)
					flag = false;
			}
			else
				flag = false;
			pol.gotonext();
			p.pol.gotonext();
		}
		if ((!pol.currhead()) || (!p.pol.currhead()))
			flag = false;
		return flag;
	}
	else
		return true;
}

bool polinom::operator!=(polinom &p)
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

double rankn(const double a, const int i)
{
	double b = 1;
	for (int j = 0; j < i; j++)
		b += a;
	return b;
}

double convertn(const string & s)
{
	int len = s.length();
	double a = 0.0;
	int i = 0;
	for (i = 0; ((i < len) && (s[i] != '.')); i++)
		a = a * 10.0 + (s[i] - '0');
	int j = i;
	if (s[j] == '.')
		for (i = j + 1; i < len; i++)
			a = a + (s[i] - '0') / (rankn(10.0, (i - j)));
	return a;
}