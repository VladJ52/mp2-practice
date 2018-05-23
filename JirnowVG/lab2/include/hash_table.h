#pragma once

#include "table.h"

template <typename val>
class HashTab : public Table<val>
{
protected:
	int* flag;
	int HashFunc(string key) const;
	void Realloc();
public:
	HashTab(int i = 5);
	HashTab(const HashTab<val>& t);
	~HashTab() { delete[] flag; }
	void insert(const val data, const string key);
	val* search(const string key);
	void del(const string key);
	void set();
	val* getcurr() const;
	void reset();
	bool IsTabEnd() const { return currindex == currrec || currindex == -1; }
	friend ostream& operator<<(ostream& out, const HashTab<val>& t);
};