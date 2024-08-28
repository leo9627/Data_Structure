#pragma once
#include<iostream>
#include<stdio.h>
#include<vector>
#include<unordered_map>
#include<bitset>
#include<queue>
#include<stack>
#include<queue>
#include<functional>
#include<algorithm>
#include<exception>
#include"UnionFindSet.h"
using std::count;


template<class V,class W,W W_MAX=INT_MAX,bool Direction=false>
class Graph
{
	typedef Graph<V, W, W_MAX, Direction> Self;
public:
	Graph() = default;
	Graph(const V* vertex, size_t n)
	{
		_vertex.resize(n);
		for (size_t i = 0; i < n; ++i)
		{
			_vertex[i] = vertex[i];
			_IndexMap[vertex[i]] = i;
		}
		_matrix.resize(n);
		for (auto& e : _matrix)
		{
			e.resize(n, W_MAX);
		}
	}
	size_t GetIndex(const V& v)
	{
		//std::unordered_map<V, size_t>::iterator it = _IndexMap.find(v);
		auto it = _IndexMap.find(v);
		if (it != _IndexMap.end())
		{
			return it->second;
		}
		else
		{
			throw std::invalid_argument("顶点不存在");
			return -1;
		}
	}
	void AddEdge(const V& src, const V& dst,const W& weigh)
	{
		size_t i = GetIndex(src);
		size_t j = GetIndex(dst);
		Add_Edge(i, j, weigh);
	}
	void Add_Edge(const size_t i, size_t j, const W& weigh)
	{
		_matrix[i][j] = weigh;
		if (!Direction)
			_matrix[j][i] = weigh;
	}

	void BFS(const V& begin)
	{
		size_t index = GetIndex(begin);
		const size_t n = 10;
		std::bitset<n> _bt;
		std::queue<size_t> qe;
		qe.push(index);
		_bt.set(index);
		size_t leve_size = 1;
		while (!qe.empty())
		{
			for (size_t j = 0; j < leve_size; ++j)
			{
				size_t f = qe.front();
				std::cout << _vertex[f] << " ";
				qe.pop();
				for (size_t i = 0; i < _matrix[f].size(); ++i)
				{
					if (_matrix[f][i] != W_MAX)
					{
						if (_bt.test(i) == false)
						{
							qe.push(i);
							_bt.set(i);
						}
					}
				}
			}
			std::cout << std::endl;
			leve_size = qe.size();
			
		}
	}
	void _DFS(size_t n, std::vector<bool>& v)
	{
		std::cout << _vertex[n] << " ";
		v[n] = true;
		for (size_t i = 0; i < _vertex.size(); ++i)
		{
			if (_matrix[n][i] != W_MAX && v[i] == false)
				_DFS(i, v);
		}
	}
	/*void DFS1(const V& src)     //有问题
	{
		std::stack<size_t> s;
		size_t n = GetIndex(src);
		s.push(n);
		std::vector<bool> v;
		v.resize(_vertex.size(),false);
		v[n] = true;
		std::cout << _vertex[n] << " ";
		while (!s.empty())
		{
			size_t front = s.top();
			s.pop();
			int f = 1;
			while (f)
			{
				f = 0;
				for (size_t i = 0; i < _vertex.size(); ++i)
				{
					if (_matrix[front][i] != W_MAX && v[i] == false)
					{
						f = 1;
						s.push(i);
						v[i] = true;
						front = i;
						std::cout << _vertex[i] << " ";
						break;
					}
				}
			}

		}
	}*/
	void DFS(const V& src)
	{
		std::vector<bool> v;
		v.resize(_vertex.size(), false);
		_DFS(GetIndex(src), v);
	}
	struct Edge
	{
		size_t _srcindex;
		size_t _dstindex;
		W _w;
		Edge(const size_t& srcindex,const size_t& dstindex,const W& w)
			:_srcindex(srcindex)
			,_dstindex(dstindex)
			,_w(w)
		{}
		bool operator>(const Edge& e)const
		{
			return _w > e._w;
		}
	};
	W Kruskal(Self& mintree)
	{
		size_t n = _vertex.size();

		mintree._vertex = _vertex;
		mintree._IndexMap = _IndexMap;
		mintree._matrix.resize(n);
		for (size_t i = 0; i < n; ++i)
		{
			mintree._matrix[i].resize(n, W_MAX);
		}
		std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;
		//入优先级队列
		for (size_t i = 0; i < n; ++i)
		{
			for (size_t j = i+1; j < n; ++j)
			{
				if (_matrix[i][j] != W_MAX)
					pq.push(Edge(i,j, _matrix[i][j]));
			}
		}
		UnionFindSet ufs(n);
		size_t edge_numbers =0;
		W w_total = W();
		while (!pq.empty())
		{
			Edge edge = pq.top();
			pq.pop();
			if (!ufs.IsSet(edge._srcindex, edge._dstindex))
			{
				ufs.Union(edge._srcindex, edge._dstindex);
				mintree.Add_Edge(edge._srcindex, edge._dstindex,edge._w);
				std::cout << _vertex[edge._srcindex] << "->" << _vertex[edge._dstindex] << std::endl;
				w_total += edge._w;
				++edge_numbers;
			}
		}
		if (edge_numbers == n - 1)
		{
			return w_total;
		}
		else
		{
			throw std::exception("无法生成最小生成树");
			return W();
		}
	}

	W Prim(Self& mintree, const V& src)
	{
		size_t n = _vertex.size();
		mintree._vertex = _vertex;
		mintree._IndexMap = _IndexMap;
		mintree._matrix.resize(n);
		for (size_t i = 0; i < n; ++i)
		{
			mintree._matrix[i].resize(n, W_MAX);
		}
		size_t srcindex = GetIndex(src);
		std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> minpq;
		std::vector<bool> x(n,false);
		x[srcindex] = true;
		for (size_t i = 0; i < n; ++i)
		{
			if (_matrix[srcindex][i] != W_MAX)
				minpq.push(Edge(srcindex, i, _matrix[srcindex][i]));
		}
		size_t edge_numbers=0;
		W w_total = W();
		while (!minpq.empty())
		{
			Edge edge = minpq.top();
			minpq.pop();
			if (x[edge._dstindex] == false)  //不会构成环
			{
				mintree.Add_Edge(edge._srcindex, edge._dstindex, edge._w);
				x[edge._dstindex] = true;
				w_total += edge._w;
				++edge_numbers;
				std::cout << _vertex[edge._srcindex] << "->" << _vertex[edge._dstindex] << std::endl;
				if (edge_numbers == n - 1)
				{
					break;
				}
				for (size_t i = 0; i < n; ++i)
				{
					if (_matrix[edge._dstindex][i] != W_MAX && x[i] == false)
					{
						minpq.push(Edge(edge._dstindex, i, _matrix[edge._dstindex][i]));
					}
				}

			}
		}
		if (edge_numbers == n - 1)
		{
			return w_total;
		}
		else
		{
			throw std::exception("无法生成最小生成树");
			return W();
		}
	}
	//dst存储节点路径的权重和，pParth存储路线的父节点
	void Dijkstra(const V& src, std::vector<W>& dst, std::vector<int>& pPath)
	{
		size_t n = _vertex.size();
		size_t srci = GetIndex(src);
		dst.resize(n, W_MAX);
		pPath.resize(n, -1);
		std::vector<bool> visited(n,false);  //记录已经可以确定最短路径的节点
		dst[srci] = W();

		for (size_t t = 0; t < n; ++t)
		{
			//找u
			size_t u = 0;
			W minw = W_MAX;
			for (size_t i = 0; i < n; ++i)
			{
				if (dst[i] < minw && visited[i] == false)
				{
					minw = dst[i];
					u = i;
				}

			}
			visited[u] = true;
			//松弛操作
			for (size_t i = 0; i < n; ++i)
			{
				if (visited[i]==false && _matrix[u][i] != W_MAX && dst[u] + _matrix[u][i] < dst[i])
				{
					dst[i] = dst[u] + _matrix[u][i];
					pPath[i] = u;
				}
			}
		}
		

	}
	void PrintShortPath(const V& src, std::vector<W>& dst, std::vector<int>& pPath)
	{
		size_t n = _vertex.size();
		size_t srci = GetIndex(src);
		for (size_t i = 0; i < n; ++i)
		{
			if (i == srci)
				continue;
			std::vector<int> path;
			size_t parent = i;
			while (pPath[parent] >= 0)
			{
				path.push_back(parent);
				parent = pPath[parent];
			}
			path.push_back(srci);
			std::reverse(path.begin(),path.end());
			for (auto& e: path)
			{
				std::cout << _vertex[e]<< "->";
			}
			std::cout <<"权值:"<< dst[i] << std::endl;
		}
	}
	bool BellmanFord(const V& src, std::vector<W>& dist, std::vector<int>& pPath)
	{
		size_t srci = GetIndex(src);
		size_t n = _vertex.size();
		dist.resize(n,W_MAX);
		pPath.resize(n,-1);
		dist[srci] = W();
		for (size_t k = 0; k < n; ++k)
		{
			bool update = false;
			for (size_t i = 0; i < n; ++i)
			{
				for (size_t j = 0; j < n; ++j)
				{
					if (dist[i] != W_MAX &&_matrix[i][j]!=W_MAX && dist[i] + _matrix[i][j] < dist[j])
					{
						update = true;
						dist[j] = dist[i] + _matrix[i][j];
						pPath[j] = i;
					}
				}
			}
			if (update == false)
				return true;
		}


		//检查是否有负权回路
		for (size_t i = 0; i < n; ++i)
		{
			for (size_t j = 0; j < n; ++j)
			{
				if (dist[i] != W_MAX && _matrix[i][j] != W_MAX && dist[i] + _matrix[i][j] < dist[j])
					return false;
			}
		}
		return true;
	}


	void FloydWarshall(std::vector<std::vector<W>>& dist, std::vector<std::vector<int>>& pPath)
	{
		size_t n = _vertex.size();
		dist.resize(n);
		pPath.resize(n);
		for (size_t i = 0; i < n; ++i)
		{
			dist[i].resize(n, W_MAX);
			pPath[i].resize(n, -1);
		}
		for (size_t i = 0; i < n; ++i)
		{
			for (size_t j = 0; j < n; ++j)
			{
				if (_matrix[i][j] != W_MAX)
				{
					dist[i][j] = _matrix[i][j];
					pPath[i][j] = i;
				}
				if (i == j)
					dist[i][j] = 0;
			}
		}

		for (size_t k = 0; k < n; ++k)  //选出中心节点,必须得先选出中间点
		{
			for (size_t i = 0; i < n; ++i)
			{
				for (size_t j = 0; j < n; ++j)
				{
					if (dist[i][k] != W_MAX && dist[k][j] != W_MAX
						&& dist[i][k] + dist[k][j] < dist[i][j])
					{
						dist[i][j] = dist[i][k] + dist[k][j];
						pPath[i][j] = pPath[k][j];
					}
					
				}
			}
			/*for (size_t i = 0; i < n; ++i)
			{
				for (size_t j = 0; j < n; ++j)
				{
					if (dist[i][j] == W_MAX)
					{
						printf("%3c", '*');
					}
					else
						printf("%3d", dist[i][j]);
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
			for (size_t i = 0; i < n; ++i)
			{
				for (size_t j = 0; j < n; ++j)
				{
					printf("%3d", pPath[i][j]);
				}
				std::cout << std::endl;
			}
			std::cout << "--------------------------------\n";*/

		}

	}
	void Print()
	{
		std::cout << "映射关系:\n";
		for (size_t i = 0; i < _vertex.size(); ++i)
		{
			printf("[%d]->", (int)i);
			std::cout << _vertex[i] << std::endl;
		}
		std::cout << "邻接矩阵\n";
		std::cout << "  ";
		for (size_t i = 0; i < _matrix.size(); ++i)
			std::cout << i<<" ";
		std::cout << std::endl;
		for (size_t i = 0; i < _matrix.size(); ++i)
		{
			std::cout << i << " ";
			for (auto& e : _matrix[i])
			{
				if (e == W_MAX)
					std::cout << "# ";
				else
					std::cout << e << " ";
			}
			std::cout << std::endl;
		}
	}
private:
	std::vector<V> _vertex;
	std::unordered_map<V, size_t> _IndexMap;  //映射关系
	std::vector<std::vector<W>> _matrix;   //邻接矩阵
};

namespace link_table
{
	template<class W>
	struct Edge
	{
		int _dst;
		W _w;
		Edge<W>* _next;
		Edge(int dst,const W& w)
			:_dst(dst)
			,_w(w)
			,_next(nullptr)
		{}
	};

	template<class V,class W,bool Direction=false>
	class Graph
	{
		typedef Edge<W> Edge;
	public:
		Graph(const V* vertex, size_t n)
		{
			_vertex.resize(n);
			for (size_t i = 0; i < n; ++i)
			{
				_vertex[i] = vertex[i];
				_IndexMap[vertex[i]] = i;
			}
			_tables.resize(n, nullptr);
		}
		size_t GetIndex(const V& v)
		{
			auto it = _IndexMap.find(v);
			if (it != _IndexMap.end())
			{
				return it->second;
			}
			else
			{
				throw std::invalid_argument("顶点不存在");
				return -1;
			}
		}
		void AddEdge(const V& src, const V& dst, const W& w)
		{
			size_t src_index = GetIndex(src);
			size_t dst_index = GetIndex(dst);
			Edge* edge = new Edge(dst_index, w);
			edge->_next = _tables[src_index];
			_tables[src_index] = edge;
			if (Direction == false)
			{
				Edge* edge = new Edge(src_index, w);
				edge->_next = _tables[dst_index];
				_tables[dst_index] = edge;
			}
		}
	private:
		std::vector<V> _vertex;
		std::unordered_map<V, int> _IndexMap;
		std::vector<Edge*> _tables;
	};
}