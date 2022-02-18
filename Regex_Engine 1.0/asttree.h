#ifndef __ASTTREE_H__
#define __ASTTREE_H__

#include "asttree_node.h"
using namespace std;
/*
eΪ�ս��
EXP -> A | EXP
    -> A
A   -> B + A
A   -> B
B   -> C
    -> C*
C   -> (EXP)
    -> e
*/

class ASTTree
{
    private:
        string re;                  // ������ʽ �ַ���
        ASTTree_node* root;         // Node �ڵ�
        char token;                 // ��ǰ�����ַ�
        int re_size;                // Ϊ��get_next_token ��ʡ��������re.size()�������õĴ���
        int pos;                    // ��ǰ���ڴ����ַ�λ�� get_next_token��

        friend class NFA;
    public:
        char get_next_token();
        void build_AST();
        void print_tree() const;
        void delete_node_helper();

        ASTTree():re(),root(nullptr),token(0),re_size(0),pos(-1)    {}
        ASTTree(const string& str):re(str),root(nullptr),token(0),re_size(re.size()),pos(-1)   { build_AST();}

        ~ASTTree()  {delete_node_helper();}
                                    // ��������BNFʽ�� �õ������﷨ת�� ��Ҫ��Ϊ���ȼ�����
        ASTTree_node* parse_EXP();  // ���� |
        ASTTree_node* parse_A();    // ���� + ע��ݹ�
        ASTTree_node* parse_B();    // ���� * ��Ŀ�����
        ASTTree_node* parse_C();    // ������ܴ��ڵ�
};

#endif // ASTTREE_H
