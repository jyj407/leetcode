// Number of Distinct Islands II
// Typical DFS problem. The hard part is how to save the shape of the island
// Version I: One clever way from the internet is save all the offest (x, y) relative to
// the top left most cell inside the island.
// Version II: have to calcualte all the rotations and treat them as the same
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
                    islands.insert(normalize(island));
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

    vector<vector<int> > normalize(vector<vector<int> >& island) {
        vector<vector<vector<int> > > res(8, vector<vector<int> >());  
        for (auto& p : island) {
            int x = p[0], y = p[1]; 
            res[0].push_back({x, y});  
            res[1].push_back({x, -y});  
            res[2].push_back({-x, y});  
            res[3].push_back({-x, -y});  
            res[4].push_back({y, x});  
            res[5].push_back({y, -x});  
            res[6].push_back({-y, x});  
            res[7].push_back({-y, -x});  
        }        
        
        for (int i = 0; i < 8; i++) {
            sort(res[i].begin(), res[i].end());
            int r_offset = 0 - res[i][0][0];
            int c_offset = 0 - res[i][0][1];
            for (int j = 0; j < res[i].size(); j++) {
               res[i][j][0] += r_offset;
               res[i][j][1] += c_offset;
            }
        }
        sort(res.begin(), res.end());
        return res[0];
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
