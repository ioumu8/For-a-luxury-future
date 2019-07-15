#include<cstdio>
#include<algorithm>
#include<vector>
#include<cmath>
#define MAX 2147483647

struct Link{
	int num;
	int cost;	
};

bool cmp(Link a, Link b){
	return a.cost > b.cost;	
}

int find_dist(int s, int t, std:: vector<std:: vector<Link> > &dist){
	std:: vector<Link> save;
	std:: vector<int> visit(dist.size(), -1); 
	Link start;
	start.num = s;
	start.cost = 0;
	save.push_back(start);
	while(!save.empty()){
		Link now = save.front();
		std:: pop_heap(save.begin(), save.end(), cmp);
		save.pop_back();
		visit[now.num] = now.cost; 	
		if(now.num == t)
			break;
		for(int i = 0; i < dist[now.num].size(); ++i){
			Link tmp = dist[now.num][i];
			if(visit[tmp.num] == -1){
				tmp.cost += now.cost; 
				save.push_back(tmp);	
				std:: push_heap(save.begin(), save.end(), cmp);
			}
		}	
	}
	return visit[t];
}

void key_in(int u, int v, int value, std:: vector<std:: vector<Link> > &dist){
	Link tmp;
	tmp.num = v;
	tmp.cost = value;
	dist[u].push_back(tmp); 	
}

int divide(int num,
		   std:: vector<std:: vector<int> > &dist,
		   std:: vector<int> &dp){
	if(dp[num] != -1 || num == 0){
		return dp[num];		
	}
	dp[num] = MAX;
	for(int i = 0; i < dist.size(); ++i){
		if(num & 1 << i){
			for(int j = i + 1; j < dist.size(); ++j){
				if(num & 1 << j){
					int next = num - (1 << i) - (1 << j);
					dp[next] = divide(next, dist, dp);
					dp[num] = std:: min(dp[num], dp[next] + dist[i][j]);	
				}
			}
		}
	}
	return dp[num];
}

int final_ans(std:: vector<std:: vector<int> > &dist){
	if(dist.size() == 0)
		return 0;
	std:: vector<int> dp((int)pow(2, dist.size()), -1);	
	int start = 0;
	int end = dist.size() - 1;
	int final = pow(2, dist.size()) - 1;
	for(int i = 0; i < dist.size(); ++i){
		for(int j = i + 1; j < dist.size(); ++j)
			dp[(1 << i) + (1 << j)] = dist[i][j];	
	}
	dp[final] = divide(final, dist, dp);
	return dp[final];	
	
}

int main(){
	int n;
	int m;
	int start;
	int sum = 0; 
	scanf("%d %d %d", &n, &m, &start);
	start--;
	std:: vector<std:: vector<Link> > dist(n);
	for(int i = 0; i < m; ++i){
		int u;
		int v;
		int value;
		scanf("%d %d %d", &u, &v, &value);
		u--;
		v--;
		key_in(u, v, value, dist);
		key_in(v, u, value, dist);
		sum += value;
	}
	std:: vector<int> keep;
	for(int i = 0; i < dist.size(); ++i)
		if(dist[i].size() % 2)
			keep.push_back(i);
	std:: vector<std:: vector<int> > new_dist(keep.size(), std:: vector<int>(keep.size(), -1));
	for(int i = 0; i < keep.size(); ++i)
		for(int j = i + 1; j < keep.size(); ++j){	
			int len = find_dist(keep[i], keep[j], dist);
			new_dist[i][j] = len;
			new_dist[j][i] = len;
		}
	sum += final_ans(new_dist);
	printf("%d\n", sum);
	return 0;	
}
