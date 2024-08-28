#pragma once
#include<vector>




class UnionFindSet
{
public:
	UnionFindSet(size_t n)
	{
		_v.resize(n, -1);
	}
	size_t FindRoot(size_t n)
	{
		size_t root = n;
		while (_v[root] >= 0)
			root = _v[root];     //路径压缩

		while (_v[n] >= 0)
		{
			size_t parent = _v[n];
			_v[n] = root;
			n = parent;
		}
		return root;
	}

	bool Union(size_t x1, size_t x2)
	{
		size_t root1 = FindRoot(x1);
		size_t root2 = FindRoot(x2);
		if (root1 == root2)
			return false;
		if (_v[root1] > _v[root2])   //也可以实现路径压缩
			std::swap(root1, root2);

		_v[root1] += _v[root2];
		_v[root2] = root1;

		return true;
	}
	bool IsSet(size_t x1, size_t x2)
	{
		return FindRoot(x1) == FindRoot(x2);
	}
	size_t Size()
	{
		size_t n = 0;
		for (auto& e : _v)
		{
			if (e < 0)
				++n;
		}
		return n;
	}


private:
	std::vector<int> _v;
};