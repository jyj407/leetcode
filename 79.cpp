// Solution 1 (Modify the input)
// class Solution {
// public:
//     bool exist(vector<vector<char>>& board, string word) {
//         for (int i = 0; i < board.size(); i++)
//             for (int j = 0; j < board[0].size(); j++) {
//                 if (backtracking(board, i, j, word, 0))
//                     return true;
//             }
        
//         return false;
//     }
    
// private:
//     // This solution modifies the input, also only works when there is no '#' in the input
//     bool backtracking(vector<vector<char>>& board, int row, int col, string& word, int start) {
//         if (row < 0 || row >= board.size() ||
//             col < 0 || col >= board[0].size() ||
//             word[start] != board[row][col])
//             return false;
        
//         if (word.size() - 1 == start)
//             return true;
        
//         auto curChar = board[row][col];
//         board[row][col] = '#';
//         bool res = backtracking(board, row - 1, col, word, start + 1) ||
//             backtracking(board, row + 1, col, word, start + 1) ||
//             backtracking(board, row, col - 1, word, start + 1) ||
//             backtracking(board, row - 1, col + 1, word, start + 1);
//         board[row][col] = curChar;
//         return res;
//     }
// };

// Solution 2: without modifying the array
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        if (board.empty() || board[0].empty())
            return false;
    
        int M = board.size();
        int N = board[0].size();
        vector<vector<bool> > visited(M, vector<bool>(N, false));
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++) {
                if (backtracking(board, i, j, word, 0, visited))
                    return true;
            }
        
        return false;
    }
    
private:
    // This solution modifies the input, also only works when there is no '#' in the input
    bool backtracking(vector<vector<char>>& board, int row, int col,
                      string& word, int start, vector<vector<bool> >& visited) {
        if (row < 0 || row >= board.size() || col < 0 || col >= board[0].size() ||
            word[start] != board[row][col] || visited[row][col])
            return false;
        
        if (word.size() - 1 == start)
            return true;
        
        visited[row][col] = true;
        bool res = backtracking(board, row - 1, col, word, start + 1, visited) ||
            backtracking(board, row + 1, col, word, start + 1, visited) ||
            backtracking(board, row, col - 1, word, start + 1, visited) ||
            backtracking(board, row, col + 1, word, start + 1, visited);
        visited[row][col] = false;
        return res;
    }
};
