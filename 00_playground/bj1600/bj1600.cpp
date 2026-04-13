#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;
int k, n, m;
int arr[201][201];
int visit[201][201];
int res[201][201];
int dRwo[] = { 0,0,1,-1 };
int dCol[] = { 1,-1,0,0 };
int chanceRow[] = { -1,-2,-2,-1,1,2,2,1 };
int chanceCol[] = { -2,-1,1,2,-2,-1,1,2 };
//2
//5 2
//0 0 1 1 0
//0 0 1 1 0  -> -1

//1
//4 4
//0 0 0 0
//1 0 0 0
//0 0 1 0
//0 1 0 0  -> 4
struct st
{
	int r, c, chance;
};
int bfs(int row, int col)
{
	queue<st> q;
	q.push({ row,col ,k });
	while (!q.empty())
	{
		int cRow = q.front().r;
		int cCol = q.front().c;
		int cChance = q.front().chance;
		visit[cRow][cCol] = 1;
		if (cChance > 0)
		{
			for (int i = 0; i < 8; i++)
			{

			}
		}
		for (int i = 0; i < 4; i++)
		{

		}
	}
}

int main()
{
	cin >> k >> m >> n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> arr[i][j];
		}
	}

	bfs(0, 0);
	//cout << min(res[n - 1][m - 1][0], res[n - 1][m - 1][1]);
}
