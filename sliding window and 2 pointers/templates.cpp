#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
using namespace std;

// fixed window
// Maximizing sum of subarray of size k
int maxSumSubarray(vector<int> &nums, int k)
{
    if (k > nums.size() || k == 0)
    {
        return 0;
    }

    int currentWindowSum = 0;
    int maximumWindowSum = 0;
    int n = nums.size();

    // initializing currentWindowSum with first k entries sum of array
    for (int i = 0; i < k; i++)
    {
        currentWindowSum += nums[i];
    }

    for (int i = k; i < n; i++)
    {
        int currentElement = nums[i];
        // currentSum + newElement + oldElement = newSum
        int oldElement = nums[i - k];
        int newSum = currentWindowSum + currentElement - oldElement;

        maximumWindowSum = max(currentWindowSum, maximumWindowSum);

        currentWindowSum = newSum;
    }

    return maximumWindowSum;
}

// dynamic window
// Problem: Find the length of the longest contiguous subarray whose sum is at most K.
int lengthOfSumK(vector<int> nums, int k)
{
    int n = nums.size();
    int left = 0;
    // int right = 0;
    int sum = 0;
    int best = 0;

    for (int right = 0; right < n; right++)
    {
        sum = sum + nums[right];

        while (sum > k)
        {
            sum = sum - nums[left];
            left = left + 1;
        }

        best = max(best, right - left + 1);
    }

    return best;
}

// longest substring without repeating characters
// use of frequency array inside it
// Given a string, find the length of the longest substring containing no repeated characters.
int lengthOfLongestString(const string &str)
{
    if (str == "")
        return 0;

    int left = 0;
    int n = str.size();
    int best = 0;
    vector<int> frequencyArray(256, 0);
    // standard ASCII characters store a character of 1 byte which is 8 bits
    // so total possible characters are 0 to 2^8-1 = 255 that is total of 256 characters

    for (int right = 0; right < n; right++)
    {
        unsigned char c = str[right];
        frequencyArray[c]++;

        while (frequencyArray[c] > 1)
        {
            unsigned char outgoing = str[left];
            frequencyArray[outgoing]--;
            left++;
        }
        best = max(best, right - left + 1);
    }

    return best;
}

// Find the length of the longest substring containing at most K distinct characters.
int longestSubstringKDistinct(const string &str, int k)
{
    // for k = 0 below logic will always return 0;
    if (k < 0)
        return 0;

    int left = 0;
    int n = str.size();
    int best = 0;
    unordered_map<char, int> freq;

    for (int right = 0; right < n; right++)
    {
        freq[str[right]]++;

        while (freq.size() > k)
        {
            unsigned char outgoing = str[left];
            freq[str[left]]--;

            if (freq[str[left]] == 0)
            {
                freq.erase(str[left]);
            }

            left++;
        }

        best = max(best, right - left + 1);
    }

    return best;
}

// A powerful trick: exactly K distinct = at most K − at most K-1

// Fixed-size window with frequency counting
//  Find all anagrams of a pattern inside a string.
vector<int> findAnagrams(const string &s, const string &p)
{
    vector<int> ans;
    if (p.size() > s.size())
    {
        return ans;
    }
    int k = p.size();
    vector<int> need(26, 0);
    vector<int> window(26, 0);

    for (unsigned char c : p)
    {
        need[c - 'a']++;
    }

    for (int right = 0; right < s.size(); right++)
    {
        window[s[right] - 'a']++;
        if (right >= k)
        {
            window[s[right - k] - 'a']--;
        }
        if (right >= k - 1 && window == need)
        {
            ans.push_back(right - (k - 1));
        }
    }

    return ans;
}

int main()
{
    vector<int> arr = {2, 1, 5, 1, 3, 2};
    cout << maxSumSubarray(arr, 3) << endl;
    cout << lengthOfSumK(arr, 9) << endl;
    cout << lengthOfLongestString("abcabcbb") << endl;
    cout << longestSubstringKDistinct("eceba", 0);
    return 0;
}