//shared_ptr智能指针使用

#include <iostream>
#include <memory>

struct Sample
{
  Sample(){
    std::cout << " Sample" << std::endl;
  }
  ~Sample()
  {
    std::cout << " ~Sample" << std::endl;
  }
};

void deleter(Sample *x)
{
  std::cout << "delete function called" << std::endl;
  delete[] x;
}

class Deleter
{
public:
  void operator() (Sample* x){
    std::cout << "Deleter delete function called" << std::endl;
    delete[] x;
  }
};



int main(int argc, char* argv[])
{
  //创建空对象
  std::shared_ptr<int> p1 = std::make_shared<int>();
  *p1 = 78;
  std::cout << " p1 = " << *p1 << std::endl;

  //打印引用个数：1
  std::cout << "p1 reference count = " << p1.use_count() << std::endl;

  //第二个 shared_ptr对象指向同一个指针
  std::shared_ptr<int> p2(p1);

  //下面两个输出都是2
  //use_count 检查shared_ptr对象的引用计数
  std::cout << "p2 reference count = " << p2.use_count() << std::endl;
  std::cout << "p1 reference count = " << p1.use_count() << std::endl;

  //比较智能指针
  if (p1 == p2)
  {
    std::cout << "p1 and p2 are pointing to same pointer" << std::endl;
  }
  //当shard_ptr对象超出范围时将调用其析构函数
  std::shared_ptr<int> p4;
  do
  {
    std::shared_ptr<int> p3(p1);
    std::cout << "dw p2 reference count = " << p2.use_count() << std::endl;
    std::cout << "dw p1 reference count = " << p1.use_count() << std::endl;
  } while (0);
  std::cout << "dw end p2 reference count = " << p2.use_count() << std::endl;
  std::cout << "dw end p1 reference count = " << p1.use_count() << std::endl;


  //reset() 使其对象取消与相关指针的关联，可以使用reset()函数
  //不带参数他的引用计数减少1，如果引用计数变为0，则删除指针
  //p1.reset(new int(34))带参数的reset他将在内部指向新的指针，因此其引用计数将再次变为1
  //无参调用reset，无关联指针，引用个数为0
  p1.reset();
  std::cout << "reset p1 reference count = " << p1.use_count() << std::endl;
  std::cout << "reset p2 reference count = " << p2.use_count() << std::endl;

  //把对象重置为null，引用计数为0
  p1 = nullptr;
  std::cout << "p1 referene count = " << p1.use_count() << std::endl;

  if (!p1)
  {
    std::cout << "p1 is NULL" << std::endl;
  }

  std::cout << "**************加入自定义删除器******************" << std::endl;
  //给他加入自定义删除器
  do
  {
    //构造函数传递自定义删除器指针
    std::shared_ptr<Sample> p3(new Sample[3], deleter);
    //将指针置nullptr，将释放指针
    p3 = nullptr;
    std::cout << "nullptr" << std::endl;
  } while (0);
  std::cout << "while end" << std::endl;

  std::cout << "***************使用lambda表达式/函数对象作为删除器***********************" << std::endl;
  //使用lambda表达式/函数对象作为删除器
  do
  {
    std::cout << " p3" << std::endl;
    std::shared_ptr<Sample> p3(new Sample[3], Deleter());
    //使用lambda表达式作为删除器
    std::cout << " p4" << std::endl;
    std::shared_ptr<Sample> p4(new Sample[3], [](Sample* x){
      std::cout << "lambda delete function called" << std::endl;
      delete[] x;
    });
  } while (0);

  std::cout << "***************NULL检测***********************" << std::endl;

  do
  {
    std::shared_ptr<Sample> ptr3;
    if (!ptr3)
    {
      std::cout << "ptr3 is empty !" << std::endl;
    }
    if (ptr3 == NULL)
    {
      std::cout << "ptr3 is empty NULL" << std::endl;
    }
    if (ptr3 == nullptr)
    {
      std::cout << "ptr3 is empty nullptr" << std::endl;
    }
  } while (0);

  std::cout << "***************不要使用同一个原始指针构造shared_ptr***********************" << std::endl;
  //创建多个shared_ptr的正常方法是使用一个已存在的shared_ptr进行创建，而不是使用同一个原始指针进行创建

  do
  {
    int* num = new int(23);
    std::shared_ptr<int> p1(num);
    //正确使用方法
    std::shared_ptr<int> p2(p1);
    //下列方法不可以，出作用域时会析构两次导致段错误
    // std::shared_ptr<int> p3(num);

    std::cout << "p1 reference count = " << p1.use_count() << std::endl;
    std::cout << "p2 reference count = " << p2.use_count() << std::endl;
    // std::cout << "p3 reference count = " << p3.use_count() << std::endl;

  } while (0);
  std::cout << "***************不要使用栈中的指针构造对象***********************" << std::endl;
  do
  {
    int x = 12;
    //当shared_ptr对象超出作用域调用析构函数时，delete指针&x会出错
    // std::shared_ptr<int> p1(&x);
  } while (0);
  

  return 0;
}

//shared_ptr相对于普通指针的优缺点
//缺少++，--，[]运算符， 仅提供->  *  和 == 运算符
//不要使用同一个原始指针构造shared_ptr
//不建议使用get()函数获取shared_ptr关联的原始指针，因为如果在shared_ptr析构之前手动调用了delete函数会同样导致错误