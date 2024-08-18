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
		while (_v[n] >= 0)
			n = _v[n];
		return n;
	}

	bool Union(size_t x1, size_t x2)
	{
		size_t root1 = FindRoot(x1);
		size_t root2 = FindRoot(x2);
		if (root1 == root2)
			return false;
		_v[root1] += _v[root2];
		_v[root2] = root1;
		return true;
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