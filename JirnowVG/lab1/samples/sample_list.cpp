#include "polinom.h"
using namespace std;

int main()
{
	int f;
	do
	{
		cout << "Actions with polinoms" << endl;
		cout << "1 - addition of polinoms" << endl;
		cout << "2 - multiplication of polinoms" << endl;
		cout << "3 - multiplication of a polinom on the number" << endl;
		cin >> f;
		cin.ignore();
		if (f == 1)
		{
			string s;
			cout << "Write first polinom" << endl;
			getline(cin, s);
			polinom p1(s);
			cout << "Write second polinom" << endl;
			getline(cin, s);
			polinom p2(s);
			polinom p3 = p1 + p2;
			cout << "Addition of polinoms: " << p3 << endl;
		}
		else
			if (f == 2)
			{
				string s;
				cout << "Write first polinom" << endl;
				getline(cin, s);
				polinom p1(s);
				cout << "Write second polinom" << endl;
				getline(cin, s);
				polinom p2(s);
				polinom p3 = p1 * p2;
				cout << "Multiplication of polinoms: " << p3 << endl;
			}
			else
				if (f == 3)
				{
					string s;
					cout << "Write a polinom" << endl;
					getline(cin, s);
					polinom p(s);
					cout << "Write a number" << endl;
					double d;
					cin >> d;
					p = p * d;
					cout << "Multiplication of a polinom on the number: " << p << endl;
				}
				else
					cout << "There is no such choice" << endl;
		cout << "Want to continue" << endl;
		cout << "1 - yes" << endl;
		cout << "2 - no" << endl;
		cin >> f;
	}
	while (f == 1);
	return 0;
}
