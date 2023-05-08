#ifndef TREE_NODE
#define TREE_NODE
#include <iostream>
#include <string>
class node
{
private:
    std::string info;
    int num;

public:
    node *father;
    node *left_child;
    node *right_cousin;
    node *next;

    node();
    node(std::string in, int num);
    ~node();

    int get_num();
    void add_num();
    node *get_root();
    std::string get_info();
};

#endif