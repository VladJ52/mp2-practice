#pragma once

#include "table.h"

template<typename val>
class UnordTab : public Table<val>
{
protected:
	void Realloc();
public:
	UnordTab(int i = 5);
	UnordTab(const UnordTab<val>& t);
	~UnordTab() {}
	void insert(const val data, const string key);
	val* search(const string key);
	void del(const string key);
	friend ostream& operator<<(ostream& out, const UnordTab<val>& t);
};

template<typename val>
UnordTab<val>::UnordTab(int i) : Table(i)
{

}

template<typename val>
UnordTab<val>::UnordTab(const UnordTab<val>& t)
{
	maxrec = t.maxrec;
	currindex = t.currindex;
	currrec = t.currrec;
	delete[] linerec;
	linerec = new TabRec<val>*[maxrec];
	if (!IsEmpty())
		for (int i = 0; i < currrec; i++)
			linerec[i] = new TabRec<val>(*(t.linerec[i]));
}

template<typename val>
void UnordTab<val>::Realloc()
{
	int newmax = (int)(maxrec * 2);
	TabRec<val>** k = new TabRec<val>*[newmax];
	for (int i = 0; i < maxrec; i++)
		k[i] = linerec[i];
	maxrec = newmax;
	delete[] linerec;
	linerec = k;
}

template<typename val>
void UnordTab<val>::insert(const val data, const string key)
{
	if (IsFull())
		Realloc();
	TabRec<val> temprec(key, data);
	reset();
	while (!IsTabEnd() && key != linerec[currindex]->key)
		currindex++;
	if (IsEmpty())
		currindex++;
	if (currindex == currrec)
	{
		linerec[currindex] = new TabRec<val>(temprec);
		currrec++;
		reset();
	}
	else
	{
		reset();
		throw "key already exists";
	}
}

template<typename val>
val* UnordTab<val>::search(const string key)
{
	reset();
	val* k = nullptr;
	if (!IsEmpty())
		throw "table is empty";
	while (!IsTabEnd() && key != linerec[currindex]->key)
		currindex++;
	if (!IsTabEnd())
		k = linerec[currindex]->data;
	else
		throw "key is not found";
	return k;
}

template<typename val>
void UnordTab<val>::del(const string key)
{
	reset();
	if (IsEmpty())
		throw "table is empty";
	search(key);
	if (currrec > 1)
		linerec[currindex] = linerec[--currrec];
	else
		currrec = 0;
}

template<typename val>
ostream& operator<<(ostream& out, const UnordTab<val>& t)
{
	int i = 0;
	while (i < t.currrec)
	{
		out << i << ". " << t.linerec[i]->key << " | " << *(t.linerec[i]->data) << endl;
		i++;
	}
	if (t.currrec == 0)
		os << "table is empty";
	return os;
}