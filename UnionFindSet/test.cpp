#include<iostream>
#include"UnionFindSet.h"

using namespace std;
int main()
{
	UnionFindSet ufs(4);
	cout << ufs.Size();
	ufs.Union(0, 1);
	cout << ufs.Size();

	return 0;
}