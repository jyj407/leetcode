// Number of Distinct Islands
// Typical DFS problem. The hard part is how to save the shape of the island
// One clever way from the internet is save all the offest (x, y) relative to
// the top left most cell inside the island.
#include <vector>
#include <set>
using namespace std;

class Solution {
public:
    int numDistinctIslands(vector<vector<int> >& grid) {
        if (grid.empty() || grid[0].empty())
            return 0;
    
        M = grid.size(); 
        N = grid[0].size(); 
        set<vector<vector<int> > > islands;
        for (int r = 0; r < M; r++)
            for (int c = 0; c < N; c++) {
                if (grid[r][c] > 0) {
                    vector<vector<int> > island;
                    DFS(r, c, r, c, grid, island);
                    islands.insert(island);
                }
            }   
        
        return islands.size(); 
    }

private:
    int M; // grid rows
    int N; // grid cols

    void DFS(int sr, int sc, int r, int c, vector<vector<int> >& grid, vector<vector<int> >& island) {
        if (r < 0 || r >= M || c < 0 || c >= N || grid[r][c] <= 0 /* visited or is water */)
            return;
             
        island.push_back({r - sr, c - sc});
        grid[r][c] = -1; // mark as visited

        DFS(sr, sc, r + 1, c, grid, island);
        DFS(sr, sc, r - 1, c, grid, island);
        DFS(sr, sc, r, c - 1, grid, island);
        DFS(sr, sc, r, c + 1, grid, island);
    }
};


int main(void) {
    vector<vector<int> > grid = { {1, 1, 0, 1, 1},
                                  {1, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 1},
                                  {1, 1, 0, 1, 1}};
    Solution sol;
    return sol.numDistinctIslands(grid);
}
