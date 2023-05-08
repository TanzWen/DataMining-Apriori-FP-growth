#ifndef Apriori
#define Apriori
#include <string>
#include <fstream>
#include <set>
#include <algorithm>
#include <unordered_map>
#include <iostream>
#include <iterator>
#include <vector>
#include <sstream>

#include "item.h"

using namespace std;
#define MAXSIZE 20000

class apriori
{
private:
    int n;       // 总数据数
    int k;       // 总频繁项集数
    double sup;  // 支持度
    double conf; // 置信度
    string file_name;
    vector<string> str_vector;  // 将每一行数据存放
    unordered_map<item, int> c; // 候选项集
    unordered_map<item, int> l; // 频繁项集
    unordered_map<string, int> str_count;// 对每一项计数

    fstream file;
    fstream output;

    /*从候选集C_k生成频繁项集L_k+1*/
    void C_2_L();
    /*从频繁项集Lk生成Ck*/
    bool L_2_C();
    /*比较两个项目最后一项*/
    bool comp_set(const item &a, const item &b);
    /*判断item是否是数组的子集*/
    bool is_find(vector<string> &v, const item &it);

public:
    apriori();
    apriori(string file);
    apriori(string file, double supp, double con);
    ~apriori();

    /*输出频繁项集*/
    void show_freq();
    /*Apriori算法*/
    void run();
    /*设置最小支持度*/
    void set_min_conf(double con);
};

#endif