#pragma once

#include "table.h"

template<typename val>
class OrdTab : public Table<val>
{
protected:
	void Realloc();
public:
	OrdTab(int i = 5);
	OrdTab(const OrdTab<val>& t);
	~OrdTab() {}
	void insert(const val data, const string key);
	val* search(const string key);
	void del(const string key);
	friend ostream& operator<<(ostream& out, const OrdTab<val>& t);
};

template<typename val>
OrdTab<val>::OrdTab(int i) : Table(i)
{

}

template<typename val>
OrdTab<val>::OrdTab(const OrdTab<val>& t)
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
void OrdTab<val>::Realloc()
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
void OrdTab<val>::insert(const val data, const string key)
{
	if (IsFull())
		Realloc();
	TabRec<val> temprec(key, data);
	reset();
	while (!IsTabEnd() && temp.rec >= linerec[currindex]->key)
	{
		if (linerec[currindex]->key == temprec.key)
			throw "key already exists";
		currindex++;
	}
	if (IsEmpty())
		currindex++;
	currrec++;
	for (int i = currrec - 1; i > currindex; i--)
	{
		linerec[i] = linerec[i - 1];
	}
	linerec[currindex] = new TabRec<val>(temprec);
	reset();
}

template<typename val>
val* OrdTab<val>::search(const string key)
{
	reset();
	val* k = nullptr;
	if (!IsEmpty())
	{
		int i = -1, j = currrec;
		int mid;
		while (i < j - 1)
		{
			mid = (j + 1) / 2;
			if (key >= linerec[mid]->key)
				i = mid;
			else
				j = mid;
		}
		if (key == linerec[i]->key)
		{
			currindex = i;
			k = linerec[currindex]->data;
		}
		else
			throw "key not found";
	}
	else
		throw "table is empty";
	return k;
}

template<typename val>
void OrdTab<val>::del(const string key)
{
	reset();
	if (IsEmpty())
		throw "table is empty";
	search(key);
	if (currrec > 1)
	{
		currec--;
		for (int i = currindex; i < currrec; i++)
			linerec[i] = linerec[i + 1];
		reset();
	}
	else
		currrec = 0;
}

template<typename val>
ostream& operator<<(ostream& out, const OrdTab<val>& t)
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