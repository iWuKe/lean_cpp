#pragma once

#include <stdio.h>
#include <random>
#include <iostream>
#include <vector>
#include <functional>
#include <time.h>
#include <queue>
#include <vector>
#include <stack>


class DirectedEdge
{
private:
  //起点
  int v;
  //终点
  int w;
  //边的权重
  double weight;
public:
  //通过顶点v和w，以及权重weight值构造一个边对象
  DirectedEdge(int v, int w, double weight)
  {
    this->v = v;
    this->w = w;
    this->weight = weight;
  }
  ~DirectedEdge();

  //获取边的权重值
  double getWeight()
  {
    return weight;
  }
  //获取有向边的起点
  int getFrom()
  {
    return v;
  }
  //获取有向边的终点
  int getTo()
  {
    return w;
  }
};























