#include "item.h"

item::item()
{
}
item::item(string v)
{
    s.insert(v);
}
item::item(item a, item b)
{
    for (string i : a.s)
    {
        s.insert(i);
    }
    for (string i : b.s)
    {
        s.insert(i);
    }
}
item::~item()
{
}
bool item::operator==(const item &other) const
{
    return s == other.s;
}
void item::insert(string v)
{
    s.insert(v);
}
void item::link(item &i)
{
    for (string v : i.s)
    {
        s.insert(v);
    }
}