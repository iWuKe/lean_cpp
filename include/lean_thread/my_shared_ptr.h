/*
手动实现shared_ptr共享指针
*/

/*
共享指针
1. 每使用一次，内部引用计数加1
2. 每析构一次，内部引用计数减1
3. 引用计数减为0时自动释放原生指针所指向的内存
*/
#pragma once
#include <stdio.h>
#include <iostream>

using namespace std;

template <typename T>
class Shared_ptr
{
private:
  //引用计数
  int *count;
  //指针
  T* _ptr;
public:
  //构造函数
  Shared_ptr():count(0), _ptr((T*)0){}
  //从原生指针构造
  Shared_ptr(T* p):count(new int(1)), _ptr(p){}
  //拷贝构造函数，引用计数器+1，让该对象的指针指向形参对象的指针
  Shared_ptr(Shared_ptr<T>& other):count(&(++ *other.count)), _ptr(other._ptr){}

  //重载->
  T* operator->(){return _ptr;}
  //重载*
  T& operator*() {return *_ptr;}
  //重载 =
  //如果原来shared_ptr已经有对象，则让其引用次数减1并判断引用是否为0（是否调用delete）
  //然后将新的对象引用次数加1
  Shared_ptr<T>& operator= (Shared_ptr<T>& other)
  {
    //如果是自己赋给自己，则直接返回
    if (this == &other)
      return *this;

    //计数器加1
    ++*other.count;
    if (this->_ptr && 0 == --*this->count)
    {
      delete count;
      delete _ptr;
      cout << "delete ptr = " << endl;
    }

    this->_ptr = other._ptr;
    this->count = other.count;
    return *this;
  }

  //析构函数，使引用次数减一并判断引用是否为0（是否调用delete）
  ~Shared_ptr()
  {
    //判断ptr是否为空，并且count--后是否为0
    if (_ptr && --*count == 0)
    {
      delete count;
      delete _ptr;
      cout << "delete ptr ~" << endl;
    }
  }
  //返回引用次数
  int use_count(){return *count;}
};





















