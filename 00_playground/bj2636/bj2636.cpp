#include<iostream>
#include<queue>
using namespace std;
int arr[101][101];
int dRow[] = { 0,0,1,-1 };
int dCol[] = { 1,-1,0,0 };
int n, m, res, t;

void bfs(int row, int col)
{
    int cheez = 0;
    int air[101][101] = { 0 };
    int visit[101][101] = { 0 };
    queue<pair<int, int>> q;
    q.push({ row,col });
    visit[row][col] = 1;
    while (!q.empty())
    {
        int pRow = q.front().first;
        int pCol = q.front().second;
        for (int i = 0; i < 4; i++)
        {
            int nRow = pRow + dRow[i];
            int nCol = pCol + dCol[i];
            if (nRow < 0 || nCol < 0 || nRow >= n || nCol >= m)continue;
            if (visit[nRow][nCol])continue;

            if (arr[nRow][nCol] == 0)
            {
                q.push({ nRow,nCol });
                visit[nRow][nCol] = 1;
            }
            else
            {
                air[nRow][nCol] = 1;
            }
        }
        q.pop();
    }
    

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (arr[i][j] == air[i][j])
            {
                arr[i][j] = 0;
            }
        }
    }


    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cheez += arr[i][j];
        }
    }
    if (!cheez)
    {
        cout <<t+1<<"\n"<< res;
    }
    else
    {
        res = cheez;
        t++;
        bfs(0, 0);
    }
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> arr[i][j];
            res += arr[i][j];
        }
    }
    if(res)bfs(0, 0);
    else
    {
        cout<<0<<"\n"<<0;
    }
    

}