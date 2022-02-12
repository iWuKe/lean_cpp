#include "lean_thread/graph.h"

Graph::Graph(int vertex)
{
  //初始化定点数量
  this->vertex = vertex;
  this->edge = 0;
  //初始化邻接表
  this->adj.resize(vertex);
  //初始化邻接表中的空队列
  // for (size_t i = 0; i < this->adj.size(); i++)
  // {

  // }
}

//获取顶点数目
int Graph::V()
{
  return this->vertex;
}

//获取边的数目
int Graph::E()
{
  return this->edge;
}

//向图中添加一条边v-w
void Graph::addEdge(int v, int w)
{
  //把w添加到v的邻接表中，这样顶点v就多了一条相邻点w
  this->adj.at(v).push_back(w);
  this->adj.at(w).push_back(v);
  this->edge++;
}

std::vector<int> Graph::Adj(int v)
{
  return this->adj.at(v);
}
