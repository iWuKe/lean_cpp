#include "lean_thread/search.h"
using namespace dfs;
using namespace dfp;
using namespace bfs;

void test()
{
  Graph graph(10);
  for (size_t i = 0; i < 4; i++)
  {
    graph.addEdge(1, 2 * i);
  }
  graph.addEdge(6, 5);
  graph.addEdge(5, 9);
  DepthFirstSearch depth(graph, 1);
  for (size_t i = 0; i < 10; i++)
  {
    if (depth.Marked(i))
    {
      std::cout << "mark " << i << std::endl;
    }
  }
  int dfs_count = depth.Count();
  std::cout << "dfs count" << dfs_count << std::endl;

  BreadthFirstSearch bread(graph, 1);
  for (size_t i = 0; i < 10; i++)
  {
    if (bread.Marked(i))
    {
      std::cout << "mark " << i << std::endl;
    }
  }
  int bfs_count = depth.Count();
  std::cout << "bfs count" << bfs_count << std::endl;

  //使用dfs查找路径
  DepthFirstPaths dfps(graph, 1);
  std::stack<int> path = dfps.pathTo(5);

  while (!path.empty())
  {
    int v = path.top();
    path.pop();
    std::cout << v << " - ";
  }
  std::cout << std::endl;
}

int main(int argc, char* argv[])
{
  test();
  return 0;
}