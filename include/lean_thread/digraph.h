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

//有向图
class Digraph
{
private:
  int vertex;
  int edge;
  std::vector<std::vector<int>> adj;
public:
  //创建一个包含v个顶点但不包含边的有向图
  Digraph(int);
  ~Digraph();
  //获取图中顶点的数量
  int V();
  //获取图中边的数量
  int E();
  //向有向图中添加一条边 v->w
  void addEdge(int v, int w);
  //获取由v支出的边所连接的所有顶点
  std::vector<int> Adj(int v);
  //该图的反向图
  Digraph reverse();
};





#endif