// #include "lean_thread/directedcycle.h"
#include "lean_thread/disearch.h"

void test()
{
  //新建一个有向图
  Digraph dg(10);
  for (size_t i = 0; i < 4; i++)
  {
    dg.addEdge(1, 2 * i);
  }
  dg.addEdge(6, 5);
  dg.addEdge(5, 9);

  DirectedCycle dc(dg);
  if (dc.HasCycle())
  {
    std::cout << "有环" << std::endl;
  }else{
    std::cout << "无环" << std::endl;
  }

  std::stack<int> order;
  //没有环则创建顶点排序对象，进行排序
  if (!dc.HasCycle())
  {
    DepthFirstOrder dfo(dg);
    order = dfo.reversePose();

    while (!order.empty())
    {
      int v = order.top();
      order.pop();
      std::cout << v << " -> ";
    }
    std::cout << std::endl;
  }
}

int main(int argc, char* argv[])
{
  test();
  return 0;
}