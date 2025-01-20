

#include"SkipList.h"

SkiplistNode::SkiplistNode(int data, int n)
    :_data(data)
{
    _nextarray.resize(n, nullptr);
}


Skiplist::Skiplist() {
    srand(time(nullptr));
    _head = new Node(-1, 1);
}

bool Skiplist::Search(int target)
{
    Node* cur = _head;
    int level = cur->_nextarray.size() - 1;
    while (level >= 0)
    {
        if (cur->_nextarray[level] == nullptr || cur->_nextarray[level]->_data > target)
        {
            //向下走
            --level;
        }
        else if (cur->_nextarray[level]->_data < target)
        {
            //向右走
            cur = cur->_nextarray[level];
        }
        else
            return true;
    }
    return false;
}


vector<Skiplist::Node*> Skiplist::FindPrev(int num)
{
    vector<Node*> prevV;
    Node* cur = _head;
    int level = cur->_nextarray.size() - 1;
    prevV.resize(level + 1);
    while (level >= 0)
    {
        //这里必须是大于等于号，往下走，才支持删除和多个相同数据
        if (cur->_nextarray[level] == nullptr || cur->_nextarray[level]->_data >= num)
        {
            prevV[level] = cur;
            //向下走
            --level;
        }
        else if (cur->_nextarray[level]->_data < num)
        {
            //向右走
            cur = cur->_nextarray[level];
        }
    }
    return prevV;
}

void Skiplist::Add(int num)
{
    vector<Node*> prevV = FindPrev(num);
    Node* newNode = new Node(num, Random());
    //newNode->_n++;


    //必须判断，不然把之前的数据会丢失
    if (newNode->_nextarray.size() > _head->_nextarray.size())
        _head->_nextarray.resize(newNode->_nextarray.size(), nullptr);


    prevV.resize(newNode->_nextarray.size(), _head);
    for (int i = 0; i < newNode->_nextarray.size(); ++i)
    {
        newNode->_nextarray[i] = prevV[i]->_nextarray[i];
        prevV[i]->_nextarray[i] = newNode;
    }

}

bool Skiplist::Erase(int num)
{
    vector<Node*> prevV = FindPrev(num);

    Node* del = prevV[0]->_nextarray[0];//prevV[0]是del第零层的前一个节点
    if (del == nullptr || del->_data != num)
    {
        return false;
    }
    else
    {
        for (int i = 0; i < del->_nextarray.size(); ++i)
        {
            prevV[i]->_nextarray[i] = del->_nextarray[i];
        }
        delete del;

        int i = _head->_nextarray.size()-1;
        while (i > 0)
        {
            if (_head->_nextarray[i] == nullptr)
                --i;
            else
                break;
        }
        _head->_nextarray.resize(i + 1);
        return true;
    }



}

void Skiplist::Print()
{
    Node* cur = _head;
    while (cur)
    {
        printf("%3d", cur->_data);
        for (int i = 0; i < cur->_nextarray.size(); ++i)
        {
            std::cout << "﹀";
        }
        cout << endl;
        cur = cur->_nextarray[0];
    }
}
//int Skiplist::Random()
//{
//    int level = 1;
//    while (rand() <= RAND_MAX * p && level < _maxlevel)
//        ++level;
//    return level;
//}

int Skiplist::Random()
{
    static std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    static std::uniform_real_distribution<double> distribution(0.0,1.0);
    size_t level = 1;
    while (distribution(generator) <= p && level < _maxlevel)
    {
        ++level;
    }
    return level;
 }