#ifndef __ASTTREE_NODE_H__
#define __ASTTREE_NODE_H__

#include "global.h"

class ASTTree_node
{
    private:
        char value;                  // ֵ
        enum exp_kind kind;          // ����
        ASTTree_node* left,*right;   // �������߽ڵ�

        friend class NFA;
    public:


        ASTTree_node(char value = 0,enum exp_kind kind = EXP_EPSILON,\
                     ASTTree_node* left = nullptr,ASTTree_node* right = nullptr)
                    :value(value),kind(kind),left(left),right(right)     {}
        ~ASTTree_node() {}

        void inorder_print_node() const;
        void delete_node();
};

#endif // ASTTREE_NODE_H
