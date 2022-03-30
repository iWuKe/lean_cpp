#include "lean_thread/tree.h"

using namespace std;

//求树的深度
uint TreeDepth(CSTree T)
{
    if (T)
    {
        if ((1 + TreeDepth(T->firstchild)) > TreeDepth(T->nextsibling))
        {
            return (1+TreeDepth(T->firstchild));
        }else{
            return TreeDepth(T->nextsibling);
        }
        // return (1 + TreeDepth(T->firstchild)) > TreeDepth(T->nextsibling) ? (1+TreeDepth(T->firstchild)) : TreeDepth(T->nextsibling);
    }
    return 0;
}

//树的路径打印
void AllPath(CSTree T, stack<ElemType> *S1)
{
    while (T != nullptr)
    {
        S1->push(T->data);
        if (T->firstchild == nullptr)
        {
            stack<ElemType> S2;
            S2 = *S1;
            while (!S2.empty())
            {
                printf("%c\n",S2.top());
                S2.pop();
            }
        }
        else{
            AllPath(T->firstchild, S1);
        }
        S1->pop();
        T = T->nextsibling;
    }    
}

//创建树
void CreateTree(CSTree *T)
{
    (*T) = nullptr;
    ElemType Felem;
    ElemType Selem;
    

}


