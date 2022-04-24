#include "asttree.h"

inline void ASTTree::build_AST()    // ����AST������ �ݹ��½�����
{
    if(re.empty())      return;

    token  = get_next_token();
    root = parse_EXP();
}

inline void ASTTree::delete_node_helper()
{
    if(!root)   return;
    root->delete_node();
    delete root;
}

inline char ASTTree::get_next_token()          // �õ���һ���ַ�
{
    return (re_size > (++pos) ? re[pos] : 0);
}

inline void ASTTree::print_tree() const          // ������� �ȽϷ�����֤�Ƿ�������ȷ
{
    if(!root)   return;
    cout << "ASTTree_Print: " << endl;
    root->inorder_print_node();
    cout << endl;
}

inline ASTTree_node* ASTTree::parse_EXP()      // ��ʼ�ݹ��½����� ����������ע�͸����� ���� BNF ������
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

inline ASTTree_node* ASTTree::parse_A()       // ���� +
{
    ASTTree_node* ret = parse_B();
    while(token != 0 && token != ')' && token != '|')       //���ܵ�ǰΪ| ���� ) ��ֱ�Ӳ������ж�
    {
        ASTTree_node* left = ret,*right = parse_B();
        ret = new ASTTree_node('+',EXP_CONCAT,left,right);
    }
    return ret;
}

inline ASTTree_node* ASTTree::parse_B()       // ���� *
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

inline ASTTree_node* ASTTree::parse_C()       //����������ȼ� () ע����� | ����ǰ��� ��Ҫ�ر�ע��
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
