#include<cstdio>
#include<vector>
#include<unordered_map>
#include<algorithm>

long long hcf(long long p, long long q){
	while(q != 0){
		p %= q;
		std:: swap(p, q);
	}
	return p;
}

void mini(long long &p, long long &q){
	if(p == 0){
		q = 1;
		return ;
	}
	long long m = hcf(p, q);
	p /= m;
	q /= m;
}

int main(){
	long long n;
	long long p;
	long long q;
	scanf("%lld %lld %lld", &n, &p, &q);
	mini(p, q);
	std:: vector<long long> num(n);
	for(int i = 0; i < n; ++i){
		scanf("%lld", &num[i]);
		num[i] *= q;
		num[i] -= p;	
	}
	for(int i = 1; i < n; ++i)
		num[i] += num[i - 1];
	std:: unordered_map<long long, long long> judge;
	long long sum = 0;
	for(int i = 0; i < n; ++i)
		judge[num[i]] = 0;
	for(int i = 0; i < n; ++i){
		sum += judge[num[i]];
		judge[num[i]]++;
		if(num[i] == 0)
			sum++;
	}
	printf("%lld\n", sum);
	return 0;	
}
