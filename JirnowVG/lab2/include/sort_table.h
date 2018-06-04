#pragma once

#include "table.h"

template<typename val>
class SortTab : public Table<val>
{
protected:
	int binsearch(const string &key) const;
public:
	SortTab(int i = 10) : Table(i) {}
	SortTab(const SortTab<val>& t) : Table(t) {}
	~SortTab() {}
	void insert(const string& tempkey, const val& tempdata) override;
	val& search(const string& tempkey) override;
	void del(const string& key) override;
};

template<typename val>
int SortTab<val>::binsearch(const string& tempkey) const
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
		return i;
}

template<typename val>
void SortTab<val>::insert(const string& tempkey, const val& tempdata)
{
	if (IsFull())
		Realloc();
	reset();
	if (currrec)
	{
		int k = binsearch(tempkey);
		if (k != currrec)
		{
			if (linerec[k]->key != tempkey)
			{
				for (int i = currrec; i > k; i--)
					linerec[i] = linerec[i - 1];
				linerec[k] = new TabRec<val>(tempkey, tempdata);
				currrec++;
			}
			else
				throw "key already exists";
		}
		else
		{
			linerec[k] = new TabRec<val>(tempkey, tempdata);
			currrec++;
		}
	}
	else
	{
		currindex++;
		linerec[currindex] = new TabRec<val>(tempkey, tempdata);
		currrec++;
	}
}

template<typename val>
val& SortTab<val>::search(const string& tempkey)
{
	reset();
	if (currindex > -1)
	{
		int k = binsearch(tempkey);
		if (linerec[k]->key == tempkey)
			return linerec[k]->data;
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
	if (currrec)
	{
		int k = binsearch(key);
		if ((k < currrec) && (linerec[k]->key == key))
		{
			for (int i = k; i < currrec; i++)
				linerec[i] = linerec[i + 1];
			currrec--;
		}
		else
			throw "key is not found";
	}
	else
		throw "table is empty";
}