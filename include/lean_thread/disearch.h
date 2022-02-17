#ifndef DISEARCH_H_
#define DISEARCH_H_

#include "lean_thread/digraph.h"
#include "lean_thread/directedcycle.h"

//基于深度优先的顶点排序
class DepthFirstOrder
{
private:

  //基于深度优先搜索，生成顶点线性序列
  void dfs(Digraph G, int v);

  //索引代表顶点，值表示当前顶点是否已经被搜索
  bool* marked;

  //使用栈，存储顶点序列
  std::stack<int> reverse_post;
public:
  DepthFirstOrder(Digraph G);

  //使用栈，存储顶点序列
  std::stack<int> reversePose();
  ~DepthFirstOrder();
};




#endif