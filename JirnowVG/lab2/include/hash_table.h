#pragma once

#include "table.h"

template <typename val>
class HashTab : public Table<val>
{
protected:
	int* flag;
	int HashFunc(const string& key) const;
	void Realloc() override;
public:
	HashTab(int i = 10);
	HashTab(const HashTab<val>& t);
	~HashTab() { delete[] flag; }
	void insert(const string& tempkey, const val& tempdata) override;
	val& search(const string& tepmkey) override;
	void del(const string& k) override;
	void set() override;
	val& getcurr() const override;
	void reset() override;
	bool IsTabEnd() const { return currindex == currrec || currindex == -1; }
	template <class val> friend ostream& operator<<(ostream& out, const HashTab<val>& t);
};


template<typename val>
HashTab<val>::HashTab(int i = 5) : Table(i)
{
	flag = new int[i];
	for (int j = 0; j < maxrec; j++)
		flag[j] = 0;
}

template<typename val>
int HashTab<val>::HashFunc(const string& key) const
{
	int hash = 0;
	for (int i = 0; i < key.length(); i++)
		hash = hash + int(key[i]);
	return hash % maxrec;
}

template<typename val>
void HashTab<val>::Realloc()
{
	int cof = 2;
	int newmax = maxrec * cof;
	TabRec<val>** k = new TabRec<val>*[newmax];
	int* tempflag = new int[newmax];
	for (int i = 0; i < maxrec; i++)
	{
		k[i] = linerec[i];
		tempflag[i] = flag[i];
	}
	delete[] linerec;
	delete[] flag;
	linerec = k;
	flag = tempflag;
	maxrec = newmax;
}

template<typename val>
HashTab<val>::HashTab(const HashTab<val>& t)
{
	currrec = t.currrec;
	maxrec = t.maxrec;
	currindex = t.currindex;
	delete[] linerec;
	delete[] flag;
	linerec = new TabRec<val>*[maxrec];
	flag = new int[maxrec];
	for (int i = 0; i < maxrec; i++)
	{
		flag[i] = t.flag[i];
		linerec[i] = t.linerec[i];
	}
}

template<typename val>
void HashTab<val>::reset()
{
	if (currrec)
	{
		currindex = 0;
		while (flag[currindex] != 1)
			currindex++;
	}
	else
		currindex = -1;
}

template<typename val>
val& HashTab<val>::search(const string& tempkey) 
{
	reset();
	if (currrec)
	{
		currindex = HashFunc(tempkey);
		int ind = currindex;
		if (linerec[currindex]->key == tempkey)
			return linerec[currindex]->data;
		else
		{
			while (flag[currindex] && ((currindex + 1) != ind) && (linerec[currindex]->key != tempkey))
				currindex = (currindex + 1) % maxrec;
			if (linerec[currindex]->key == tempkey)
				return linerec[currindex]->data;
			else
				throw "key is not found";
		}
	}
	else
		throw "table is empty";
}

template<typename val>
void HashTab<val>::insert(const string& tempkey, const val& tempdata)
{
	if (IsFull())
		Realloc();
	currindex = HashFunc(tempkey);
	if (!flag[currindex])
		{
			linerec[currindex] = new TabRec<val>(tempkey, tempdata);
			currrec++;
			flag[currindex] = 1;
		}
	else
			if (linerec[currindex]->key != tempkey)
			{
				int ind = currindex;
				while (flag[currindex] && ((currindex + 1) != ind))
					currindex = (currindex + 1) % maxrec;
				linerec[currindex] = new TabRec<val>(tempkey, tempdata);
				currrec++;
				flag[currindex] = 1;
			}
			else
				throw "key already exists";
}

template<typename val>
void HashTab<val>::del(const string& key)
{
	reset();
	if (currrec)
	{
		currindex = HashFunc(key);
		int ind = currindex;
		if (flag[currindex])
		{
			if (linerec[currindex]->key != key)
			{
				while (flag[currindex] && ((currindex + 1) != ind) && (linerec[currindex]->key != key))
					currindex = (currindex + 1) % maxrec;
				if (!flag[currindex] || linerec[currindex]->key != key)
					throw "key is not found";
				else
				{
					linerec[currindex] = new TabRec<val>;
					flag[currindex] = 0;
					currrec--;
				}
			}
			else
			{
				linerec[currindex] = new TabRec<val>;
				flag[currindex] = 0;
				currrec--;
			}
		}
		else
			throw "key is not found";
	}
	else
		throw "table is empty";
}

template<typename val>
val& HashTab<val>::getcurr() const
{
	if (currrec)
		return linerec[currindex]->data;
	else
		throw "table is empty";
}

template<typename val>
void HashTab<val>::set()
{
	if (currrec)
	{
		currindex++;
		while (flag[currindex] != 1)
			currindex = (currindex + 1) % maxrec;
	}
	else
		throw "table is empty";
}

template <typename val>
ostream& operator<< (ostream& os, const HashTab<val>& t)
{
	if (t.currrec)
	{
		for (int i = 0; i < t.maxrec; i++)
			if (t.flag[i])
				os << i << " | " << t.linerec[i]->key << " | " << t.linerec[i]->data << endl;
	}
	else
		os << "Table is empty" << endl;
	return os;
}