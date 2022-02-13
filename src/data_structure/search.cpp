#include "lean_thread/search.h"


DepthFirstSearch::DepthFirstSearch(Graph G, int s)
{
  //创建一个和图中顶点数一样大小的布尔数组
  this->marked = new bool[s];
  dfs(G,s);
}

DepthFirstSearch::~DepthFirstSearch()
{
  if (this->marked != nullptr)
  {
    delete[] this->marked;
  }
}

void DepthFirstSearch::dfs(Graph G, int v)
{
  //把当前顶点标记为已搜索
  marked[v] = true;
  //遍历v顶点的邻接表，得到每一个顶点w
  std::vector<int> adj = G.Adj(v);
  for (auto w : adj)
  {
    if (!this->marked[w])
    {
      dfs(G,w);
    }
  }
  //相通的顶点数+1
  this->count ++;
}

bool DepthFirstSearch::Marked(int w)
{
  return this->marked[w];
}

int DepthFirstSearch::Count()
{
  return this->count;
}


