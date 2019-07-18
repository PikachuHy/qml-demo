//
// Created by pikachu on 2019/7/18.
//

#ifndef DATASTRUCTURES_TREE_H
#define DATASTRUCTURES_TREE_H
struct TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;
typedef int ElementType;
SearchTree CreateTree();
SearchTree MakeEmpty(SearchTree T);
Position Find(ElementType X, SearchTree T);
Position FindMin(SearchTree T);
Position FindMax(SearchTree T);
SearchTree Insert(ElementType X, SearchTree T);
SearchTree Delete(ElementType X, SearchTree T);
ElementType Retrieve(Position P);

char* ToString(SearchTree T);
#endif //DATASTRUCTURES_TREE_H
