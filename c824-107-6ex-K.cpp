#include<cstdio>
#include<vector>
#include<algorithm>


struct Num{
	int time;
	long long value;	
};

bool cmp(Num a, Num b){
	if(a.time == b.time)
		return a.value < b.value;
	return a.time > b.time;	
}

long long calculate(std:: vector<Num> &box, int m){
	if(box[0].time > m)
		return 0;
	while(box.size() > 1){
		Num num1 = box.front();
		std:: pop_heap(box.begin(), box.end(), cmp);
		if(num1.time == m)
			return num1.value;
		if(num1.time != box[0].time){
			box.back().time = box[0].time > m ? m : box[0].time;
			std::push_heap(box.begin(), box.end(), cmp);	
			continue;
		}
		box.pop_back();
		Num num2 = box.front();
		std:: pop_heap(box.begin(), box.end(), cmp);
		box.pop_back();
		num1.time++;
		num1.value += num2.value;
		box.push_back(num1);
		std:: push_heap(box.begin(), box.end(), cmp); 
	}
	if(box[0].time <= m)
		return box[0].value; 
	return 0;
}

int main(){
	int n;
	long long m;
	scanf("%d %lld", &n, &m);
	std:: vector<Num> box;
	for(int i = 0; i < n; ++i){
		Num tmp;
		scanf("%d %lld", &tmp.time, &tmp.value);
		box.push_back(tmp);
		std:: push_heap(box.begin(), box.end(), cmp);
	}
	long long ans = calculate(box, m);
	printf("%lld\n", ans);
	return 0;
}
