#include"Trie.h"
#include<iostream>
#include<string>
using namespace std;

int main()
{
	Trie te;
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; ++i)
	{
		string s;
		cin >> s;
		te.Insert(s);
	}
	for (int i = 0; i < m; ++i)
	{
		string s;
		cin >> s;
		cout << te.Count(s) << endl;
	}
	return 0;
}