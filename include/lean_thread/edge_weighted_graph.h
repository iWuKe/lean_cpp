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



//相关概念

/*
最小生成树：包含一颗含有其所有顶点的无环连通子图，一副加权无向图的最小生成树他的一颗权值（书中所有边的权重之和）最小生成树
最小生成树只存在于连通图中，如果图不是联通的，那么分别计算每个联通图子图的最小生成树，合并到一起称为最小生成森林
如果边的权重可以相同，那么一幅图的最小生成树可能不唯一

性质：1. 用一条边连接图中的任意两个顶点，都会产生新的一个环
     2. 从树中删除任意一条边，将会得到两颗独立的树

切分定理：要从一副连通图中找出该图的最小生成树，需要通过切分定理完成
        切分：将图中的所有顶点按照某些规则分为两个非空且没有交集的集合
        横切边：连接两个属于不同集合的顶点的边称之为横切边
 * /

#endif