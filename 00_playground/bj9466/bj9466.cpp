#include <iostream>
#include <cstring>
using namespace std;

int t, n;
int arr[100001];
int visited[100001];
int finished[100001];
int cnt;

void dfs(int now)
{
    visited[now] = 1;
    int next = arr[now];

    if (!visited[next])
    {
        dfs(next);
    }
    else if (!finished[next])
    {
        for (int i = next; i != now; i = arr[i])
        {
            cnt++;
        }
        cnt++;
    }

    finished[now] = 1;
}

int main()
{
    cin >> t;
    while (t--)
    {
        cin >> n;

        for (int i = 1; i <= n; i++)
        {
            cin >> arr[i];
        }

        memset(visited, 0, sizeof(visited));
        memset(finished, 0, sizeof(finished));
        cnt = 0;

        for (int i = 1; i <= n; i++)
        {
            if (!visited[i])
            {
                dfs(i);
            }
        }

        cout << n - cnt << '\n';
    }
}