#include<cstdio>
#include<vector>

struct Place{
	bool check_left;
	std:: vector<int> right;
	bool check_down;
	std:: vector<int>top;

};

int cal_width(int now, std:: vector<Place> &point, std:: vector<int> &width){
	if(point[now].right.empty()){
		width[now] = 1;
		return 1;
	}
	if(width[now] != 0)
		return width[now];
	int maxa = -1;
	for(int i = 0; i < point[now].right.size(); ++i){
		int sum = cal_width(point[now].right[i], point, width);
		maxa = sum > maxa ? sum : maxa;
	}
	width[now] = maxa + 1;
	return maxa + 1;			
}

int find_width(std:: vector<Place> &point){
	std:: vector<int> width(point.size(), 0);
	int maxa = -1;
	for(int i = 0; i < point.size(); ++i){
		if(!point[i].check_left){
			int now_width = cal_width(i, point, width);
			maxa = now_width > maxa ? now_width : maxa;
		}
	}
	return maxa;
}

int cal_height(int now, std:: vector<Place> &point, std:: vector<int> &height){
	if(point[now].top.empty()){
		height[now] = 1;
		return 1;
	}
	if(height[now] != 0)
		return height[now];
	int maxa = -1;
	for(int i = 0; i < point[now].top.size(); ++i){
		int sum = cal_height(point[now].top[i], point, height);
		maxa = sum > maxa ? sum : maxa;
	}
	height[now] = maxa + 1;
	return maxa + 1;			
}

int find_height(std:: vector<Place> &point){
	std:: vector<int> height(point.size(), 0);
	int maxa = -1;
	for(int i = 0; i < point.size(); ++i){
		if(!point[i].check_down){
			int now_height = cal_height(i, point, height);	
			maxa = now_height > maxa ? now_height : maxa; 
		}
	}
	return maxa;
}

int main(){
	int n;
	int w;
	scanf("%d", &n);
	scanf("%d", &w);
	std:: vector<Place> point(n);
	for(int i = 0; i < n; ++i){
		point[i].check_left = false;
		point[i].check_down = false;
		point[i].right.clear();
		point[i].top.clear();	
	}
	int range = n * (n - 1) / 2;
	for(int i = 0; i < range; ++i){
		int u;
		int v;
		int p;
		scanf("%d %d %d", &u, &v, &p);
		u--;
		v--;
		if(p == 0){
			point[u].check_left = true;
			point[v].right.push_back(u);
		}else if(p == 1){
			point[u].check_down = true;
			point[v].top.push_back(u);
		}
	}
	int width = find_width(point);
	int height = find_height(point);
	printf("%d\n", width * height * w * w);
	return 0;	
}
