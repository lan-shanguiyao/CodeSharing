//本项目基于 ISO C++17 标准
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <regex>

using namespace std;

struct Node
{
    Node():parent(nullptr), flag(true), depth(0) {}
    Node(const string& e): data(e), parent(nullptr), flag(true), depth(0) {}
    //data
    string data;//数据域
    Node* parent;//父节点
    bool flag;//是否可以有子节点，即，该节点是否为文件夹
    vector<Node*>child;//子节点
    unsigned depth;//树深,即当前节点所处的层数
};

//文件IO
class IO
{
public:
    vector<string> FileData;
    void InPut(const string& name)
    {
        InFile.open(name, ios_base::in);
        //如果文件打开失败
        if (!InFile.is_open())
        {
            cout << "File can't open" << endl;
            exit(EXIT_FAILURE);
        }
        char a[501];
        int i = 0;
        while (InFile.getline(a, sizeof(a)))
            FileData.push_back(a);
        InFile.clear();
        InFile.close();
    }
    void OutPut(const string& name, const vector<string>& data)//输出文件名，输出的行数，输出的数据
    {
        OutFile.open(name, ios_base::out);
        for (unsigned i = 0; i < data.size(); ++i)
            OutFile << data[i] << endl;
        OutFile.close();
    }
    //曲线救国,不符合 IO 类的通用性，慎用，使用时，三个函数必须全部使用
    void OutInit1(const string& filename) { OutFile.open(filename, ios_base::out); }
    void OutInit(const string& data) { OutFile << data; }
    void OutInit2() { OutFile.close(); }

private:
    fstream InFile;//文件输入
    ofstream OutFile;//文件输出
    string FileName;//文件名
};

//一个KTree类的对象就是一个 k-ary tree
class KTree
{
public:
    KTree():_size(0), _root(nullptr), _height(0) {}
    bool Empty() { return !_root; }//判空
    Node* Root()const { return _root; }//root
    unsigned Size()const { return _size; }//size
    //插入
    //插入根节点
    Node* InsertAsRoot(const string& e)
    {
        _size = 1;
        return _root = new Node(e);
    }
    //插入子节点 e 作为 x 的孩子插入
    Node* InsertAsChild(const string& e, Node* x)
    {
        _size++;
        Node* a = new Node(e);
        a->parent = x;
        a->depth = x->depth + 1;
        x->child.push_back(a);
        return a;
    }
    //遍历
    void Trav(Node* e, IO& io)
    {
        out(e->depth, io);//利用层数来显示次序
        io.OutInit(e->data);
        io.OutInit("\n");
        if (e->child.empty())
            return;
        for (unsigned i = 0; i < e->child.size(); ++i)
            Trav(e->child[i], io);
    }
    inline void out(unsigned x, IO& io)
    {
        for (unsigned i = 0; i < x; ++i)
            io.OutInit("    ");
    }
    //删除
    //高度更新

private:
    Node* _root;//root 节点
    unsigned _size;//树的节点个数
    unsigned _height;//树高

};

//输入数据处理，存入 k-ary tree 中
void ProcessIn(const vector<string>& data, KTree& tree)
{
    for (unsigned i = 0; i < data.size(); ++i)
    {
        unsigned cnt = 0;
        auto res = data[i].find('\\', cnt);
        vector<string> s;
        while (res != string::npos)
        {
            s.push_back(data[i].substr(cnt, res - cnt));
            cnt = res + 1;
            res = data[i].find('\\', cnt);
        }
        s.push_back(data[i].substr(cnt));
        //后期优化掉下面的循环,似乎没法优化？！
        if (i == 0)
            tree.InsertAsRoot(s[0]);
        Node* a = tree.Root();
        for (unsigned j = 1; j < s.size(); ++j)
        {
            bool f = false;
            for (unsigned k = 0; k < a->child.size(); ++k)
            {
                if (s[j] == a->child[k]->data)
                {
                    f = true;
                    a = a->child[k];
                }
            }
            //没找到就作为子节点插入
            if (!f)
                a = tree.InsertAsChild(s[j], a);
        }
    }
}

int main()
{
    IO io;
    KTree tree;
    io.InPut("Input1.txt");

    ProcessIn(io.FileData, tree);

    io.OutInit1("Output.txt");
    tree.Trav(tree.Root(), io);
    io.OutInit2();

    return 0;
}
