#include <iostream>
#include <string>
#include <type_traits>
#include <memory>

using namespace std;

//用户定义字面量
long double operator""_mm(long double x){return x / 1000;}
long double operator""_m(long double x){return x;};
long double operator""_km(long double x){return x * 1000;}
size_t operator""_len(char const* str, size_t size)
{
  return size;
}

//强枚举类型
enum class status{ ok, error};
enum class status1{ok, error};

//函数抛出异常
void blockThrow() noexcept
{
  // throw 2;
  // throw 2.0;
}

//常量表达式主要是允许一些计算发生在编译时，即发生在代码编译而不是运行的时候
struct Date
{
  constexpr Date(int y): year(y){}
  constexpr int getYear() {return year;}
private:
  int year;
};

//继承构造
class A
{
public:
  // A(int i){cout << "i = " << i << endl;}
  // A(double d, int i){}
  // A(float f, int i, const char* c){}
  A(int x, int y){
    a = x;
    b = y;
  }
protected:
  int a;
  int b;
};

class B:public A
{
public:
  using A::A;
  virtual void test(){}
  void display(){cout << "a = " << a << " b = " << b << endl;}
  int tmp;
};

//委托构造
class Info
{
private:
  //目标构造函数
  Info(int i, char e):type(i), name(e){}

  int type;
  char name;
public:
  //委托构造函数
  Info() : Info(1){}
  //既是目标构造函数，也是委托构造函数
  Info(int i): Info(i, 'a'){}
  Info(char e): Info(1, 'e'){}

  void display(){cout << "type " << type << " name " << name << endl;}
};

//继承控制
//final阻止类的进一步派生和虚函数的进一步重写
//override确保在派生类中声明的函数跟基类的虚函数有相同的签名

//类的默认函数的控制

//模板的改进
//右尖括号改进
template <int i> class X{};
template <class T> class Y{};
//模板的别名
using uint = unsigned int;
typedef unsigned int UINT;
using sint = int;



//可变参数模板
void func()
{
  cout << "empty" << endl;
}
template <class T, class ... Args> void func(T head, Args... reset)
{
  cout << "params " << head  << " size " << sizeof...(reset) << endl;
  func(reset...);
}
//可变参数模板非递归方式展开
template<class T>
void print(T arg)
{
  cout << "param" << arg << endl;
}
template<class ... Args>
void expand(Args ... args)
{
  int a[] = {(print(args), 0)...};
}

//右值引用
//标准库函数 std::move
//完美转发 std::forward
template<typename T> void process_value(T & val)
{
  cout << "T &" << endl;
}
template<typename T> void process_value(T && val)
{
  cout << "T &&" << endl;
}
template<typename T> void process_value(const T & val)
{
  cout << "const T &" << endl;
}
template<typename T> void process_value(const T && val)
{
  cout << "const T &&" << endl;
}
  //函数 forward_value 是一个泛型函数，它将一个参数传递给另一个函数 process_value
template <typename T> void forward_value(T && val)
{
  //c++11中，forward可以保存参数的左值或右值特性
  process_value(std::forward<T>(val));
}

int main(int argc, char* argv[])
{
  // static_assert(sizeof(void *) == 4, "64-bit code generation is not supported");
  static_assert(sizeof(void *) == 8, "32-bit code generation is not supported");
  cout << "hello world!" << endl;

  blockThrow();

  Date data(10);
  cout << "year " << data.getYear() << endl;

  cout << 1.0_mm << endl;
  cout << 1.0_m << endl;
  cout << 1.0_km << endl;
  cout << "1.0_km"_len << endl;

  //原生字符串字面值
  // cout << R"hello, \n
  // world" << endl;

  B obj(10, 20);
  obj.display();

  Info info(1), info1('z'), info2;
  info.display();
  info1.display();
  info2.display();

  Y<X<1> > x1;
  Y<X<2>> x2;

  //判断类型是否一致
  cout << "type " << is_same<uint, UINT>::value << endl;
  cout << "type2 " << is_same<sint, UINT>::value << endl;

  func(2,5,66,"ss");
  expand(313,215,1564,"sad");

  int a = 0;
  const int &b = 1;

  forward_value(a); // T &
  forward_value(b); // const T &
  forward_value(2); // T &&
  forward_value( std::move(b) ); // const T &&

  //智能指针unique_pr
  {
    //无法复制的unique_ptr
    unique_ptr<int> up1(new int (11));
    //unique_ptr<int> up2 = up1;  //err不能通过编译
    cout << "up1 " << *up1 << endl;
    //现在p3是数据的唯一智能指针
    unique_ptr<int> up3 = move(up1);
    cout << "up3 " << *up3 << endl;
    // cout << *up1 << endl; //运行时错误

    //显式释放内存
    up3.reset();
    //不会导致运行时错误
    up1.reset();
    // cout << "up3 " << *up3 << endl; //运行时错误

    unique_ptr<int> up4(new int(22));
    //绑定动态对象
    up4.reset(new int(44));
    cout << "up4 " << *up4 << endl; //44
    //显式销毁所指对象，同时智能指针变为空指针，与up4.reset()等价
    up4 = nullptr;

    unique_ptr<int> up5(new int(55));
    //只是释放控制权，不会释放内存
    int *p = up5.release();
    cout << *p << endl;
    // cout << *up5 << endl; //运行时错误
    //释放堆区资源
    delete p;
  }



  return 0;
}