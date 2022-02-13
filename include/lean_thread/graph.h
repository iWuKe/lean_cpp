#ifndef GRAPH_H_
#define GRAPH_H_

#include <stdio.h>
#include <random>
#include <iostream>
#include <vector>
#include <functional>
#include <time.h>
#include <queue>
#include <vector>

class Graph
{
private:
  //记录顶点的数量
  int vertex;
  //记录边的数量
  int edge;
  //邻接表
  std::vector<std::vector<int>>  adj;

public:
  Graph(int);
  // ~Graph();
  //获取图中顶点的数量
  int V();
  //获取途中边的数量
  int E();
  //向途中增加一条边v-w
  void addEdge(int v, int w);
  //获取和定点v相邻的所有定点
  std::vector<int> Adj(int v);
};











#endif