#include<iostream>
#include<algorithm>
using namespace std;
int r, c, res;
int arr[21][21];
int visit[26];
int dRow[] = { 0,0,1,-1 };
int dCol[] = { 1,-1,0,0 };
bool check(int row, int col)
{
	if (row < 0 || row >= r || col < 0 || col >= c) return false;
	if (visit[arr[row][col]])return false;
	return true;
}
void dfs(int row, int col, int cnt)
{
	visit[arr[row][col]] = 1;

	res = max(res, cnt);
	for (int i = 0; i < 4; i++)
	{
		int nRow = row + dRow[i];
		int nCol = col + dCol[i];
		if (check(nRow, nCol))
		{
			dfs(nRow, nCol, cnt + 1);
		}
	}
	visit[arr[row][col]] = 0;
}
int main()
{
	cin >> r >> c;
	for (int i = 0; i < r; i++)
	{
		string s;
		cin >> s;
		for (int j = 0; j < c; j++)
		{
			arr[i][j] = s[j] - 'A';
		}
	}
	dfs(0, 0, 1);
	cout << res;
}