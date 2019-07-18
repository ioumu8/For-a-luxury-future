#include<cstdio>
#include<vector>
#include<algorithm>
#define MAX 10000000

void set_h(std:: vector<std:: vector<int> > &set, std:: vector<std:: vector<int> > &h, int n, int m){
	for(int i = 0; i < m; ++i)
		h[0][i] = 1;
	for(int i = 1; i < n; ++i)
		for(int j = 0; j < m; ++j)
			h[i][j] = set[i][j] > set[i - 1][j] ? h[i - 1][j] + 1 : 1;
}

void set_l(std:: vector<std:: vector<int> > &set, std:: vector<std:: vector<int> > &l, int n, int m){
	for(int i = 0; i < n; ++i)
		l[i][0] = 1;
	for(int i = 1; i < m; ++i)
		for(int j = 0; j < n; ++j)
			l[j][i] = set[j][i] > set[j][i - 1] ? l[j][i - 1] + 1 : 1;
}

int find(int ny, int nx, int n, int m,
	     std:: vector<std:: vector<int> > &h,
		 std:: vector<std:: vector<int> > &l){
	int maxa = -1;
	for(int keep_h = 1; keep_h <= h[ny][nx]; ++keep_h){
		int keep_l = MAX;
		for(int j = 0; j < keep_h; ++j){
			keep_l = std:: min(keep_l, l[ny - j][nx]);
		}
		int range = keep_l - 1;
		for(int j = 0; j < keep_l; ++j){
			if(h[ny][nx - j] < keep_h){
				maxa = std:: max(maxa, keep_h * j);
				break; 
			}
			if(j == range)
				maxa = std:: max(maxa, keep_h * keep_l);
		}
	}
	return maxa;
}

int main(){
	int n;
	int m;
	scanf("%d %d", &n, &m);
	std:: vector<std:: vector<int> > set(n, std:: vector<int>(m));
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			scanf("%d", &set[i][j]);
	std:: vector<std:: vector<int> > h(n, std:: vector<int>(m));
	std:: vector<std:: vector<int> > l(n, std:: vector<int>(m));
	set_h(set, h, n, m);
	set_l(set, l, n, m);
	int maxa = -1;
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < m; ++j){
			int ans = find(i, j, n, m, h, l);
			maxa = maxa > ans ? maxa : ans;
		}
	}
	printf("%d\n", maxa);
	return 0;	
}
