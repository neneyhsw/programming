#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#define NUM 20
using namespace std;

class Solution
{
public:
    vector<vector<int>> Gale_Shapley_Algorithm(vector<vector<int>> &pursuer, vector<vector<int>> &chooser, vector<int> &marriage_index_c)
    {
        int rank = NUM + 1, boy_number = -1, ex_boy_rank = -1;
        bool be_choosed = false;
        vector<int> pursuer_list, man_propose_index(NUM, 0);
        vector<bool> whetherMarried(NUM, false);

        // pursuer喜歡名單一輪一輪往下檢查
        while (true)
        {
            // 是否全部都結婚，全部完成配對即可跳出
            if (find(marriage_index_c.begin(), marriage_index_c.end(), -1) == marriage_index_c.end())
                break;

            // 該輪的追求者人員
            pursuer_list.clear();
            for (int i = 0; i < NUM; i++)
            {
                if (whetherMarried[i] == false)
                {
                    pursuer_list.push_back(pursuer[i][man_propose_index[i] % NUM]);
                    man_propose_index[i]++;
                }
                else
                    pursuer_list.push_back(-1);
            }

            // i表示chooser的編號
            for (int i = 0; i < NUM; i++)
            {
                rank = NUM + 1;
                boy_number = -1;
                ex_boy_rank = -1;
                be_choosed = false;

                for (int j = 0; j < NUM; j++)         // j表示pursuer的編號
                    if (pursuer_list[j] == i)         // pursuer喜歡的人的編號 == i
                        for (int k = 0; k < NUM; k++) // chooser所有的preference儲存min，表示此pursuer為最高順位
                            if (chooser[i][k] == j && k < rank)
                            {
                                rank = k;
                                boy_number = j;
                                be_choosed = true;
                            }

                // 更新結婚名單
                if (marriage_index_c[i] == -1 && be_choosed == true) // 如果chooser沒有結婚且有被pursuer指名
                {
                    marriage_index_c[i] = boy_number;  // 將chooser vector內容儲存pursuer的index
                    whetherMarried[boy_number] = true; // pursuer結婚
                }
                else // 如果chooser已結婚
                {
                    for (int j = 0; j < NUM; j++)
                        if (marriage_index_c[i] == chooser[i][j])
                        {
                            ex_boy_rank = j; // 紀錄當前結婚對象的排名
                            break;
                        }
                    if (rank < ex_boy_rank)
                    {
                        whetherMarried[marriage_index_c[i]] = false; // 原本的pursuer變為未婚
                        marriage_index_c[i] = boy_number;
                        whetherMarried[boy_number] = true;
                    }
                }
            }
        }

        // Return 配對答案
        // 計算時為了方便讀取array的address所以有將編號-1
        // 因此將index+1恢復編號
        vector<vector<int>> ans(NUM, vector<int>(NUM));
        for (int i = 0; i < NUM; i++)
        {
            ans[i][0] = marriage_index_c[i] + 1; // pursuer number
            ans[i][1] = i + 1;                   // chooser number
        }

        return ans;
    }
};

int main(int argc, char **argv)
{
    /*
        此程式直接讀取csv檔中的資料，因此需要設定完成csv檔的路徑才可順利執行程式
        Gale-Shapley Algorithm pseudo code如下 (以男生向女生求婚為例):
        Reference: https://www.geeksforgeeks.org/stable-marriage-problem/

        Initialize all men and women to free
        while there exist a free man m who still has a woman w to propose to 
        {
            w = m's highest ranked such woman to whom he has not yet proposed
            if w is free
                (m, w) become engaged
            else some pair (m', w) already exists
                if w prefers m to m'
                    (m, w) become engaged
                    m' becomes free
                else
                    (m', w) remain engaged    
        }

        實作流程如下:
        1. 抓出每位男生對於未被拒絕的女生的最高排名，存為list
        2. 搜尋每位女生的n個排行，讀取第1步驟男生每輪抓出的list
        3. 以男生preference list搜尋每位女生的排名，儲存排名最高者的女生
        4. 如果女生未婚，直接結婚，如果女生已婚，則比較已婚對象的排名，如果新人排名較高則離婚舊人並結婚新人
        5. 重複2, 3, 4步驟，直到每個人都配對成功
    */

    // 設定20*20的two dimensional vector
    vector<vector<int>> man(NUM, vector<int>(NUM)), woman(NUM, vector<int>(NUM));
    vector<int> MarriageIndex(NUM, -1); // 紀錄chooser是否已經結婚

    // 讀取csv檔存入vector
    // row index is person number, column is preference
    fstream file_m, file_w;
    string row_m, row_w, num_m, num_w;
    file_m.open("./Gale_Shapley_Algorithm_Test_Data/20_man.csv");
    file_w.open("./Gale_Shapley_Algorithm_Test_Data/20_woman.csv");

    // csv檔的第一個row和第一個column的值不須存入vector，所以i, j的初始值為-1
    for (int i = -1; getline(file_m, row_m, '\n') && getline(file_w, row_w, '\n'); i++)
    {
        if (i < 0)
            continue;

        stringstream prefer_num_m(row_m), prefer_num_w(row_w);
        for (int j = -1; getline(prefer_num_m, num_m, ',') && getline(prefer_num_w, num_w, ','); j++)
        {
            if (j < 0)
                continue;

            // string to int，將所有編號-1以符合array index
            man[i][j] = stoi(num_m) - 1;
            woman[i][j] = stoi(num_w) - 1;
        }
    }
    file_m.close();
    file_w.close();

    /**** Gale-and-Shapley algorithm ****/
    vector<vector<int>> woman_favored, man_favored;
    Solution s;
    woman_favored = s.Gale_Shapley_Algorithm(man, woman, MarriageIndex);
    for (int i = 0; i < NUM; i++)
        MarriageIndex[i] = -1; // reset vector值為-1
    man_favored = s.Gale_Shapley_Algorithm(woman, man, MarriageIndex);

    /**** PRINT ****/
    // sorting by column man
    // reference: https://stackoverflow.com/questions/45494567/c-how-to-sort-the-rows-of-a-2d-vector-by-the-values-in-each-rows-column
    // 皆以man來排序
    sort(woman_favored.begin(), woman_favored.end(), [](const vector<int> &a, const vector<int> &b)
         { return a[0] < b[0]; });
    sort(man_favored.begin(), man_favored.end(), [](const vector<int> &a, const vector<int> &b)
         { return a[1] < b[1]; });

    // print result
    cout << "woman favored strategy:" << endl;
    cout << "[man, woman]" << endl;
    for (int i = 0; i < NUM; i++)
        for (int j = 0; j < 2; j++)
            if (j == 0)
                cout << "[" << woman_favored[i][j] << ", ";
            else
                cout << woman_favored[i][j] << "]" << endl;

    cout << "\nman favored strategy:" << endl;
    cout << "[man, woman]" << endl;
    for (int i = 0; i < NUM; i++)
        for (int j = 1; j >= 0; j--) // 因為先顯示男生，所以2維陣列的index從high到low
            if (j == 1)
                cout << "[" << man_favored[i][j] << ", ";
            else
                cout << man_favored[i][j] << "]" << endl;

    system("pause");
    return EXIT_SUCCESS;
}
