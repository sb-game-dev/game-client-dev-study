#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;

int m, n,z_cnt,res;
int arr[1001][1001];
bool visit[1001][1001];
int dRow[] = { 0,0,1,-1 };
int dCol[] = { 1,-1,0,0 };
bool check(int row, int col)
{
	if (row < 0 || row >= n || col < 0 || col >= m) return false;
	if (visit[row][col])return false;
	if (arr[row][col]) return false;
	return true;
}
int main()
{
	cin >> m >> n;
	queue<pair<int, int>> q;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> arr[i][j];
			if (arr[i][j] == 1)
			{
				q.push({ i,j });
				visit[i][j] = 1;
			}
			if (arr[i][j] == 0 )z_cnt++;
		}
	}
	if (!z_cnt)
	{
		cout << 0;
		return 0;
	}
	while (!q.empty())
	{
		int pRow = q.front().first;
		int pCol = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++)
		{
			int nRow = pRow + dRow[i];
			int nCol = pCol + dCol[i];
			if (check(nRow, nCol))
			{
				visit[nRow][nCol] = 1;
				arr[nRow][nCol] = arr[pRow][pCol] + 1;
				q.push({ nRow,nCol });
				
			}
		}
	}
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (arr[i][j] == 0)
			{
				cout << -1;
				return 0;
			}
			res = arr[i][j] > res ? arr[i][j] : res;
		}
	}
	//수정 되는지 확인
	cout << res-1;
}
