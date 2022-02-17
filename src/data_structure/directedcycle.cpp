#include "lean_thread/directedcycle.h"

DirectedCycle::DirectedCycle(Digraph G)
{
  int dg_size = G.V();
  //创建一个和图的顶点数一样大小的marked数组
  this->marked = new bool[dg_size];
  //创建一个和图中顶点数一样大小的onStack数组
  this->onStack = new bool[dg_size];
  //默认没有环
  this->hasCycle = false;
  //遍历搜索图中每一个顶点
  for (int i = 0; i < dg_size; i++)
  {
    if(!this->marked[i])
    {
      //如果当前顶点没搜索过则搜索
      dfs(G, i);
    }
  }
}

DirectedCycle::~DirectedCycle()
{
  if (this->onStack != nullptr)
  {
    delete[] this->onStack;
    this->onStack = nullptr;
  }
  if (this->marked != nullptr)
  {
    delete[] this->marked;
    this->marked = nullptr;
  }
}

void DirectedCycle::dfs(Digraph G, int v)
{
  //将当前顶点标记为已搜索
  this->marked[v] = true;
  //将当前点入栈
  this->onStack[v] = true;

  //遍历v顶点的邻接表，得到每一个顶点w
  std::vector<int> adj = G.Adj(v);
  for(auto w : adj)
  {
    //如果当前顶点w没有被搜索过，则递归搜索与w顶点相通的其他顶点
    if (!this->marked[w])
    {
      dfs(G, w);
    }
    //如果当前顶点w已经被搜索过，则查看顶点w是否在栈中，如果在，则证明图中有环，修改hasCycle标记，结束循环
    if (this->onStack[w])
    {
      this->hasCycle = true;
      return;
    }
  }
  //当前顶点已经搜索完毕让当前顶点出栈
  this->onStack[v] = false;
}

//判断w顶点与s顶点是否相通
bool DirectedCycle::HasCycle()
{
  return this->hasCycle;
}

