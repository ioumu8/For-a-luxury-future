#include<cstdio>
#include<algorithm>
#include<vector>

struct Num{
	int place;
	int value;
};

bool cmp(Num a, Num b){
	if(a.value == b.value)
		return a.place > b.place;
	return a.value < b.value;
}

void find(int n, std:: vector<int> &s, std:: vector<int> &a){
	std:: vector<Num> left;
	std:: vector<Num> right;
	left.push_back({-1 ,-1});
	right.push_back({-1, -1});
	for(int i = 0; i < n; ++i){
		right.push_back({i ,s[i] * 2 + a[i]});
		std:: push_heap(right.begin(), right.end(), cmp);
	}
	int ans = right.front().value;
	int start = 0;
	int terminal = right.front().place;
	for(int i = start; i < terminal; ++i){
		left.push_back({i, a[i]});
		std:: push_heap(left.begin(), left.end(), cmp);
	}
	std:: pop_heap(right.begin(), right.end(), cmp);
	right.pop_back();
	start = terminal + 1;
	printf("%d\n", ans);
	for(int i = 1; i < n; ++i){
		while(right.front().place < terminal && right.front().place != -1){
			std:: pop_heap(right.begin(), right.end(), cmp);
			right.pop_back();
		}
		ans += std:: max(right.front().value - s[terminal] * 2, left.front().value);
		if(left.front().value >= right.front().value - s[terminal] * 2){
			std:: pop_heap(left.begin(), left.end(), cmp);
			left.pop_back();
		}else{
			terminal = right.front().place;
			for(int j = start; j < terminal; ++j){
				left.push_back({j, a[j]});
				std:: push_heap(left.begin(), left.end(), cmp);
			}
			std:: pop_heap(right.begin(), right.end(), cmp);
			right.pop_back();
			start = terminal + 1;
		}
		printf("%d\n", ans);
	}
}

int main(){
	int n;
	scanf("%d", &n);
	std:: vector<int> s(n);
	std:: vector<int> a(n);
	for(int i = 0; i < n; ++i)
		scanf("%d", &s[i]);
	for(int i = 0; i < n; ++i)
		scanf("%d", &a[i]);
	find(n, s, a);
	return 0;
}

