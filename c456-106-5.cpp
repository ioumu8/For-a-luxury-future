#include<cstdio>
#include<vector>
#include<queue>

struct Member{
	int club;
	int line;	
};

int set_member(std:: vector<Member> &member, std:: vector<std:: vector<int> > &connect){
	int num = 1;
	for(int i = 0; i < member.size(); ++i){
		if(member[i].club == 0){
			member[i].club = num;
			member[i].line = connect[i].size();
			std:: queue<int> set;
			set.push(i);
			while(!set.empty()){
				int keep = set.front();
				set.pop();
				for(int j = 0; j < connect[keep].size(); ++j){
					int now = connect[keep][j];
					if(member[now].club == 0){
						member[now].club = num;
						member[now].line = connect[now].size();
						set.push(now);	
					}
				}
			} 
			num++;	
		}
	}
	return num - 1;
}

int find(int now,int club, std:: vector<Member> &member, std:: vector<std:: vector<int> > &connect){
	bool check = false;
	while(!check){
		check = true;
		for(int i = 0; i < member.size(); ++i){
			if(member[i].club == club && member[i].line != 0){
				if(member[i].line < now){
					check = false;
					member[i].line = 0;
					for(int j = 0; j < connect[i].size(); ++j){
						int keep = connect[i][j];
						member[keep].line = member[keep].line == 0 ? 0 : member[keep].line - 1;
					}
				}
			}
		}
	}
	int num = 0;
	for(int i = 0; i < member.size(); ++i){
		if(member[i].club == club && member[i].line != 0)
			num++;
	}
	return num;
}

int calculate(int club, std:: vector<Member> &member, std:: vector<std:: vector<int> > &connect){
	int now = 1;
	int maxa = 0;
	bool ok = false;
	while(!ok){
		int num = find(now, club, member, connect);
		maxa = num * now > maxa ? num * now : maxa; 
		now++;
		if(num == 0)
			ok = true;
	}
	return maxa;
}

int main(){
	int n;
	int m;
	scanf("%d %d", &n, &m);
	std:: vector<std:: vector<int> > connect(n);
	std::vector<Member> member(n);
	for(int i = 0; i < n; ++i){
		member[i].club = 0;
		member[i].line = 0;	
	}
	for(int i = 0; i < m; ++i){
		int a, b;
		scanf("%d %d", &a, &b);
		a--;
		b--;
		connect[a].push_back(b);
		connect[b].push_back(a);	
	}
	int club = set_member(member, connect);
	int F = 0;
	for(int i = 1; i <= club; ++i){
		int run_F = calculate(i, member, connect);
		F = run_F > F ? run_F : F;	
	}
	printf("%d\n", F);
	return 0;	
}
