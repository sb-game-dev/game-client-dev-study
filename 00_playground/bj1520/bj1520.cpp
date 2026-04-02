#include<iostream>
#include<cstring>
using namespace std;

int n, m, res;
int arr[501][501];
int visit[501][501];
int dRow[] = { 0,0,1,-1 };
int dCol[] = { 1,-1,0,0 };
struct st
{
	int row, col;
};

bool check(int row, int col)
{
	if (row < 0 || row >= n || col < 0 || col >= m)return false;
	return true;
}
int dfs(int row, int col)
{
	if (row == n - 1 && col == m - 1)
	{
		return 1;
	}

	if (visit[row][col] != -1) return visit[row][col];

	visit[row][col] = 0;
	for (int i = 0; i < 4; i++)
	{
		int nRow = row + dRow[i];
		int nCol = col + dCol[i];

		if (check(nRow, nCol) && arr[nRow][nCol] < arr[row][col])
		{
			visit[row][col] += dfs(nRow, nCol);
		}
	}

	return visit[row][col];
}
int main()
{
	cin >> n >> m;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> arr[i][j];
		}
	}
	memset(visit, -1, sizeof(visit));
	cout << dfs(0, 0) << endl;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << visit[i][j] << "\t";
		}
		cout << endl;
	}

}