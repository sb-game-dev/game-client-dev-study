#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;
int n, m;
struct st
{
    int row, col;
    bool brk;
};
int arr[1001][1001];
int dist[1001][1001][2];
bool visit[1001][1001][2];
int d_row[] = { 0,0,1,-1 };
int d_col[] = { 1,-1,0,0 };

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        string s;
        cin >> s;
        for (int j = 1; j <= m; j++)
        {
            arr[i][j] = s[j - 1] - '0';
        }
    }

    queue<st> q;
    q.push({ 1,1,0 });
    visit[1][1][0] = true;
    dist[1][1][0] = 1;
    while (!q.empty())
    {
        int p_row = q.front().row;
        int p_col = q.front().col;
        bool brk = q.front().brk;
        for (int i = 0; i < 4; i++)
        {
            int n_row = q.front().row + d_row[i];
            int n_col = q.front().col + d_col[i];

            if (n_row<1 || n_row>n || n_col<1 || n_col>m) continue;

            if (arr[n_row][n_col] == 0 && !visit[n_row][n_col][brk])
            {
                visit[n_row][n_col][brk] = 1;
                dist[n_row][n_col][brk] = dist[p_row][p_col][brk] + 1;
                q.push({ n_row,n_col,brk });
            }
            if (arr[n_row][n_col] == 1 && brk == 0 && !visit[n_row][n_col][1])
            {
                visit[n_row][n_col][1] = 1;
                dist[n_row][n_col][1] = dist[p_row][p_col][0] + 1;
                q.push({ n_row,n_col,1 });
            }

        }
        q.pop();
    }
    int brk_false = dist[n][m][0], brk_true = dist[n][m][1];
    if (!brk_false && !brk_true) cout << -1;
    else if (!brk_false ) cout << brk_true;
    else if (!brk_true ) cout << brk_false;
    else cout << min(brk_false, brk_true);

}