#ifndef ASTTREE_H
#define ASTTREE_H

#include "ASTTree_node.h"

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
        ASTTree_node* root;         // Node �ڵ�
        string re;                  // ������ʽ �ַ���
        char token;                 // ��ǰ�����ַ�
        int re_size;                // Ϊ��get_next_token ��ʡ��������re.size()�������õĴ���
        int pos;                    // ��ǰ���ڴ����ַ�λ�� get_next_token��

        friend class NFA;
    public:
        ASTTree():root(nullptr),token(0),re_size(0),pos(-1){
            re.clear();
        }

        ~ASTTree()  {delete_node_helper();}
                                    // ��������BNFʽ�� �õ������﷨ת�� ��Ҫ��Ϊ���ȼ�����
        ASTTree_node* parse_EXP();  // ���� |
        ASTTree_node* parse_A();    // ���� + ע��ݹ�
        ASTTree_node* parse_B();    // ���� * ��Ŀ�����
        ASTTree_node* parse_C();    // ������ܴ��ڵ�

        char get_next_token();
        void build_AST(string& str);
        void print_tree();

        void delete_node_helper();
};


char ASTTree::get_next_token()          // �õ���һ���ַ�
{
    return (re_size > (++pos) ? re[pos] : 0);
}

void ASTTree::build_AST(string& str)    // ����AST������ �ݹ��½�����
{
    if(str.empty())      return;

    re = str; re_size = re.size();
    pos = -1; token  = get_next_token();
    root = parse_EXP();
}

ASTTree_node* ASTTree::parse_EXP()      // ��ʼ�ݹ��½����� ����������ע�͸����� ���� BNF ������
{
    ASTTree_node* ret = parse_A();
    while(token == '|')
    {
        token = get_next_token();
        ASTTree_node* left = ret,*right = parse_EXP();
        ret = new ASTTree_node('|',EXP_SELECT,left,right);
    }

    return ret;
}

ASTTree_node* ASTTree::parse_A()       // ���� +
{
    ASTTree_node* ret = parse_B();
    while(token != 0 && token != ')' && token != '|')       //���ܵ�ǰΪ| ���� ) ��ֱ�Ӳ������ж�
    {
        ASTTree_node* left = ret,*right = parse_B();
        ret = new ASTTree_node('+',EXP_CONCAT,left,right);
    }
    return ret;
}

ASTTree_node* ASTTree::parse_B()       // ���� *
{
    ASTTree_node* ret = parse_C();
    if(token == '*')
    {
        ASTTree_node* left = ret;
        ret   = new ASTTree_node(token,EXP_CLOSURE,left);
        token = get_next_token();
    }
    return ret;
}

ASTTree_node* ASTTree::parse_C()       //����������ȼ� () ע����� | ����ǰ��� ��Ҫ�ر�ע��
{
    ASTTree_node* ret = nullptr;
    if(token == ')')    return ret;

    if(token == '(')
    {
        token = get_next_token();
        ret = parse_EXP();
        token = get_next_token();      //�����ұ�����(
    }
    else
    {
        if(token == '|' || !token)               // �������
            ret = new ASTTree_node(0,EXP_EPSILON);
        else                           // �������� �ս��
        {
            ret = new ASTTree_node(token,EXP_CHR);
            token = get_next_token();
        }
    }
    return ret;
}

void ASTTree::print_tree()              // ������� �ȽϷ�����֤�Ƿ�������ȷ
{
    if(!this)   return;
    cout << "ASTTree_Print: " << endl;
    root->inorder_print_node();
    cout << endl;
}

void ASTTree::delete_node_helper()
{
    if(!root)   return;
    root->delete_node();
}

#endif // ASTTREE_H
