#include <iostream>
#include <cstring>
using namespace std;

int n, m, res;
char arr[501][501];
int dp[501][501];
bool visit[501][501];
bool dfs(int row, int col)
{
    if (dp[row][col]!=-1) return dp[row][col];
    if (visit[row][col]) return dp[row][col] = 0;

    dp[row][col] = 0;
    visit[row][col] = true;
    int nRow = row;
    int nCol = col;
    if (arr[row][col] == 'U') nRow--;
    else if (arr[row][col] == 'R') nCol++;
    else if (arr[row][col] == 'L')nCol--;
    else if (arr[row][col] == 'D')nRow++;

    if (nRow < 0 || nRow >= n || nCol < 0 || nCol >= m)
    {
        visit[row][col] = false;
        return dp[row][col] = 1;
    }
    visit[row][col] = false;
    return dp[row][col] = dfs(nRow, nCol);
    
}
int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++)
        {
            arr[i][j] = s[j];
        }
    }
    memset(dp, -1, sizeof(dp));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (dp[i][j] == -1)
            {
                dp[i][j] = dfs(i, j);
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
     
            if(dp[i][j] == 1) res += dp[i][j];
            //cout << dp[i][j]<<" ";
        }
        //cout << "\n";
    }
    cout << res;
}

