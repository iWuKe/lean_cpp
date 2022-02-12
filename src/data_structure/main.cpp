#include "lean_thread/search.h"

void test()
{
  Graph graph(10);
  for (size_t i = 0; i < 4; i++)
  {
    graph.addEdge(1, 2 * i);
  }
  // graph.addEdge(6, 5);
  // graph.addEdge(5, 9);
  DepthFirstSearch depth(graph, 1);
  for (size_t i = 0; i < 10; i++)
  {
    if (depth.Marked(i))
    {
      std::cout << "mark " << i << std::endl;
    }
  }
}

int main(int argc, char* argv[])
{
  test();
  return 0;
}