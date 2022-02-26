#ifndef DIGRAPH_H_
#define DIGRAPH_H_

#include <stdio.h>
#include <random>
#include <iostream>
#include <vector>
#include <functional>
#include <time.h>
#include <queue>
#include <vector>
#include <stack>

//加权无向图

//边
class Edge
{
private:

  //顶点1
  int v;
  int w;
  //当前边的权重
  double weight;

public:
  Edge(int v, int w, double weight);
  ~Edge();

  //获取边的权重值
  double getWeight();
  //获取边上一点
  int getEither();
  //获取边上除顶点v的另外一个顶点
  int getOther(int vertex);
  //比较当前边和参数that边的权重，如果当前边权重大，返回1，如果一样大返回0，如果当前权重小返回-1
  int compareTo(Edge that);
};


class EdgeWeightedGraph
{
private:
  //顶点数量
  int vertexs;
  //记录边的数量
  int edges;
  std::vector<std::vector<Edge>> adj;

public:
  //创建一个包含v个顶点的空加权无向图
  EdgeWeightedGraph(int v);
  ~EdgeWeightedGraph();
  //获取图中顶点的数量
  int V();
  //获取图中边的数量
  int E();
  //向加权无向图中添加一条边e
  void addEdge(Edge e);
  //获取和顶点v关联的所有边
  std::vector<Edge> Adj(int v);
  //获取加权无向图的所有边
  std::vector<Edge> edges();
};









#endif