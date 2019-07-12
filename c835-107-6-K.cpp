#include<cstdio>
#include<vector>
#include<algorithm>

bool cmp(long long a, long long b){
	return a < b;	
}

long long find(std:: vector<std:: vector<long long> > &bag){
	int range = bag.size() - 1;
	for(int i = 0; i < range; ++i){
		while(bag[i].size() > 1){
			long long now = bag[i].front();
			std:: pop_heap(bag[i].begin(), bag[i].end(), cmp);
			bag[i].pop_back();
			now += bag[i].front();
			std:: pop_heap(bag[i].begin(), bag[i].end(), cmp);
			bag[i].pop_back();
			bag[i + 1].push_back(now);
			std:: push_heap(bag[i + 1].begin(), bag[i + 1].end(), cmp);	
		}
		if(!bag[i].empty()){
			bag[i + 1].push_back(bag[i].front());
			std:: push_heap(bag[i + 1].begin(), bag[i + 1].end(), cmp);
			bag[i].pop_back();
		}
	}
	return bag[range].front();
}

int main(){
	int n;
	int m;
	scanf("%d %d", &n, &m);
	std:: vector<std:: vector<long long> > bag(m + 1);
	for(int i = 0; i < n; ++i){
		long long weight;
		long long	value;
		scanf("%lld %lld", &weight, &value);
		if(weight <= m){
			bag[weight].push_back(value);
			std:: push_heap(bag[weight].begin(), bag[weight].end(), cmp);	
		}
	}
	long long sum = find(bag);
	printf("%lld\n", sum);
	return 0;	
}
