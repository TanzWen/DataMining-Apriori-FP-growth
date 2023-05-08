#ifndef Item
#define Item
#include <string>
#include <fstream>
#include <set>
#include <algorithm>
using namespace std;

class item
{
private:
public:
    set<string> s;

    item();
    item(string v);
    item(item a, item b);
    ~item();

    void insert(string v);

    bool operator==(const item &other) const;

    void link(item &i);
};

namespace std
{
    template <>
    struct hash<item>
    {
        size_t operator()(const item &it) const
        {
            std::size_t hash = 0;
            for (const string &i : it.s)
            {
                hash ^= std::hash<string>()(i);
            }
            return hash;
        }
    };
}

#endif