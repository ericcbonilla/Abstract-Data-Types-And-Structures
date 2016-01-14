//Eric Bonilla
//COEN 12
//11-30-14
//Lab 5
//Binary Search Tree Implementation

# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <math.h>
# include "tree.h"

typedef struct tree TREE;

struct tree
{
    int data;
    struct tree *parent;
    struct tree *left;
    struct tree *right;
};

//detaches the child from its parent
void detach(struct tree *root, struct tree *child)
{
    if(root->parent && root->parent->left == root)
        root->parent->left=NULL;
    if(root->parent && root->parent->right == root)
        root->parent->right=NULL;
}

//return a pointer to a new tree with the specified left and right subtrees and data for its root
struct tree *createTree(int data, struct tree *left, struct tree *right)
{
    struct tree *root;
    root = malloc(sizeof(struct tree));
    assert(root!=NULL);
    root->data = data;
    root->parent = NULL;
    if(left!=NULL)
        setLeft(root,  left);
    if(right!=NULL)
        setRight(root, right);
    return root;
}

//deallocate memory for the entire subtree pointed to by the root
void destroyTree(struct tree *root)
{
    if(root!=NULL)
    {
        destroyTree(root->left);
        destroyTree(root->right);
        free(root);
    }
}

//return the data in the root of the subtree pointed to by root
int getData(struct tree *root)
{
    assert(root!=NULL);
    return root->data;
}

//return the left subtree of the subtree pointed to by root
struct tree *getLeft(struct tree *root)
{
    assert(root!=NULL);
    return root->left;
}

//return the right subtree of the subtree pointed to by root
struct tree *getRight(struct tree *root)
{
    assert(root!=NULL);
    return root->right;
}

//return the parent tree of the subtree pointed to by root
struct tree *getParent(struct tree *root)
{
    assert(root!=NULL);
    return root->parent;
}

//update the left subtree of root
void setLeft(struct tree *root, struct tree *left)
{
    assert(root!=NULL && left!=NULL);
    root->left = left;
    detach(root, left);
    left->parent = root;
}

//update the right subtree of root
void setRight(struct tree *root, struct tree *right)
{
    assert(root!=NULL && right !=NULL);
    root->right = right;
    detach(root, right);
    right->parent = root;
}
