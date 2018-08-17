// Closest Leaf in a Binary Tree
#include <vector>
#include <queue>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
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

class Solution {
public:
    int findClosestLeaf(TreeNode* root, int k) {
        unordered_map<TreeNode*, TreeNode*> back;
        TreeNode* kNode = dfsFind(root, k, back);
        queue<TreeNode*> q{{kNode}};
        unordered_set<TreeNode*> visited{kNode};
        while (!q.empty()) {
            TreeNode* cur = q.front(); q.pop();

            if (!cur->left && !cur->right)
                return cur->val;

            // left subtree
            if (cur->left && !visited.count(cur->left)) {
                visited.insert(cur->left);
                q.push(cur->left);
            }

            // right subtree
            if (cur->right && !visited.count(cur->right)) {
                visited.insert(cur->right);
                q.push(cur->right);
            }

            // parent
            if (back.count(cur) && !visited.count(back[cur])) {
                visited.insert(back[cur]);
                q.push(back[cur]);
            }
        }

        return -1;
    }

private:
    TreeNode* dfsFind(TreeNode* root, int k, unordered_map<TreeNode*, TreeNode*>& back) {
        if (root->val == k)
            return root;
        
        if (root->left) {
            back[root->left] = root;
            auto left = dfsFind(root->left, k, back);
            if (left)
                return left;
        }
        
        if (root->right) {
            back[root->right] = root;
            auto right = dfsFind(root->right, k, back);
            if (right)
                return right;
        }

        return nullptr;
    }
};

int main(void) {
    //vector<int> preorder = {2,3,0,5,1};
    //vector<int> inorder = {0,3,2,1,5};
    vector<int> preorder = {1,2,4,5,7,8,3,6,9,10};
    vector<int> inorder = {4,2,7,5,8,1,9,6,10,3};
    TreeNode* root = buildTree(preorder, inorder);
    Solution sol;
    int res = sol.findClosestLeaf(root, 4);
    cout << res << endl;

    return 0;
}    
