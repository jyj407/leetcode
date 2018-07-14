#include<vector>
#include<numeric>
#include<functional>
using namespace std;

/* Without optimization
class Solution {
public:
    bool makesquare(vector<int>& nums) {
        if (nums.size() < 4)
            return false;
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (0 != sum % 4)
            return false;
        
        vector<int> sides(4, 0);
        return backtracking(nums, sides, 0, sum / 4);
    }
    
private:
    bool backtracking(vector<int>& nums, vector<int>& sides, int start, int target) {
        if (start == nums.size()) {
            return (sides[0] == sides[1] && sides[1] == sides[2] && sides[2] == sides[3]);
        }
        // Try adding the current match to each side
        for (int i = 0; i < 4; i++) {
            if (sides[i] + nums[start] > target) // cannot put into this side
                continue;
            sides[i] += nums[start]; // add this match to sides[i]
            if (backtracking(nums, sides, start + 1, target))
                return true;
            sides[i] -= nums[start]; // not add this match to sides[i]
        }
        
        return false;
    }
};
*/

// With optimization 4ms (beat 100%)
class Solution {
public:
    bool makesquare(vector<int>& nums) {
        if (nums.size() < 4)
            return false;
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (0 != sum % 4)
            return false;
        
        vector<int> sides(4, 0);
        // Optimize: Sort the match in descending order
        sort(nums.begin(), nums.end(), greater<int>());
        return backtracking(nums, sides, 0, sum / 4);
    }
    
private:
    bool backtracking(vector<int>& nums, vector<int>& sides, int start, int target) {
        if (start == nums.size()) {
            return (sides[0] == sides[1] && sides[1] == sides[2] && sides[2] == sides[3]);
        }
        // Try adding the current match to each side
        for (int i = 0; i < 4; i++) {
            if (sides[i] + nums[start] > target) // cannot put into this side
                continue;
            
            // Prune same state occurred before
            int j = 0;
            while (j < i) {
                if (sides[j] == sides[i])
                    break;    
                j++;
            }
            if (j < i)
                continue;
            
            sides[i] += nums[start]; // add this match to sides[i]
            if (backtracking(nums, sides, start + 1, target))
                return true;
            sides[i] -= nums[start]; // not add this match to sides[i]
        }
        
        return false;
    }
};
