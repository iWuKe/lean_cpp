#include "lean_thread/my_unique_ptr.h"
#include <memory>

using namespace std;

class A
{
private:
public:
  string name;
  A(string name_):name(name_) {
    cout << "我构造了 A :" << name << endl;
  }
  ~A()
  {
    cout << "我析构了 A :" << name << endl;
  }
};

int main(int argc, char* argv[])
{
  SmartPointer<A> a(new A("a"));
  // a = nullptr;
  cout << "-----------------" << endl;

  if (true)
  {
    SmartPointer<A> b(new A("b"));
  }
  cout << "-----------------" << endl;

  SmartPointer<A> b(new A("b1"));
  SmartPointer<A> c(new A("c"));

  SmartPointer<A> d = std::move(a);
  cout << "move -> " << d->name << endl;
  cout << "move * " << (*d).name << endl;
  d.reset(new A("reset"));
  cout << "reset -> " << d->name << endl;

  A* e = d.get();
  cout << "get : " << d->name << endl;
  //强制删除该指针会出现段错误
  // delete e;

  unique_ptr<A> f(new A("f"));
  A* g = f.get();
  cout << "get : " << g->name << endl;
  // delete g;


  cout << "return" << endl;
  return 0;
}