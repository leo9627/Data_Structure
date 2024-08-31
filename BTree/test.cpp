#include<iostream>
#include"BTree.h"
using std::cout;

int main()
{
	BTree<int, 1024> bt;
	//int arr[] = { 53, 139, 75, 49, 145, 36, 101 };
	vector<int> arr;
	srand(time(nullptr));
	size_t n = -1;
	for (size_t i = 0; i <10; ++i)
	{
		arr.push_back(rand());
	}
	for (auto& e : arr)
	{
		bt.Insert(e);
	}
	for (auto& e : arr)
	{
		if (bt.Find(e).second < 0||bt.Find(e).first->_keys[bt.Find(e).second]!=e)
		{
			cout << "No";
			return 0;
		}
	}
	cout << "Yes\n";

	bt.InOrder();

	return 0;
}