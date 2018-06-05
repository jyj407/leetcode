// 525 Contiguous Array
// Solution 1: brute force try every starting point in the array to get the max length.
// class Solution {
// public:
//     int findMaxLength(vector<int>& nums) {
//         int maxLen = 0;
//         int n = nums.size();
        
//         for (int i = 0; i < n; i++) {
//             int ones = 0;
//             int zeros = 0;
//             for (int j = i; j < n; j++) {
//                 if (nums[j] == 1)
//                     ones++;
//                 else if (nums[j] == 0)
//                     zeros++;
//                 if (ones == zeros)
//                     maxLen = max(maxLen, j - i + 1);
//             }
//         }
        
//         return maxLen;
//     }
// };


   
// Solution 2: hash map
// In this approach, we make use of a countcount variable, which is used to store the relative number of ones and zeros encountered so far while traversing the array. The countcount variable is incremented by one for every 1 encountered and the same is decremented by one for every 0 encountered.
// We start traversing the array from the beginning. If at any moment, the countcount becomes zero, it implies that we've encountered equal number of zeros and ones from the beginning till the current index of the array(ii). Not only this, another point to be noted is that if we encounter the same countcount twice while traversing the array, it means that the number of zeros and ones are equal between the indices corresponding to the equal countcount values. 


class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        int maxLen = 0;
        int n = nums.size();
        unordered_map<int, int> mp;
        int count = 0;
        
        mp[0] = -1; // pseudo pair to help calculate same number of 0s and 1s 
        for (int i = 0; i < n; i++) {
            count += nums[i] == 1 ? 1 : -1;
            auto iter = mp.find(count);
            if (iter != mp.end())
                maxLen = max(maxLen, i - iter->second);
            else
                mp[count] = i;
        }
        
        return maxLen;
    }
};
