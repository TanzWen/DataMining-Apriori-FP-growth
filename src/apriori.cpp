#include "apriori.h"

/*从候选集C_k生成频繁项集L_k+1*/
void apriori::C_2_L()
{
    for (auto &i : c)
    {
        if (c[i.first] >= sup * n)
        { // 支持度大于给定支持度
            l[i.first] = i.second;
        }
    }
    k += l.size();
    show_freq();
    c.clear();
}
/*判断两个item是否可以自链接*/
bool apriori::comp_set(const item &a, const item &b)
{ // 只有最后一个不同
    if (a.s.size() != b.s.size())
        return false;
    set<string>::iterator i1 = a.s.begin();
    set<string>::iterator i2 = b.s.begin();
    int n = a.s.size();

    for (int i = 1; i < n; i++)
    { // 遍历到最后一个
        if (*i1 != *i2)
            return false;
        i1++;
        i2++;
    }

    /* 长度等于1 || 最后一位相同 */
    if (n == 1 || *i1 == *i2)
        return *i1 != *i2;
    else
    {
        /* 新建状态 */
        item temp;
        temp.insert(*i1);
        temp.insert(*i2);
        bool flag = false;

        /* 剪枝 */
        for (auto &i : l)
        {
            vector<string> v;
            for(auto &j:i.first.s)
            {
                v.push_back(j);
            }
            if (is_find(v, temp))
            {
                flag = true;
                break;
            }
        }
        return flag;
    }
}
/*模式匹配*/
bool apriori::is_find(vector<string> &v, const item &it)
{ // 判断item是否是数组的子集
    if (v.size() < it.s.size())
        return false;
    for (string i : it.s)
    { // 只要有不存在
        if (find(v.begin(), v.end(), i) == v.end())
            return false;
    }
    return true;
}
/*从频繁项集Lk生成Ck*/
bool apriori::L_2_C()
{
    unordered_map<item, int>::iterator begin = l.begin();
    unordered_map<item, int>::iterator end = l.end();

    /*将频繁项集L_k中的元素进行连接*/
    for (auto i = begin; i != end; i++)
    {
        for (auto j = i; j != end; j++)
        {
            if (comp_set(i->first, j->first))
            { // 满足条件（只有最后一项不同，已减枝）
                item it(i->first, j->first);
                c[it] = 0;
            }
        }
    }

    /*如果无法生成项数更多的候选项集，返回false*/
    int max_len = 0;
    for (auto &i : c)
    {
        if (i.first.s.size() > max_len)
            max_len = i.first.s.size();
    }
    if (max_len <= l.begin()->first.s.size())
        return false;

    /* 对候选项集中的每一项计数 */

    // 读取文件
    string lines;
    string str;
    while (getline(file, lines))
    {
        stringstream ss(lines);
        vector<string> v;
        while (ss >> str)
        { // 将文件每一行的数据存在数组中
            if (str_count[str] >= sup * n)
                v.push_back(str);
            else
                str_count.erase(str);
        }
        for (auto &i : c)
        {
            if (is_find(v, i.first))
            { // 判断当前项集是否为数组的子集
                i.second++;
            }
        }
    }

    // 将文件指针移回文件开头
    file.clear();
    file.seekg(0);

    l.clear();
    return true;
}

/*Apriori算法*/
void apriori::run()
{

    int count_line = 0; // 计数有多少行

    /*读取文件内容并生成候选项集C_1*/
    string line;
    string input;
    while (getline(file, line))
    {
        stringstream ss(line);
        str_vector.push_back(line);
        while (ss >> input)
        {
            item i(input);
            c[i]++;
            str_count[input]++;
        }
        count_line++;
    }

    // 将文件指针移回文件开头
    file.clear();
    file.seekg(0);

    n = count_line;
    C_2_L(); // 从候选项集中生成L_1
    while (!l.empty())
    { // 当频繁项集为空||无法生成更长的候选项集 跳出循环
        if (!L_2_C())
            break;
        C_2_L();
    }

    cout << endl
         << "sum_freq:" << k << endl;
    output << endl
           << "sum_freq:" << k << endl;
}

apriori::apriori() {}
apriori::apriori(string file) : file_name(file), k(0)
{
    remove("data/apriori_output.txt");
    output.open("data/apriori_output.txt", ios::out);
    this->file.open(file, ios::in);
    // run();
}
apriori::apriori(string file, double supp, double con) : file_name(file), sup(supp), conf(con), k(0)
{
    remove("./data/apriori_output.txt");
    output.open("./data/apriori_output.txt", ios::out);
    this->file.open(file, ios::in);
    // run();
}
apriori::~apriori()
{
    file.close();
    output.close();
}

/*输出频繁项集*/
void apriori::show_freq()
{
    if (l.empty())
    {
        // cout << "l:null" << endl;
        output << "l:null" << endl;
    }
    else
    {
        cout << "k=" << l.begin()->first.s.size() << " finised..." << endl;
        // cout << "k:" << l.begin()->first.s.size() << " sum:" << l.size() << endl;

        for (auto &i : l)
        {
            for (string j : i.first.s)
            {
                // cout << j << " ";
                output << j << " ";
            }
            // cout << "supp:" << i.second << endl;
            output << "supp:" << i.second << endl;
        }
        output << "k:" << l.begin()->first.s.size() << " sum:" << l.size() << endl;
        // cout << endl;
        output << endl;
    }
}
void apriori::set_min_conf(double con)
{
    sup = con;
}