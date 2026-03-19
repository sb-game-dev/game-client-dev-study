#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;
int arr[101][101];
bool visit[101][101];
int dRow[] = { 0,0,1,-1 };
int dCol[] = { 1,-1,0,0 };
int n, m;
bool check(int row, int col)
{
    if (row<1 || row >n || col<1 || col>m) return false;
    if (visit[row][col] == true) return false;
    if (arr[row][col] == 0) return false;
    return true;
}
int main()
{
    cin >> n >> m;

    for (int i = 1; i <= n; ++i)
    {
        string s;
        cin >> s;
        for (int j = 1; j <= m; ++j)
        {
            arr[i][j] = s[j - 1] - '0';
        }
    }
    queue<pair<int, int>> q;
    q.push({ 1,1 });

    while (!q.empty())
    {
        int preR = q.front().first;
        int preC = q.front().second;

        cout << preR << " " << preC << "\n";
        for (int i = 0; i < 4; ++i)
        {
            if (check(preR + dRow[i], preC + dCol[i]))
            {
                visit[preR + dRow[i]][preC + dCol[i]] = true;
                q.push({ preR + dRow[i],preC + dCol[i] });
                arr[preR + dRow[i]][preC + dCol[i]] = arr[preR][preC] + 1;
            }
        }
        q.pop();
    }

    cout << arr[n][m];
}