#ifndef FPGROWTH
#define FPGROWTH
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include <sstream>
#include <math.h>
#include "fp_tree.h"
#include "item.h"
using namespace std;

class fp_growth
{
private:
    int n; // 总数据数
    int k; // 总频繁项集数
    int m; // 最多有m项集
    int lines;
    double sup;  // 支持度
    double conf; // 置信度
    string file_name;
    fstream file;
    fstream output;
    unordered_map<string, int> map;
    unordered_map<item, int> items;

    fp_tree tree;

    // bool comp(const pair<string, int> &a, const pair<string, int> &b);
    // bool comp1(const string &a, const string &b);
    void proce_fp_growth(fp_tree &fptree, stack<pair<string, int>> &alpha);
    int output_freq(node *root, vector<pair<string, int>> &v, item &it);
    void show_items();

public:
    fp_growth();
    fp_growth(string file, double supp, double con);
    ~fp_growth();

    void run();
};

#endif