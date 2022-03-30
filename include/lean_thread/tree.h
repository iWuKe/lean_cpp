#pragma once

#include <stdio.h>
#include <iostream>
#include <vector>
#include <stack>

//树的存储结构
typedef char ElemType;

typedef struct CSNode{
    ElemType data;
    struct CSNode *firstchild, *nextsibling;
} CSNode, *CSTree;

