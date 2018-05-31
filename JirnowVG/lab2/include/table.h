#pragma once

#include <string>
#include <iostream>

using namespace std;

template <typename val>
class TabRec
{
public:
	string key;
	val data;
	TabRec() { key = "null"; val d=0; data = d; }
	TabRec(const string& s, const val& d) { key = s; data = d; }
	TabRec(const TabRec& t) { key = t.key; data = t.data; }
	TabRec& operator= (const TabRec<val>& t)
	{
		data = t.data;
		key = t.key;
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
	virtual void Realloc();
public:
	Table(int i = 5);
	Table(const Table<val>& t);
	virtual ~Table() { delete[] linerec; };
	virtual void insert(const string& tempkey, const val& tempdata) = 0;
	virtual void del(const string &k) = 0;
	virtual val& search(const string& tempkey) const = 0;
	virtual void reset();
	virtual bool IsTabEnd() const { return currindex == currrec || currindex == -1; }
	bool IsFull() const { return currrec == maxrec; }
	bool IsEmpty() const { return currrec == 0; }
	virtual void set();
	virtual val& getcurr() const;
	virtual int getcurrind() { return currindex; }
	virtual int getcurrrec() { return currrec; }
	template <class val> friend ostream& operator<< (ostream& os, const Table<val>& t);
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
Table<val>::Table(const Table<val>& t)
{
	currrec = t.currrec;
	maxrec = t.maxrec;
	currindex = t.currindex;
	delete[] linerec;
	linerec = new TabRec<val>*[maxrec];
	for (int i = 0; i < currrec; i++)
		linerec[i] = t.linerec[i];
}

template <typename val>
void Table<val>::Realloc()
{
	int newmax = maxrec * 2;
	TabRec<val>** k = new TabRec<val>*[newmax];
	reset();
	for (int i = 0; i < maxrec; i++)
		k[i] = linerec[i];
	delete[] linerec;
	maxrec = newmax;
	linerec = k;
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
val& Table<val>::getcurr() const
{
	if (currrec)
		return linerec[currindex]->data;
	else
		throw "table is empty";
}

template<typename val>
void Table<val>::set()
{
	if (currrec)
		currindex++;
	else
		throw "table is empty";
	if (IsTabEnd())
		reset();
}

template <typename val>
ostream& operator<< (ostream& os, const Table<val>& t)
{
	if (t.currrec)
		for (int i = 0; i < t.currrec; i++)
			os << i << " | " << t.linerec[i]->key << " | " << t.linerec[i]->data << endl;
	else
		os << "Table is empty" << endl;
	return os;
}