#pragma once

#include "table.h"

template<typename val>
class ScanTab : public Table<val>
{
public:
	ScanTab(int i = 10) : Table(i) {}
	ScanTab(const ScanTab<val>& t) : Table(t) {}
	~ScanTab() {}
	void insert(const string& tempkey, const val& tempdata) override;
	val& search(const string& key) override;
	void del(const string& key) override;
};


template<typename val>
void ScanTab<val>::insert(const string& tempkey, const val& tempdata)
{
	if (IsFull())
		Realloc();
	reset();
	if (currrec)
	{
		while ((currindex < currrec) && (linerec[currindex]->key != tempkey))
			currindex++;
		if (currindex==currrec)
		{
			linerec[currindex] = new TabRec<val>(tempkey,tempdata);
			currrec++;
		}
		else
			throw "this key is already exists";
	}
	else
	{
		currindex++;
		linerec[currindex] = new TabRec<val>(tempkey,tempdata);
		currrec++;
	}
}

template<typename val>
val& ScanTab<val>::search(const string& tempkey)
{
	reset();
	if (currindex > -1)
	{
		while ((linerec[currindex]->key != tempkey) && (currindex < currrec))
			currindex++;
		if (currindex < currrec)
			return linerec[currindex]->data;
		else
			throw "key is not found";
	}
	else
		throw "table is empty";
}

template<typename val>
void ScanTab<val>::del(const string& key)
{
	reset();
	if (currindex > -1)
	{
		while ((currindex < currrec) && (linerec[currindex]->key != key))
			currindex++;
		if (currrec && (currindex < currrec))
		{
			if (currrec > 1)
				linerec[currindex] = linerec[--currrec];
			else
				currrec = 0;
		}
		else
			throw "key is not found";
	}
	else
		throw "table is empty";
}