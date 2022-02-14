#include "lean_thread/digraph.h"

Digraph::Digraph(int V)
{
  //初始化顶点数量
  this->vertex = V;
  //初始化边的数量
  this->edge = 0;
  //初始化邻接表
  this->adj.resize(V);
}

Digraph::~Digraph()
{
}

//返回顶点的数目
int Digraph::E()
{
  return this->edge;
}

//返回边的数目
int Digraph::V()
{
  this->vertex;
}

//向有向图中添加一条边 v->w
void Digraph::addEdge(int v, int w)
{
  //由于是有项目，v->w 边，只需要w出现在v的邻接表中，而不需要让v出现在w的邻接表中
  this->adj[v].push_back(w);
  this->edge ++;
}

//获取v支出的边所连接的所有顶点
std::vector<int> Digraph::Adj(int v)
{
  return this->adj.at(v);
}

//获取该图的反响图
Digraph Digraph::reverse()
{
  Digraph r(this->vertex);
  //遍历 0-v-1所有顶点，拿到没一个顶点v
  for (size_t i = 0; i < this->vertex; i++)
  {
    
  }
  

}

