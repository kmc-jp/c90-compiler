/*Solve Knapsack problem*/

#include <stdio.h>
#define N 100
#define W 10000

int n, mw, v[N], w[N];

int max(int a, int b)
{
	return a>b?a:b;
}
int main(void){
	int i, j;
	scanf("%d%d",&n,&mw);
	for(i=0;i<n;i++)
		scanf("%d%d", &v[i], &w[i]);

	int dp[N+1][W+1]={0};
	for(j=0;j<n;j++)
		for(i=0;i<=mw;i++)
		{
			dp[j + 1][i] = max(dp[j+1][i], dp[j][i]);
			if(i+w[j] <= mw)
				dp[j + 1][i + w[j]] = max(dp[j+1][i + w[j]], dp[j][i] + v[j]);
		}

	int ans=0;
	for(i=0;i<=mw;i++)
		ans = max(ans, dp[n][i]);
	printf("%d\n", ans);
	return 0;
}
