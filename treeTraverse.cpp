/** 
 * @file treeTraverse.cpp
 * @Synopsis  get the tree structure with preorder and inorder
 * @author Yao lu
 * @version 1.0
 * @date 2014-03-11
 */

#include <iostream>

using namespace std;

template <typename T>
struct Node{
    const Node *parent;
    const Node *left;
    const Node *right;
    T    data;

    Node(const T &t):parent(NULL), left(NULL), right(NULL), data(t){}
};

enum TraverseType{
    PREORDER  = 0,
    INORDER   = 1,
    POSTORDER = 2
};

template <typename T>
void traverse_tree(const Node<T> *root, TraverseType type = INORDER)
{
    if (root == NULL) return;
    if (type == PREORDER) {
        cout<<root->data<<" ";
    }

    traverse_tree(root->left);

    if (type == INORDER) {
        cout<<root->data<<" ";
    }

    traverse_tree(root->right);

    if (type == POSTORDER) {
        cout<<root->data<<" ";
    }
}

template<typename T>
const Node<T>* buildTree(const T *preorder_array, const T *inorder_array, 
                         size_t array_len, const Node<T> *parent)
{
    cout<<*preorder_array<<" " <<*inorder_array<<" " <<array_len<<endl;
    if (1 == array_len) {
        cout<< "new" << *preorder_array<<endl;
        return new Node<T>(*preorder_array);
    }else if ( 0 >= array_len) {
        return NULL;
    }

    //get the sub-root from preoder sequence
    cout<< "new" << *preorder_array<<endl;
    Node<T> *root = new Node<T>(*preorder_array);
    root->parent = parent;

    const T &data = *preorder_array;
    //now we find the place in the inorder sequence
    size_t index = 0;
    while (index < array_len) {
        if (data == inorder_array[index] ) {
            break;
        }
        ++index;
    }
    if (index == array_len) {
        cerr<<"FATAL ERROR"<<endl;
        return NULL;
    }

    root->left  = buildTree(preorder_array+1, inorder_array, index, root);
    root->right = buildTree(preorder_array+index+1, inorder_array+index+1, 
                            array_len-index-1, root);
    return root;
}


int main()
{
    int preorder[] = {1, 2, 3, 5, 4, 6, 7, 8, 9, 10};
    int inorder[]  = {3, 5, 2, 6, 4, 1, 8, 7, 9, 10};
    const Node<int> *root = buildTree<int>(preorder, inorder, sizeof(preorder)/sizeof(int), NULL);
    traverse_tree(root);
    cout<<endl;
    return 0;
}









/* vim: set ts=256 sw=4 sts=4 tw=80 expandtab noet: */
