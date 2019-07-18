#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<iostream>

struct Place{
	int y;
	int x;
};

struct Section{
	int L;
	int R;	
};

void BFS(Place start, int n, int m, 
		 std:: vector<std:: vector<bool> > &visit,
		 std:: vector<std:: vector<int> > &city){
	std:: queue<Place> order;
	order.push(start);	
	visit[start.y][start.x] = true;
	while(!order.empty()){
		Place now = order.front();
		order.pop();
		int d[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
		for(int i = 0; i < 4; ++i){
			int ny = now.y + d[i][0];
			int nx = now.x + d[i][1];
			if(nx < 0 || nx >= m || ny < 0 || ny >= n){
			}else if(!visit[ny][nx] && city[ny][nx] < city[now.y][now.x]){
				visit[ny][nx] = true;
				order.push({ny, nx});
			}
		}
	}
}

std:: pair<bool, int> check_city(std:: vector<std:: vector<int> > &city, int n, int m){
	std:: vector<std:: vector<bool> > visit(n, std:: vector<bool>(m, 0));
	for(int i = 0; i < m; ++i)
		if(!visit[0][i])
			BFS({0, i}, n, m, visit, city);
	int range = n - 1;
	int sum = 0;
	bool ok = true;
	for(int i = 0; i < m; ++i){
		if(!visit[range][i]){
			sum ++;
			ok = false;
		}
	}
	return std:: make_pair(ok, sum);
}

void get_section(int now, int last, std:: vector<std:: vector<bool> > &visit, std:: vector<Section> &section){
	section[now].R = -1;
	section[now].L = -1;
	for(int i = 0; i < visit[last].size(); ++i)
		if(visit[last][i]){
			section[now].L = i;
			break;
		}
	for(int i = visit[last].size() - 1; i >= 0; --i)
		if(visit[last][i]){
			section[now].R = i;
			break;	
		}
}

bool cmp(Section a, Section b){
	if(a.L == b.L)
		return a.R > b.R;
	return a.L < b.L;
}

int find(int n, int m, std:: vector<std:: vector<int> > &city){
	std:: vector<Section> section(m);
	for(int i = 0; i < m; ++i){
		std:: vector<std:: vector<bool> > visit(n, std:: vector<bool>(m, 0));
		BFS({0, i}, n, m, visit, city);
		get_section(i, n - 1, visit, section);	
	}
	std:: sort(section.begin(), section.end(), cmp);
	int last = 0;
	int far = 0;
	int sum = 0;
	int start = 0;
	for(start; section[start].L == -1; ++start){
	}
	for(int i = start; i < section.size(); ++i){
		if(last >= m)
		 	return sum;
		if(section[i].L <= last)
			far = far > section[i].R ? far : section[i].R;
		else{
			last = far + 1;
			sum++;
			if(section[i].L <= last)
				far = far > section[i].R ? far : section[i].R;
		}
	}
	if(last <= m - 1)
		sum ++;
	return sum;
}

int main(){
	int n;
	int m;
	scanf("%d %d", &n, &m);
	std:: vector<std:: vector<int> > city(n, std:: vector<int>(m));
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			scanf("%d", &city[i][j]);
	std:: pair<bool, int> check = check_city(city, n, m);
	if(!check.first){
		printf("0\n");
		printf("%d\n", check.second);	
	}else{
		int ans = find(n, m, city);
		printf("1\n");
		printf("%d\n", ans);	
	}
	return 0;	
}
