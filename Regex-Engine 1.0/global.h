#ifndef __GLOBAL_H__
#define __GLOBAL_H__

enum states{UNACCEPTABLE,ACCEPTABLE};

//���� AST�� ÿ���ڵ��״̬
//             epsilon     �ַ�char    ѡ��|     ����+    �հ�*
enum exp_kind {EXP_EPSILON,EXP_CHR,EXP_SELECT,EXP_CONCAT,EXP_CLOSURE};

#endif // GLOBAL_H
