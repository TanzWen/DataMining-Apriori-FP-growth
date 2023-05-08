#include "tree_node.h"

node::node():info("$"),num(0)
{
    father=NULL;
    left_child=NULL;
    right_cousin=NULL;
    next=NULL;
}
node::node(std::string in, int num):info(in),num(num)
{
    father=NULL;
    left_child=NULL;
    right_cousin=NULL;
    next=NULL;
}
node::~node(){}

std::string node::get_info()
{
    return info;
}
int node::get_num()
{
    return num;
}
void node::add_num()
{
    num++;
}

node* node::get_root()
{
    node *temp=father;
    while(temp!=NULL)
    {
        temp=temp->father;
    }
    return temp;
}