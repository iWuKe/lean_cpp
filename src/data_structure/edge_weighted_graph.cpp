#include "learn_thread/edge_weighted_graph.h"


Edge::Edge(int v, int w, double weight)
{
  this->v = v;
  this->w = w;
  this->weight = weight;
}

Edge::~Edge()
{
}

//获取边上一个点
int Edge::getEither()
{
  return this->v;
}

//获取边上处理顶点vertex外的另外一个点
int Edge::getOther(int vertex)
{
  if (vertex == this->v)
  {
    return this->w;
  }
  else if (vertex == this->w)
  {
    return this->v;
  }
}

double Edge::getWeight()
{
  return this->weight;
}

int Edge::compareTo(Edge that)
{
  int cmp;
  if (this->weight > that.getWeight())
  {
    cmp = 1;
  }else if (this->weight < that.getWeight())
  {
    cmp = -1;
  }else
  {
    cmp = 0;
  }
  return cmp;
}


EdgeWeightedGraph::EdgeWeightedGraph(int v)
{
  this->vertexs = v;
  this->edges = 0;
  this->adj.resize(v);
}

EdgeWeightedGraph::~EdgeWeightedGraph()
{
}

//获取顶点的数量
int EdgeWeightedGraph::V()
{
  return this->vertexs;
}

//获取边的数量
int EdgeWeightedGraph::E()
{
  return this->edges;
}

//向加权无向图中添加一条边e
void EdgeWeightedGraph::addEdge(Edge e)
{
  //获取边中的一个顶点v
  int v = e.getEither();
  //获取边中的另一个顶点w
  int w = e.getOther(v);

  //因为是无向图，所以边e需要同时出现在两个顶点的邻接表中
  this->adj.at(v).push_back(e);
  this->adj.at(w).push_back(e);

  this->edges ++;
}

//获取边和顶点v关联的所有边
std::vector<Edge> EdgeWeightedGraph::Adj(int v)
{
  return this->adj.at(v);
}

//获取加权无向图的所有边
std::vector<Edge> EdgeWeightedGraph::edges()
{
  std::vector<Edge> allEdge;
  //遍历每一个顶点拿到每个顶点的邻接表
  for (size_t i = 0; i < this->vertexs; i++)
  {
    for (const auto e : this->adj.at(i))
    {
      //因为无向图中，每条边对象Edge都会在两个顶点的邻接表中各出现一次，为了不重复获取，暂定一条规则
      //出了当前点v，在获取边e中的另外一个顶点w，如果v<w则添加，这样保证同一条边只会被统计一次
      if(e.getOther(i) < v)
      {
        allEdge.push_back(e);
      }
    }
  }
  return allEdge;
}














