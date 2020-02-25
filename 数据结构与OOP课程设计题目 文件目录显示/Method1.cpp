//本项目基于 ISO C++17 标准
#include <iostream>
#include <filesystem>

using namespace std;
using namespace filesystem;

inline void print(int n)
{
    for (int i = 0; i < n; ++i)
        cout << "    ";
}

int main()
{
    string s;
    cout << "输入文件夹路径（绝对路径）：" << endl;
    cin >> s;
    path str(s);

    if (!exists(str)) { return 1; }//确认路径存在

    directory_entry entry(str);//文件入口
    recursive_directory_iterator list(str);//文件入口容器
    for (auto& it : list)
    {
        print(list.depth());
        cout << it.path().filename() << endl;
    }
    return 0;
}
