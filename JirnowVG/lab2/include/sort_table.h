#pragma once

#include "table.h"

template<typename val>
class SortTab : public Table<val>
{
public:
	SortTab(int i = 5) : Table(i) {}
	SortTab(const SortTab<val>& t) : Table(t) {}
	~SortTab() {}
	void insert(const string& tempkey, const val& tempdata) override;
	val& search(const string& tempkey) const override;
	void del(const string& key) override;
	//friend ostream& operator<<(ostream& out, const SortTab<val>& t);
};

template<typename val>
void SortTab<val>::insert(const string& tempkey, const val& tempdata)
{
	if (IsFull())
		Realloc();
	TabRec<val> temprec(tempkey, tempdata);
	reset();
	while (!IsTabEnd() && temprec.tempkey >= linerec[currindex]->key)
	{
		if (linerec[currindex]->key == temprec.tempkey)
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
val& SortTab<val>::search(const string& tempkey) const
{
	SortTab<val> temp(*this);
	temp.reset();
	if (currindex > -1)
	{
		int i = 0, mid;
		int j = currrec - 1;
		while (i <= j)
		{
			mid = (i + j) / 2;
			if (tempkey > linerec[mid]->key)
				i = mid + 1;
			else
				j = mid - 1;
		}
		if (temp.linerec[i]->key == tempkey)
			return temp.linerec[i]->data;
		else
			throw "key is not found";
	}
	else
		throw "table is empty";
}

template<typename val>
void SortTab<val>::del(const string& key)
{
	reset();
	if (IsEmpty())
		throw "table is empty";
	search(key);
	if (currrec > 1)
	{
		currrec--;
		for (int i = currindex; i < currrec; i++)
			linerec[i] = linerec[i + 1];
		reset();
	}
	else
		currrec = 0;
}