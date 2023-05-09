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
    cout << "please input supp(0-1):";
    double supp; // 输入x，支持度x%
    cin >> supp;
    double conf = 0.01;

    apriori apri(file_name, supp , conf);
    fp_growth fp_g(file_name, supp , conf);

    cout << "choose algorithm( 1 || 2 || 3 ):" << endl
         << "1. Apriori" << endl
         << "2. FP-growth" << endl
         << "3. Apriori && FP-growth" << endl
         << endl;

    int c;
    cin >> c;
    switch (c)
    {
    case 1:
        /*采用 Apriori 算法求解频繁项集*/

        cout << "Apriori:" << endl;
        start = clock();

        apri.run();

        end = clock();                                                             // 结束时间
        cout << "time = " << double(end - start) / CLOCKS_PER_SEC << " s" << endl; // 输出时间（单位：ｓ）
        break;
    case 2:
        /*采用 FP-growth 算法*/
        cout << "FP-growth:" << endl;
        start = clock();
        fp_g.run();
        end = clock();                                                             // 结束时间
        cout << "time = " << double(end - start) / CLOCKS_PER_SEC << " s" << endl; // 输出时间（单位：ｓ）
        break;

    case 3:
        /*采用 Apriori 算法求解频繁项集*/

        cout << "Apriori:" << endl;
        start = clock();

        apri.run();

        end = clock();                                                             // 结束时间
        cout << "time = " << double(end - start) / CLOCKS_PER_SEC << " s" << endl; // 输出时间（单位：ｓ）

        /*采用 FP-growth 算法*/

        cout << endl
             << "FP-growth:" << endl;
        start = clock();

        fp_g.run();

        end = clock();                                                             // 结束时间
        cout << "time = " << double(end - start) / CLOCKS_PER_SEC << " s" << endl; // 输出时间（单位：ｓ）
        break;
    default:
        break;
    }
    return 0;
}
