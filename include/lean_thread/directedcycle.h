#ifndef DIRECTED_CYCLE_H_
#define DIRECTED_CYCLE_H

#include "lean_thread/digraph.h"

//拓扑排序
/*
给定一副有向图，将所有的定点排序，使得所有的有向边均从排在前面的元素指向排在后面的元素，此时就可以明确地表示每个顶点的优先级
*/

//检测有向环
class DirectedCycle
{
private:
  //基于深度有限搜索，检测图中是否有环
  void dfs(Digraph G,int v);

  //索引代表顶点，值表示当前顶点是否已经被搜索
  bool* marked;
  //记录图中是否有环
  bool hasCycle;
  //索引代表顶点，使用栈的思想，记录当前顶点有没有已经处于正在搜索的有向路径上
  bool* onStack;
public:
  DirectedCycle(Digraph G);
  ~DirectedCycle();

  //判断图中是否有环
  bool HasCycle();

};



#endif