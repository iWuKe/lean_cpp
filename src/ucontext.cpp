#include <ucontext.h>
#include <stdio.h>
#include <unistd.h>
void func1(void * arg)
{
    puts("1");
    puts("11");
    puts("111");
    puts("1111");
}
void context_test()
{
    char stack[1024*128];
    ucontext_t child,main;
    getcontext(&child); //获取当前上下文
    child.uc_stack.ss_sp = stack;//指定栈空间
    child.uc_stack.ss_size = sizeof(stack);//指定栈空间大小
    child.uc_stack.ss_flags = 0;
    child.uc_link = &main;//设置后继上下文
    // child.uc_link = nullptr;//未设置后继上下文，程序直接退出

    makecontext(&child,(void (*)(void))func1,0);//修改上下文指向func1函数

    swapcontext(&main,&child);//切换到child上下文，保存当前上下文到main
    puts("main");//如果设置了后继上下文，func1函数指向完后会返回此处
}

void context_text1()
{
  ucontext_t context;
  getcontext(&context);
  puts("hello world");
  sleep(1);
  setcontext(&context);
  return;
}

int main()
{
  // context_text1();
    context_test();
    return 0;
}

/***************************************************
当当前上下文(如使用makecontext创建的上下文）运行终止时系统会恢复uc_link指向的上下文；
uc_sigmask为该上下文中的阻塞信号集合；uc_stack为该上下文中使用的栈；
uc_mcontext保存的上下文的特定机器表示，包括调用线程的特定寄存器等。

//初始化ucp结构体，将当前的上下文保存到ucp中
int getcontext(ucontext_t *ucp);

// 设置当前的上下文为ucp，setcontext的上下文ucp应该通过getcontext或者makecontext取得，
如果调用成功则不返回。如果上下文是通过调用getcontext()取得,程序会继续执行这个调用。
如果上下文是通过调用makecontext取得,程序会调用makecontext函数的第二个参数指向的函数，
如果func函数返回,则恢复makecontext第一个参数指向的上下文第一个参数指向的上下文context_t中指向的uc_link.
如果uc_link为NULL,则线程退出。
int setcontext(const ucontext_t *ucp);

// makecontext修改通过getcontext取得的上下文ucp(这意味着调用makecontext前必须先调用getcontext)。
然后给该上下文指定一个栈空间ucp->stack，设置后继的上下文ucp->uc_link.
当上下文通过setcontext或者swapcontext激活后，执行func函数，argc为func的参数个数，后面是func的参数序列。
当func执行返回后，继承的上下文被激活，如果继承上下文为NULL时，线程退出。
void makecontext(ucontext_t *ucp, void (*func)(), int argc, ...);

//保存当前上下文到oucp结构体中，然后激活upc上下文
int swapcontext(ucontext_t *oucp, ucontext_t *ucp);

如果执行成功，getcontext返回0，setcontext和swapcontext不返回；如果执行失败，getcontext,setcontext,swapcontext返回-1，并设置对于的errno.
简单说来，  getcontext获取当前上下文，setcontext设置当前上下文，swapcontext切换上下文，makecontext创建一个新的上下文。
***************************************************/