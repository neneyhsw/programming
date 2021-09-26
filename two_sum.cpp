#include <ctime>
#include <iostream>
#include <map>
#include <stdlib.h>
#include <vector>
using namespace std;

class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        for (int i = 0; i < nums.size(); i++)
        {
            for (int j = i + 1; j < nums.size(); j++)
            {
                if (nums[i] + nums[j] == target)
                    return vector<int>({i, j});
            }
        }
        return vector<int>();
    }

    vector<int> twoSum_HashTable(vector<int> &nums, int target)
    {
        vector<int> ans;
        map<int, int> HT;
        map<int, int>::iterator iter;

        for (int i = 0; i <= nums.size(); i++)
        {
            if ((iter = HT.find(target - nums[i])) == HT.end())
            {
                // not found, save pair to HT
                HT.insert(pair<int, int>(nums[i], i));
            }
            else
            {
                // found it
                ans.push_back(iter->second);
                ans.push_back(i);
                return ans;
            }
        }
        return {};
    }
};

int main(int argc, char *argv[])
{
    //vector<int> nums = {2, 7, 11, 15};
    //int target = 9;  // [0,1]
    vector<int> nums = {3, 2, 4};
    clock_t start, stop;
    int target = 6; // [1,2]
    //vector<int> nums = {3,3}; int target = 6;  // [0,1]
    Solution s;

    vector<int> ts = s.twoSum(nums, target);
    vector<int> tsh = s.twoSum_HashTable(nums, target);

    if (ts.empty() || tsh.empty())
    {
        printf("no sum in vector, EXIT.\n");
        system("pause");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < ts.size(); ++i)
    {
        cout << ts[i] << endl;
    }
    //cout << "[" << ret[0] << "," << ret[1] << "]\n";

    system("pause");
    return EXIT_SUCCESS;
}
