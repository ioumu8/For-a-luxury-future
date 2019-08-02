#include<cstdio>
#include<vector>
#include<queue>

struct Num{
	int tie;
	std:: vector<int> connect; 	
};

struct Line{
	int u;
	int v;	
};

void set_people(std:: vector<Num> &people){
	for(int i = 0; i < people.size(); ++i)
		people[i].tie = 0;	
}

void kill(int line, int n, std:: vector<Num> &people, std:: vector<Line> &keep){
	bool ok = true;
	while(ok){	
		ok = false;
		for(int i = 0; i < n; ++i){
			if(people[i].tie != 0 && people[i].tie <= line){
				ok  = true;
				people[i].tie = 0;
				for(int j = 0; j < people[i].connect.size(); ++j){
					int now = people[i].connect[j];
					if(people[now].tie != 0){
						people[now].tie--;	
						keep.push_back({i, now});
					}
				}
			}
		}
	}
}

int find(int now, std:: vector<int> &club){
	return 	club[now] == now ? now : club[now] = find(club[now], club);
}

void build(std:: vector<int> &club, std:: vector<Line> &order){
	if(order.size() == 0)
		return ;
	for(int i = 0; i < order.size(); ++i){
		int x = find(club[order[i].u], club);
		int y = find(club[order[i].v], club);
		club[x] = y;
	}
}

int calculate(std:: vector<int> &club){
	for(int i = 0; i < club.size(); ++i)
		club[i] = find(club[i], club);
	std:: vector<int> num(club.size(), 0);
	for(int i = 0; i < club.size(); ++i)
		num[club[i]]++;
	int maxa = -1;
	for(int i = 0; i < num.size(); ++i)
		maxa = maxa > num[i] ? maxa : num[i];
	return maxa;
}

int main(){
	int n;
	int m;
	scanf("%d %d", &n, &m);
	std:: vector<Num> people(n);
	set_people(people);
	for(int i = 0; i < m; ++i){
		int u;
		int v;
		scanf("%d %d", &u, &v);
		u--;
		v--;
		people[u].tie++;
		people[u].connect.push_back(v);
		people[v].tie++;
		people[v].connect.push_back(u);
	}
	std:: vector<std:: vector<Line> > order;
	for(int i= 0; i < n; ++i){
		std:: vector<Line> keep;
		kill(i, n, people, keep);
		order.push_back(keep);
	}
	std:: vector<int> club(n);
	for(int i = 0; i < n; ++i)
		club[i] = i;
	int ans = -1;
	for(int i = order.size() - 1; i >= 0; --i){
		build(club, order[i]);
		int now = calculate(club);
		if(now != 1){
			now *= i;
			ans = ans > now ? ans : now;
		}
	}
	printf("%d\n", ans);
	return 0;	
}
