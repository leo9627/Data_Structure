#pragma once
#include<vector>
#include<chrono>
#include<random>
#include<iostream>
#include<time.h>
using namespace std;

struct SkiplistNode
{
    int _data;
    int _n = 0;
    vector<SkiplistNode*> _nextarray;
    SkiplistNode(int data, int n);
};
class Skiplist {
    typedef SkiplistNode Node;
public:
    Skiplist();

    bool Search(int target);

    void Add(int num);

    bool Erase(int num);
    void Print();
private:
    int Random();
    vector<Node*> FindPrev(int num);
    Node* _head;
    int _maxlevel = 32;
    double p = 0.5;
};