#pragma once
#include<vector>
#include<unordered_map>
#include<string>

class Trie
{
private:
	struct Node
	{
		size_t cnt = 0;
		bool EndFlag;
		std::vector<Node*> child;
		Node()
		{
			EndFlag = false;
			child.resize(52,nullptr);
		}
	};
	std::unordered_map<char, int> dict_;
	Node* P_ = NULL;
public:
	Trie()
	{
		int num = 0;
		for (char c = 'a'; c <= 'z'; ++c)
			dict_[c] = num++;
		for (char c = 'A'; c <= 'Z'; ++c)
			dict_[c] = num++;
		P_ = new Node;
	}
	Trie(const std::string& s)
	{
		Insert(s);
	}
	bool Insert(const std::string& s)
	{
		//if (Find(s)) return false;
		Node* P = P_;
		for (auto c : s)
		{
			if (P->child[dict_[c]] == nullptr)
				P->child[dict_[c]] = new Node;
			P = P->child[dict_[c]];
		}
		P->EndFlag = true;
		P->cnt++;
		return true;
	}
	bool Find(const std::string& s)
	{
		Node* P = P_;
		for (auto c : s)
		{
			if (P->child[dict_[c]] == nullptr)
				return false;
			P = P->child[dict_[c]];
		}
		return P->EndFlag;
	}
	size_t Count(const std::string s)
	{
		size_t ret = 0;
		Node* P = P_;
		for (auto c : s)
		{
			if (P->child[dict_[c]] == nullptr)
				return 0;
			P = P->child[dict_[c]];
			if (P->EndFlag == true) ret+=P->cnt;
		}
		return ret;
	}
	~Trie()
	{
		Free(P_);
	}
private:
	void Free(Node* ptr)
	{
		for (auto p : ptr->child)
			if (p) Free(p);
		delete ptr;
	}
};