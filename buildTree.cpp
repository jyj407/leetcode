// Ref: http://www.cnblogs.com/AnnieKim/archive/2013/06/15/morristraversal.html
// Boundary of Binary Tree
#include <vector>
#include <iostream>
using namespace std;

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* constructTree(vector<int>& preorder, int preStart, int preEnd,
                        vector<int>& inorder, int inStart, int inEnd) {
    if (preStart > preEnd)
        return NULL;
    
    int index = 0;
    // Note must be "<=" rather that "<", since the right subtree could be null, 
    //i.e: (root is the last element in inorder)
    for (int i = inStart; i <= inEnd; i++) {
        if (inorder[i] == preorder[preStart]) {
            index = i;
            break;
        }
    }
    
    TreeNode* root = new TreeNode(preorder[preStart]);
    root->left = constructTree(preorder, preStart + 1,preStart + 1 + (index -1 - inStart),
                               inorder, inStart, index - 1);
    root->right = constructTree(preorder,  preEnd - (inEnd - index - 1), preEnd,
                                inorder, index + 1, inEnd);
    return root;
}


TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    return constructTree(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
}

int main(void) {
    //vector<int> preorder = {2,3,0,5,1};
    //vector<int> inorder = {0,3,2,1,5};
    vector<int> preorder = {1,2,4,5,7,8,3,6,9,10};
    vector<int> inorder = {4,2,7,5,8,1,9,6,10,3};
    TreeNode* root = buildTree(preorder, inorder);
    vector<int> res = boundaryOfBinaryTree(root);
    for (auto& num : res)
        cout << num << endl;

    return 0;
}    
