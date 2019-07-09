#include<cstdio>
#include<vector>
#include<cmath>

int find(int now, std:: vector<int> &dp, std:: vector<int> &point, int n){
	if(dp[now] != -1)
		return dp[now];
	int maxa = -1;
	for(int i = 0; i < n; ++i){
		if(now & 1 << i){
			dp[now - (1 << i)] = find(now - (1 << i), dp, point, n);
			maxa =  dp[now - (1 << i)] > maxa ? dp[now - (1 << i)] : maxa;	
		}
	}
	return maxa + point[now];
}

int main(){
	int n;
	scanf("%d", &n);
	while(n != 0){
		int ter = (int)pow(2, n);
		std:: vector<int> point(ter);
		std:: vector<int> dp(ter, -1);
		for(int i = 0; i < ter; ++i)
			scanf("%d", &point[i]);
		dp[0] = point[0];
		dp[ter - 1] = find(ter - 1, dp, point, n);
		printf("%d\n", dp[ter - 1]);
		scanf("%d", &n);
	}
	return 0;	
}
