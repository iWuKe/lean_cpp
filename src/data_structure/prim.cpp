#include "lean_thread/prim.h"


PrimMST::PrimMST(EdgeWeightedGraph G)
{
  int g_size = G.V();
  //创建一个和图的顶点数一样大小的edge数组，表示边
  this->edgeTo.resize(g_size);
  //创建一个和图中顶点数一样大小的double数组，表示权重，并且初始化数组中的内容为无穷大，无穷大及表示不存在这样的边
  this->distTo = new double[g_size];
  for (size_t i = 0; i < g_size; i++)
  {
    this->distTo[i] = 1e6;
  }
  
  //创建一个和图的顶点数一样大小的bool数组，表示当前顶点是否已经在树中
  this->marked = new bool[g_size];
  //创建一个和图的顶点数一样大小的索引优先队列，存储有效横切边
  this->pq.resize(g_size);
  //默认让树顶点0进入树中，但0顶点目前没有与树中其他的顶点相连接，因此初始化distTo[0] = 0.0
  this->distTo[0] = 0.0;
  //
}

PrimMST::~PrimMST()
{
}


void PrimMST::visit(EdgeWeightedGraph G, int v)
{
  //将顶点v添加到树中
  this->marked[v] = true;
  //
  std::vector<Edge> adj = G.Adj(v);
  for (Edge e : adj)
  {
    //边e的一个顶点是v，找到另外一个顶点w
    int w = e.other(v);
    //检测是否已经在树中，如果在，则继续下一次循环，如果不在，则需要修正当前顶点w距离最小生成树
    //的最小边edgeTo[w]以及他的权重diistTo[w],还有有效横切边也需要修正
    if (this->marked[w])
    {
      continue;
    }

    //如果v-w边e的权重比目前distTo[w]权重小，则需要修正数据
    if (e.weight() < distTo[w])
    {
      //把顶点w距离最小生成树的边修改为e
      this->edgeTo[w] = e;
    }
    
  }
  

}