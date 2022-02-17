#ifndef SEARCH_H_
#define SEARCH_H_

#include "lean_thread/graph.h"

//搜索
namespace dfs
{
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
} // namespace dfs

namespace dfp
{
class DepthFirstPaths
{
private:
  void dfs(Graph G, int v);

  bool* marked;
  //起点
  int s;
  //索引代表顶点，值代表从起点s到当前顶点路径上的最后一个顶点
  int* edgeTo;
public:
  DepthFirstPaths(Graph G, int s);
  ~DepthFirstPaths();
  //判断v顶点与s顶点是否存在路径
  bool hasPathTo(int v);
  //找出从起点s到顶点v的路径(就是该路径经过的顶点)
  std::stack<int> pathTo(int v);
};

} // namespace dfp

namespace bfs
{
class BreadthFirstSearch
{
private:
  //
  bool* marked;
  //
  int count;
  //栈容器先进先出
  std::queue<int> waitSearch;
public:
  BreadthFirstSearch(Graph G, int s);
  ~BreadthFirstSearch();
  void bfs(Graph G, int v);
  //
  bool Marked(int w);
  //
  int Count();
};

} // namespace bfs









#endif