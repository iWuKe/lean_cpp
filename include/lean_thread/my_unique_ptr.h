/*
手工实现独占指针
*/

/*
unique_ptr特性
1. 独享所有权
2. 重置对象 reset()
3. 对象不可复制，不能通过=号进行复制
4. 通过std::move转移对象所有权
5. 释放关联指针release()
6. get()仅仅返回关联指针(强制delete该返回指针后，独占指针在销毁时会出错-段错误)
*/
#pragma once
#include <stdio.h>
#include <iostream>

using namespace std;

template<typename T>
class SmartPointer
{
private:
public:
  //构造函数
  SmartPointer(T* ptr_ = nullptr): m_ptr(ptr_){}
  //支持移动拷贝构造
  SmartPointer(SmartPointer &&p) noexcept : m_ptr(p.m_ptr)
  {
    cout << "移动拷贝" << endl;
    p.m_ptr = nullptr;
  }
  //禁用拷贝构造函数
  SmartPointer(const SmartPointer &ptr_) = delete;

  //析构函数
  ~SmartPointer()
  {
    if (m_ptr)
    {
      delete m_ptr;
      m_ptr = nullptr;
    }
  }
  //重载->符号
  T* operator->() const noexcept{return m_ptr;}
  //重载 * 符号
  T& operator* () const noexcept{return *m_ptr;}
  //禁用赋值运算符
  SmartPointer &operator = (const SmartPointer &p) = delete;
  //释放智能指针地址
  T* release() noexcept{
    T *res = m_ptr;
    m_ptr = nullptr;
    return res;
  }
  //将托管指针重置为传入的指针
  void reset(T* p = nullptr) noexcept{
    std::swap(m_ptr, p);
    delete p;
  }
  //swap
  void swap(SmartPointer &p) noexcept{
    std::swap(m_ptr, p.m_ptr);
  }
  //获取被管理对象的指针
  T* get(){
    return m_ptr;
  }
  //存放智能指针
  T* m_ptr;
};
