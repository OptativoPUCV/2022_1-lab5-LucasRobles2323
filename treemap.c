#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap *new = (TreeMap*) malloc (sizeof(TreeMap));
    new->root = NULL;
    new->current = NULL;
    new->lower_than = lower_than;
    return new;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
    TreeNode *new = createTreeNode(key, value);
    if(tree->root == NULL){
        tree->root = new;
        tree->current = new;
        return;
    }
    if (searchTreeMap(tree, key) == NULL){
        if(tree->lower_than(key, tree->current->pair->key) == 1){
            tree->current->left = new;
            new->parent = tree->current;
            tree->current = tree->current->left;
        }else if (tree->lower_than(tree->current->pair->key, key) == 1){
            tree->current->right = new;
            new->parent = tree->current;
            tree->current = tree->current->right;
        }
    }
}

TreeNode * minimum(TreeNode * x){
    if(x->left == NULL){return x;}
    x = x->left;
    return minimum(x);
}


void removeNode(TreeMap * tree, TreeNode* node) {
    TreeNode *parent = node->parent;
    TreeNode *leftSon = node->left;
    TreeNode *rightSon = node->right;
    TreeNode *aux = NULL;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;

    if(leftSon == NULL && rightSon == NULL){
        if(tree->lower_than(node->pair->key, parent->pair->key) == 1){
            parent->left = NULL;
        }else if (tree->lower_than(parent->pair->key, node->pair->key) == 1){
            parent->right = NULL;
        }
        return;
    }
    
    if (rightSon != NULL ){
        node->pair = searchTreeMap(tree, rightSon->pair->key);
        
        parent = tree->current;
        if(tree->lower_than(rightSon->pair->key, parent->pair->key) == 1){
            aux = parent->left;
            parent->left = rightSon;
        }else if (tree->lower_than(parent->pair->key, rightSon->pair->key) == 1){
            aux = parent->right;
            parent->right = rightSon;
        }
        node->pair = searchTreeMap(tree, aux->pair->key);
        parent = tree->current;
        if(tree->lower_than(aux->pair->key, parent->pair->key) == 1){
            parent->left = aux;
        }else if (tree->lower_than(parent->pair->key, aux->pair->key) == 1){
            parent->right = aux;
        }
    }
    if (leftSon != NULL){
        node->pair = searchTreeMap(tree, leftSon->pair->key);
        
        parent = tree->current;
        if(tree->lower_than(leftSon->pair->key, parent->pair->key) == 1){
            aux = parent->left;
            parent->left = leftSon;
        }else if (tree->lower_than(parent->pair->key, leftSon->pair->key) == 1){
            aux = parent->right;
            parent->right = leftSon;
        }
        node->pair = searchTreeMap(tree, aux->pair->key);
        parent = tree->current;
        if(tree->lower_than(aux->pair->key, parent->pair->key) == 1){
            parent->left = aux;
        }else if (tree->lower_than(parent->pair->key, aux->pair->key) == 1){
            parent->right = aux;
        }
    }
    
    /*parent = NULL;
    leftSon = NULL;
    rightSon = NULL;
    aux = NULL;
    unUse = NULL;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    free(node);*/
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;
    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    TreeNode *aux = tree->root;

    while (aux != NULL)
    {
        tree->current = aux;
        if(tree->lower_than(key, aux->pair->key) == 1){
            aux = aux->left;
        }else if (tree->lower_than(aux->pair->key, key) == 1){
            aux = aux->right;
        }
        else{
            tree->current = aux;
            return aux->pair;
        }
    }

    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
