#include"Grap.h"
#include<string>
#include<functional>
using namespace std;
int test1()
{
	cout << sizeof(false);
	Graph<char, int, INT_MAX, true> g("0123", 4);
	g.AddEdge('0', '1', 1);
	g.AddEdge('0', '3', 4);
	g.AddEdge('1', '3', 2);
	g.AddEdge('1', '2', 9);
	g.AddEdge('2', '3', 8);
	g.AddEdge('2', '1', 5);
	g.AddEdge('2', '0', 3);
	g.AddEdge('3', '2', 6);
	g.Print();
	g.BFS('1');
	printf("\n");
	g.DFS('1');
	return 0;
}

int t1()
{
	string arr[] = { "mask","trump","biden","mike" };
	Graph<string, int> g(arr,4);
	function<void(string,string)> g_AddEdge = bind(&Graph<string, int>::AddEdge, &g, placeholders::_1, placeholders::_2, 2);
	g_AddEdge("mask", "trump");
	g_AddEdge("biden", "trump");
	//g.Breadth_Search("mask");
	//g.Print();
	return 0;
}

int test2()
{
	Graph<char, int> g("ABCDEFGHI", 9);
	g.AddEdge('A', 'B', 1);
	g.AddEdge('E', 'B', 1);
	g.AddEdge('A', 'D', 1);
	g.AddEdge('A', 'C', 1);
	g.AddEdge('E', 'G', 1);
	g.AddEdge('D', 'F', 1);
	g.AddEdge('C', 'F', 1);
	g.AddEdge('F', 'H', 1);
	g.AddEdge('H', 'I', 1);
	g.AddEdge('C', 'B', 1);
	g.Print();
	//g.DFS1('A');
	cout << endl;
	g.DFS('A');
	return 0;
}

int test3()
{
	Graph<char, int, INT_MAX> g("012345", 6);
	g.AddEdge('0', '1', 1);
	g.AddEdge('2', '1', 1);
	g.AddEdge('2', '3', 1);
	g.AddEdge('2', '4', 1);
	g.AddEdge('2', '5', 1);
	g.DFS('0');
	return 0;
}

int test4()
{
	const char* str = "abcdefghi";
	Graph<char, int> g(str, strlen(str));
	g.AddEdge('a', 'b', 4);
	g.AddEdge('a', 'h', 8);
	g.AddEdge('b', 'c', 8);
	g.AddEdge('b', 'h', 11);
	g.AddEdge('c', 'i', 2);
	g.AddEdge('c', 'f', 4);
	g.AddEdge('c', 'd', 7);
	g.AddEdge('d', 'f', 14);
	g.AddEdge('d', 'e', 9);
	g.AddEdge('e', 'f', 10);
	g.AddEdge('f', 'g', 2);
	g.AddEdge('g', 'h', 1);
	g.AddEdge('g', 'i', 6);
	g.AddEdge('h', 'i', 7);
	g.Print();
	Graph<char, int> kminTree;
	cout << "Kruskal:" << g.Kruskal(kminTree) << endl;
	kminTree.Print();
	cout << endl;
	Graph<char, int> pminTree;
	cout << "Prim:" << g.Prim(pminTree,'a') << endl;
	pminTree.Print();
	return 0;
}

int test5()
{
	const char* str = "syztx";
	Graph<char, int, INT_MAX, true> g(str, strlen(str));
	g.AddEdge('s', 't', 10);
	g.AddEdge('s', 'y', 5);
	g.AddEdge('y', 't', 3);
	g.AddEdge('y', 'x', 9);
	g.AddEdge('y', 'z', 2);
	g.AddEdge('z', 's', 7);
	g.AddEdge('z', 'x', 6);
	g.AddEdge('t', 'y', 2);
	g.AddEdge('t', 'x', 1);
	g.AddEdge('x', 'z', 4);
	vector<int> dist;
	vector<int> parentPath;
	g.Dijkstra('s', dist, parentPath);
	g.PrintShortPath('s', dist, parentPath);
	return 0;
}


int test6()
{
	const char* str = "12345";
	Graph<char, int, INT_MAX, true> g(str, strlen(str));
	g.AddEdge('1', '2', 3);
	g.AddEdge('1', '3', 8);
	g.AddEdge('1', '5', -4);
	g.AddEdge('2', '4', 1);
	g.AddEdge('2', '5', 7);
	g.AddEdge('3', '2', 4);
	g.AddEdge('4', '1', 2);
	g.AddEdge('4', '3', -5);
	g.AddEdge('5', '4', 6);
	vector<vector<int>> vvDist;
	vector<vector<int>> vvParentPath;
	g.FloydWarshall(vvDist, vvParentPath);
	// 打印任意两点之间的最短路径
	for (size_t i = 0; i < strlen(str); ++i)
	{
		g.PrintShortPath(str[i], vvDist[i], vvParentPath[i]);
		cout << endl;
	}
	return 0;

}

int main()
{
	const char* str = "syztx";
	Graph<char, int, INT_MAX, true> g(str, strlen(str));
	g.AddEdge('s', 't', 6);
	g.AddEdge('s', 'y', 7);
	g.AddEdge('y', 'z', 9);
	g.AddEdge('y', 'x', -3);
	//g.AddEdge('z', 's', 2);
	g.AddEdge('y', 's', 1);
	g.AddEdge('z', 'x', 7);
	g.AddEdge('t', 'x', 5);
	//g.AddEdge('t', 'y', 8);
	g.AddEdge('t', 'y', -8);
	g.AddEdge('t', 'z', -4);
	g.AddEdge('x', 't', -2);
	vector<int> dist;
	vector<int> parentPath;
	if (g.BellmanFord('s', dist, parentPath))
		g.PrintShortPath('s', dist, parentPath);
	else
		cout << "负权回路\n";
	return 0;
}