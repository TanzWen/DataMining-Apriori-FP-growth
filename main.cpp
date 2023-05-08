#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

#include "apriori.h"
#include "FP-growth.h"
using namespace std;

int main()
{
    clock_t start, end; // 定义clock_t变量
    string file_name = "./data/retail.dat";
    cout << "please input supp(s%):";
    double supp; // 输入x，支持度x%
    cin >> supp;
    double conf = 0.01;

    /*采用 Apriori 算法求解频繁项集*/

    cout << "Apriori:" << endl;
    start = clock();
    apriori apri(file_name, supp / 100.0, conf);
    end = clock();                                                             // 结束时间
    cout << "time = " << double(end - start) / CLOCKS_PER_SEC << " s" << endl; // 输出时间（单位：ｓ）
    cout << endl
         << "FP-growth:" << endl;

    /*采用 FP-growth 算法*/

    start = clock();
    fp_growth fp_g(file_name, supp / 100.0, conf);
    end = clock();                                                             // 结束时间
    cout << "time = " << double(end - start) / CLOCKS_PER_SEC << " s" << endl; // 输出时间（单位：ｓ）

    // system("pause");

    return 0;
}
