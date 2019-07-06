#include<cstdio>
#include<string>
#include<iostream>
#include<algorithm>
#include<vector>

struct Date{
	int M;
	int D;
	int H;
	int Y;	
};

struct Article{
	int order;
	std:: string subject;
	Date date;
	long long id;
};

struct Final_ans{
	std:: string subject;
	std:: vector<long long> id; 	
};

void find_subject(Article &now, std:: string &name){
	int keep = 0;
	for(keep; name[keep] != 32; ++keep){
	}
	for(keep; name[keep] == 32; ++keep){
	}
	if(name[keep] == 'R'){
		if(name[keep + 1] == 'e' || name[keep + 1] == 'E' )
			if(name[keep + 2] == ':'){
				keep += 3;	
				for(keep; name[keep] == 32; ++keep){
				}
			}
	}
	int last;
	for(last = name.size() - 1; name[last] == 32; last--){
	}
	for(keep; keep <= last; ++keep)
		now.subject.push_back(name[keep]);
}

bool cmp(Article a, Article b){
	if(a.date.Y == b.date.Y){
		if(a.date.M == b.date.M){
			if(a.date.D == b.date.D){
				if(a.date.H == b.date.H){
					return a.order < b.order;
				}
				return a.date.H < b.date.H;
			}
			return a.date.D < b.date.D;
		}
		return a.date.M < b.date.M;
		
	}
	return a.date.Y < b.date.Y;	
}

void find_ans(Final_ans ans[], std:: vector<Article> &keep){
	std:: sort(keep.begin(), keep.end(), cmp);
	ans[0].subject = keep[0].subject;
	ans[0].id.push_back(keep[0].id);
	for(int i = 1; i < keep.size(); ++i)
		if(keep[i].subject == ans[0].subject)
			ans[0].id.push_back(keep[i].id);
	int now;
	for(int i = 1; i < keep.size(); ++i)
		if(keep[i].subject != ans[0].subject){
			ans[1].subject = keep[i].subject;
			ans[1].id.push_back(keep[i].id);
			now = i;
			break;	
		}
	for(int i = now + 1; i < keep.size(); ++i)
		if(keep[i].subject == ans[1].subject)
			ans[1].id.push_back(keep[i].id);
}

void PRINT(Final_ans ans[]){
	for(int i = 0; i < 2; ++i)
		if(!ans[i].subject.empty()){
			printf("Subject: ");
			std:: cout << ans[i].subject << "\n";
			printf("ID: ");
			for(int j = 0; j < ans[i].id.size(); ++j){
				printf("%lld", ans[i].id[j]);
				if(j == ans[i].id.size() - 1)
					printf("\n");
				else
					printf(",");	
			}	
		}
} 

int main(){
	std:: string name;
	std:: string time;
	std:: string index;
	char tmp[2];
	std:: vector<Article> keep;
	
	int num = 1;
	while(std:: getline(std:: cin, name)){
		Article now;
		std:: cin >> time;
		scanf("%d %d %d %d", &now.date.M, &now.date.D, &now.date.H, &now.date.Y);
		std:: cin >> index;
		scanf("%lld", &now.id);
		scanf("%c", &tmp[0]);
		scanf("%c", &tmp[1]);
		now.order = num;
		find_subject(now, name);
		keep.push_back(now);
		num ++;
		
	} 
	std:: sort(keep.begin(), keep.end(), cmp);
	Final_ans ans[2];
	find_ans(ans, keep);
	PRINT(ans); 
	return 0;	
}
