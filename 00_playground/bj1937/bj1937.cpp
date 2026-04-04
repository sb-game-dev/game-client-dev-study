#include <iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int n,res;
int arr[501][501];
int dp[501][501];
int dRow[] = { 0,0,1,-1 };
int dCol[] = { 1,-1,0,0 };
int dfs(int row, int col)
{
	if (dp[row][col] != -1)
		return dp[row][col];
	dp[row][col] = 0;
	for (int i = 0; i < 4; i++)
	{
		int nRow = row + dRow[i];
		int nCol = col + dCol[i];
		if (nRow < 0 || nRow >= n || nCol < 0 || nCol >= n)continue;
		if (arr[row][col] < arr[nRow][nCol])
		{
			dp[row][col] = max(dp[row][col] , dfs(nRow, nCol));
		}
	}
	return ++dp[row][col];
}
int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++) cin >> arr[i][j];
	}
	memset(dp, -1, sizeof(dp));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++) dp[i][j] = dfs(i, j);
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++) res = max(res, dp[i][j]);
	}
	cout << res;
}

