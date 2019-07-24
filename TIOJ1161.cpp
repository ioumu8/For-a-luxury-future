#include<cstdio>
#include<vector>
#include<algorithm>
#define MAX 2147483647

struct Power{
	int strength;
	int agility;	
};

bool cmp(Power a, Power b){
	if(a.strength == b.strength)
		return a.agility < b.agility;
	return a.strength < b.strength;	
}

bool cmp2(int a, int b){
	return a < b;	
}

int find(int n, int k, std:: vector<Power> &skill){
	std:: sort(skill.begin(), skill.end(), cmp);
	std:: vector<int> keep;
	for(int i = 0; i < k; ++i){
		keep.push_back(skill[i].agility);	
		std:: push_heap(keep.begin(), keep.end(), cmp2);
	}
	int mini = skill[k - 1].strength + keep.front();
	for(int i = k; i < n; ++i){
		if(skill[i].agility >= keep.front())
			continue;
		std:: pop_heap(keep.begin(), keep.end(), cmp2);
		keep.pop_back();
		keep.push_back(skill[i].agility);
		std:: push_heap(keep.begin(), keep.end(), cmp2);	
		int now = keep.front() + skill[i].strength;
		mini = mini > now ? now : mini;
	}
	return mini;
}

int main(){
	int t;
	int n, k;
	scanf("%d", &t);
	for(int i = 0; i < t; ++i){
		scanf("%d %d", &n, &k);
		std:: vector<Power> skill(n);
		for(int j = 0; j < n; ++j)
			scanf("%d %d", &skill[j].strength, &skill[j].agility);
		int ans = find(n, k, skill);	
		printf("%d\n", ans);
	}
	return 0;	
}
