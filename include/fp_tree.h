#ifndef FP_TREE
#define FP_TREE
#include <vector>
#include <stack>
#include <unordered_map>
#include "tree_node.h"
#include <algorithm>
using namespace std;
class fp_tree
{
private:
    int dfs(node *p, int layer);

public:
    node *tree_root;
    node *table_root;

    fp_tree();
    fp_tree(fp_tree &t, string info, double n);
    void add_table(pair<string, int> &pa);
    void insert_table(string info, node *p);
    void insert_fp_tree(vector<pair<string, int>> &v);

    void show_tree();
    void show_table();

    node *bottom_of_table();
    bool is_single_path();
    bool empty();
    
    int layer();
};

#endif