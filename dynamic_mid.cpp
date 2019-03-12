#include<cstdio>
#include<algorithm>
#include<vector>

bool cmp_max(int a, int b){
	return a > b;
}

bool cmp_min(int a, int b){
	return a < b;
}

class Data{
private:
	std::vector<int> mini;
	std::vector<int> maxa;	
	int mid;
	double ans;
public:
	Data(){
		mini.push_back(-1);
		maxa.push_back(2147483647);
	}
	void push(int n){
		mid = n;
	}
	void renew(){
		if(mini.size() == maxa.size()){
			if(mid > maxa.front()){
				maxa.push_back(mid);
				std::push_heap(maxa.begin(), maxa.end(), cmp_max);
				ans = (double)maxa.front();
			}else{
				mini.push_back(mid);
				std::push_heap(mini.begin(), mini.end(), cmp_min);
				ans = (double)mini.front();
			}
		}else if(mini.size() > maxa.size()){
			if(mid < mini.front()){
				mini.push_back(mid);
				std::push_heap(mini.begin(), mini.end(), cmp_min);
				maxa.push_back(mini.front());
				std::push_heap(maxa.begin(), maxa.end(), cmp_max);
				std::pop_heap(mini.begin(), mini.end(), cmp_min);
				mini.pop_back();
				ans = (double) (maxa.front() + mini.front()) / 2;
			}else{
				maxa.push_back(mid);
				std::push_heap(maxa.begin(), maxa.end(), cmp_max);
				ans = (double) (maxa.front() + mini.front()) / 2;	
			}
		}else{
			if(mid > maxa.front()){
				maxa.push_back(mid);
				std::push_heap(maxa.begin(), maxa.end(), cmp_max);
				mini.push_back(maxa.front());
				std::push_heap(mini.begin(), mini.end(), cmp_min);
				std::pop_heap(maxa.begin(), maxa.end(), cmp_max);
				maxa.pop_back();
				ans = (double) (maxa.front() + mini.front()) / 2;
			}else{
				mini.push_back(mid);
				std::push_heap(mini.begin(), mini.end(), cmp_min);
				ans = (double) (maxa.front() + mini.front()) / 2;
			}
		}	
	}
	double middle(){
		return ans;
	}
};

double find_mid(int n){
	static Data num_set;
	num_set.push(n);
	num_set.renew();
	return num_set.middle();
	
}

int main(){
	int n;
	while(scanf("%d", &n) != EOF){
		printf("%lf\n", find_mid(n));
	}	
	//how to release the memory of function find)mid() ?
	return 0;	
}
