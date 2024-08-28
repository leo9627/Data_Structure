#include<iostream>
#include"UnionFindSet.h"

using namespace std;
int x1()
{
	UnionFindSet ufs(4);
	cout << ufs.Size();
	ufs.Union(0, 1);
	cout << ufs.Size();

	return 0;
}
int main()
{
	UnionFindSet ufs(10);
	ufs.Union(8, 9);
	ufs.Union(7, 8);
	ufs.Union(6, 7);
	ufs.Union(5, 6);
	ufs.FindRoot(9);

	return 0;
}