//
// Created by pikachu on 2019/7/18.
//

#include "tree.h"
#include "debug.h"
#include <stdlib.h>
#include <string.h>

struct TreeNode {
    ElementType Element;
    SearchTree Left;
    SearchTree Right;
};
typedef struct TreeNode *PtrToNode;

PtrToNode newNode(ElementType X) {
    PtrToNode ret;
    ret = malloc(sizeof(struct TreeNode));
    ret->Element = X;
    ret->Left = NULL;
    ret->Right = NULL;
    return ret;
}

SearchTree MakeEmpty(SearchTree T) {
    if (T != NULL) {
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }
    return NULL;
}

Position Find(ElementType X, SearchTree T) {
    if (T == NULL) {
        return NULL;
    } else if (X < T->Element) {
        return Find(X, T->Left);
    } else if (X > T->Element) {
        return Find(X, T->Right);
    } else {
        return T;
    }
}

Position FindMin(SearchTree T) {
    if (T == NULL) {
        return NULL;
    } else if (T->Left == NULL) {
        return T;
    } else {
        return FindMin(T->Left);
    }
}

Position FindMax(SearchTree T) {
    if (T == NULL) {
        return NULL;
    } else if (T->Right == NULL) {
        return T;
    } else {
        return FindMax(T->Right);
    }
}

SearchTree Insert(ElementType X, SearchTree T) {
    if (T == NULL) {
        T = newNode(X);
    } else if (X < T->Element) {
        T->Left = Insert(X, T->Left);
    } else if (X > T->Element) {
        T->Right = Insert(X, T->Right);
    }
    return T;
}

SearchTree Delete(ElementType X, SearchTree T) {
    Position TmpCell;
    if (T == NULL) {
        Warning("Fail to delete element: %d\n", X);
        return T;
    }
    if (X < T->Element) {
        T->Left = Delete(X, T->Left);
    } else if (X > T->Element) {
        T->Right = Delete(X, T->Right);
    } else if (T->Left != NULL && T->Right != NULL) {
        TmpCell = FindMin(T->Right);
        T->Element = TmpCell->Element;
        T->Right = Delete(TmpCell->Element, T->Right);
    } else {
        TmpCell = T;
        if (T->Left == NULL) {
            T = T->Right;
        } else if (T->Right == NULL) {
            T = T->Left;
        }
        free(TmpCell);
    }
    return T;
}


char* ToString(SearchTree T) {
    char str[1000] = "";
    if (T != NULL) {
        char *left = ToString(T->Left);
        char *right = ToString(T->Right);
        if (strlen(left) > 0) {
            sprintf(str, "%s", left);
        }
        sprintf(str, "%s,%d", str, T->Element);
        if(strlen(right) > 0) {
            sprintf(str, "%s%s", str, right);
        }
        free(left);
        free(right);
    }
    char *ret;
    ret = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(ret, str);
    return ret;
}

SearchTree CreateTree() {
    return NULL;
}

ElementType Retrieve(Position P) {
    return P->Element;
}
