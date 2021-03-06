#ifndef PRIM_H_
#define PRIM_H_
#include "learn_thread/edge_weighted_graph.h"

//prim算法
//prim算法始终将图中的顶点切分成两个集合，最小生成树顶点和非最小生成树顶点，通过不断的重复做某些操作
//可以逐渐将非最小生成树中的顶点加入到最小生成树中，直到所有的顶点都加入到最小生成树中。

class PrimMST
{
private:
  /* data */
  //将顶点v添加到最小生成树中，并且更新数据
  void visit(EdgeWeightedGraph G, int v);
  //获取最小生成树的所有边
  std::vector<Edge> edges();
  //索引代表顶点，值表示当前顶点和最小生成树之间的最短边
  std::vector<Edge> edgeTo;
  //索引代表顶点，值表示当前顶点和最小生成树之间的最短边的权重
  double* distTo;
  //索引代表顶点，如果当前顶点已经在树中，则值为true，否则为false
  bool* marked;
  //存放树中顶点与非树中顶点之间的有效横切边
  std::multimap<int, double> pq;
  // std::priority_queue<int, std::vector<int>, greater<int>> pq;
public:
  //根据一副加权无向图，创建最小生成树计算对象
  PrimMST(EdgeWeightedGraph G);
  ~PrimMST();
};




#endif