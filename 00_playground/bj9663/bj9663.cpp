#include<iostream>
using namespace std;
int n, cnt;
int visit[16][16];

bool check(int row, int col)
{
    for (int c = 0; c < col; c++)
    {
        if (visit[row][c])return false;
    }

    int r = row - 1;
    int c = col - 1;
    while (r >= 0 && c >= 0)
    {
        if (visit[r][c]) return false;
        r--;
        c--;
    }
    r = row + 1;
    c = col - 1;
    while (r < n && c >= 0)
    {
        if (visit[r][c]) return false;
        r++;
        c--;
    }
    return true;
}

void dfs(int col)
{
    if (col == n)
    {
        cnt++;
        return;
    }
    for (int row = 0; row < n; row++)
    {
        if (check(row, col))
        {
            visit[row][col] = 1;
            dfs(col + 1);
            visit[row][col] = 0;
        }
    }
}

int main()
{
    cin >> n;
    dfs(0);
    cout << cnt;
}