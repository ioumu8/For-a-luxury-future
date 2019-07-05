#include<cstdio>
#include<vector>
#include<cmath>
#include<algorithm>
# define MIN 0.00001

struct Place{
	double x;
	double y;	
};

bool cmp(Place a, Place b){
	if(a.x == b.x)
		return a.y < b.y;
	return a.x < b.x; 
} 

bool find_side(Place a, Place b, Place c){
	double positive = a.x * b.y + b.x * c.y + c.x * a.y;
	double negitive = b.x * a.y + c.x * b.y + a.x * c.y;
	return (positive - negitive) >= 0 ? true : false;
}

void make_tobo(std:: vector<Place> &shape){
	std:: vector<Place> keep;
	std:: sort(shape.begin(), shape.end(), cmp);
	if(shape.size() != 0)
		keep.push_back(shape[0]);
	for(int i = 1; i < shape.size() - 1; ++i){
		bool ok = find_side(keep.back(), shape[i + 1], shape[i]);
		if(!ok)
			keep.push_back(shape[i]);
	}
	if(shape.size() > 1)
		keep.push_back(shape.back());
	for(int i = shape.size() - 2; i >= 1; --i){
		bool ok = find_side(keep.back(), shape[i - 1], shape[i]);
		if(!ok)
			keep.push_back(shape[i]);	
	}
	shape = keep;
}

void find_edge(double &maxa, double &mini, std:: vector<Place> &shape){
	for(int i = 0; i < shape.size(); ++i){
		maxa = shape[i].y / shape[i].x > maxa ? shape[i].y / shape[i].x : maxa;
		mini = shape[i].y / shape[i].x < mini ? shape[i].y / shape[i].x : mini;
	}
}

Place get_point(double k, Place a, Place b){
	// ax + by = c;
	double fun_1[3] = {k, -1, 0};
	double fun_2[3] = {a.y - b.y, b.x - a.x, a.y * b.x - b.y * a.x};
	Place ans;
	ans.x = (fun_1[2] * fun_2[1] - fun_1[1] * fun_2[2]) / (fun_1[0] * fun_2[1] - fun_1[1] * fun_2[0]);
	ans.y = (fun_1[0] * fun_2[2] - fun_1[2] * fun_2[0]) / (fun_1[0] * fun_2[1] - fun_1[1] * fun_2[0]);
	return ans;	
}

std:: pair<Place, Place> find_cross(double k, std:: vector<Place> &shape){
	std:: vector<Place> keep;
	Place a;
	Place b;
	a.x = 0;
	a.y = 0;
	b.x = 1;
	b.y = k;
	int range = shape.size() - 1;
	for(int i = 0; i <= range; ++i){
		bool check_1;
		bool check_2;
		Place point_1 = shape[i];
		Place point_2 = i == range ? shape[0] : shape[i + 1];
		check_1 = find_side(a, b, point_1);
		check_2 = find_side(a, b, point_2);
		if(check_1 ^ check_2)
			keep.push_back(get_point(k, point_1, point_2));	
	}
	std:: sort(keep.begin(), keep.end(), cmp);
	return std:: make_pair(keep[0], keep[1]);
}


double cal_area(std:: vector<Place> &area){
	double positive = 0;
	double negitive = 0;
	area.push_back(area.front());
	int range = area.size() - 1;
	for(int i = 0; i < range; ++i){
		positive += (area[i].x * area[i + 1].y) / 2;
		negitive += (area[i + 1].x * area[i].y) / 2; 	
	}
	double ans = positive - negitive;
	return ans > 0 ? ans : -ans;
}

int find_area(double k, std:: vector<Place> &shape){
	std:: pair<Place, Place> cross = find_cross(k, shape);
	std:: vector<Place> area_up;
	std:: vector<Place> area_down;
	area_up.push_back(cross.first);
	area_up.push_back(cross.second);
	area_down.push_back(cross.first);
	area_down.push_back(cross.second);
	for(int i = 0; i < shape.size(); ++i){
		bool side = find_side(cross.first, cross.second, shape[i]);
		if(side)
			area_up.push_back(shape[i]);
		else
			area_down.push_back(shape[i]);
	}
	make_tobo(area_up);
	make_tobo(area_down);
	double ans = cal_area(area_up) - cal_area(area_down);
	if(ans == 0)
		return 0;
	if(ans > 0)
		return 1;
	return 2;
}

double find_ans(int n, std:: vector<Place> &shape){
	double maxa = -2147483647;
	double mini = 2147483647;
	find_edge(maxa, mini, shape);
	double half;
	while((maxa - mini) > MIN){
		half = (maxa + mini) / 2;
		int check = find_area(half, shape);
		if(check == 1)
			mini = half;
		else if(check == 2)
			maxa = half;
		else
			break;
	}
	return (maxa + mini) / 2;
}

int main(){
	int n;
	scanf("%d", &n);
	std:: vector<Place> shape(n);
	for(int i = 0; i < n; ++i)
		scanf("%lf %lf", &shape[i].x, &shape[i].y);
	make_tobo(shape);
	double k = find_ans(n, shape);
	printf("%.4lf\n", k);
	return 0;	
}
