#include<cstdio>
#include<vector>
#include<algorithm>
#define MIN -1000000000000000

void set_dp(std:: vector<std:: vector<long long> > &dp,
			std:: vector<long long> &num, long long k, int m){
	for(int i = 0; i < m && i < num.size(); ++i){
		dp[1][i] = num[i] - k;
	}
	for(int i = 2; i < m ; ++i){
		for(int j = 1; j < m && j < num.size(); ++j)
			dp[i][j] = dp[i- 1][j - 1] + num[j];
	}
	if(m <= num.size())
		dp[0][m - 1] = dp[m - 1][m - 2] + num[m - 1];
	for(int i = m; i < num.size(); ++i){
		for(int j = 0; j < m; ++j){
			if(j == 0)
				dp[j][i] = dp[m - 1][i - 1] + num[i];
			else if(j == 1)
				dp[j][i] = std:: max(num[i] - k, dp[0][i - 1] + num[i] - k);
			else
				dp[j][i] = dp[j - 1][i - 1] + num[i];
		}
	}
}

void set_dp2(std:: vector<std:: vector<long long> > &dp,
			std:: vector<long long> &num, long long k, int m){
	dp[0][0] = num[0] - k;
	for(int i = 1; i < num.size(); ++i)
		dp[0][i] = std:: max(dp[0][i - 1] + num[i] - k, num[i] - k);
}

long long find(std:: vector<std:: vector<long long> > &dp){
	long long maxa = 0;
	for(int i = 0; i < dp.size(); ++i)
		for(int j = 0; j < dp[0].size(); ++j)
			maxa = std:: max(maxa, dp[i][j]);
	return maxa;
}

int main(){
	int n;
	long long k;
	int m;
	scanf("%d %d %lld", &n, &m, &k);
	std:: vector<long long> num(n);
	for(int i = 0; i < n; ++i)
		scanf("%lld", &num[i]);
	std:: vector<std:: vector<long long> > dp(m, std:: vector<long long>(n, MIN));
	if(m != 1)
		set_dp(dp, num, k, m); 
	if(m == 1)
		set_dp2(dp, num, k, m);
	long long ans = find(dp);
	printf("%lld\n", ans);
	return 0;	
}
