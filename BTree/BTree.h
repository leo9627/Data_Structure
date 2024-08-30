#pragma once
#include<vector>
#include<utility>
using std::vector;
using std::pair;



//关键字类型K 关键字个数M
template<class K,size_t M>
struct Node
{
	vector<K> _keys;
	vector<Node<K, M>*> _subs;
	Node<K, M>* _parents;
	size_t _n;
	Node()
	{
		_keys.resize(M, K());
		_subs.resize(M+1, nullptr);
		_parents = nullptr;
		_n = 0;
	}
};

template<class K,size_t M>
class BTree
{
	typedef Node<K, M> Node;
public:

	//返回key所在节点的地址和在节点中keys的下标
	pair<Node*, int> Find(const K& key)
	{
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			size_t i = 0;
			while (i < cur->_n)
			{
				if (cur->_keys[i] > key)
				{
					break;
				}
				else if (cur->_keys[i] < key)
				{
					++i;
				}
				else
					return std::make_pair(cur, i);
			}
			parent = cur;
			cur = cur->_subs[i];  //不在该节点，去下一个节点找
		}
		return std::make_pair(parent, -1);
	}

	bool Insert(const K& key)
	{
		if (_root == nullptr)
		{
			_root = new Node;
			_root->_keys[0] = key;
			++_root->_n;
			return true;
		}
		pair<Node*, int> ret = Find(key);
		if (ret.second >= 0)   //B树中存在
		{
			return false;
		}
		//不存在,插入key

		int end = (ret.first)->_n-1;
		while (end >= 0)
		{
			if (ret.first->_keys[end] > key)
			{
				ret.first->_keys[end + 1] = ret.first->_keys[end];
				//ret.first->_subs[end + 2] = ret.first->_subs[end+1];
				--end;
			}
			else
				break;
		}
		ret.first->_keys[end + 1] = key;
		++ret.first->_n;

		Node* cur = ret.first;
		while (1)
		{
			if (cur->_n == M)   //需要分裂
			{
				Node* brother = new Node;
				int mid = M / 2;
				size_t j = 0;
				for (size_t i = mid + 1; i < M; ++i)  //copy一半到brother节点,brother的parent要改变
				{
					brother->_keys[j] = cur->_keys[i];
					brother->_subs[j++] = cur->_subs[i];
					if (cur->_subs[i])    //这里要加上,特别要注意父节点
						cur->_subs[i]->_parents = brother;
					cur->_keys[i] = K();
					cur->_subs[i] = nullptr;
				}
				brother->_subs[j] = cur->_subs[M];
				if (cur->_subs[M])
					cur->_subs[M]->_parents = brother;
				cur->_subs[M] = nullptr;
				brother->_n = j;
				cur->_n = M - j - 1;

				Node* parent = cur->_parents;
				if (parent == nullptr)
				{
					_root = new Node;
					_root->_keys[0] = cur->_keys[mid];
					cur->_keys[mid] = K();
					_root->_subs[0] = cur;
					cur->_parents = _root;
					_root->_subs[1] = brother;
					brother->_parents = _root;
					++_root->_n;
					return true;
				}
				else
				{
					int end = parent->_n - 1;
					while (end >= 0)
					{
						if (parent->_keys[end] > key)
						{
							parent->_keys[end + 1] = parent->_keys[end];
							parent->_subs[end + 2] = parent->_subs[end + 1];
							--end;
						}
						else
							break;
					}
					parent->_keys[end + 1] = cur->_keys[mid];
					cur->_keys[mid] = K();
					parent->_subs[end + 2] = brother;
					++parent->_n;
					brother->_parents = parent;
				}
				cur = parent;
			}
			else
			{
				break;
			}
		}


		return true;
	}
private:
	Node* _root=nullptr;
};