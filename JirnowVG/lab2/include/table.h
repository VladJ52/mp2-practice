#pragma once

#include <string>
#include <iostream>

using namespace std;

template <typename val>
class TabRec
{
public:
	string key;
	val* data;
	TabRec() { key = "null"; data = new val(NULL); }
	TabRec(string s, val d) { key = s; data = new val(d); }
	TabRec(const TabRec& t) { key = t.key; data = new val(*(t.data)); }
	TabRec<val>& opertator = (const TabRec<val>& t)
	{
		data = new val(*(t.data));
		key = t.key;
		return *this;
	}
};

template <typename val>
class Table
{
protected:
	TabRec<val>** linerec;
	int maxrec;
	int currrec;
	int currindex;
	virtual void Realloc() = 0;
public:
	Table(int i = 5);
	virtual ~Table() { delete[] linerec; };
	virtual void insert(const val data, const string key) = 0;
	virtual void del(const string key) = 0;
	virtual val* search(const string key) = 0;
	virtual void reset();
	virtual bool IsTabEnd() const { return currindex == currrec || currindex == -1; }
	bool IsFull() const { return currrec == maxrec; }
	bool IsEmpty() const { return currrec == 0; }
	virtual void set();
	virtual val* getcurr() const;
	int getcurrrec() const { return currrec; }
	int getmaxrec() const { return maxrec };
};

template<typename val>
Table<val>::Table(int i)
{
	maxrec = i;
	currrec = 0;
	currindex = -1;
	linerec = new TabRec <val>*[maxrec];
}

template<typename val>
void Table<val>::reset()
{
	if (currrec > 0)
		currindex = 0;
	else
		currindex = -1;
}

template<typename val>
val* Table<val>::getcurr() const
{
	val* k;
	if (currindex >= 0 && currindex < currrec)
	{
		k = linerec[currindex]->data;
	}
	else
	{
		throw "Empty Table"
	}
	return k;
}

template<typename val>
void Table<val>::set()
{
	if (currindex != -1)
		currindex++;
	else
		throw "EmptyTable";
	if (IsTabEnd())
		reset();
}