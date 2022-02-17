#include "lean_thread/disearch.h"

DepthFirstOrder::DepthFirstOrder(Digraph G)
{
  int g_size = G.V();
  //创建一个和图中顶点数一样大小的marked数组
  this->marked = new bool[g_size];
  for (size_t i = 0; i < g_size; i++)
  {
    if (!this->marked[i])
    {
      dfs(G, i);
    }
  }
}

DepthFirstOrder::~DepthFirstOrder()
{
  if (this->marked != nullptr)
  {
    delete[] this->marked;
    this->marked = nullptr;
  }
}

void DepthFirstOrder::dfs(Digraph G, int)
{
  
}