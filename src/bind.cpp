#include <iostream>
#include <functional>
using namespace std;

int add3(int a ,int b){
  cout <<"执行了add函数" << endl;
  return a + b;
}

int main (){
  //可以看成是把p 绑定到add3上， 以后使用p() 等同于 add3()
  //但是bind的一个好处是，参数不用在后续调用p()的时候传递了，因为在绑定的时候已经传递进来了。
  auto p1 = bind(add3 , 3 ,4 );
  int result1 = p1();
  cout <<"result1 = "<< result1 << endl;
  //也可以是用function来接收，但是由于参数的值已经在bind的时候传递进去了，所以接收的时候
  //function的参数可以使用() 表示无参。否则在调用p1的时候，还必须传递参数进来
  function<int ()> p2 = bind(add3 , 5 ,4 );
  int result2 =p2();
  cout <<"result2 = "<< result2 << endl;
  return 0 ;
}