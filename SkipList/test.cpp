#include<iostream>
#include"SkipList.h"

using namespace std;


int main()
{
	Skiplist sl;
	for (int i = 0; i < 1; ++i)
	{
		sl.Add(i);
	}
	sl.Print();
	

	while (1)
	{
		int a, b;
		cin >> a >> b;
		if (a == 1)
		{
			sl.Add(b);
		}
		else
		{
			sl.Erase(b);
		}
		sl.Print();
		cout << "\n----------------------\n";
	}
	return 0;
}