#include "lean_thread/disearch.h"

DepthFirstOrder::DepthFirstOrder(Digraph G)
{
  int g_size = G.V();
  //创建一个和图中顶点数一样大小的marked数组
  this->marked = new bool[g_size];
  std::cout << "marked " << std::endl;
  for (size_t i = 0; i < g_size; i++)
  {
    std::cout << "marked : " << i << std::endl;
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

void DepthFirstOrder::dfs(Digraph G, int v)
{
  this->marked[v] = true;
  std::vector<int> adj = G.Adj(v);
  for (auto w : adj)
  {
    //如果当前顶点没有被搜索过，则递归搜索与w顶点相通的其他顶点
    if (!this->marked[w])
    {
      dfs(G, w);
    }
  }
  //当前顶点已经搜索完毕，让当前顶点入栈
  this->reverse_post.push(v);
}

//获取顶点线性队列
std::stack<int> DepthFirstOrder::reversePose()
{
  return this->reverse_post;
}