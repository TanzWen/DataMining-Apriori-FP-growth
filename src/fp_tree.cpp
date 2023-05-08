#include "fp_tree.h"

fp_tree::fp_tree()
{
    tree_root = new node();
    table_root = new node();
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
fp_tree::fp_tree(fp_tree &t, string info, double n)
{ // 利用t提供的info条件模式基生成条件模式树以及头指针表
    tree_root = new node();
    table_root = new node();
    unordered_map<string, int> map;
    node *p = t.table_root;
    while (p->get_info() != info)
    { // 遍历到头表为info的位置
        p = p->left_child;
    }
    node *x = p;
    p = p->next;
    while (p)
    { // 对于每一个next前缀路径计数
        node *q = p->father;
        while (q->get_info() != "$")
        { // 支持度为节点自带的支持度
            map[q->get_info()] += p->get_num();
            q = q->father;
        }
        p = p->next;
    }
    vector<pair<string, int>> temp_vec;

    // 对条件模式基排序
    for (auto &i : map)
    {
        temp_vec.push_back(make_pair(i.first, i.second));
    }
    sort(temp_vec.begin(), temp_vec.end(), comp);

    // 添加头指针表
    for (pair<string, int> &pa : temp_vec)
    {
        if (pa.second >= n)
            add_table(pa);
        else
            map.erase(pa.first);
    }

    // 将每一条条件模式基建树
    p = x;
    p = p->next;
    while (p)
    { // 对于每一个next求前缀路径
        node *q = p->father;
        vector<pair<string, int>> v;
        while (q->get_info() != "$")
        {
            if (map[q->get_info()])
                v.push_back(make_pair(q->get_info(), map[q->get_info()]));
            q = q->father;
        }
        sort(v.begin(), v.end(), comp);
        for (int i = 0; i < p->get_num(); i++)
            insert_fp_tree(v);
        p = p->next;
    }
}
void fp_tree::insert_table(string info, node *p)
{
    node *q = table_root;
    while (q->get_info() != info)
    { // 从头指针表找到对应的节点
        q = q->left_child;
    }
    while (q->next)
    { // 遍历到最后一个next
        q = q->next;
    }
    q->next = p;
}
void fp_tree::add_table(pair<string, int> &pa)
{
    node *p = table_root;
    bool flag = true;
    while (p->left_child != NULL)
    {
        if (p->get_info() == pa.first)
        {
            flag = false;
            break;
        }
        p = p->left_child;
    }
    if (flag)
    {
        node *q = new node(pa.first, pa.second);
        p->left_child = q;
        q->father = p;
    }
}
void fp_tree::insert_fp_tree(vector<pair<string, int>> &v)
{
    node *p = tree_root;
    for (pair<string, int> &i : v)
    { // 遍历数组的每一个元素
        if (!p->left_child && p->get_info() != i.first)
        { // 当前节点没有孩子节点 && 节点信息不匹配

            // 新建节点，成为子节点
            node *q = new node(i.first, 1);
            q->father = p;
            insert_table(i.first, q);
            p->left_child = q;
            p = q;
        }
        else
        {
            node *q = p->left_child;
            while (q)
            { // 遍历当前节点的子节点
                if (q->get_info() == i.first)
                { // 如果字符匹配则+1
                    q->add_num();
                    p = q;
                    break;
                }
                if (!q->right_cousin)
                { // 兄弟节点为空，新建分支
                    node *k = new node(i.first, 1);
                    k->father = p;
                    insert_table(i.first, k);
                    q->right_cousin = k;
                    p = k;
                    break;
                }
                else // 不为空下一个节点为兄弟节点
                    q = q->right_cousin;
            }
        }
    }
}
int fp_tree::dfs(node *p, int layer)
{
    if (!p)
        return 0;
    for (int i = 0; i < layer; i++)
        cout << "|";
    cout << p->get_info() << ":" << p->get_num() << endl;
    dfs(p->left_child, layer + 1);
    dfs(p->right_cousin, layer);
    return 0;
}
void fp_tree::show_tree()
{
    dfs(tree_root, 0);
}
void fp_tree::show_table()
{
    node *p = table_root->left_child;
    int sum = 0;
    while (p)
    {
        cout << p->get_info() << ":" << p->get_num();
        node *q = p->next;
        while (q)
        {
            cout << " -> " << q->get_info() << ":" << q->get_num();
            q = q->next;
        }
        cout << endl;
        p = p->left_child;
        sum++;
    }
    if (!sum)
        cout << "NULL" << endl;
}
node *fp_tree::bottom_of_table()
{ // 返回头指针表最末尾
    node *p = table_root;
    while (p->left_child)
    {
        p = p->left_child;
    }
    return p;
}
bool fp_tree::is_single_path()
{ // 判断树是否是单路径
    node *p = tree_root->left_child;
    while (p)
    {
        if (p->right_cousin)
            return false;
        p = p->left_child;
    }
    return true;
}
bool fp_tree::empty()
{
    return tree_root->left_child != NULL ? false : true;
}
int fp_tree::layer()
{ // 单径树的层数
    int l = 0;
    node *p = tree_root;
    while (p->left_child)
    {
        l++;
        p = p->left_child;
    }
    return l;
}