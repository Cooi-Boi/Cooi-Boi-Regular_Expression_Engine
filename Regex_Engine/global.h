#ifndef GLOBAL_H
#define GLOBAL_H

using namespace std;

enum states{UNACCEPTABLE,ACCEPTABLE};

//���� AST�� ÿ���ڵ��״̬
//             epsilon     �ַ�char    ѡ��|     ����+    �հ�*
enum exp_kind {EXP_EPSILON,EXP_CHR,EXP_SELECT,EXP_CONCAT,EXP_CLOSURE};

#endif // GLOBAL_H
