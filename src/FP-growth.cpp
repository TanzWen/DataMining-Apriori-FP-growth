#include "FP-growth.h"

fp_growth::fp_growth() {}
fp_growth::fp_growth(string file_name, double supp, double con) : m(0), lines(0), file_name(file_name), sup(supp), conf(con), n(0), k(0)
{
    remove("./data/fp_growth_output.txt");
    output.open("./data/fp_growth_output.txt", ios::out);
    file.open(this->file_name, ios::in);
    // root = new node();
    // table = new node();
    // run();
}
fp_growth::~fp_growth()
{
    file.close();
    output.close();
}
int fp_growth::output_freq(node *root, vector<pair<string, int>> &v, item &it)
{ // 求单条路径的所有组合并输出到文件
    if (!root)
    {
        bool flag = false;
        int min = 99999999;
        for (auto &i : v)
        {
            if (i.first != "#")
            {
                flag = true;
                it.insert(i.first);
                if (i.second < min)
                    min = i.second;
            }
        }
        if (flag)
        {
            if (it.s.size() > m)
                m = it.s.size();
            items[it] = min;
        }
        return 0;
    }
    vector<pair<string, int>> v1 = v;
    vector<pair<string, int>> v2 = v;
    v1.push_back(make_pair<string, int>("#", 0));
    v2.push_back(make_pair<string, int>(root->get_info(), root->get_num()));

    output_freq(root->left_child, v1, it);
    output_freq(root->left_child, v2, it);
    return 1;
}
inline bool comp(const pair<string, int> &a, const pair<string, int> &b)
{

    if (a.second == b.second)
    {
        if (a.first[0] >= 0 + '0' && a.first[0] <= 9 + '0')
            return atoi(a.first.c_str()) < atoi(b.first.c_str());
        else
            return a.first < b.first;
    }
    else
        return a.second > b.second;
}
void fp_growth::proce_fp_growth(fp_tree &fptree, stack<pair<string, int>> &alpha)
{
    if (fptree.is_single_path())
    {
        k += (pow(2, fptree.layer()) - 1);
        item it;
        stack<pair<string, int>> s = alpha;
        while (!s.empty())
        {
            it.insert(s.top().first);
            s.pop();
        }
        vector<pair<string, int>> v;
        output_freq(fptree.tree_root->left_child, v, it);
    }
    else
    {
        node *p = fptree.bottom_of_table();
        while (p->get_info() != "$")
        {
            // cout<<p->get_info()<<":"<<p->get_num()<<endl;
            stack<pair<string, int>> beta = alpha;
            beta.push(make_pair<string, int>(p->get_info(), p->get_num()));
            k++;
            item it;
            stack<pair<string, int>> th = beta;
            while (!th.empty())
            {
                it.insert(th.top().first);
                th.pop();
            }
            items[it] = beta.top().second;
            if (it.s.size() > m)
                m = it.s.size();
            // cout<<p->get_info()<<endl;
            fp_tree fp_tree_beta(fptree, p->get_info(), sup * lines);
            if (!fp_tree_beta.empty())
                proce_fp_growth(fp_tree_beta, beta);
            // cout<<k<<endl;
            p = p->father;
        }
    }
}
void fp_growth::run()
{
    /* - 生成模式匹配树 */

    // 1. 读取并遍历数据库，对每一个item计数

    string str;
    while (getline(file, str))
    {
        lines++;
        stringstream ss(str);
        string s;
        while(ss>>s)
        {
            map[s]++;
        }
    }
    file.clear();
    file.seekg(0); // 将文件指针回到开头

    // 2. 将计数的item放进vector进行排序，并建立频繁单项集的头指针表
    vector<pair<string, int>> temp_vec;
    for (auto &i : map)
    {
        temp_vec.push_back(make_pair(i.first, i.second));
    }
    sort(temp_vec.begin(), temp_vec.end(), comp);
    for (pair<string, int> &p : temp_vec)
    {
        if (p.second >= sup * lines)
            tree.add_table(p);
        else
            map.erase(p.first);
    }

    // 3. 根据table修剪原数据，并建立fp_tree
    while (getline(file, str))
    {
        vector<pair<string, int>> v;
        stringstream ss(str);
        string s;
        while (ss >> s)
        {
            if (map[s])
                v.push_back(make_pair(s, map[s]));
        }
        sort(v.begin(), v.end(), comp);
        tree.insert_fp_tree(v);
    }
    cout << "fp_tree finished..." << endl;

    /* - 从FP树中挖掘频繁项集 */

    stack<pair<string, int>> s;
    proce_fp_growth(tree, s);
    cout << "procedure finished..." << endl;

    /* - 输出频繁项集 */
    show_items();
    if (tree.empty())
    {
        cout << endl
             << "freq_num:" << 0 << endl;
        output << "freq_num:" << 0 << endl;
    }
    else
    {
        cout << endl
             << "freq_num:" << k << endl;
        output << "freq_num:" << k << endl;
    }
}
void fp_growth::show_items()
{
    for (int a = 1; a <= m; a++)
    {
        int sum = 0;
        for (auto &i : items)
        {
            if (i.first.s.size() == a)
            {
                sum++;
                for (auto &j : i.first.s)
                {
                    output << j << " ";
                }
                output << "supp:" << i.second << endl;
            }
        }
        output << "k:" << a << " sum:" << sum << endl
               << endl;
    }
}