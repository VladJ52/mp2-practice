#include "polinom.h"
#include <conio.h>
#include "table.h"
#include "scan_table.h"
#include "sort_table.h"
#include "hash_table.h"
void main()
{
	cout << "Choose the action" << endl;
	char c = 0, str;
	ScanTab<polinom> Tab1;
	SortTab<polinom> Tab2;
	HashTab<polinom> Tab3;
	string key;
	polinom P;

	while (c != ' ')
	{
		cout << "1. Insert   2. Delete   3. Search   4.Show" << endl;
		cin >> str;
		switch (str)
		{
		case '1':
		{
			cout << "Enter polinom for insert:" << endl;
			getline(cin, key);
			if (key == "")
				getline(cin, key);
			P = polinom(key);
			try
			{
				Tab1.insert(key, P);
				Tab2.insert(key, P);
				Tab3.insert(key, P);
			}
			catch (...)
			{
				cout << "Error" << endl;
			}
			break;
		}

		case '2':
		{
			cout << "Enter polinom for delete:" << endl;
			getline(cin, key);
			if (key == "")
				getline(cin, key);
			try
			{
				Tab1.del(key);
				Tab2.del(key);
				Tab3.del(key);
			}
			catch (...)
			{
				cout << "Error" << endl;
			}
			break;
		}
		case '3':
		{
			cout << "Enter polinom for search:" << endl;
			getline(cin, key);
			if (key == "")
				getline(cin, key);
			try
			{
				Tab1.search(key);
				cout << "ScanTable: " << endl << Tab1 << endl;
				cout << "-------------------------" << endl;
				cout << "Search in ScanTable: " << Tab1.search(key) << endl;
				cout << "-------------------------" << endl;
				cout << "SortedTable:" << endl << Tab2 << endl;
				cout << "-------------------------" << endl;
				cout << "Search in SortedTable: " << Tab2.search(key) << endl;
				cout << "-------------------------" << endl;
				cout << "HashTable:" << endl << Tab3 << endl << endl;
				cout << "-------------------------" << endl;
				cout << "Search in HashTable: " << Tab3.search(key) << endl;
				cout << "-------------------------" << endl;
			}
			catch (...)
			{
				cout << "Error" << endl;
			}
			break;
		}
		case '4':
		{
			cout << "ScanTable: " << endl << Tab1 << endl;
			cout << "-------------------------" << endl;
			cout << "SortedTable:" << endl << Tab2 << endl;
			cout << "-------------------------" << endl;
			cout << "HashTable:" << endl << Tab3 << endl << endl;
			cout << "-------------------------" << endl;
		}
		default:
			cout << "try again" << endl;
		}
		cout << "Press SPACE to exit" << endl;
		cout << "Press any key to enter" << endl;
		c = _getch();
	}
}