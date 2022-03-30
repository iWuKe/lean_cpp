#include "lean_thread/my_shared_ptr.h"
#include <memory>
using namespace std;

class A
{
private:
public:
  string name;
  A(string name_):name(name_) {
    cout << "我构造了 A : " << name << endl;
  }
  ~A()
  {
    cout << "我析构了 A : " << name << endl;
  }
};

template<class T>
struct ListNode
{
        ListNode(T value)
        :_value(value)
        {
               cout << "ListNode()" << endl;
        }
        ~ListNode()
        {
               cout << "~ListNode()" << endl;
        }
        T _value;
        shared_ptr<ListNode<T>> _prev;
        shared_ptr<ListNode<T>> _next;
};

void test0()
{
  Shared_ptr<A> sptra(new A("aaa"));
  cout << "sptra " << sptra.use_count() << " " << sptra->name << endl;

  Shared_ptr<A> sptrb(sptra);
  cout << "sptrb " << sptrb.use_count() << " " << sptrb->name << endl;

  Shared_ptr<A> sptrc(new A("ccc"));
  cout << "sptrc " << sptrc.use_count() << " " << sptrc->name << endl;

  sptrc = sptra;
  sptrc = sptrb;
  // sptrc = nullptr;
  cout << "sptra " << sptra.use_count() << " " << sptra->name << endl;
  cout << "sptrb " << sptrb.use_count() << " " << sptrb->name << endl;
  cout << "sptrc " << sptrc.use_count() << " " << sptrc->name << endl;
}

//循环引用
void test1()
{
  shared_ptr<ListNode<int>> p1(new ListNode<int>(1));
  shared_ptr<ListNode<int>> p2(new ListNode<int>(2));
  cout << p1.use_count() << endl;
  cout << p2.use_count() << endl;
  p1->_next = p2;
  p2->_prev = p1;
  cout << p1.use_count() << endl;
  cout << p2.use_count() << endl;
}

int main(int argc, char* argv[])
{
  test0();
  test1();

  return 0;
}