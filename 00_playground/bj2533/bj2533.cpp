#include<iostream>
#include<algorithm>
#include<vector>
#define MAX 1000001
using namespace std;
int n;
vector<int> tree[MAX];
int dp[MAX][2];
void dfs(int node, int parent)
{
	dp[node][0] = 0;
	dp[node][1] = 1;

	for (int i = 0; i < tree[node].size(); i++)
	{
		int next = tree[node][i];
		if (next == parent) continue;

		dfs(next, node);

		dp[node][0] += dp[next][1];
		dp[node][1] += min(dp[next][0], dp[next][1]);
	}
}
int main()
{
	cin >> n;
	for (int i = 0; i < n-1; i++)
	{
		int a, b;
		cin >> a >> b;
		tree[a].push_back(b);
		tree[b].push_back(a);
	}

	dfs(1,0);
	cout << min(dp[1][0], dp[1][1]);
}