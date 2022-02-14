#include "lean_thread/search.h"

namespace dfs
{
DepthFirstSearch::DepthFirstSearch(Graph G, int s):count(0)
{
  //创建一个和图中顶点数一样大小的布尔数组
  this->marked = new bool[G.V()];
  dfs(G,s);
}

DepthFirstSearch::~DepthFirstSearch()
{
  if (this->marked != nullptr)
  {
    delete[] this->marked;
    this->marked = nullptr;
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
} // namespace dfs

namespace dfp{

DepthFirstPaths::DepthFirstPaths(Graph G, int s)
{
  this->marked = new bool[G.V()];
  for (size_t i = 0; i < G.V(); i++)
  {
    this->marked[i] = false;
  }
  //创建一个和图顶点数一样大小的整形数组
  this->edgeTo = new int[G.V()];
  this->s = s;
  dfs(G,s);
}

DepthFirstPaths::~DepthFirstPaths()
{
  if (this->marked != nullptr)
  {
    delete[] this->marked;
    this->marked = nullptr;
  }
}

void DepthFirstPaths::dfs(Graph G, int v)
{
  this->marked[v] = true;
  std::vector<int> adj = G.Adj(v);
  for (auto w : adj)
  {
    if (!this->marked[w])
    {
      this->edgeTo[w] = v;
      dfs(G, w);
    }
  }
}

//判断w顶点和s顶点是否存在路径
bool DepthFirstPaths::hasPathTo(int v)
{
  return this->marked[v];
}

std::stack<int> DepthFirstPaths::pathTo(int v)
{
  std::stack<int> path;
  //当前v顶点与s顶点不通，直接返回空，没有路径
  if (!hasPathTo(v))
  {
    std::cout << "null " << std::endl;
    return path;
  }
  for (int x = v; x != this->s; x = this->edgeTo[x])
  {
    path.push(x);
  }
  //吧起点放入容器
  path.push(this->s);
  return path;
}

}


namespace bfs
{
BreadthFirstSearch::BreadthFirstSearch(Graph G, int s): count(0)
{
  this->marked = new bool[G.V()];
  for (size_t i = 0; i < G.V(); i++)
  {
    this->marked[i] = false;
  }
  bfs(G,s);
}

BreadthFirstSearch::~BreadthFirstSearch()
{
  if (this->marked != nullptr)
  {
    delete[] this->marked;
    this->marked = nullptr;
  }
}

//广度优先搜索
void BreadthFirstSearch::bfs(Graph G, int v)
{
  this->marked[v] = true;
  this->waitSearch.push(v);
  
  //查看开放队列是否为空
  while (!this->waitSearch.empty())
  {
    //弹出
    int wait = this->waitSearch.back();
    this->waitSearch.pop();
    std::vector<int> adj = G.Adj(wait);
    for (auto w : adj)
    {
      if (!this->marked[w])
      {
        bfs(G,w);
      }
    }
  }
  this->count++;
}

bool BreadthFirstSearch::Marked(int w)
{
  return this->marked[w];
}

int BreadthFirstSearch::Count()
{
  return count;
}

} // namespace bfs

