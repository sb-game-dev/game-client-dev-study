#include<iostream>
using namespace std;
int n, m;
bool isLoop;
int arr[51][51];
int dp[51][51];
bool visit[51][51] = {};
int dRow[] = { 0,0,1,-1 };
int dCol[] = { 1,-1,0,0 };

int dfs(int row, int col)
{
    if (dp[row][col]) return dp[row][col];

    visit[row][col] = 1;
    dp[row][col] = 1;
    for (int i = 0; i < 4; i++)
    {
        int nRow = row + dRow[i]*arr[row][col];
        int nCol = col + dCol[i]*arr[row][col];
        if (nRow < 0 || nRow >= n || nCol < 0 || nCol >= m) continue;
        if (!arr[nRow][nCol]) continue;
        if (visit[nRow][nCol])
        {
            isLoop = true;
            return 0;
        }
        dp[row][col] = max(dp[row][col], 1 + dfs(nRow, nCol));
    }
    visit[row][col] = 0;
    return dp[row][col];
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
            if (s[j] == 'H') arr[i][j] = 0;
            else arr[i][j] = s[j] - '0';
        }
    }

    dfs(0, 0);
    if (isLoop) cout << -1;
    else cout << dp[0][0];
}