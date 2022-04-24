#include "dfa_node.h"
#include <unordered_set>

inline void DFA_node::print_DFA(unordered_set<DFA_node*>& set)
{
    if(!this || set.find(this) != set.end())   return;
    cout << "now_DFA_id: " << id;

    //ע�Ͳ����� �ж��Ƿ���ȷ���ֵ�һ���Ӽ���
    /*cout << ",now_NFA_ids: ";
    for(const auto& node: work_list)
        cout << node->id << " ";*/

    cout << ",state: " << (state == ACCEPTABLE ? "ACCEPTABLE" : "UNACCEPTABLE") << endl;
    set.emplace(this);

    int size = next_work_edges.size();
    cout << "next_DFA_id & cost_chr: ";
    for(int i=0;i<size;++i)
        cout << next_values[i] << "->" << next_work_edges[i]->id << " ";

    cout << "\n" << endl;
    for(int i=0;i<size;++i)
        next_work_edges[i]->print_DFA(set);
}
