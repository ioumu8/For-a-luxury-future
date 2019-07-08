#include<cstdio>
#include<vector>
#include<algorithm>

struct Place{
	int num;
	int order;	
};

bool cmp(Place a, Place b){
	return a.num < b.num;	
}

int main(){
	int n;
	scanf("%d", &n);
	std:: vector<Place> place(n);
	for(int i = 0; i < n; ++i){
		scanf("%d", &place[i].num);	
		place[i].order = i;
	}
	std:: sort(place.begin(), place.end(), cmp);
	bool up = true;
	int sum = 0;
	for(int i = 1; i < n; ++i){
		if(up){
			if(place[i - 1].order > place[i].order){
				up = false;
				sum++;	
			}
		}else{
			if(place[i - 1].order < place[i].order){
				up = true;
				sum++;
			}
		}
	}
	printf("%d\n", sum);
	return 0;	
}
