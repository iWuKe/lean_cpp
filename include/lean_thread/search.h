#ifndef SEARCH_H_
#define SEARCH_H_

#include "lean_thread/graph.h"

class DepthFirstSearch
{
private:
  //使用深度优先搜索找出G图中v顶点的所有想通顶点
  void dfs(Graph G, int v);

  //索引代表顶点，值表示当前顶点是否已经被搜索
  bool *marked;
  //记录有多少顶点与s顶点相通
  int count;
public:
  DepthFirstSearch(Graph G, int s);
  ~DepthFirstSearch();
  //判断w顶点和s顶点是否想通
  bool Marked(int w);
  //获取与顶点s相通的所有顶点的总数
  int Count();
};






#endif