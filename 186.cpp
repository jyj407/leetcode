#include <string>
#include <iostream>
using namespace std;

class Solution {
public:
    void reverseWords(string &s) {
        // reverse the whole string
        reverse(s, 0, s.size() - 1); 
        
        // reverse each word 
        int start = 0;
        for (int i = 0; i <= s.size(); i++) {
            if (s[i] == ' ' || i == s.size()) {
                reverse(s, start, i - 1);
                start = i + 1;
            }
        }
    }

private:
    void reverse(string& str, int left, int right) {
        int i = left, j = right;
        while (i < j) {
            swap(str[i], str[j]);
            i++;
            j--;
        }
    }
};

int main(void) {
    Solution sol;
    string s = "the sky is blue";
    sol.reverseWords(s);
    cout << s << endl;
}
